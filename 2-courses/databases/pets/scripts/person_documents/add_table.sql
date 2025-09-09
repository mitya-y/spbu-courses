CREATE TABLE Document(
  Document_ID  INTEGER         NOT NULL,
  Type         VARCHAR(50)     NOT NULL,
  Number       VARCHAR(50)     NOT NULL,
  Person_ID    INTEGER         NOT NULL,
CONSTRAINT Document_PK PRIMARY KEY (Document_ID)
);

-- ALTER TABLE Document ADD CONSTRAINT FK_Document_Person
--   FOREIGN KEY (Person_ID)
--   REFERENCES Person(Person_ID)
-- ;

ALTER TABLE Document ADD
  FOREIGN KEY (Person_ID) 
  REFERENCES Person(Person_ID)
  ON UPDATE CASCADE
  ON DELETE CASCADE;


INSERT INTO Document(Document_ID, Type, Number, Person_ID)
  VALUES (1, 'passport', '3047 123456', 11);

INSERT INTO Document(Document_ID, Type, Number, Person_ID)
  VALUES (2, 'snills', '474747', 11);

