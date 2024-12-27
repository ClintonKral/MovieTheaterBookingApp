#include "Theater.h"

Theater::Theater() {};

Theater::Theater(string name, int state_id) {
	this->name = name;
	this->state_id = state_id;
}

void Theater::insertTheater() {
	string sql = "INSERT INTO theater (theater_name, state_id) VALUES (?, ?)";
	vector<variant<int, string>> info = { name, state_id };
	int rowsAffected = db->executeUpdate(sql, info);
	if (rowsAffected > 0) {
		cout << "Theater Inserted Successfully" << endl;
	}
	else {
		cout << "Something went wrong. Theater was not inserted into database" << endl;
	}
}

void Theater::showTheaters() {
	string sql = "SELECT * FROM theater";
	sql::ResultSet* res = db->getRecords(sql);
	try {
		while (res->next()) {
			cout << "Theater ID: " + to_string(res->getInt("theater_id")) << endl;
			cout << "Theater Name: " + res->getString("theater_name") << endl;
			string state_name = "SELECT state_name FROM state WHERE state_id=" + to_string(res->getInt("state_id"));
			sql::ResultSet* anotherRes = db->getRecords(state_name);
			anotherRes->next();
			cout << "State ID: " + anotherRes->getString("state_name") << endl;
			cout << endl;
		}
	}
	catch (sql::SQLException e) {
		cout << e.what() << endl;
	}
}