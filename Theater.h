#pragma once
#include <iostream>
#include <vector>
#include "DatabaseOperation.h"
#include <time.h>

using namespace std;

class Theater {
private:
	string name;
	int state_id;

	DatabaseOperation* db = new DatabaseOperation();

public:

	Theater();
	Theater(string name, int state_id);
	void insertTheater();
	void showTheaters();
};