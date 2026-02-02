SELECT action_date, person.name as person_name FROM (SELECT order_date AS action_date, person_id FROM person_order
                                                    INTERSECT ALL
                                                    SELECT visit_date, person_id FROM person_visits) as t1
                                                    INNER JOIN person on t1.person_id = person.id ORDER by 1, 2 DESC