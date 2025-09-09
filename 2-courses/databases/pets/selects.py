from postgre_utils import execute_query
from pprint import pprint

def select_part1():
    print("select 1")
    result = execute_query("SELECT * FROM Pet WHERE Nick = 'Partizan';")
    pprint(result)

    print("select 2")
    result = execute_query("SELECT Nick, Breed, Age FROM Pet ORDER BY Age;")
    pprint(result)

    print("select 3")
    result = execute_query("SELECT * FROM Pet WHERE Description IS NOT NULL AND Description NOT LIKE '';")
    pprint(result)

    print("select 4")
    result = execute_query("SELECT AVG(Age) FROM Pet WHERE breed = 'poodle';")
    assert result is not None
    pprint(result[0][0])

    print("select 5")
    result = execute_query("SELECT COUNT(DISTINCT Owner_ID) FROM Pet;")
    assert result is not None
    pprint(result[0][0])

    print("select 6")
    result = execute_query("SELECT Breed, COUNT(*) FROM Pet GROUP BY Breed;")
    pprint(result)

    print("select 7")
    result = execute_query("SELECT Breed, COUNT(*) FROM Pet GROUP BY Breed HAVING COUNT(*) > 1;")
    pprint(result)

    print("select 8")
    result = execute_query("SELECT * FROM Pet WHERE Age BETWEEN 5 AND 10;")
    pprint(result)

    print("select 9")
    result = execute_query("SELECT * FROM Pet WHERE Breed IN ('poodle', 'spaniel');")
    pprint(result)

def select_part2():
    print("select 1")
    result = execute_query("SELECT Pet.Nick, Pet_Type.Name FROM Pet, Pet_Type\
                            WHERE Pet.Pet_Type_Id = Pet_Type.Pet_Type_Id AND Pet.Nick = 'Partizan';")
    pprint(result)

    print("select 2")
    result = execute_query("SELECT Pet.Nick, Pet.Breed, Pet.Age FROM Pet, Pet_Type\
                            WHERE Pet.Pet_Type_Id = Pet_Type.Pet_Type_Id AND Pet_Type.Name = 'DOG';")
    pprint(result)

    print("select 3")
    result = execute_query("SELECT AVG(Pet.Age) FROM Pet, Pet_Type\
                            WHERE Pet.Pet_Type_Id = Pet_Type.Pet_Type_Id AND Pet_Type.Name = 'CAT';")
    assert result is not None
    pprint(result[0][0])

    print("select 4")
    result = execute_query("SELECT Order1.Time_Order, Person.Last_Name FROM Order1, Employee, Person\
                            WHERE Order1.Employee_ID = Employee.Employee_ID AND Employee.Person_ID = Person.Person_ID\
                            AND Order1.Is_Done = 0;")
    pprint(result)

    print("select 5")
    result = execute_query("SELECT Person.First_Name, Person.Last_Name, Person.phone\
                            FROM Pet, Pet_Type, Owner, Person\
                            WHERE Pet.Pet_Type_Id = Pet_Type.Pet_Type_Id AND Pet.Owner_ID = Owner.Owner_ID\
                            AND Owner.Person_Id = Person.Person_ID AND\
                            Pet_Type.Name = 'DOG';")
    pprint(result)

    print("select 6")
    result = execute_query("SELECT Pet_Type.Name, Pet.Nick\
                            FROM Pet_Type LEFT JOIN Pet\
                            ON Pet.Pet_Type_Id = Pet_Type.Pet_Type_Id\
                            ORDER BY Pet_Type.Pet_Type_ID;")
    pprint(result)

    print("select 7")
    result = execute_query("SELECT Pet.Age, Pet_Type.Name, COUNT(*)\
                            FROM Pet_Type JOIN Pet\
                            ON Pet.Pet_Type_Id = Pet_Type.Pet_Type_Id\
                            GROUP BY Pet.Age, Pet_Type.Name\
                            ORDER BY Pet.Age;")
    pprint(result)

    print("select 8")
    result = execute_query("SELECT Person.Last_Name, COUNT(*) FROM Order1, Employee, Person\
                            WHERE Order1.Employee_ID = Employee.Employee_ID AND Employee.Person_ID = Person.Person_ID\
                            AND Order1.Is_Done = 1\
                            GROUP BY Person.Person_ID\
                            HAVING COUNT(*) > 3;")
    pprint(result)

    print("select 9")
    # Показать всеx сиамских кошек, у которых есть вакцина от чумки, и вывести сканы
    result = execute_query("SELECT Pet.Nick, Vacine.SkanUrl\
                            FROM Pet, Pet_Type, Vacine, VacineType\
                            WHERE Pet.Pet_Type_ID = Pet_Type.Pet_Type_ID AND Pet_Type.Name = 'CAT'\
                            AND Vacine.Pet_ID = Pet.Pet_ID AND VacineType.VacineType_ID = Vacine.VacineType_ID\
                            AND VacineType.Name = 'chumka'")
    pprint(result)

def select_part3():
    print("select 1")
    select1 = "SELECT Employee.Employee_ID FROM Employee WHERE Employee.Spec = 'student'"
    select2 = f"SELECT Order1.Mark FROM Order1 WHERE\
                Order1.Employee_ID in ({select1} AND Order1.Mark != 0)"
    result = execute_query(select2 + ';')
    pprint(result)
    print("dont ready now")

    print("select 2")
    select1 = "SELECT Employee.Employee_ID FROM Employee, Order1\
               WHERE Order1.Employee_ID = Employee.Employee_ID"
    select2 = f"SELECT Person.Last_Name FROM Person, Employee\
                WHERE Employee.Person_ID = Person.Person_ID\
                AND Employee.Employee_ID NOT IN ({select1})"
    result = execute_query(select2 + ';')
    pprint(result)

    print("select 3")
    select1 = "SELECT Service.NAME, Order1.Time_Order, EmployeePers.Last_Name, Pet.Nick, OwnerPers.Last_Name\
               FROM Order1, Service, Owner, Employee, Pet,\
               Person as EmployeePers, Person as OwnerPers\
               WHERE Order1.Employee_ID = Employee.Employee_ID AND Employee.Person_ID = EmployeePers.Person_ID\
               AND Order1.Owner_ID = Owner.Owner_ID AND Owner.Person_ID = OwnerPers.Person_ID\
               AND Order1.Service_ID = Service.Service_ID AND Order1.Pet_ID = Pet.Pet_ID"
    result = execute_query(select1 + ';')
    assert result is not None
    for s in result:
        print(s)

    print("select 4")
    select1 = "SELECT Order1.Comments FROM Order1 WHERE Order1.Comments != '' UNION\
               SELECT Pet.Description FROM Pet WHERE Pet.Description != '' UNION \
               SELECT Owner.Description FROM Owner WHERE Owner.Description != ''"
    result = execute_query(select1 + ';')
    pprint(result)

    print("select 5")
    select1 = "SELECT Person.First_Name, Person.Last_Name\
               FROM Person, Employee\
               WHERE Employee.Person_ID = Person.Person_ID\
               AND EXISTS (SELECT Order1.Mark FROM Order1\
                           WHERE Employee.Employee_ID = Order1.Employee_ID AND Order1.Mark = 4)"
    result = execute_query(select1 + ';')
    pprint(result)

    print("select 6")
    select1 = "SELECT Person.First_Name, Person.Last_Name\
               FROM Person, Employee\
               WHERE Employee.Person_ID = Person.Person_ID\
               AND 4 = ANY (SELECT Order1.Mark FROM Order1\
                            WHERE Employee.Employee_ID = Order1.Employee_ID)"
    result = execute_query(select1 + ';')
    pprint(result)

select_part3()
