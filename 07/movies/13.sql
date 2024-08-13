SELECT DISTINCT people.name
FROM people
JOIN stars ON people.id = stars.person_id
JOIN movies ON stars.movie_id = movies.id
JOIN stars kbStars ON movies.id = kbStars.movie_id
JOIN people kb ON kb.id = kbStars.person_id
WHERE kb.name = "Kevin Bacon"
AND kb.birth = 1958
AND people.name <> "Kevin Bacon";
