SELECT name 
FROM people
WHERE people.id IN (SELECT person_id 
FROM directors 
WHERE movie_id IN (SELECT movie_id FROM ratings WHERE movie_id IN (SELECT id 
FROM movies) AND rating >= 9.0));