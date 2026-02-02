SELECT 
    p.name as person_name,
    menu.pizza_name as pizza_name,
    pz.name as pizzeria_name
FROM person_order po
INNER JOIN person p ON p.id = po.person_id
INNER JOIN menu ON po.menu_id = menu.id
INNER JOIN pizzeria pz ON menu.pizzeria_id = pz.id
ORDER BY 1, 2, 3
