from postgre_utils import execute_query_file
from postgre_utils import execute_query
from pprint import pprint

def reset_table():
    execute_query_file("scripts/pets_vacine/clear.sql")
    execute_query_file("scripts/pets_vacine/old_bd.sql")
    execute_query_file("scripts/pets_vacine/add_vacines.sql")

def part1():
    print("1 task")
    reset_table()
    select1 = "SELECT Employee_ID FROM Employee WHERE Spec = 'student'"
    select2 = f"UPDATE Order1 SET Comments = 's' || Comments WHERE Employee_ID in ({select1})"
    execute_query(select2 + ';')
    pprint(execute_query("SELECT * FROM Order1"), width=200)
    
    print("2 task")
    reset_table()
    select1 = "SELECT Order1.Order_Id FROM Order1, Service\
               WHERE Order1.Service_ID = Service.Service_ID\
               AND Service.NAME = 'Combing' AND Order1.Is_Done = 0"
    select2 = f"DELETE FROM Order1 WHERE Order_Id in ({select1})"
    execute_query(select2 + ';')
    pprint(execute_query("SELECT * FROM Order1"), width=200)
    
    print("3 task")
    reset_table()
    select1 = "SELECT MAX(Person_ID) + 1 FROM Person"
    select2 = f"INSERT INTO Person(Person_ID, Last_Name, First_Name, Phone, Address)\
                VALUES (({select1}), 'Kozenko', 'Mitya', '+79217776660', 'las angelose stret dlya_majorov house 47')"
    execute_query(select2 + ';')
    pprint(execute_query("SELECT * FROM Person"), width=200)

def part2():
    execute_query_file("scripts/person_documents/add_table.sql")

    pprint(execute_query("SELECT * FROM Document;"), width=200)

    select1 = "UPDATE Person SET Person_ID = Person_ID + 1 WHERE First_Name = 'Mitya'"
    execute_query(select1 + ';')
 
    pprint(execute_query("SELECT * FROM Document;"), width=200)

    execute_query_file("scripts/person_documents/delete_table.sql")

part1()
part2()
