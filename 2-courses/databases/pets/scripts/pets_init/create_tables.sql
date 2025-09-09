CREATE TABLE IF NOT EXISTS Person(
    Person_ID         INTEGER      NOT NULL,
    Last_Name	      VARCHAR(20)  NOT NULL,
    First_Name	      VARCHAR(20),
    Phone	      VARCHAR(15)  NOT NULL,
    Address	      VARCHAR(50)  NOT NULL,
CONSTRAINT Person_PK PRIMARY KEY (Person_ID)
)
;
CREATE TABLE IF NOT EXISTS Owner(
    Owner_ID                INTEGER         NOT NULL,
    Description	            VARCHAR(50),
    Person_ID               INTEGER         NOT NULL,
CONSTRAINT Owner_PK PRIMARY KEY (Owner_ID)
)
;
CREATE TABLE IF NOT EXISTS Employee(
    Employee_ID           INTEGER         NOT NULL,
    Spec	          VARCHAR(15),
    Person_ID             INTEGER         NOT NULL,
CONSTRAINT Employee_PK PRIMARY KEY (Employee_ID)
)
;
CREATE TABLE IF NOT EXISTS Pet_Type(
    Pet_Type_ID           INTEGER      NOT NULL,
    Name	          VARCHAR(15)  NOT NULL,
CONSTRAINT Pet_Type_PK PRIMARY KEY (Pet_Type_ID)
)
;
CREATE TABLE IF NOT EXISTS Pet(
    Pet_ID                  INTEGER      NOT NULL,
    Nick	            VARCHAR(15)  NOT NULL,
    Breed                   VARCHAR(20),
    Age                     INTEGER,
    Description             VARCHAR(50),
    Pet_Type_ID             INTEGER         NOT NULL,
    Owner_ID                INTEGER         NOT NULL,
CONSTRAINT Pet_PK PRIMARY KEY (Pet_ID)
)
;
CREATE TABLE IF NOT EXISTS Service(
    Service_ID              INTEGER         NOT NULL,
    Name	            VARCHAR(15)  NOT NULL,
CONSTRAINT Service_PK PRIMARY KEY (Service_ID)
)
;
CREATE TABLE IF NOT EXISTS Employee_Service(
    Employee_ID                   INTEGER         NOT NULL,
    Service_ID                    INTEGER         NOT NULL,
    Is_Basic	                  INTEGER
)
;
CREATE TABLE IF NOT EXISTS Order1(
    Order_ID                      INTEGER         NOT NULL,
    Owner_ID                      INTEGER         NOT NULL,
    Service_ID                    INTEGER         NOT NULL,
    Pet_ID                        INTEGER         NOT NULL,
    Employee_ID                   INTEGER         NOT NULL,
    Time_Order                    TIMESTAMP      DEFAULT NOW()    NOT NULL,
    Is_Done	                  INTEGER       DEFAULT 0           NOT NULL,
    Mark	                  INTEGER,
    Comments                      VARCHAR(50),
CONSTRAINT Order_Is_Done CHECK (Is_Done in (0,1)),
CONSTRAINT Order_PK PRIMARY KEY (Order_ID)
)
;
