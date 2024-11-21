Flight Reservation System Project:

Project Description:

The Fokir Marka Airlines Reservation System is a C-based console application designed for managing flight reservations, cancellations, and tracking customer details. It allows users to reserve, view, and cancel seats across multiple classes (Economy, Business, and First Class) while incorporating a simple pricing and discount system for students, seniors, and regular passengers.
The system also provides various functionalities such as checking seat availability, displaying all reservation records, and calculating the total revenue generated from bookings. This system simulates an airline’s core operations in a user-friendly manner with efficient seat and passenger management.

Key Features:

1.	Reservation System:
	Users can book seats across three available classes: First Class, Business Class, and Economy Class.
  A unique passport number is used to identify each reservation, ensuring that no duplicate bookings are made.
2.	Seat Availability and Status:
  Allows customers to check available seats in each class (First, Business, Economy).
	Users can check seat status by specifying the seat class and number.
3.	Pricing and Discounts:
	Standard pricing based on class (Economy: $60, Business: $150, First Class: $300).
	Discount functionality based on customer type:
	Student: 20% discount
	Senior: 15% discount
	Regular: No discount
4.	Cancel Reservation:
	Users can cancel their reservations by providing their passport number.
	Cancelling a reservation frees up the seat for future bookings.
5.	Revenue Tracking:
	Tracks and displays total revenue from all reservations.
	Provides insight into the financial performance of the airline through ongoing bookings.
6.	Record Search by Name:
	Allows customers to search for reservations by customer name.
	Displays detailed information including passport number, destination, seat class, and price.
7.	Data Storage and Management:
	Handles up to 90 reservations and 30 seats per class.
	Automatically tracks and updates seat availability.

Limitations:

1.	Limited Seat Capacity:
	The system can handle up to 30 seats per class, and a total of 90 reservations in the system. It may not scale well for larger airline operations without modifications.
2.	Basic User Interface:
	The system operates through a console-based interface, which may not be intuitive for non-technical users.
	There are no GUI elements for users to interact with the system; everything is text-based.
3.	Single User Interaction:
	The system allows only a single user to interact with it at any given time. Multiple concurrent users cannot interact with the system simultaneously.
4.	No Advanced Error Handling:
	The system does not handle all edge cases or potential user input errors (e.g., non-numeric input for seat selection). Additional validation could be added for better robustness.
5.	No Persistence:
	All data (reservations, seat availability, revenue) is lost when the program exits. There is no integration with a database or file system for saving and restoring data.
6.	No Advanced Search Features:
	Search functionality is limited to searching by name. There is no ability to search by seat class, destination, or other attributes.

Main Menu:

![Screenshot (779)](https://github.com/user-attachments/assets/9ab3d282-e9ca-4768-9426-47936016f1a1)

Reservation Menu:

![Screenshot 2024-11-12 204544](https://github.com/user-attachments/assets/d5f2e07a-137d-421c-84ea-c8ff71d01797)

Available Seat Display:

![Screenshot 2024-11-12 204815](https://github.com/user-attachments/assets/6e8f4430-0015-4ef3-acff-a51ecd4c578e)

Total Revenue:

![Screenshot 2024-11-12 204643](https://github.com/user-attachments/assets/05b90865-307e-4e9f-a2af-6cf0d90a6dc1)

Show Records:

![Screenshot 2024-11-12 204632](https://github.com/user-attachments/assets/e0fc5a00-83d2-4050-8476-58841e3d03d6)


