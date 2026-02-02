SELECT order_date, name || ' (age:'||age||')' as person_information FROM person_order
INNER JOIN person p on p.id = person_order.person_id ORDER by 1,2