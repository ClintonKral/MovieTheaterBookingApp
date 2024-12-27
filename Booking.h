#pragma once
#include "Showtime.h"
#include "Movie.h"
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <string>

using namespace std;

class Booking {

public:
	DatabaseOperation* db = new DatabaseOperation();
	Showtime* s = new Showtime();
	Booking();
	void bookTicket(int user_id);
	void seeTicket(int user_id);
	void cancelTicket(int user_id);

};