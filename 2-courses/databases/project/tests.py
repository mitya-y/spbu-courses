from postgre_utils import execute_query
from database import create_db, delete_db
from pprint import pprint

def test_triggers():
    print("test trigger 1")
    # this must be successfull
    execute_query("DELETE FROM Account WHERE account_id = 101;")
    res = execute_query("SELECT active, value FROM Account WHERE account_id = 101;")
    pprint(res)

    # here must be error, cannot delete not empty account
    execute_query("DELETE FROM Account WHERE account_id = 102;")
    res = execute_query("SELECT active, value FROM Account WHERE account_id = 102;")
    pprint(res)

    print()
    print("test trigger 2")
    # client 3 can create kredit, he has not any yet
    execute_query("INSERT INTO Account (account_id, active, valute_id,\
                   value, client_id, account_type_id, create_date) VALUES\
                   (109, TRUE, 4, 0.0, 3, 2, '2023-05-07')")
    res = execute_query("SELECT * FROM Account WHERE account_id = 109;")
    pprint(res)

    # client 1 can not create kredit, he has other kredit already
    execute_query("INSERT INTO Account (account_id, active, valute_id,\
                   value, client_id, account_type_id, create_date) VALUES\
                   (110, TRUE, 3, 0.0, 1, 2, '2023-06-17')")
    res = execute_query("SELECT * FROM Account WHERE account_id = 110;")
    pprint(res)

    print()
    print("test trigger 3")
    # before delete client 3
    # TODO: select from ActualTable view
    res = execute_query("SELECT * FROM Account WHERE client_id = 3;")
    pprint(res)

    # client 1 can not create kredit, he has other kredit already
    execute_query("DELETE FROM Client WHERE client_id = 3;")
    res = execute_query("SELECT * FROM Account WHERE client_id = 3;")
    pprint(res)

def test_views():
    print("test view 1")
    # show all accounts of Мария Петорова
    query = "SELECT * FROM ActiveAccountsStat WHERE\
             client_name = 'Мария' AND client_surname = 'Петрова'"
    res = execute_query(query + ';')
    pprint(res)

    # delete kredit account
    execute_query(f"DELETE FROM Account WHERE account_id IN\
                    (SELECT account_id FROM ({query}) WHERE account_type = 'Кредитный');")
    res = execute_query(query + ';')
    pprint(res)

    print()
    print("test view 3")
    res = execute_query("SELECT * FROM AllTranslates;")
    pprint(res)

def test_functions():
    print("test function 1")
    execute_query("CALL AddNewClientWithDefaultAccount('Митя', 'Бебра', '+73047', 'USD')")

    res = execute_query("SELECT * FROM Client WHERE name = 'Митя'")
    pprint(res)
    res = execute_query("SELECT * FROM ActiveAccountsStat WHERE client_name = 'Митя'")
    pprint(res)

    print()
    print("test function 2")
    res = execute_query("SELECT ConvertValute(2, 1, 5)")
    pprint(res)
    res = execute_query("SELECT ConvertValute(4, 4, 47)")
    pprint(res)

    print()
    print("test function 3")
    execute_query("UPDATE Account SET value = 47.30 WHERE client_id = 6;")

    # Mitya tranlsate 30 USD to RUB kredit account of Dmitriy Kozlov
    res = execute_query("SELECT * FROM Account WHERE account_id IN (107, 110);")
    pprint(res)
    execute_query("CALL TranslateMoneys(110, 107, 30.0);")
    res = execute_query("SELECT * FROM Account WHERE account_id IN (107, 110);")
    pprint(res)


#==========================================================================
# test part
#==========================================================================

def print_header(test_name: str):
    delim = '----------------------------'
    text = f'* tests {test_name}'
    text += ' ' * (len(delim) - len(text) - 1)
    text += '*'

    print('')
    print(delim)
    print(text)
    print(delim)
    print('')

# execute_query_file("scripts/functions.sql")
# # execute_query_file("scripts/bank/delete.sql")
# exit()

create_db()

print_header('triggers')
test_triggers()

print_header('views')
test_views()

print_header('functions')
test_functions()

delete_db()