#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "blood_bank.h"

int login(void)
{
    char user[20], pass[20];

    printf("===== LOGIN =====\n");

    printf("Enter Username: ");
    scanf("%19s", user);

    printf("Enter Password: ");
    scanf("%19s", pass);

    if (strcmp(user, "Arjun") == 0 &&
        strcmp(pass, "2005") == 0)
    {
        printf("Login Successful!\n");
        return 1;
    }
    else
    {
        printf("Invalid Login!\n");
        return 0;
    }
}

int main(void)
{
    int choice;

    if (login() == 0)
    {
        return 0;
    }

    while (1)
    {
        printf("\n===== BLOOD BANK SYSTEM =====\n");
        printf("1. Add Donor\n");
        printf("2. View Donors\n");
        printf("3. Search Donor\n");
        printf("4. Blood Availability\n");
        printf("5. Request Blood\n");
        printf("6. Delete Donor\n");
        printf("7. Update Donor\n");
        printf("8. Stock Report\n");
        printf("9. Exit\n");

        printf("Enter choice: ");

        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input!\n");
            return 1;
        }

        switch (choice)
        {
            case 1:
                addDonor();
                break;

            case 2:
                viewDonors();
                break;

            case 3:
                searchDonor();
                break;

            case 4:
                bloodAvailability();
                break;

            case 5:
                requestBlood();
                break;

            case 6:
                deleteDonor();
                break;

            case 7:
                updateDonor();
                break;

            case 8:
                stockReport();
                break;

            case 9:
                printf("Exiting Blood Bank System.\n");
                return 0;

            default:
                printf("Invalid choice!\n");
        }
    }
}