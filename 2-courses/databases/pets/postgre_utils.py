import psycopg2
from psycopg2 import Error

def execute_query_callback(query_func, *args):
    result = None
    try:
        connection = psycopg2.connect(
           user="postgres",
           password="",
           host="localhost",
           port="5432",
           database="pet-db"
        )
        # autocommit in this case
        connection.autocommit = True
        with connection.cursor() as cursor:
            result = query_func(connection, cursor, *args)
    except (Exception, Error) as error:
        print("Error: ", error)
    finally:
        if connection:
            cursor.close()
            connection.close()
            print("Connection closed")
    return result

def execute_query(query: str):
    def callback(connection, cursor, query):
        cursor.execute(query)
        if cursor.description:
            return cursor.fetchall()
    return execute_query_callback(callback, query)

def execute_query_file(filename: str):
    with open(filename) as file:
        query = "".join(file.readlines())
        return execute_query(query)
