#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "blood_bank.h"

void addDonor(void)
{
    FILE *fp;
    char name[30], blood[5];
    int units;

    fp = fopen("donor.txt", "a");

    if (fp == NULL)
    {
        printf("File error!\n");
        return;
    }

    printf("\nEnter Name: ");
    scanf("%29s", name);

    printf("Enter Blood Group: ");
    scanf("%4s", blood);

    printf("Enter Units: ");
    if (scanf("%d", &units) != 1 || units <= 0)
    {
        printf("Invalid units!\n");
        fclose(fp);
        return;
    }

    fprintf(fp, "%s %s %d units\n", name, blood, units);

    fclose(fp);

    printf("Donor added successfully!\n");
}

void viewDonors(void)
{
    FILE *fp;
    char ch;

    fp = fopen("donor.txt", "r");

    if (fp == NULL)
    {
        printf("\nNo donor records found!\n");
        return;
    }

    printf("\n===== DONOR LIST =====\n");

    while ((ch = fgetc(fp)) != EOF)
    {
        printf("%c", ch);
    }

    fclose(fp);
}

void searchDonor(void)
{
    FILE *fp;
    char name[30], blood[5], search[5];
    int units, found = 0;

    fp = fopen("donor.txt", "r");

    if (fp == NULL)
    {
        printf("No records found!\n");
        return;
    }

    printf("Enter Blood Group to search: ");
    scanf("%4s", search);

    printf("\n===== SEARCH RESULTS =====\n");

    while (fscanf(fp, "%29s %4s %d units",
                  name, blood, &units) == 3)
    {
        if (strcmp(blood, search) == 0)
        {
            printf("%s %s %d units\n", name, blood, units);
            found = 1;
        }
    }

    if (found == 0)
    {
        printf("No donors found for %s\n", search);
    }

    fclose(fp);
}

void bloodAvailability(void)
{
    FILE *fp;
    char name[30], blood[5];
    int units;
    int O = 0, A = 0, B = 0, AB = 0;

    fp = fopen("donor.txt", "r");

    if (fp == NULL)
    {
        printf("No data found!\n");
        return;
    }

    while (fscanf(fp, "%29s %4s %d units",
                  name, blood, &units) == 3)
    {
        if (strcmp(blood, "O+") == 0)
            O += units;
        else if (strcmp(blood, "A+") == 0)
            A += units;
        else if (strcmp(blood, "B+") == 0)
            B += units;
        else if (strcmp(blood, "AB+") == 0)
            AB += units;
    }

    fclose(fp);

    printf("\n===== BLOOD STOCK =====\n");
    printf("O+  : %d units\n", O);
    printf("A+  : %d units\n", A);
    printf("B+  : %d units\n", B);
    printf("AB+ : %d units\n", AB);
}

void requestBlood(void)
{
    FILE *fp;
    char name[30], blood[5], search[5];
    int units, reqUnits, available = 0;

    fp = fopen("donor.txt", "r");

    if (fp == NULL)
    {
        printf("No blood data found!\n");
        return;
    }

    printf("Enter Blood Group Needed: ");
    scanf("%4s", search);

    printf("Enter Units Required: ");
    if (scanf("%d", &reqUnits) != 1 || reqUnits <= 0)
    {
        printf("Invalid units!\n");
        fclose(fp);
        return;
    }

    while (fscanf(fp, "%29s %4s %d units",
                  name, blood, &units) == 3)
    {
        if (strcmp(blood, search) == 0)
        {
            available += units;
        }
    }

    fclose(fp);

    printf("\n===== REQUEST RESULT =====\n");

    if (available >= reqUnits)
    {
        printf("REQUEST APPROVED\n");
        printf("%d units of %s available\n", reqUnits, search);
    }
    else
    {
        printf("REQUEST REJECTED\n");
        printf("Only %d units available\n", available);
    }
}

void deleteDonor(void)
{
    FILE *fp, *temp;
    char name[30], blood[5], search[30];
    int units, found = 0;

    fp = fopen("donor.txt", "r");

    if (fp == NULL)
    {
        printf("No file found!\n");
        return;
    }

    temp = fopen("temp.txt", "w");

    if (temp == NULL)
    {
        printf("Unable to create temporary file!\n");
        fclose(fp);
        return;
    }

    printf("Enter donor name to delete: ");
    scanf("%29s", search);

    while (fscanf(fp, "%29s %4s %d units",
                  name, blood, &units) == 3)
    {
        if (strcmp(name, search) != 0)
        {
            fprintf(temp, "%s %s %d units\n",
                    name, blood, units);
        }
        else
        {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp);

    if (remove("donor.txt") != 0 ||
        rename("temp.txt", "donor.txt") != 0)
    {
        printf("Error updating donor file!\n");
        return;
    }

    if (found)
        printf("Donor deleted successfully!\n");
    else
        printf("Donor not found!\n");
}

void updateDonor(void)
{
    FILE *fp, *temp;
    char name[30], blood[5], search[30];
    int units, found = 0;

    fp = fopen("donor.txt", "r");

    if (fp == NULL)
    {
        printf("No file found!\n");
        return;
    }

    temp = fopen("temp.txt", "w");

    if (temp == NULL)
    {
        printf("Unable to create temporary file!\n");
        fclose(fp);
        return;
    }

    printf("Enter name to update: ");
    scanf("%29s", search);

    while (fscanf(fp, "%29s %4s %d units",
                  name, blood, &units) == 3)
    {
        if (strcmp(name, search) == 0)
        {
            printf("Enter new blood group: ");
            scanf("%4s", blood);

            printf("Enter new units: ");

            if (scanf("%d", &units) != 1 || units <= 0)
            {
                printf("Invalid units!\n");
                fclose(fp);
                fclose(temp);
                remove("temp.txt");
                return;
            }

            found = 1;
        }

        fprintf(temp, "%s %s %d units\n",
                name, blood, units);
    }

    fclose(fp);
    fclose(temp);

    if (!found)
    {
        remove("temp.txt");
        printf("Donor not found!\n");
        return;
    }

    if (remove("donor.txt") != 0 ||
        rename("temp.txt", "donor.txt") != 0)
    {
        printf("Error updating donor file!\n");
        return;
    }

    printf("Donor updated successfully!\n");
}

void stockReport(void)
{
    FILE *fp;
    char name[30], blood[5], text[10];
    int units;

    int Aplus = 0, Bplus = 0, Oplus = 0, ABplus = 0;

    fp = fopen("donor.txt", "r");

    if (fp == NULL)
    {
        printf("No data found!\n");
        return;
    }

    while (fscanf(fp, "%29s %4s %d %9s",
                  name, blood, &units, text) == 4)
    {
        if (strcmp(blood, "A+") == 0)
            Aplus += units;
        else if (strcmp(blood, "B+") == 0)
            Bplus += units;
        else if (strcmp(blood, "O+") == 0)
            Oplus += units;
        else if (strcmp(blood, "AB+") == 0)
            ABplus += units;
    }

    fclose(fp);

    printf("\n===== BLOOD STOCK REPORT =====\n");
    printf("A+  : %d units\n", Aplus);
    printf("B+  : %d units\n", Bplus);
    printf("O+  : %d units\n", Oplus);
    printf("AB+ : %d units\n", ABplus);
}