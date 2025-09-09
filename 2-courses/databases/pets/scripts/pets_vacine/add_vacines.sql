-------- Vacine ------- 
CREATE TABLE VacineType(
    VacineType_ID           INTEGER      NOT NULL,
    Name	              VARCHAR(15)  NOT NULL,
CONSTRAINT VacineType_PK PRIMARY KEY (VacineType_ID)
);

CREATE TABLE Vacine(
    Vacine_ID               INTEGER      NOT NULL,
    VacineType_ID           INTEGER      NOT NULL,
    DateVac                 TIMESTAMP    DEFAULT NOW() NOT NULL,
    SkanUrl	              VARCHAR(30)  NOT NULL,
    Pet_ID                  INTEGER      NOT NULL,
CONSTRAINT Vacine_PK PRIMARY KEY (Vacine_ID)
);

-------- Vacine -------
ALTER TABLE Vacine ADD CONSTRAINT FK_Vacine_VacineType
    FOREIGN KEY (VacineType_ID)
    REFERENCES VacineType(VacineType_ID)
;
ALTER TABLE Vacine ADD CONSTRAINT FK_Vacine_Pet
    FOREIGN KEY (Pet_ID)
    REFERENCES Pet(Pet_ID)
;


--- Vacine ---
INSERT INTO VacineType(VacineType_ID, NAME) VALUES (1, 'chumka');
INSERT INTO VacineType(VacineType_ID, NAME) VALUES (2, 'crazy');

-- bobik has 2 vacines
INSERT INTO Vacine(Vacine_ID, Pet_ID, VacineType_ID, SkanUrl) VALUES (1, 1, 1, 'https://vacine1.com');
INSERT INTO Vacine(Vacine_ID, Pet_ID, VacineType_ID, SkanUrl) VALUES (2, 1, 2, 'https://vacine2.com');

INSERT INTO Vacine(Vacine_ID, Pet_ID, VacineType_ID, SkanUrl) VALUES (3, 2, 1, 'https://vacine1.com');
INSERT INTO Vacine(Vacine_ID, Pet_ID, VacineType_ID, SkanUrl) VALUES (4, 3, 2, 'https://vacine2.com');


