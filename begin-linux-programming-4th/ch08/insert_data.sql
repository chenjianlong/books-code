USE blpcd;

-- Delete existing data
DELETE FROM track;
DELETE FROM cd;
DELETE FROM artist;

-- Now the data INSERTs

-- First the artist (or group) tables
INSERT INTO artist(id, name) VALUES(1, 'Pink Floyd');
INSERT INTO artist(id, name) VALUES(2, 'Genesis');
INSERT INTO artist(id, name) VALUES(3, 'Einaudi');
INSERT INTO artist(id, name) VALUES(4, 'Melanie C');

-- Then the cd table
INSERT INTO cd(id, title, artist_id, catalogue) VALUES(1, 'Dark Side of the Moon', 1, 'B000024D4P');
INSERT INTO cd(id, title, artist_id, catalogue) VALUES(2, 'Wish You Were Here', 1, 'B000024D4S');
INSERT INTO cd(id, title, artist_id, catalogue) VALUES(3, 'A Trick of the Tail', 2, 'B000024EXM');
INSERT INTO cd(id, title, artist_id, catalogue) VALUES(4, 'Selling England By the Pound', 2, 'B000024E9M');
INSERT INTO cd(id, title, artist_id, catalogue) VALUES(5, 'I Giorni', 3, 'B000071WEV');
INSERT INTO cd(id, title, artist_id, catalogue) VALUES(6, 'Northern Star', 4, 'B00004YMST');

-- Finally we populate the track
INSERT INTO track(cd_id, track_id, title) VALUES(1, 1, 'Speak to me');
INSERT INTO track(cd_id, track_id, title) VALUES(1, 2, 'Breathe');
INSERT INTO track(cd_id, track_id, title) VALUES(1, 3, 'On the run');
INSERT INTO track(cd_id, track_id, title) VALUES(1, 4, 'Time');
INSERT INTO track(cd_id, track_id, title) VALUES(1, 5, 'Great gig in the sky');
INSERT INTO track(cd_id, track_id, title) VALUES(1, 6, 'Money');
INSERT INTO track(cd_id, track_id, title) VALUES(1, 7, 'Us and them');
INSERT INTO track(cd_id, track_id, title) VALUES(1, 8, 'Any colour you like');
INSERT INTO track(cd_id, track_id, title) VALUES(1, 9, 'Brain damage');
INSERT INTO track(cd_id, track_id, title) VALUES(1, 10, 'Eclipse ');

INSERT INTO track(cd_id, track_id, title) VALUES(2, 1, 'Shine on you crazy diamond');
INSERT INTO track(cd_id, track_id, title) VALUES(2, 2, 'Welcome to the machine');
INSERT INTO track(cd_id, track_id, title) VALUES(2, 3, 'Have a cigar');
INSERT INTO track(cd_id, track_id, title) VALUES(2, 4, 'Wish you were here');
INSERT INTO track(cd_id, track_id, title) VALUES(2, 5, 'Shine on you crazy diamond pt.2');

INSERT INTO track(cd_id, track_id, title) VALUES(3, 1, 'Dance on a volcano');
INSERT INTO track(cd_id, track_id, title) VALUES(3, 2, 'Entangled');
INSERT INTO track(cd_id, track_id, title) VALUES(3, 3, 'Squonk');
INSERT INTO track(cd_id, track_id, title) VALUES(3, 4, 'Madman moon');
INSERT INTO track(cd_id, track_id, title) VALUES(3, 5, 'Robbery assault and battery');
INSERT INTO track(cd_id, track_id, title) VALUES(3, 6, 'Ripples');
INSERT INTO track(cd_id, track_id, title) VALUES(3, 7, 'Trick of the tail');
INSERT INTO track(cd_id, track_id, title) VALUES(3, 8, 'Los Endos');

INSERT INTO track(cd_id, track_id, title) VALUES(4, 1, 'Melodia Africana (part 1)');
INSERT INTO track(cd_id, track_id, title) VALUES(4, 2, 'I due fiumi');
INSERT INTO track(cd_id, track_id, title) VALUES(4, 3, 'In un\'altra vita');
INSERT INTO track(cd_id, track_id, title) VALUES(4, 4, 'Melodia Africana (part 2)');
INSERT INTO track(cd_id, track_id, title) VALUES(4, 5, 'Stella del mattino');
INSERT INTO track(cd_id, track_id, title) VALUES(4, 6, 'I giorni');
INSERT INTO track(cd_id, track_id, title) VALUES(4, 7, 'Samba');
INSERT INTO track(cd_id, track_id, title) VALUES(4, 8, 'Melodia Africana (part 3)');
INSERT INTO track(cd_id, track_id, title) VALUES(4, 9, 'La nascita delle cose segrete');
INSERT INTO track(cd_id, track_id, title) VALUES(4, 10, 'Quel che resta');
INSERT INTO track(cd_id, track_id, title) VALUES(4, 11, 'Inizio');
INSERT INTO track(cd_id, track_id, title) VALUES(4, 12, 'Limbo');
INSERT INTO track(cd_id, track_id, title) VALUES(4, 13, 'Bella notte');
INSERT INTO track(cd_id, track_id, title) VALUES(4, 14, 'Canzone Africana (part 4)');

INSERT INTO track(cd_id, track_id, title) VALUES(6, 1, 'Go!');
INSERT INTO track(cd_id, track_id, title) VALUES(6, 2, 'Northern Star');
INSERT INTO track(cd_id, track_id, title) VALUES(6, 3, 'Goin\' Down');
INSERT INTO track(cd_id, track_id, title) VALUES(6, 4, 'I Turn To You');
INSERT INTO track(cd_id, track_id, title) VALUES(6, 5, 'If That Were Me');
INSERT INTO track(cd_id, track_id, title) VALUES(6, 6, 'Never Be The Same Again');
INSERT INTO track(cd_id, track_id, title) VALUES(6, 7, 'Why');
INSERT INTO track(cd_id, track_id, title) VALUES(6, 8, 'Suddenly Monday');
INSERT INTO track(cd_id, track_id, title) VALUES(6, 9, 'Ga Ga');
INSERT INTO track(cd_id, track_id, title) VALUES(6, 10, 'Be The One');
INSERT INTO track(cd_id, track_id, title) VALUES(6, 11, 'Closer');
INSERT INTO track(cd_id, track_id, title) VALUES(6, 12, 'Feel The Sun');

