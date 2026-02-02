SELECT name FROM pizzeria WHERE id not in (SELECT pizzeria_id from person_visits)
/*SELECT name FROM pizzeria WHERE NOT EXISTS (SELECT 1 from person_visits pv WHERE pv.pizzeria_id = pizzeria.id)*/