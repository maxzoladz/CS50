-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Take the given Information to gain more information about the theft of the duck
SELECT * 
FROM crime_scene_reports 
WHERE year = 2023 AND month = 7 AND day = 28 and street = 'Humphrey Street';
--Theft took place at 10:15am at Humphrey Street bakery, 3 witnesses, each transcript mentions bakery

-- Search for transcripts that contain the word bakery (case insensitive)
SELECT * 
FROM interviews 
WHERE transcript LIKE "%bakery%" AND  year = 2023 AND month = 7 AND day = 28;
-- Person 1: ID: 161, Name: Ruth, Transcript: within ten minutes of the theft, thief got into car at bakery
-- parking lot and drove away, look in security logs for cars that left in that time frame
-- Person 2: ID: 162, Name: Eugene, Transcript: recognized the thief, Emma's bakery, thief was withdrawing money
-- at the ATM on Leggett Street
-- Person 3: ID: 163, Name: Raymond, Transcript: thief called someone for less than a minute, planning to take
-- the earliest flight out of fiftyville tomorrow, thief asked the person on call to buy the plane ticket

-- Look for cars that left the bakery at given timeframe
SELECT * 
FROM bakery_security_logs 
WHERE year = 2023 AND month = 7 AND day = 28 AND hour = 10 AND minute BETWEEN 15 AND 25 AND activity = "exit";

-- Look for atm withdrawals at given timeframe
SELECT * 
FROM atm_transactions 
WHERE year = 2023 AND month = 7 AND day = 28 AND atm_location = "Leggett Street" AND transaction_type = 'withdraw';

-- Look for phonecalls that have a duration of less than 60 seconds
SELECT * 
FROM phone_calls 
WHERE year = 2023 AND month = 7 AND day = 28 AND duration < 60;

-- Look for people that called someone for less than 60 seconds after exiting the bakery as well as exiting the parking lot within 10 minutes after the theft
SELECT people.id, people.name 
FROM people 
JOIN phone_calls ON phone_calls.caller = people.phone_number 
JOIN bakery_security_logs ON bakery_security_logs.license_plate = people.license_plate 
WHERE (phone_calls.year = 2023 AND phone_calls.month = 7 AND phone_calls.day = 28 AND phone_calls.duration < 60) AND (bakery_security_logs.hour = 10 AND bakery_security_logs.minute BETWEEN 15 AND 25 AND bakery_security_logs.year = 2023 AND bakery_security_logs.month = 7 AND bakery_security_logs.day = 28);

398010|Sofia
514354|Diana
560886|Kelsey
686048|Bruce

-- Look if any of the people made a transaction in the given timeframe
SELECT name FROM people 
JOIN bank_accounts ON bank_accounts.person_id = people.id 
JOIN atm_transactions ON atm_transactions.account_number = bank_accounts.account_number 
WHERE (people.id = 398010 OR people.id = 514354 OR people.id = 560886 OR people.id = 686048) AND (atm_transactions.year = 2023 AND atm_transactions.month = 7 AND atm_transactions.day = 28);

Diana
Bruce

-- Get airport information
SELECT * FROM airports 
WHERE city = 'Fiftyville';

8|CSF|Fiftyville Regional Airport|Fiftyville

-- Get earliest flight out of Fiftyville a day after theft
SELECT flights.id 
FROM flights 
WHERE origin_airport_id = 8 AND year = 2023 AND month = 7 AND day = 29 ORDER BY hour ASC LIMIT 1;

36

-- Look if any of the people took the flight
SELECT name 
FROM people 
JOIN passengers ON passengers.passport_number = people.passport_number 
WHERE passengers.flight_id = 36 AND (people.id = 514354 OR people.id = 686048);

Bruce
-- Found thief -> Bruce 

-- Look for destination of flight 
SELECT full_name 
FROM airports 
WHERE id IN (SELECT destination_airport_id 
FROM flights 
WHERE id = 36 AND origin_airport_id = 8 AND year = 2023 AND month = 7 AND day = 29);

LaGuardia Airport
-- Found destination

-- Look for the person that Bruce has called after his theft
SELECT name 
FROM people
WHERE phone_number IN(
SELECT receiver 
FROM phone_calls 
WHERE caller IN (SELECT phone_number 
FROM people 
WHERE id = 686048) AND year = 2023 AND month = 7 AND day = 28 AND duration < 60);

Robin
-- Found Accomplice -> Robin