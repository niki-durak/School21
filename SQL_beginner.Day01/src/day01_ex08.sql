SELECT order_date, name || ' (age:'||age||')' as person_information FROM person_order
NATURAL JOIN (SELECT p.id as person_id, name, age from person p) as p ORDER by 1, 2