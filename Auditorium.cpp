#include "DatabaseOperation.h"

#include <iostream>
#include <string>
#include <vector>
#include <variant>

using namespace std;

class Auditorium {
private:
	int theater_id;
	int seatingCapacity;

	DatabaseOperation* db = new DatabaseOperation();

public:

	Auditorium() { };

	Auditorium(int theater_id, int seatingCapacity) {
		this->theater_id = theater_id;
		this->seatingCapacity = seatingCapacity;
	}

	void insertAuditorium(int theater_id, int seatingCapacity) {
		string sql = "INSERT INTO theater (theater_id, capacity) VALUES (?, ?)";
		vector<variant<int, string>> info = {theater_id, seatingCapacity };
		int rowsAffected = db->executeUpdate(sql, info);
		if (rowsAffected > 0) {
			cout << "Theater Inserted Successfully" << endl;
		}
		else {
			cout << "Something went wrong. Theater was not inserted into database" << endl;
		}
	}

	void showTheaters() {
		string sql = "SELECT * FROM theater";
		sql::ResultSet* res = db->getRecords(sql);
		try {
			while (res->next()) {
				cout << "Theater ID: " + to_string(res->getInt("auditorium_id")) << endl;
				cout << "Theater Name: " + to_string(res->getInt("theater_id")) << endl;
				cout << "Seating Capacity: " + to_string(res->getInt("capacity")) << endl;
				cout << endl;
			}
		}
		catch (sql::SQLException e) {
			cout << e.what() << endl;
		}
	}
};

//string showtime;
	//vector<string> seats;

	//Theater(string time, int capacity) {
	//	if (capacity > 100) {
	//		capacity = 100;
	//	}
	//	int row = 64;
	//	bool newRow = 0;
	//	int seatNum = 1;
	//	for (int i = 0; i < capacity; i++) {
	//		if (i % 10 == 0) {
	//			row++;
	//			newRow = true;
	//			seatNum = 1;
	//		}
	//		char rowChar = row;
	//		seats.push_back(rowChar + to_string(seatNum));
	//		//cout << rowChar + to_string(seatNum) << endl;
	//		seatNum++;
	//		newRow = false;
	//	}
	//}

	//void displaySeats() {
	//	cout << "Available seats for " << showtime << ":" << endl;
	//	for (int i = 0; i < seats.size(); i++) {
	//		if (i % 10 == 0 && i != 0) {
	//			cout << "\n";
	//		}
	//		cout << seats[i] << " ";
	//	}
	//	cout << endl;
	//}

	//bool reserveSeats(vector<int> seating) {
	//	for (int seat : seating) {
	//		if (seat > 0 && seat <= seats.size()) {
	//			seats[seat - 1] = "X";
	//		}
	//		else {
	//			cout << "Invalid seat number " << seat << ". Please select again." << endl;
	//			return false;
	//		}
	//	}
	//	return true;
	//}