#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "DatabaseOperation.h"

using namespace std;

class Movie {

private:
	// Instances
	string title;
	string age_rating;
	int runtime;
	string release_date;
	string description;
	string status;

	DatabaseOperation* db = new DatabaseOperation();

public:

	Movie();
	Movie(string title, string age_rating, int runtime, string release_date, string description, string status);
	void insertMovie();
	void showMovies();
};