ALTER TABLE Account ADD CONSTRAINT FK_Account_Client
    FOREIGN KEY (client_id)
    REFERENCES Client(client_id)
;

ALTER TABLE Account ADD CONSTRAINT FK_Account_Valute
    FOREIGN KEY (valute_id)
    REFERENCES Valute(valute_id)
;

ALTER TABLE Account ADD CONSTRAINT FK_Account_AccountType
    FOREIGN KEY (account_type_id)
    REFERENCES AccountType(account_type_id)
;

ALTER TABLE Operation ADD CONSTRAINT FK_Operation_OperationType
    FOREIGN KEY (operation_type_id)
    REFERENCES OperationType(operation_type_id)
;

ALTER TABLE Operation ADD CONSTRAINT FK_Operation_Account
    FOREIGN KEY (account_id)
    REFERENCES Account(account_id)
;

ALTER TABLE TranslateOperation ADD CONSTRAINT FK_TranslateOperation_Operation
    FOREIGN KEY (operation_id)
    REFERENCES Operation(operation_id)
;

ALTER TABLE TranslateOperation ADD CONSTRAINT FK_TranslateOperation_Client
    FOREIGN KEY (reciever_account_id)
    REFERENCES Account(account_id)
;

ALTER TABLE RecieveOperation ADD CONSTRAINT FK_RecieveOperation_Operation
    FOREIGN KEY (operation_id)
    REFERENCES Operation(operation_id)
;

ALTER TABLE RecieveOperation ADD CONSTRAINT FK_RecieveOperation_Client
    FOREIGN KEY (sender_account_id)
    REFERENCES Account(account_id)
;

ALTER TABLE ReplenishmentOperation ADD CONSTRAINT FK_ReplenishmentOperation_Operation
    FOREIGN KEY (operation_id)
    REFERENCES Operation(operation_id)
;

ALTER TABLE WithdrawalOperation ADD CONSTRAINT FK_WithdrawalOperation_Operation
    FOREIGN KEY (operation_id)
    REFERENCES Operation(operation_id)
;

