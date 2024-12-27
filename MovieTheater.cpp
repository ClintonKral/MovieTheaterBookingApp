#include <iostream>
#include <string>
#include <regex>
#include <vector>
#include "DatabaseOperation.h"
#include "Customer.cpp"
#include "Theater.h"
#include "Movie.h"
#include "Showtime.h"
#include "Booking.h"

#include <stdlib.h>
#include <time.h>

#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

using namespace std;

int checkEmail(string &email);
int checkUsername(string &username, sql::Connection* con, bool newUser);
int checkPass(string &pass);
Moviegoer createAccount(sql::Connection* con);
Moviegoer userLogin(sql::Connection* con);

DatabaseOperation* db = new DatabaseOperation();


int main() {
	
	sql::Connection* con = db->connectToDatabase();
	int user_id  = 0;

	int choice;
	cout << "Welcome to Clinton's Cinema!\n[1] Create an Account\n[2] Sign In" << endl;
	cin >> choice;
	cin.ignore(256, '\n');
	if (choice == 1) {
		Moviegoer currUser = createAccount(con);
		user_id = currUser.getUserID();
		currUser.customerMenu();
	}
	else {
		Moviegoer currUser = userLogin(con);
		currUser.customerMenu();
	}

	return 0;
}

/*
	Creates an account in the database with information given by the user such as username,
	password, first & last name, birthday, and email.
*/
Moviegoer createAccount(sql::Connection* con) {
	string username;
	string password;
	string first_name;
	string last_name;
	string birthdate;
	string email;
	int valid = 0;
	cout << "Create Username: ";
	getline(cin, username);
	while (!checkUsername(username, con, true)) {
		cout << "Enter a valid username: ";
		getline(cin, username);
	}

	cout << "Create Password: ";
	getline(cin, password);
	while (!checkPass(password)) {
		cout << "Enter a valid password: ";
		getline(cin, password);
	}

	cout << "Enter First Name: ";
	getline(cin, first_name);

	cout << "Enter Last Name: ";
	getline(cin, last_name);

	cout << "Enter Date of Birth (MM/DD/YYYY): ";
	getline(cin, birthdate);
	
	cout << "What email would you like to use? ";
	getline(cin, email);
	while (!checkEmail(email)) {
		cout << "Enter a valid email: ";
		getline(cin, email);
	}

	vector<variant<int,string>> info = { username, password, first_name, last_name, birthdate, email };
	
	db->executeUpdate("INSERT INTO moviegoer(username, pass, first_name, last_name, birthdate, email) VALUES(? , ? , ? , ? , ? , ? )", info);

	Moviegoer myCust = Moviegoer(username, password, first_name, last_name, email, birthdate);
	
	return myCust;
}

/*
	Login function where the user will enter the username and password to be searched through the 
	database 'moviegoer' to see if the user/pass combination exists.
*/
Moviegoer userLogin(sql::Connection* con) {
	sql::PreparedStatement* post;
	sql::ResultSet* result;
	string username = "";
	string pass = "";

	cout << "Enter Username: ";
	getline(cin, username);
	while (!checkUsername(username, con, false)) {
		cout << "Enter Username: ";
		getline(cin, username);
	}

	cout << "Enter Password: ";
	getline(cin, pass);
	while (!checkPass(pass)) {
		cout << "Enter Password: ";
		getline(cin, pass);
	}

	//TO-DO: encrypting password?
	post = con->prepareStatement("SELECT * FROM moviegoer WHERE username = (?) AND pass = (?)");
	post->setString(1, username);
	post->setString(2, pass);

	result = post->executeQuery();
	int attempts = 1;
	while (result->next() == NULL && attempts < 3) {
		cout << "User not found. Please try again." << endl;

		cout << "Enter Username: ";
		getline(cin, username);
		while (!checkUsername(username, con, false)) {
			cout << "Enter Username: ";
			getline(cin, username);
		}

		cout << "Enter Password: ";
		getline(cin, pass);
		while (!checkPass(pass)) {
			cout << "Enter Password: ";
			getline(cin, pass);
		}

		cout << username << endl;
		cout << pass << endl;

		//TO-DO: encrypting password?
		post = con->prepareStatement("SELECT * FROM moviegoer WHERE username = ? AND pass = ?");
		post->setString(1, username);
		post->setString(2, pass);

		result = post->executeQuery();
		attempts++;
	}

	if (attempts == 3 && result->next() == NULL) {
		cout << "You have attempted too many times. Please try again later." << endl;
		exit(0);
	}
	
	printf("Welcome Back, %s!\n", result->getString(4));
	Moviegoer myCust = Moviegoer(result->getString(2), result->getString(3), result->getString(4), result->getString(5), result->getString(6), result->getString(7));
	return myCust;

}

// Checking for valid email address format.
int checkEmail(string &email) {
	const regex format("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");

	return regex_match(email, format);
}

/*
	Criteria:
	password must be 8 to 25 characters in length.
	At least one number.
	No spaces, ampersands, accents, mathematical signs, asterisks, commas, accented letters, brackets, colons.
*/
int checkPass(string &pass) {
	if (pass.size() < 8) {
		cout << "Password is too short" << endl;
		return 0;
	}
	else if (pass.size() > 25) {
		cout << "Password is too long" << endl;
		return 0;
	}
	vector<char> banned{ ' ', '<', '>', '\"', '\'', '\\', '/', ',', ';', ':', '[', ']', '=', '+', '&', '(', ')', '{', '}'};
	bool oneNum = false;

	for (char c : pass) {
		if (!isalnum(c)) {
			std::vector<char>::iterator it;
			it = find(banned.begin(), banned.end(), c);
			if (it != banned.end()) {
				cout << "Invalid character found in password." << endl;
				return 0;
			}
		}
		if (isdigit(c)) {
			oneNum = true;
		}
	}

	if (!oneNum) {
		cout << "No number in password." << endl;
		return 0;
	}

	return 1;
}

/*
	Criteria:
	Username must be 4 to 25 characters in length.
	No more than one period.
	No spaces, ampersands, accents, mathematical signs, asterisks, commas, accented letters, brackets, or exclamation points.
*/
int checkUsername(string &uname, sql::Connection* con, bool newUser) {
	sql::PreparedStatement* pstmt;
	sql::ResultSet* result;

	pstmt = con->prepareStatement("SELECT username FROM moviegoer WHERE username = (?)");
	pstmt->setString(1, uname);
	result = pstmt->executeQuery();

	if (newUser == true && result->next() != NULL) {
		cout << "Username already exists." << endl;
		return 0;
	}

	if (uname.size() < 4) {
		cout << "Username is too short" << endl;
		return 0;
	}
	else if (uname.size() > 25) {
		cout << "Username is too long" << endl;
		return 0;
	}
	vector<char> banned{' ', '<', '>', '\"', '\'', '\\', '/', ',', ';', ':', '[', ']', '?', '!', '=', '+', '&', '(', ')', '{', '}'};
	int periodCnt = 0;

	for (char c : uname) {
		if (!isalnum(c)) {
			std::vector<char>::iterator it;
			it = find(banned.begin(), banned.end(), c);
			if (it != banned.end()) {
				cout << "Invalid character found in username." << endl;
				return 0;
			}
			if (c == '.') {
				periodCnt++;
			}
		}
	}

	if (periodCnt > 1) {
		cout << "Too many periods in username." << endl;
		return 0;
	}

	return 1;
}