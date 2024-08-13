SELECT movies.title
FROM movies
JOIN stars ON movies.id = stars.movie_id
JOIN people ON stars.person_id = people.id
JOIN stars s2 ON movies.id = s2.movie_id
JOIN people p2 ON s2.person_id = p2.id
WHERE people.name = "Bradley Cooper"
AND p2.name = "Jennifer Lawrence";
