-- активные (реальные) счета, а так же информацию про их клиентов
CREATE VIEW ActiveAccountsStat AS
SELECT Account.account_id, AccountType.name AS account_type, Account.create_date,
       Account.value, Valute.name AS valute,
       Client.name AS client_name, Client.Surname AS Client_surname, Client.Phone
FROM Account, Client, AccountType, Valute
WHERE Account.client_id = Client.client_id AND Account.account_type_id = AccountType.account_type_id
AND Account.valute_id = Valute.valute_id
AND Account.active = TRUE;

-- операции с активными счетами
CREATE VIEW ActualOperation AS
SELECT Operation.* FROM Operation, Account
WHERE Operation.account_id = Account.account_id AND Account.active = TRUE;

-- все актуальные переводы (пары отправитель/получаетль)
CREATE VIEW AllTranslates AS
SELECT SenderAccount.client_name AS sender_name, SenderAccount.client_surname AS sender_surname,
       RecieverAccount.client_name AS reciever_name, RecieverAccount.client_surname AS reciever_surname,
       TranslateOperation.value, TranslateOperation.prev_value, SenderAccount.valute
FROM ActiveAccountsStat as SenderAccount, ActiveAccountsStat AS RecieverAccount,
     TranslateOperation, Operation
WHERE TranslateOperation.operation_id = Operation.operation_id AND
      SenderAccount.account_id = Operation.account_id AND
      RecieverAccount.account_id = TranslateOperation.reciever_account_id;
