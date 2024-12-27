#include "Booking.h"

// Constructor
Booking::Booking() {};

/*
	Books a ticket by showing available seats that are not already claimed
	in the database by another user and then 
*/
void Booking::bookTicket(int user_id) {
	int choice;
	cout << "Available Showtimes: \n";
	s->showTimes();
	cout << "Enter your choice: ";
	cin >> choice;

	int capacity = s->getTheaterCapacity(choice);
	cout << capacity;

	vector<int> bookedSeats = db->getBookedSeats(choice);
	cout << "----- Available Seats -----" << endl;
	for (int i = 1; i <= capacity; i++) {
		if (find(bookedSeats.begin(), bookedSeats.end(), i) != bookedSeats.end()) {
			cout << " X ";
		}
		else {
			cout << " " + to_string(i) + " ";
		}

		if (i % 8 == 0) {
			cout << "\n";
		}
	}

	//TODO: Make sure a double booking cannot happen.
	cout << "Enter seat you would like to book: ";
	int seat;
	cin >> seat;

	string sql = "INSERT INTO booking (showing_id, user_id, booking_fee, selected_seats) VALUES (?,?,12,?)";
	vector<variant<int, string>> info{ choice, user_id, seat };
	int rowsAffected = db->executeUpdate(sql, info);
	if (rowsAffected > 0) {
		cout << "Booking Made Successfully" << endl;
	}
	else {
		cout << "Something went wrong. Booking was not inserted into database" << endl;
		cout << "It is most likely due to seat already being booked. Please choose the showing and try again." << endl;
	}
}

void Booking::seeTicket(int user_id) {
	cout << "Tickets booked at different showtimes:" << endl;
	db->getUserBookings(user_id);
	cout << "\nEnter Showtime ID to know more information: ";
	int showtime;
	cin >> showtime;
	s->getShowtimeInfo(showtime);
}

void Booking::cancelTicket(int user_id) {
	cout << "Tickets booked at different showtimes:" << endl;
	db->getUserBookings(user_id);
	cout << "\nEnter Booking ID to cancel booking: ";
	int booking;
	cin >> booking;
	int rowsAffected = db->deleteBooking(booking, user_id);
	if (rowsAffected > 0) {
		cout << "Booking Cancelled Successfully" << endl;
	}
	else {
		cout << "Something went wrong. Booking was not removed from database" << endl;
	}

}
