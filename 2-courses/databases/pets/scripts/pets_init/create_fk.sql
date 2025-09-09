---------------------------------------------------------------
-- Создание FK 
---------------------------------------------------------------
ALTER TABLE Owner ADD CONSTRAINT FK_Owner_Person 
    FOREIGN KEY (Person_ID)
    REFERENCES Person(Person_ID)
;
ALTER TABLE Employee ADD CONSTRAINT FK_Employee_Person 
    FOREIGN KEY (Person_ID)
    REFERENCES Person(Person_ID)
;
ALTER TABLE Pet ADD CONSTRAINT FK_Pet_0wner 
    FOREIGN KEY (Owner_ID)
    REFERENCES Owner(Owner_ID)
;
ALTER TABLE Pet ADD CONSTRAINT FK_Pet_Pet_Type 
    FOREIGN KEY (Pet_Type_ID)
    REFERENCES Pet_Type(Pet_Type_ID)
;
ALTER TABLE Employee_Service ADD CONSTRAINT FK_Empl_Serv_Employee 
    FOREIGN KEY (Employee_ID)
    REFERENCES Employee(Employee_ID)
;
ALTER TABLE Employee_Service ADD CONSTRAINT FK_Empl_Serv_Service 
    FOREIGN KEY (Service_ID)
    REFERENCES Service(Service_ID)
;
ALTER TABLE Order1 ADD CONSTRAINT FK_Order_Employee 
    FOREIGN KEY (Employee_ID)
    REFERENCES Employee(Employee_ID)
;
ALTER TABLE Order1 ADD CONSTRAINT FK_Order_0wner 
    FOREIGN KEY (Owner_ID)
    REFERENCES Owner(Owner_ID)
;
ALTER TABLE Order1 ADD CONSTRAINT FK_Order_Pet 
    FOREIGN KEY (Pet_ID)
    REFERENCES Pet(Pet_ID)
;
ALTER TABLE Order1 ADD CONSTRAINT FK_Order_Service 
    FOREIGN KEY (Service_ID)
    REFERENCES Service(Service_ID)
;
