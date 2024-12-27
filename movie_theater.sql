DROP DATABASE IF EXISTS `Movie_Theater`;
CREATE DATABASE `Movie_Theater`;
use `Movie_Theater`;

create table moviegoer (
	user_id INT AUTO_INCREMENT,
	username varchar(50) UNIQUE,
    pass varchar(50) NOT NULL,
	first_name varchar(50),
    last_name varchar(50),
	birthdate varchar(50),
    email varchar(50) UNIQUE,
     constraint pk_user PRIMARY KEY (user_id)
);

create table movie (
	movie_id INT AUTO_INCREMENT,
	title varchar(200) UNIQUE,
    age_rating varchar(5),
    runtime INT,
    release_date DATE,
    description varchar(2000),
    status varchar(20),
    constraint pk_movie PRIMARY KEY(movie_id)
);

create table genre (
	genre_id INT,
    genre_name varchar(50),
    CONSTRAINT fk_genre PRIMARY KEY(genre_id)
);

create table movie_genre(
	movie_id INT AUTO_INCREMENT,
    genre_id INT,
    constraint fk_movie_id FOREIGN KEY(movie_id) REFERENCES movie(movie_id),
    constraint fk_genre_id foreign key(genre_id) REFERENCES genre(genre_id)
);

create table state (
	state_id INT AUTO_INCREMENT,
    state_name varchar(20),
    constraint pk_state primary key (state_id)
);

create table theater (
	theater_id INT auto_increment,
    theater_name varchar(200) UNIQUE,
    state_id INT,
    constraint pk_theater primary key(theater_id),
    constraint fk_theater_state foreign key(state_id) references state(state_id)
);

create table seat_type (
	type_id INT,
    type_name varchar(20),
    constraint pk_seat_type primary key (type_id)
);

create table auditorium (
	auditorium_id int unique,
	theater_id int,
    capacity int,
    constraint pk_auditorium primary key (auditorium_id),
    constraint fk_theater_audit foreign key (theater_id) references theater(theater_id)
);

create table show_time (
	time_id INT NOT NULL AUTO_INCREMENT,
    movie_id INT,
    auditorium_id INT,
    show_datetime DATETIME UNIQUE,
    constraint pk_showtime primary key (time_id),
    constraint fk_showing_movie foreign key (movie_id) references movie(movie_id),
    constraint fk_show_auditorium foreign key (auditorium_id) references auditorium(auditorium_id)
);

create table seat (
	seat_id INT,
    seat_type_id INT,
    auditorium_id INT,
    seat_location varchar(5),
    constraint fk_seat primary key (seat_id),
    constraint fk_seat_type foreign key (seat_type_id) references seat_type(type_id),
    constraint fk_auditorium foreign key (auditorium_id) references auditorium(auditorium_id)
);

create table booking (
	booking_id INT AUTO_INCREMENT,
    showing_id INT,
    user_id INT,
    booking_fee INT,
    selected_seats INT UNIQUE,
    constraint pk_booking primary key (booking_id),
    constraint fk_booking_user foreign key (user_id) references moviegoer (user_id),
    constraint fk_booking_show foreign key (showing_id) references show_time (time_id)
);

create table booking_seat (
	booking_id INT,
    seat_id INT,
    constraint fk_bkst_booking foreign key (booking_id) references booking (booking_id),
    constraint fk_bkst_seat foreign key (seat_id) references seat (seat_id)
);

create table ticket_type (
	type_id INT,
    ticket_type_name varchar(50),
    ticket_price INT,
    constraint pk_ticket_type primary key (type_id)
);

create table booking_ticket (
	ticket_type_id INT,
    booking_id INT,
    ticket_qty INT,
    constraint fk_booktk_type foreign key (ticket_type_id) references ticket_type (type_id),
    constraint fk_booktk_booking foreign key (booking_id) references booking (booking_id)
);

insert into state (state_id, state_name) VALUES
(1, 'AK'),
(2, 'AL'),
(3, 'AR'),
(4, 'AZ');

insert into theater (theater_id, theater_name, state_id) VALUES
(1, 'Cinemark Century Anchorage 16 and XD', 1),
(2, 'Cinemark Bridge Street and XD', 2),
(3, 'Cinemark Tinseltown USA Benton', 3),
(4, 'Cinemark Towne Centre and XD', 3),
(5, 'Cinemark Colonel Glenn and XD', 3),
(6, 'Cinemark Mesa 16', 4),
(7, 'Cinemark Century Oro Valley Marketplace', 4),
(8, 'Cinemark Sierra Vista 10', 4),
(9, 'Cinemark Century El Con 20 and XD', 4),
(10, 'Cinemark Century Park Place 20 and XD', 4),
(11, 'Cinemark Century Tucson Marketplace and XD', 4);

insert into moviegoer (username, pass, first_name, last_name, birthdate, email)
values
('ClintonomoBay', 'RandomPass1234', 'Clinton', 'Kral', '07/29/1997', 'dashkral@yahoo.com');

insert into genre(genre_id, genre_name) VALUES
(1, 'Adventure'),
(2, 'Animation'),
(3, 'Comedy'),
(4, 'Drama'),
(5, 'Horror'),
(6, 'Family'),
(7, 'Action'),
(8, 'Romance');

insert into movie (movie_id, title, age_rating, runtime, release_date, description, status)
VALUES (1, 'The Wild Robot', 'PG', 101, 20240927, 'Shipwrecked on a deserted island, a robot named Roz must learn to adapt to its new surroundings. 
Building relationships with the native animals, Roz soon develops a parental bond with an orphaned gosling.', 'Tickets on Sale');

insert into movie_genre(movie_id, genre_id) values
(1, 1),
(1, 2),
(1, 6);

insert into auditorium (auditorium_id, theater_id, capacity) VALUES
(1, 10, 64),
(2, 10, 64),
(3, 10, 64),
(4, 10, 64),
(5, 10, 64);

insert into show_time (time_id, movie_id, auditorium_id, show_datetime) VALUES
(1, 1, 1, '2024-11-05 10:30:00'),
(2, 1, 2, '2024-11-05 12:00:00'),
(3, 1, 3, '2024-11-05 12:30:00'),
(4, 1, 4, '2024-11-05 13:40:00'),
(5, 1, 5, '2024-11-05 14:30:00');

insert into seat_type (type_id, type_name) VALUES
(1, 'Standard'),
(2, 'DBOX'),
(3, 'Accessible');

insert into seat (seat_id, seat_type_id, auditorium_id, seat_location) VALUES
(1,1,1,'A1'),
(2,1,1,'A2'),
(3,1,1,'A3'),
(4,1,1,'A4'),
(5,1,1,'A5'),
(6,1,1,'A6'),
(7,1,1,'A7'),
(8,1,1,'A8'),
(9,1,1,'A9'),
(10,1,1,'A10'),
(11,1,1,'B1'),
(12,1,1,'B2'),
(13,1,1,'B3'),
(14,1,1,'B4'),
(15,1,1,'B5'),
(16,1,1,'B6'),
(17,1,1,'B7'),
(18,1,1,'B8'),
(19,1,1,'B9'),
(20,1,1,'B10'),
(21,3,1,'C3'),
(22,3,1,'C6'),
(23,3,1,'C9'),
(24,3,1,'C12'),
(25,2,1,'D1'),
(26,2,1,'D2'),
(27,2,1,'D3'),
(28,2,1,'D4'),
(29,2,1,'D5'),
(30,2,1,'D6'),
(31,2,1,'D7'),
(32,2,1,'D8'),
(33,2,1,'D9'),
(34,2,1,'D10');


    