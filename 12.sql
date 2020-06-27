SELECT title FROM movies
JOIN stars ON movies.id = stars.movie_id
JOIN people ON stars.person_id = people.id
WHERE people.name = "Johnny Depp"
AND movie_id IN (
SELECT movie_id FROM stars
JOIN people ON people.id = stars.person_id
WHERE people.name = "Helena Bonham Carter"
);