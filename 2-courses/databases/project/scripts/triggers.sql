-- 1. Нельзя удалить счет на котором есть деньги, а при удалении счет остается в базе данных,
--    просто деактивируется
CREATE OR REPLACE FUNCTION check_account_empty()
RETURNS TRIGGER AS $$
BEGIN
    IF OLD.value != 0 THEN
        RAISE EXCEPTION 'Clinet can delete only empty account';
    END IF;

    UPDATE Account SET active = FALSE WHERE account_id = OLD.account_id;
    RETURN NULL;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER TR_del_not_empty_account
BEFORE DELETE ON Account
FOR EACH ROW
EXECUTE FUNCTION check_account_empty();

-- 2. Нельзя создать создать второй кредитный счет
CREATE OR REPLACE FUNCTION check_not_first_kredit()
RETURNS TRIGGER AS $$
DECLARE
    kredit_count INTEGER;
BEGIN
    IF NEW.account_type_id = 2 THEN
        SELECT COUNT(*) INTO kredit_count FROM
            (SELECT * FROM Client, Account
             WHERE Account.client_id = NEW.client_id AND Account.client_id = Client.client_id
             AND Account.account_type_id = 2);

        IF kredit_count > 0 THEN
            RAISE EXCEPTION 'Clinet can delete only empty account';
        END IF;
    END IF;

    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER TR_create_second_kredit
BEFORE INSERT ON Account
FOR EACH ROW
EXECUTE FUNCTION check_not_first_kredit();

-- 3. вместо удаления клиент помечается неактиынм, и все его счета тоже
CREATE OR REPLACE FUNCTION deactivate_client()
RETURNS TRIGGER AS $$
BEGIN
    UPDATE Client SET active = FALSE WHERE client_id = OLD.client_id;
    UPDATE Account SET active = FALSE WHERE client_id = OLD.client_id;
    RETURN NULL;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER TR_deactivate_client
BEFORE DELETE ON Client
FOR EACH ROW
EXECUTE FUNCTION deactivate_client();

