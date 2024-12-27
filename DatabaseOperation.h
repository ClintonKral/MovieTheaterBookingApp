#pragma once
#include <variant>
#include <iostream>
#include <string>
#include <vector>
#include <variant>
#include <fstream>
#include <stdlib.h>
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

using namespace std;
class DatabaseOperation {

public:

	string server;
	string user;
	string pass;
	
	DatabaseOperation();

	sql::Connection* connectToDatabase();
	int executeUpdate(string sql, vector<variant<int, string>> values);
	sql::ResultSet* getRecords(string sql);
	int selectSeatingCapacity(string sql, int argument);
	vector<int> getBookedSeats(int argument);
	void getUserBookingsForShowtime(int user_id, int show_time);
	void getUserBookings(int user_id);
	void getShowtimeInfo(string sql, int show_time);
	int deleteBooking(int booking_id, int user_id);
	int getUserId(string sql, string username);

};