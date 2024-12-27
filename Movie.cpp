#include "Movie.h"

// Constructors
Movie::Movie() {};

Movie::Movie(string title, string age_rating, int runtime, string release_date, string description, string status) {
	this->title = title;
	this->age_rating = age_rating;
	this->runtime = runtime;
	this->release_date = release_date;
	this->description = description;
	this->status = status;
}

// Methods

// Insert movie into database
void Movie::insertMovie() {
	string sql = "INSERT INTO movie (title, age_rating, runtime, release_date, description, status) VALUES (?, ?, ?, ?, ?, ?)";
	vector<variant<int, string>> info = { title, age_rating, runtime, release_date, description, status };
	int rowsAffected = db->executeUpdate(sql, info);
	if (rowsAffected > 0) {
		cout << "Movie Inserted Successfully" << endl;
	}
	else {
		cout << "Something went wrong. Movie was not inserted into database" << endl;
	}
}

// Show movies that are in database
void Movie::showMovies() {
	string sql = "SELECT * FROM movie";
	sql::ResultSet* res = db->getRecords(sql);
	try {
		while (res->next()) {
			cout << "Movie ID: " + to_string(res->getInt("movie_id")) << endl;
			cout << "Movie Title: " + res->getString("title") << endl;
			cout << "Age Rating: " + res->getString("age_rating") << endl;
			cout << "Duration: " + to_string(res->getInt("runtime")) + " minutes" << endl;
			cout << "Release Date: " + res->getString("release_date") << endl;
			cout << "Movie Description: " + res->getString("description") << endl;
			cout << "Status: " + res->getString("status") + "\n" << endl;
		}
	}
	catch (sql::SQLException e) {
		cout << e.what() << endl;
	}
}