#include "DatabaseOperation.h"

using namespace std;

DatabaseOperation::DatabaseOperation() {
	ifstream inputFile("connectionInfo.txt");
	if (inputFile.is_open()) {
		string inputs;
		int i = 0;
		while (getline(inputFile, inputs)) {
			if (i == 0) {
				server = inputs;
			}
			else if (i == 1) {
				user = inputs;
			}
			else if (i == 2) {
				pass = inputs;
			}
			i++;
		}
		inputFile.close();
	}
	else {
		cerr << "Error opening file" << endl;
	}

};

//TO-DO: put this in a file

// Connection to the database that is defined
sql::Connection* DatabaseOperation::connectToDatabase() {
	sql::Driver* driver;
	sql::Connection* con;
	try
	{
		driver = get_driver_instance();
		con = driver->connect(server, user, pass);
	}
	catch (sql::SQLException e)
	{
		cout << "Could not connect to server. Error message: " << e.what() << endl;
		system("pause");
		exit(1);
	}
	con->setSchema("movie_theater");
	return con;
}

int DatabaseOperation::executeUpdate(string sql, vector<variant<int, string>> values) {
	int rowsAffected = 0;
	try {
		sql::Connection* con = connectToDatabase();
		sql::PreparedStatement* ps = con->prepareStatement(sql);

		for (int i = 0; i < values.size(); i++) {
			if (holds_alternative<string>(values[i])) {
				ps->setString(i + 1, get<string>(values[i]));
			}
			else if (holds_alternative<int>(values[i])) {
				ps->setInt(i + 1, get<int>(values[i]));
			}
		}
		rowsAffected = ps->executeUpdate();
	}

	catch (sql::SQLException e) {
		cout << e.what() << endl;
	}

	return rowsAffected;
}

sql::ResultSet* DatabaseOperation::getRecords(string sql) {
	sql::ResultSet* res = nullptr;
	try {
		sql::Connection* con = connectToDatabase();
		sql::PreparedStatement* ps = con->prepareStatement(sql);
		res = ps->executeQuery();
	}
	catch (sql::SQLException e) {
		cout << e.what() << endl;
	}

	return res;
}

int DatabaseOperation::selectSeatingCapacity(string sql, int argument) {
	int record = 0;
	try {
		sql::Connection* con = connectToDatabase();
		sql::PreparedStatement* ps = con->prepareStatement(sql);
		ps->setInt(1, argument);
		sql::ResultSet* rs = ps->executeQuery();
		while (rs->next()) {
			record = rs->getInt("capacity");
		}
	}
	catch (sql::SQLException e) {
		cout << e.what() << endl;
	}

	return record;
}

vector<int> DatabaseOperation::getBookedSeats(int argument) {
	string sql = "SELECT selected_seats FROM booking WHERE showing_id = ?";
	vector<int> bookedSeats;
	try {
		sql::Connection* con = connectToDatabase();
		sql::PreparedStatement* ps = con->prepareStatement(sql);
		ps->setInt(1, argument);
		sql::ResultSet* rs = ps->executeQuery();
		while (rs->next()) {
			bookedSeats.push_back(rs->getInt("selected_seats"));
		}
	}
	catch (sql::SQLException e) {
		cout << e.what() << endl;
	}

	return bookedSeats;
}

void DatabaseOperation::getUserBookingsForShowtime(int user_id, int show_time) {
	string sql = "SELECT selected_seats FROM booking WHERE user_id = ? AND showing_id = ?";

	try {
		sql::Connection* con = connectToDatabase();
		sql::PreparedStatement* ps = con->prepareStatement(sql);
		ps->setInt(1, user_id);
		ps->setInt(2, show_time);
		sql::ResultSet* rs = ps->executeQuery();
		while (rs->next()) {
			cout << "----- Booking Details -----" << endl;
			cout << "Seat number: " + rs->getInt("selected_seats");
		}
	}
	catch (sql::SQLException e) {
		cout << e.what() << endl;
	}
}

void DatabaseOperation::getUserBookings(int user_id) {
	string sql = "SELECT * FROM booking WHERE user_id = ?";
	try {
		sql::Connection* con = connectToDatabase();
		sql::PreparedStatement* ps = con->prepareStatement(sql);
		ps->setInt(1, user_id);
		sql::ResultSet* rs = ps->executeQuery();
		while (rs->next()) {
			cout << "----- Booking Details -----" << endl;
			cout << "Booking ID: " + to_string(rs->getInt("booking_id")) << endl;
			cout << "Showtime ID: " + to_string(rs->getInt("showing_id")) << endl;
			cout << "Seat number: " + to_string(rs->getInt("selected_seats")) << endl;
		}
	}
	catch (sql::SQLException e) {
		cout << e.what() << endl;
	}
}

void DatabaseOperation::getShowtimeInfo(string sql, int show_time) {

	try {
		sql::Connection* con = connectToDatabase();
		sql::PreparedStatement* ps = con->prepareStatement(sql);
		ps->setInt(1, show_time);
		sql::ResultSet* rs = ps->executeQuery();
		while (rs->next()) {
			cout << "----- Showtime Details -----" << endl;
			cout << "Showtime_id: " + to_string(rs->getInt("time_id")) << endl;
			cout << "Title: " + rs->getString("title") << endl;
			cout << "Duration: " + to_string(rs->getInt("runtime")) << endl;
			cout << "Time of Showing: " + rs->getString("show_datetime") << endl;

		}
	}
	catch (sql::SQLException e) {
		cout << e.what() << endl;
	}
}

int DatabaseOperation::deleteBooking(int booking_id, int user_id) {
	int rowsAffected = 0;
	string sql = "DELETE from booking where booking_id = ? AND user_id = ?";
	try {
		sql::Connection* con = connectToDatabase();
		sql::PreparedStatement* ps = con->prepareStatement(sql);
		ps->setInt(1, booking_id);
		ps->setInt(2, user_id);
		rowsAffected = ps->executeUpdate();
	}
	catch (sql::SQLException e) {
		cout << e.what() << endl;
	}

	return rowsAffected;
}

int DatabaseOperation::getUserId(string sql, string username) {
	sql::ResultSet* res = nullptr;
	int user_id = -1;
	try {
		sql::Connection* con = connectToDatabase();
		sql::PreparedStatement* ps = con->prepareStatement(sql);
		ps->setString(1, username);
		res = ps->executeQuery();
		res->next();
		user_id = res->getInt("user_id");
	}
	catch (sql::SQLException e) {
		cout << e.what() << endl;
	}

	return user_id;
}
