CREATE INDEX client_name_index ON Client (name);
CREATE INDEX client_surname_index ON Client (surname);

CREATE UNIQUE INDEX withdrawal_operation_account_id_unique_index ON WithdrawalOperation (operation_id);
CREATE UNIQUE INDEX replenishment_operation_account_id_unique_index ON ReplenishmentOperation (operation_id);
CREATE UNIQUE INDEX translate_operation_account_id_unique_index ON TranslateOperation (operation_id);
CREATE UNIQUE INDEX recieve_operation_account_id_unique_index ON RecieveOperation (operation_id);

