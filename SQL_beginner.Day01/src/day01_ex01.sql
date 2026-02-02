SELECT t1.object_name FROM (SELECT pizza_name as object_name, 'menu' AS LABEL FROM menu
                            UNION all
                            SELECT name, 'person' AS LABEL FROM person order BY LABEL DESC, object_name) as t1