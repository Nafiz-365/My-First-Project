#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SEATS 30
#define MAX_RESERVATIONS 90
#define MAX_USERS 5

struct airline {
    char passport[50];
    char name[50];
    char destination[50];
    int seat_num;
    char email[50];
    char seat_class;
    int price;
};

struct user {
    char username[50];
    char password[50];
};

struct airline reservations[MAX_RESERVATIONS];
int reservation_count = 0;
int total_revenue = 0;

int seats_z[MAX_SEATS + 1] = {0};
int seats_j[MAX_SEATS + 1] = {0};
int seats_y[MAX_SEATS + 1] = {0};

struct user users[MAX_USERS] = {
    {"admin", "admin123"},
    {"user1", "password1"},
    {"user2", "password2"},
    {"user3", "password3"},
    {"user4", "password4"}
};

void details(struct airline *reservation);
void reserve();
void cancel();
void display();
void display_record_by_name();
void show_available_seats();
void check_seat_status(char seat_prefix, int seat_num);
void display_revenue();
int get_price(char seat_class);
int is_seat_taken(char seat_prefix, int seat_num);
void remove_newline(char *str);
int apply_discount(int price);
int login();

int main() {

    int choice;
    if (!login()) {
        printf("Login failed! Exiting program...\n");
        exit(1);
    }

    do {
        printf("\n\n\t\t ***************************************************************************************");
    printf("\n\n\t\t          __|__                                                     __|__ \n");
    printf("                   --@--@--(_)--@--@--                                       --@--@--(_)--@--@-- ");
    printf("\n\t\t                                                                 ");
    printf("\n\t\t *                         Welcome to Fokir Marka Airlines LTD                         *");
    printf("\n\t\t *                      Your Comfort and Safety is Our Priority                        *");
    printf("\n\t\t *                                                                                     *");
    printf("\n\t\t ***************************************************************************************");
    printf("\n\n");
        printf("\n\n\n\t\t Please enter your choice from below:");
        printf("\n\n\t\t 1. Reservation");
        printf("\n\n\t\t 2. Cancel");
        printf("\n\n\t\t 3. Display all records");
        printf("\n\n\t\t 4. Show available seats");
        printf("\n\n\t\t 5. Check seat status");
        printf("\n\n\t\t 6. Display total revenue");
        printf("\n\n\t\t 7. Display customer record by name");
        printf("\n\n\t\t 8. EXIT");
        printf("\n\n\t\t Enter your choice :");

        scanf("%d", &choice);
        system("cls");
        switch (choice) {
            case 1:
                reserve();
                break;
            case 2:
                cancel();
                break;
            case 3:
                display();
                break;
            case 4:
                show_available_seats();
                break;
            case 5: {
                char seat_prefix;
                int seat_num;
                printf("\nEnter seat class (Z for First, J for Business, Y for Economy): ");
                scanf(" %c", &seat_prefix);
                printf("Enter seat number to check status (1-50): ");
                scanf("%d", &seat_num);
                check_seat_status(seat_prefix, seat_num);
                break;
            }
            case 6:
                display_revenue();
                break;
            case 7:
                display_record_by_name();
                break;
            case 8:
                printf("Thank you for considering Fokir Marka Airlines LTD.\n");
                exit(0);
                break;
            default:
                printf("\n\n\t SORRY INVALID CHOICE!");
                printf("\n\n\t PLEASE CHOOSE FROM 1-8");
        }
        getch();

    } while (choice != 8);

}

int login() {

    char username[50], password[50];
    int attempts = 3;

    while (attempts > 0) {
        printf("\nEnter username: ");
        fflush(stdin);
        fgets(username, sizeof(username), stdin);
        remove_newline(username);

        printf("Enter password: ");
        fflush(stdin);
        fgets(password, sizeof(password), stdin);
        remove_newline(password);

        for (int i = 0; i < MAX_USERS; i++) {
            if (strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0) {
                printf("\nLogin successful! Welcome %s.\n", username);
                return 1;  // Successful login
            }
        }

        attempts--;
        printf("\nInvalid credentials. You have %d attempt(s) remaining.\n", attempts);
    }

    return 0;

}


void remove_newline(char *str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

// The rest of the code (details, reserve, cancel, display, etc.) remains the same



void details(struct airline *reservation) {
    printf("\n\t Enter your passport number: ");
    fflush(stdin);
    fgets(reservation->passport, sizeof(reservation->passport), stdin);
    remove_newline(reservation->passport);

    printf("\n\t Enter your name: ");
    fgets(reservation->name, sizeof(reservation->name), stdin);
    remove_newline(reservation->name);

    char email_prefix[50];
    printf("\n\t Enter your email address (without @gmail.com): ");
    fgets(email_prefix, sizeof(email_prefix), stdin);
    remove_newline(email_prefix);
    snprintf(reservation->email, sizeof(reservation->email), "%s@gmail.com", email_prefix);

    printf("\n\t Enter the Destination: ");
    fgets(reservation->destination, sizeof(reservation->destination), stdin);
    remove_newline(reservation->destination);

    printf("\n\t Seat Class Options:");
    printf("\n\t - Economy (Y): $60");
    printf("\n\t - Business (J): $150");
    printf("\n\t - First Class (Z): $300");

    printf("\n\t Enter seat class (Z for First Class, J for Business, Y for Economy): ");
    scanf(" %c", &reservation->seat_class);
    reservation->seat_class = toupper(reservation->seat_class);
    reservation->price = get_price(reservation->seat_class);

    reservation->price = apply_discount(reservation->price);  // Apply discount based on customer type
}

int get_price(char seat_class) {
    switch (seat_class) {
        case 'Y': return 60;
        case 'J': return 150;
        case 'Z': return 300;
        default:
            printf("\nInvalid seat class. Setting default price to $60 (Economy).\n");
            return 60;
    }
}

int apply_discount(int price) {
    char customer_type[10];
    printf("\n\t Are you a 'student', 'senior', or 'regular' customer? ");
    fflush(stdin);
    fgets(customer_type, sizeof(customer_type), stdin);
    remove_newline(customer_type);

    if (strcasecmp(customer_type, "student") == 0) {
        price = price * 0.8;  // 20% discount
        printf("\n\t Applied 20%% student discount. Discounted price: $%d", price);
    } else if (strcasecmp(customer_type, "senior") == 0) {
        price = price * 0.85;  // 15% discount
        printf("\n\t Applied 15%% senior discount. Discounted price: $%d", price);
    } else if (strcasecmp(customer_type, "regular") == 0) {
        printf("\n\t No discount applied. Full price: $%d", price);
    } else {
        printf("\n\t Invalid type. No discount applied. Full price: $%d", price);
    }

    return price;
}

void reserve() {
    int num_seats, seat_num;
    char seat_prefix;

    printf("\nEnter the number of seats you would like to reserve: ");
    scanf("%d", &num_seats);
    fflush(stdin);

    for (int i = 0; i < num_seats; i++) {
        if (reservation_count >= MAX_RESERVATIONS) {
            printf("\nCannot reserve more seats; reservation list is full.\n");
            return;
        }

        details(&reservations[reservation_count]);

        seat_prefix = reservations[reservation_count].seat_class;
        for (seat_num = 1; seat_num <= MAX_SEATS; seat_num++) {
            if (!is_seat_taken(seat_prefix, seat_num)) {
                reservations[reservation_count].seat_num = seat_num;
                break;
            }
        }

        if (seat_num > MAX_SEATS) {
            printf("\nNo available seats in %c class for reservation %d.\n", seat_prefix, i + 1);
            continue;
        }

        switch (seat_prefix) {
            case 'Z':
                seats_z[seat_num] = 1;
                break;
            case 'J':
                seats_j[seat_num] = 1;
                break;
            case 'Y':
                seats_y[seat_num] = 1;
                break;
        }

        total_revenue += reservations[reservation_count].price;

        printf("\n\t Seat booking successful for reservation %d!", i + 1);
        printf("\n\t Seat: %c-%d", seat_prefix, reservations[reservation_count].seat_num);
        printf("\n\t Class: %c", reservations[reservation_count].seat_class);
        printf("\n\t Price: $%d\n", reservations[reservation_count].price);

        reservation_count++;
        fflush(stdin);
        printf("Press enter to continue.\n");
    }
}

void show_available_seats() {
    printf("\n++===================== Available Seats =====================++\n");

    printf("\n%-18s %-18s %-18s\n", "First Class (Z)", "Business Class (J)", "Economy Class (Y)");

    for (int i = 1; i <= MAX_SEATS; i++) {
        if (seats_z[i] == 0) {
            printf("Z-%-2d%-18s", i, " ");
        } else {
            printf(" %-18s", " ");
        }

        if (seats_j[i] == 0) {
            printf("J-%-2d%-18s", i, " ");
        } else {
            printf(" %-18s", " ");
        }

        if (seats_y[i] == 0) {
            printf("Y-%-2d\n", i);
        } else {
            printf(" %-18s\n", " ");
        }
    }

    printf("\n++============================================================++\n");
}

void check_seat_status(char seat_prefix, int seat_num) {
    int taken = 0;

    switch (seat_prefix) {
        case 'Z':
            taken = seats_z[seat_num];
            break;
        case 'J':
            taken = seats_j[seat_num];
            break;
        case 'Y':
            taken = seats_y[seat_num];
            break;
        default:
            printf("\nInvalid seat class.\n");
            return;
    }

    if (taken) {
        printf("\nSeat %c-%d is taken.\n", seat_prefix, seat_num);
    } else {
        printf("\nSeat %c-%d is available.\n", seat_prefix, seat_num);
    }
}

void cancel() {
    char passport[50];
    printf("\nEnter the passport number for the reservation to cancel: ");
    fflush(stdin);
    fgets(passport, sizeof(passport), stdin);
    remove_newline(passport);

    int found = 0;
    for (int i = 0; i < reservation_count; i++) {
        if (strcmp(reservations[i].passport, passport) == 0) {
            found = 1;
            int seat_num = reservations[i].seat_num;
            char seat_class = reservations[i].seat_class;

            switch (seat_class) {
                case 'Z': seats_z[seat_num] = 0; break;
                case 'J': seats_j[seat_num] = 0; break;
                case 'Y': seats_y[seat_num] = 0; break;
            }

            printf("\nReservation cancelled for %s.\n", reservations[i].name);
            total_revenue -= reservations[i].price;

            for (int j = i; j < reservation_count - 1; j++) {
                reservations[j] = reservations[j + 1];
            }
            reservation_count--;
            break;
        }
    }

    if (!found) {
        printf("\nReservation with passport number %s not found.\n", passport);
    }
}

void display() {
    printf("\n++======================== Reservations ========================++\n");
    for (int i = 0; i < reservation_count; i++) {
        printf("Name: %s | Passport: %s | Destination: %s | Seat: %c-%d | Class: %c | Price: $%d\n",
            reservations[i].name, reservations[i].passport, reservations[i].destination,
            reservations[i].seat_class, reservations[i].seat_num, reservations[i].seat_class, reservations[i].price);
    }
    printf("\n++============================================================++\n");
}

void display_record_by_name() {
    char name[50];
    printf("\nEnter the name of the customer to search: ");
    fflush(stdin);
    fgets(name, sizeof(name), stdin);
    remove_newline(name);

    int found = 0;
    for (int i = 0; i < reservation_count; i++) {
        if (strcasecmp(reservations[i].name, name) == 0) {
            printf("\nRecord found:\n");
            printf("Name: %s | Passport: %s | Destination: %s | Seat: %c-%d | Class: %c | Price: $%d\n",
                reservations[i].name, reservations[i].passport, reservations[i].destination,
                reservations[i].seat_class, reservations[i].seat_num, reservations[i].seat_class, reservations[i].price);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("\nNo record found for customer with name %s.\n", name);
    }
}

void display_revenue() {
    printf("\nTotal Revenue: $%d\n", total_revenue);
}

int is_seat_taken(char seat_prefix, int seat_num) {
    switch (seat_prefix) {
        case 'Z': return seats_z[seat_num];
        case 'J': return seats_j[seat_num];
        case 'Y': return seats_y[seat_num];
        default: return 0;
    }
}
