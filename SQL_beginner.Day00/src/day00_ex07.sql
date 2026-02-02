SELECT id, name,
	CASE
    	when age BETWEEN 10 and 20 THEN 'interval #1'
        when age > 20 AND age < 24 THEN 'interval #2'
        ELSE 'inverval #3'
	END as interval_info
 FROM person ORDER by 3