-- создание счета
CREATE OR REPLACE PROCEDURE AddNewClientWithDefaultAccount(
    name VARCHAR(20),
    surname VARCHAR(20),
    phone VARCHAR(15),
    valute_name VARCHAR(10)
) AS $$
DECLARE
    client_new_id INTEGER;
    account_new_id INTEGER;
    id_of_valute INTEGER;
BEGIN
    SELECT MAX(client_id) + 1 INTO client_new_id FROM Client;
    INSERT INTO Client (client_id, name, surname, phone, percent)
        VALUES(client_new_id, name, surname, phone, 7);

    SELECT valute_id INTO id_of_valute FROM Valute WHERE Valute.name = valute_name;
    SELECT MAX(account_id) + 1 INTO account_new_id FROM Account;
    INSERT INTO Account(account_id, valute_id, value, client_id, account_type_id, create_date)
        VALUES(account_new_id, id_of_valute, 0, client_new_id, 1, NOW());
END;
$$ LANGUAGE plpgsql;

-- Конвертация валют
CREATE OR REPLACE FUNCTION ConvertValute(from_val_id INTEGER, to_val_id INTEGER, value FLOAT) RETURNS FLOAT AS $$
DECLARE
    in_rubles FLOAT;
    to_rubles_coef FLOAT;
    from_rubles_coef FLOAT;
BEGIN
    SELECT coef_to_rub INTO to_rubles_coef FROM Valute WHERE valute_id = from_val_id;
    SELECT coef_to_rub INTO from_rubles_coef FROM Valute WHERE valute_id = to_val_id;
    in_rubles := value * to_rubles_coef;
    RETURN in_rubles / from_rubles_coef;
END;
$$ LANGUAGE plpgsql;


-- перевод денег (транзакция)
CREATE OR REPLACE PROCEDURE TranslateMoneys(sender_acc_id INTEGER, reciever_acc_id INTEGER, send_value FLOAT) AS $$
DECLARE
    active_acc_number INTEGER;
    operation_new_id INTEGER;

    sender_old_value INTEGER;
    reciever_old_value INTEGER;

    recieve_value FLOAT;
    sender_val_id INTEGER;
    reciever_val_id INTEGER;
BEGIN
    -- check both accounts are active
    SELECT COUNT(*) INTO active_acc_number FROM Account
    WHERE Account.Active = TRUE AND Account.account_id IN (reciever_acc_id, sender_acc_id);
    IF active_acc_number < 2 THEN
        RAISE EXCEPTION 'At least one of the accounts is invalid';
    END IF;

    SELECT value, valute_id INTO sender_old_value, sender_val_id FROM Account
        WHERE Account.account_id = sender_acc_id;
    SELECT value, valute_id INTO reciever_old_value, reciever_val_id FROM Account
        WHERE Account.account_id = reciever_acc_id;

    SELECT ConvertValute(sender_val_id, reciever_val_id, send_value) INTO recieve_value;

    -- transaction
    BEGIN
        -- UPDATE Account SET value = ROUND(value - send_value, 3) WHERE account_id = sender_acc_id;
        -- UPDATE Account SET value = ROUND(value + recieve_value, 3) WHERE account_id = reciever_acc_id;
        UPDATE Account SET value = value - send_value WHERE account_id = sender_acc_id;
        UPDATE Account SET value = value + recieve_value WHERE account_id = reciever_acc_id;
        -- COMMIT;
    EXCEPTION
        WHEN OTHERS THEN
            ROLLBACK;
            RAISE EXCEPTION 'Tranlaste error: %', SQLERRM;
    END;

    SELECT MAX(operation_id) INTO operation_new_id FROM Operation;
    INSERT INTO Operation(operation_id, operation_type_id, account_id, date)
    VALUES
      (operation_new_id + 1, 1, sender_acc_id, NOW()),
      (operation_new_id + 2, 4, reciever_acc_id, NOW());

    INSERT INTO TranslateOperation(operation_id, reciever_account_id, value, prev_value)
    VALUES
    (operation_new_id + 1, reciever_acc_id, send_value, sender_old_value);

    INSERT INTO RecieveOperation(operation_id, sender_account_id, value, prev_value)
    VALUES
    (operation_new_id + 2, sender_acc_id, recieve_value, reciever_old_value);
END;
$$ LANGUAGE plpgsql;


-- снять/положить денеги
-- статистика валют (количество счетов, общая сумма)