#pragma once
#include "DatabaseOperation.h"
#include <variant>
#include <iostream>
#include <string>
#include <vector>
#include <variant>
#include <stdlib.h>
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

using namespace std;

class Showtime {

private:
	int movie_id;
	int auditorium_id;
	string time;

	DatabaseOperation* db = new DatabaseOperation();

public:
	Showtime();
	Showtime(int movie_id, int auditorium_id, string time);
	void insertShowtime(int movie_id, int auditorium_id, string time);
	void showTimes();
	int getTheaterCapacity(int showtime);
	void getShowtimeInfo(int show_time);

};