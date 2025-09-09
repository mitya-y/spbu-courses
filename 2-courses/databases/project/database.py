from postgre_utils import execute_query_file
from postgre_utils import execute_query

def create_db():
    execute_query_file("scripts/bank/create.sql")
    print("tables were created")

    execute_query_file("scripts/bank/add_fk.sql")
    print("fk were added")

    execute_query_file("scripts/indexes.sql")
    print("indexes were added")

    execute_query_file("scripts/triggers.sql")
    print("triggers were added")

    execute_query_file("scripts/views.sql")
    print("views were added")

    execute_query_file("scripts/functions.sql")
    print("functions were added")

    execute_query_file("scripts/bank/fill.sql")
    print("tables were filled by initial data")

def delete_db():
    execute_query_file("scripts/bank/delete.sql")
    print("tables was droped")
