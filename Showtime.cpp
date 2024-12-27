#include "Showtime.h"

using namespace std;

Showtime::Showtime() {};

Showtime::Showtime(int movie_id, int auditorium_id, string time) {
	this->movie_id = movie_id;
	this->auditorium_id = auditorium_id;
	this->time = time;
}

void Showtime::insertShowtime(int movie_id, int auditorium_id, string time) {
	string sql = "INSERT INTO show_time (movie_id, auditorium_id, show_datetime) VALUES (?,?,STR_TO_DATE(?, \'%m-%d-%Y %T\'))";
	vector<variant<int, string>> values = { movie_id, auditorium_id, time };
	int rowsAffected = db->executeUpdate(sql, values);

	if (rowsAffected > 0) {
		cout << "Showtime Inserted Successfully" << endl;
	}
	else {
		cout << "Something went wrong. Showtime was not inserted into database" << endl;
	}
}

void Showtime::showTimes() {
	string sql = "SELECT * FROM show_time";
	sql::ResultSet* res = db->getRecords(sql);
	try {
		while (res->next()) {
			cout << "Time ID: " + to_string(res->getInt("time_id")) << endl;
			cout << "Movie ID: " + to_string(res->getInt("movie_id")) << endl;
			cout << "Auditorium ID: " + to_string(res->getInt("auditorium_id")) << endl;
			cout << "Showtime: " + res->getString("show_datetime") << endl;
			cout << endl;
		}
	}
	catch (sql::SQLException e) {
		cout << e.what() << endl;
	}
}

int Showtime::getTheaterCapacity(int showtime) {
	string sql = "SELECT capacity FROM auditorium WHERE auditorium_id = (SELECT auditorium_id from show_time where time_id = ?)";
	return db->selectSeatingCapacity(sql, showtime);
}

void Showtime::getShowtimeInfo(int show_time) {
	string sql = "SELECT s.time_id, m.title, m.runtime, s.show_datetime FROM show_time s, movie m WHERE s.movie_id = m.movie_id and s.time_id = ?";
	return db->getShowtimeInfo(sql, show_time);
}