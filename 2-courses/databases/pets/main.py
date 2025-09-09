from postgre_utils import execute_query_file

execute_query_file("scripts/pets_vacine/clear.sql")
execute_query_file("scripts/pets_vacine/old_bd.sql")
execute_query_file("scripts/pets_vacine/add_vacines.sql")

