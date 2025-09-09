CREATE TABLE IF NOT EXISTS Client(
    client_id     INTEGER      NOT NULL,
    active        BOOLEAN      DEFAULT TRUE,
    name          VARCHAR(20)  NOT NULL,
    surname       VARCHAR(20)  NOT NULL,
    phone         VARCHAR(15)  NOT NULL,
    percent       INTEGER      NOT NULL,
    -- address?
    -- passport?
    CONSTRAINT client_PK PRIMARY KEY (client_id)
);


CREATE TABLE IF NOT EXISTS AccountType(
    account_type_id  INTEGER      NOT NULL,
    name             VARCHAR(20)  NOT NULL,
    -- base percent?
    CONSTRAINT account_type_PK PRIMARY KEY (account_type_id)
);

CREATE TABLE IF NOT EXISTS Valute(
    valute_id    INTEGER      NOT NULL,
    name         VARCHAR(20)  NOT NULL,
    coef_to_rub  FLOAT        NOT NULL,
    CONSTRAINT valute_PK PRIMARY KEY (valute_id)
);

CREATE TABLE IF NOT EXISTS Account(
    account_id       INTEGER  NOT NULL,
    active           BOOLEAN  DEFAULT TRUE,
    valute_id        INTEGER  NOT NULL,
    value            FLOAT    NOT NULL,
    client_id        INTEGER  NOT NULL,
    account_type_id  INTEGER  NOT NULL,
    create_date      TIMESTAMP DEFAULT NOW() NOT NULL,
    CONSTRAINT account_FK PRIMARY KEY (account_id)
);

CREATE TABLE IF NOT EXISTS OperationType(
    operation_type_id  INTEGER      NOT NULL,
    name               VARCHAR(20)  NOT NULL,
    CONSTRAINT operation_type_PK PRIMARY KEY (operation_type_id)
);

CREATE TABLE IF NOT EXISTS Operation(
    operation_id       INTEGER  NOT NULL,
    operation_type_id  INTEGER  NOT NULL,
    account_id         INTEGER  NOT NULL,
    date               TIMESTAMP  DEFAULT NOW()  NOT NULL,
    CONSTRAINT operation_PK PRIMARY KEY (operation_id)
);

-- i think concrete operations is not need to have PK

CREATE TABLE IF NOT EXISTS TranslateOperation(
    operation_id         INTEGER  NOT NULL,
    reciever_account_id  INTEGER  NOT NULL,
    value                FLOAT    NOT NULL,
    prev_value           FLOAT    NOT NULL
);

CREATE TABLE IF NOT EXISTS RecieveOperation(
    operation_id       INTEGER      NOT NULL,
    sender_account_id  INTEGER      NOT NULL,
    value              FLOAT        NOT NULL,
    prev_value         FLOAT        NOT NULL
);

CREATE TABLE IF NOT EXISTS ReplenishmentOperation(
    operation_id  INTEGER      NOT NULL,
    value         FLOAT        NOT NULL,
    prev_value    FLOAT        NOT NULL,
    ATM_address   VARCHAR(50)  NOT NULL
);

CREATE TABLE IF NOT EXISTS WithdrawalOperation(
    operation_id  INTEGER      NOT NULL,
    value         FLOAT        NOT NULL,
    prev_value    FLOAT        NOT NULL,
    ATM_address   VARCHAR(50)  NOT NULL
);

