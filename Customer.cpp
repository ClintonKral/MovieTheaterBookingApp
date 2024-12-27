#include <iostream>
#include "Booking.h"
#include "Showtime.h"
#include "Movie.h"
#include "Theater.h"

using namespace std; 

class Moviegoer {

	private:
		string username;
		string pass;
		string first_name;
		string last_name;
		string email;
		string bday;

		Showtime* s = new Showtime();
		Booking* b = new Booking();
		DatabaseOperation* db = new DatabaseOperation;

	public:
		Moviegoer() {};

		Moviegoer(string uname, string pw, string first_name, string last_name, string mail, string birthday) {
			this->username = uname;
			this->pass = pw;
			this->first_name = first_name;
			this->last_name = last_name;
			this->email = mail;
			this->bday = birthday;
		}

		int getUserID() {
			string sql = "SELECT user_id FROM moviegoer WHERE username = ?";
			int user_id = db->getUserId(sql, this->username);
			return user_id;
		}
		
		void customerMenu() {
			int user_id = getUserID();
			while (true) {
				cout << "------------Customer Menu ------------" << endl;
				cout << "Enter [1] to see all showtimes" << endl;
				cout << "Enter [2] to book a ticket" << endl;
				cout << "Enter [3] to see tickets already purchased" << endl;
				cout << "Enter [4] to cancel booking" << endl;
				cout << "Enter [5] to exit" << endl;
				int choice;
				cin >> choice;
				switch (choice) {
					case 1:
						s->showTimes();
						break;
					case 2:
						b->bookTicket(user_id);
						break;
					case 3:
						b->seeTicket(user_id);
						break;
					case 4:
						b->cancelTicket(user_id);
						break;
					case 5:
						exit(0);
				}
			}
		}

		string getPass() {
			string temp;
			int count = 0;
			while (count < 3) {
				cout << "Enter email associated with account: ";
				cin >> temp;
				if (temp == email) {
					cout << "Your password is the following: ";
					cout << pass << endl;
					return pass;
				}
				cout << "Invalid Email Address!" << endl;
				count++;
			}

			cout << "You have attempted too many times. Please try again later." << endl;
			return "";
		}

};