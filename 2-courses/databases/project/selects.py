from postgre_utils import execute_query
from database import create_db, delete_db
from pprint import pprint

def select1():
    print('')
    print('Сумма всех денег на всех счетах клиентов в рублях:')
    res = execute_query("SELECT Client.name, Client.surname," \
                        "       (SELECT SUM(ConvertValute(valute_id, 1, value))" \
                        "        FROM Account WHERE Account.client_id = Client.client_id" \
                        "                           AND Account.active)" \
                        "FROM Client WHERE Client.active;")
    pprint(res)

def select2():
    print('')
    print('Все траты клиента Мария Петрова в рублях:')
    query1 = "SELECT ConvertValute(Account.valute_id, 1, TranslateOperation.value) " \
             "FROM Account, TranslateOperation, ActualOperation AS Operation " \
             "WHERE Account.client_id = 2 AND" \
             "      Operation.account_id = Account.account_id AND" \
             "      TranslateOperation.operation_id = Operation.operation_id"
    query2 = "SELECT ConvertValute(Account.valute_id, 1, WithdrawalOperation.value) " \
             "FROM Account, WithdrawalOperation, ActualOperation AS Operation " \
             "WHERE Account.client_id = 2 AND" \
             "      Operation.account_id = Account.account_id AND" \
             "      WithdrawalOperation.operation_id = Operation.operation_id"
    res = execute_query(f"{query1} UNION {query2};")
    pprint(res)

def select3():
    print('')
    print('Все пополнения клиента Мария Петрова в рублях:')
    query1 = "SELECT ConvertValute(Account.valute_id, 1, RecieveOperation.value) " \
             "FROM Account, RecieveOperation, ActualOperation AS Operation " \
             "WHERE Account.client_id = 2 AND" \
             "      Operation.account_id = Account.account_id AND" \
             "      RecieveOperation.operation_id = Operation.operation_id"
    query2 = "SELECT ConvertValute(Account.valute_id, 1, ReplenishmentOperation.value) " \
             "FROM Account, ReplenishmentOperation, ActualOperation AS Operation " \
             "WHERE Account.client_id = 2 AND" \
             "      Operation.account_id = Account.account_id AND" \
             "      ReplenishmentOperation.operation_id = Operation.operation_id"
    res = execute_query(f"{query1} UNION {query2};")
    pprint(res)

def select4():
    print()
    print('Количество денег на всех счетах каждой авлюты:')
    res = execute_query("SELECT name, " \
                        "       (SELECT SUM(value) FROM Account" \
                        "        WHERE Account.valute_id = Valute.valute_id" \
                        "              AND Account.active)" \
                        "FROM Valute")
    pprint(res)

def select5():
    print()
    print('Самый состоятельный клиент:')
    query = "SELECT Client.name, Client.surname," \
                        "       (SELECT SUM(ConvertValute(valute_id, 1, value)) AS value" \
                        "        FROM Account WHERE Account.client_id = Client.client_id" \
                        "                           AND Account.active)" \
                        "FROM Client WHERE Client.active"
    max_value = f"SELECT MAX(value) FROM ({query})"
    res = execute_query(f"SELECT name, surname FROM ({query}) " \
                        f"WHERE value = ({max_value})")
    print(res)

def select6():
    print()
    print('Все клиенты у которых есть кредитные счета с долгами:')
    query = "SELECT Client.name, Client.surname FROM Client, Account, AccountType " \
            "WHERE Client.client_id = Account.client_id" \
            "      AND Account.account_type_id = AccountType.account_type_id" \
            "      AND AccountType.Name = 'Кредитный' AND Account.value < 0" \
            "      AND Client.active AND Account.active"
    res = execute_query(query)
    pprint(res)

def select7():
    print()
    print('Сколько операций провел каждый клиент:')
    query1 = "SELECT account_id AS acc_id, COUNT(*) AS number FROM ActualOperation GROUP BY account_id"
    query2 = "SELECT Client.name, Client.surname, " \
            f"       (SELECT SUM(Tmp.number) FROM ({query1}) AS Tmp, Account " \
             "        WHERE Tmp.acc_id = Account.account_id AND Account.active " \
             "        AND Account.client_id = Client.client_id) " \
             "FROM Client WHERE Client.active GROUP BY client_id"
    res = execute_query(query2)
    pprint(res)

def select8():
    print()
    print('Клиенты, у которых больше 1 счета:')
    query = "SELECT Client.name, Client.surname FROM Client, Account " \
            "WHERE Client.client_id = Account.client_id " \
            "AND Client.active AND Account.active " \
            "GROUP BY Client.client_id HAVING COUNT(*) > 1"
    res = execute_query(query)
    pprint(res)


def select9():
    print()
    print('Владелец самого старого счета:')
    query = "SELECT Client.name, Client.surname FROM Client, Account " \
            "WHERE Client.client_id = Account.client_id " \
            "AND Account.create_date = (SELECT MIN(create_date) FROM Account)" \
            "AND Client.active AND Account.active"
    res = execute_query(query)
    pprint(res)

def select10():
    print()
    print('Адреса всех использованных банкоматов в отсортированном порядке')
    unsorted = "SELECT ATM_address FROM ReplenishmentOperation " \
               "UNION " \
               "SELECT ATM_address FROM WithdrawalOperation"
    sorted = f"SELECT * FROM ({unsorted}) AS Tmp ORDER BY Tmp.ATM_address"
    res = execute_query(sorted)
    pprint(res)

def select11():
    print()
    print('Количество счетов у каждого клиента')
    query = "SELECT Client.name, Client.surname, COUNT(*) " \
            "FROM Client, Account WHERE Client.client_id = Account.client_id " \
            "AND Account.active AND Client.active " \
            "GROUP BY Client.client_id"
    res = execute_query(query)
    pprint(res)


def select12():
    print()
    print('Тип последней операции для каждого клиента')
    client_operations = "SELECT Client.client_id, OperationType.name, Operation.date " \
                        "FROM ActualOperation AS Operation, Client, Account, OperationType " \
                        "WHERE Operation.account_id = Account.account_id " \
                        "AND Account.client_id = Client.client_id " \
                        "AND Operation.operation_type_id = OperationType.operation_type_id"
    query = "SELECT Client.name, Client.surname, Oper.name " \
           f"FROM Client, ({client_operations}) AS Oper " \
            "WHERE Oper.client_id = Client.client_id AND Client.active AND " \
           f"Oper.date = (SELECT MAX(date) FROM ({client_operations}) AS Oper " \
            "             WHERE Oper.client_id = Client.client_id)"
    res = execute_query(query)
    pprint(res)

def select13():
    print('')
    print('Добавим нового клиента:')
    execute_query("INSERT INTO Client (client_id, name, surname, phone, percent) " \
                              "VALUES (6, 'Новый', 'Клиент', '+79217777777', 7)")
    pprint(execute_query("SELECT * FROM Client;"))
    print()

    print('Все клиенты и количество их счетов')
    query = (
        "SELECT Client.name, Client.surname, COUNT(Account.active) "
        "FROM Client LEFT JOIN Account ON Client.client_id = Account.client_id AND Account.active "
        "WHERE Client.active "
        "GROUP BY Client.client_id"
    )
    res = execute_query(query)
    pprint(res)


create_db()

select1()
select2()
select3()
select4()
select5()
select6()
select7()
select8()
select9()
select10()
select11()
select12()
select13()


delete_db()
