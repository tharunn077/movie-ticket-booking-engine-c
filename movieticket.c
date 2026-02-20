#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GOLD_RATE 150
#define SILVER_RATE 100
#define ECONOMY_RATE 30
#define TAX_RATE 30

struct Node {
    int seat_number;
    int tier;
    int booked;
    struct Node* next;
};

struct Node* initializeSeats() {
    struct Node* head = NULL;
    int gold_seats = 50;
    int silver_seats = 70;
    int economy_seats = 30;
    int total_seats = gold_seats + silver_seats + economy_seats;

    for (int i = 1; i <= total_seats; i++) {
        struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
        newNode->seat_number = i;
        if (i <= gold_seats) {
            newNode->tier = 1;
        } else if (i <= gold_seats + silver_seats) {
            newNode->tier = 2;
        } else {
            newNode->tier = 3;
        }
        newNode->next = head;
        newNode->booked = 0;
        head = newNode;
    }

    return head;
}

void displayAvailableSeats(struct Node* head) {
    printf("Available Seats before booking:\n");
    printf("Gold Tier: 1-50\n");
    printf("Silver Tier: 51-120\n");
    printf("Economy Tier: 121-150\n");
}

void bookSingleTicket(struct Node* head, int seat_number, int tier, int apply_discount) {
    struct Node* temp = head;
    while (temp != NULL) {
        if (temp->seat_number == seat_number && temp->tier == tier) {
            if (temp->booked) {
                printf("Seat %d is already booked.\n", seat_number);
                return;
            }
            if (apply_discount) {
                int tier_price = (temp->tier == 1) ? GOLD_RATE : (temp->tier == 2) ? SILVER_RATE : ECONOMY_RATE;
                int discounted_price = (tier_price * 50) / 100;
                printf("You have got 50%% cashback.Money will be credited soon.. Discounted price: %d\n", discounted_price);
            }
            temp->booked = 1;
            printf("Ticket booked successfully for seat %d.\n", seat_number);
            return;
        }
        temp = temp->next;
    }
    printf("Seat %d not found in the specified tier.\n", seat_number);
}

void bookGroupTickets(struct Node* head, int num_seats, int tier, int apply_discount) {
    int booked = 0;
    struct Node* temp = head;
    int discounted_price;
    int total_price = 0;
    while (temp != NULL && booked < num_seats) {
        if (temp->tier == tier && !temp->booked) {
            total_price += (temp->tier == 1) ? GOLD_RATE : (temp->tier == 2) ? SILVER_RATE : ECONOMY_RATE;
            booked++;
        }
        temp = temp->next;
    }

    if (apply_discount) {
        if (tier == 1)
            discounted_price = (total_price * 80) / 100;
        else
            discounted_price = (total_price * 90) / 100;
        printf("Coupon for 20%% cashback for tier 1 or 10%% cashback for tier 2 and 3 has been applied successfully.Money will be credited soon..Total discounted price: %d\n", discounted_price);
    }

    booked = 0;
    temp = head;
    while (temp != NULL && booked < num_seats) {
        if (temp->tier == tier && !temp->booked) {
            if (apply_discount)
                temp->booked = 2;
            else
                temp->booked = 1;
            printf("Ticket booked successfully for seat %d.\n", temp->seat_number);
            booked++;
        }
        temp = temp->next;
    }

    if (booked < num_seats) {
        printf("Could not book %d tickets in the specified tier.\n", num_seats - booked);
    }
}

void displayInformation(struct Node* head) {
    printf("Ticket Information:\n");
    printf("Tier\tSeat Number\tPrice without Tax\tPrice with Tax\n");
    struct Node* temp = head;
    int total_amount = 0;
    while (temp != NULL) {
        if (temp->booked) {
            int tier_price = (temp->tier == 1) ? GOLD_RATE : (temp->tier == 2) ? SILVER_RATE : ECONOMY_RATE;
            int price_with_tax = tier_price + TAX_RATE;
            printf("%s\t%d\t\t%d\t\t\t%d\n", (temp->tier == 1) ? "Gold" : (temp->tier == 2) ? "Silver" : "Economy",
                   temp->seat_number, tier_price, price_with_tax);
            total_amount += price_with_tax;
        }
        temp = temp->next;
    }
    printf("Total Amount (with tax) for the booked seats: %d\n", total_amount);
}

int main() {
    struct Node* head = initializeSeats();
    int choice;
    char coupon_code[10];
    int rate;
    do {
        printf("\nWELCOME TO SPYDAR CINEMAS:\n");
        printf("1. Book a single ticket\n");
        printf("2. Book group tickets\n");
        printf("3. Display tickets\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
    displayAvailableSeats(head);
    printf("Enter seat number and tier (1 for Gold(RS.150), 2 for Silver(RS.100), 3 for Economy(RS.30): ");
    int seat_number, tier;
    scanf("%d %d", &seat_number, &tier);
    printf("Do you have a coupon? (yes/no): ");
    scanf("%s", coupon_code);
    if (strcmp(coupon_code, "yes") == 0) {
        printf("Enter coupon code: ");
        scanf("%s", coupon_code);
        if (strcmp(coupon_code, "CASH50") == 0) {
            bookSingleTicket(head, seat_number, tier, 1);
        } else {
            printf("Invalid coupon code.\n");
            bookSingleTicket(head, seat_number, tier, 0);
        }
    } else {
        bookSingleTicket(head, seat_number, tier, 0);
    }
    break;
case 2:
    printf("Enter number of seats and tier (1 for Gold, 2 for Silver, 3 for Economy): ");
    int num_seats, group_tier;
    scanf("%d %d", &num_seats, &group_tier);
    printf("Do you have a coupon? (yes/no): ");
    scanf("%s", coupon_code);
    if (strcmp(coupon_code, "yes") == 0) {
        printf("Enter coupon code: ");
        scanf("%s", coupon_code);
        if (strcmp(coupon_code, "GROUP20") == 0) {
            bookGroupTickets(head, num_seats, group_tier, 1);
        } else {
            printf("Invalid coupon code.\n");
            bookGroupTickets(head, num_seats, group_tier, 0);
        }
    } else {
        bookGroupTickets(head, num_seats, group_tier, 0);
    }
    break;


            case 3:
                displayInformation(head);
                break;
            case 4:
                printf("Thanks for booking\n");
                printf("Rate us from 1-5: ");
                scanf("%d", &rate);
                if (rate == 1 || rate == 2) {
                    printf("Sorry for the poor experience... We are currently working on the flaws to improve the service\n");
                } else if (rate == 3) {
                    printf("We are trying our best to improve the service.\n");
                } else {
                    printf("Thanks for your positive feedback!\n");
                }
                break;
            default:
                printf("Invalid choice. Please enter a number between 1 and 4.\n");
        }
    } while (choice != 4);

    return 0;
}
