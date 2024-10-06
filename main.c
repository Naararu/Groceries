#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// FINAL PROJECT
// Case : Groceries
// Team : Golden Hour
// Name :
// Alfin Syaghaf Rifai - 2602181364
// Annisa'U Rahma - 2602181603
// Nabila Shifa Putri - 2602183584

// structure for groceries items
struct groceries
{
    int record;        // record of the data
    char category[50]; // category string name
    char gName[50];    // product name
    int quantity;      // int quantity
    float price;       // price with float
    int aisle;         // aisle of the product

} gData[1000];

// global index to count the record from the data
int globalCount;

void quickSort(int left,int right,struct groceries *gData)
{
    int i, j, pivot;

    if (left < right)
    {
        pivot = left;
        i = left;
        j = right;

        while (i < j)
        {
            while (gData[i].record >= gData[pivot].record && i < right)
            {
                i++;
            }
            while (gData[j].record < gData[pivot].record)
            {
                j--;
            }
            if (i < j)
            {
                struct groceries temp = gData[i];
                gData[i] = gData[j];
                gData[j] = temp;
            }
        }

        struct groceries temp = gData[pivot];
        gData[pivot] = gData[j];
        gData[j] = temp;

        quickSort(left, j - 1, gData);
        quickSort(j + 1, right,gData);
    }
}

void showItems()
{
    // print the tittle of data
    // printf("\n");
    system("cls");
    
    printf("Record\t\tCategory\t\tProduct Name\t\tQuantity\tPrice\t\tAisle\n");
    printf("=================================================================================================================\n");
    
    //for showing list of the data
    for (int i = 0; i < globalCount; i++)
    {
        quickSort(i, i - 1, gData);
        if (strlen(gData[i].gName) > 8 || strlen(gData[i].category) > 8)
        {
            printf(" %d\t\t%s\t\t%s\t\t%d\t\t%.3f\t\t%d\n", gData[i].record, gData[i].category, gData[i].gName, gData[i].quantity, gData[i].price, gData[i].aisle);
        }
        else
        {
            printf(" %d\t\t%s\t\t\t%s\t\t\t%d\t\t%.3f\t\t%d\n", gData[i].record, gData[i].category, gData[i].gName, gData[i].quantity, gData[i].price, gData[i].aisle);
        }
    }
    // for spacing before return to menu
    system("pause");
    system("cls");
}

void createItem()
{
    FILE *fp;
    fp = fopen("groceries.txt", "a");

    system("cls");
    printf("--------- Add New item To Data ---------\n");
    printf("Input the Record : ");
    scanf("%d", &gData[globalCount].record);
    getchar();

    for (int i = 0; i < globalCount; i++)
    {
        if(gData[globalCount].record == gData[i].record) {
            printf("System : Record already exist!\n");
            printf("System : Returning to main menu...\n");
            system("pause");
            system("cls");
            break;
        }   
    }

    printf("Input the category of the item : ");
    scanf("%s", gData[globalCount].category);
    getchar();

    printf("Input the Product Name : ");
    scanf("%[^\n]", gData[globalCount].gName);
    getchar();

    printf("Input the quantity of the items : ");
    scanf("%d", &gData[globalCount].quantity);
    getchar();

    printf("Input the price of the items (exampe : 25 in the data it wil 25.000): ");
    scanf("%f", &gData[globalCount].price);
    getchar();

    printf("Input the aisle that you want to put this item on it: ");
    scanf("%d", &gData[globalCount].aisle);
    getchar();

    
    
    fprintf(fp, "%d,%s,%s,%d,%.3f,%d\n", gData[globalCount].record, gData[globalCount].category, gData[globalCount].gName, gData[globalCount].quantity, gData[globalCount].price, gData[globalCount].aisle);
    fclose(fp);
    globalCount++;
    quickSort(0, globalCount - 1, gData);
    printf("\n\nSystem : Succesfuly added new item!\n");
    system("pause");
    system("cls");
}

void updateItem()
{
    bool exist = false;
    FILE *fp;
    fp = fopen("groceries.txt", "w");
    int record;

    system("cls");
    printf("--------- Update Quantity & Price ---------\n");
    printf("Choose record of data : ");
    scanf("%d", &record);
    getchar();

    for (int i = 0; i <= globalCount; i++)
    {
        if(record == gData[i].record) {
        
            printf("Input new Quantity : ");
            scanf("%d", &gData[i].quantity); getchar();

            printf("Input new price : ");
            scanf("%f", &gData[i].price); getchar();

            fprintf(fp, "RECORD,CATEGORY,NAMA,QUANTITY,PRICE,AISLE\n");
            for(int j = i; j < globalCount; j++) {
                fprintf(fp, "%d,%s,%s,%d,%.3f,%d\n", gData[j].record, gData[j].category, gData[j].gName, gData[j].quantity, gData[j].price, gData[j].aisle);
            }
            fclose(fp);
            printf("System : Data Succesfully Updated!\n");
            system("pause");
            system("cls");
            exist = true;
        } 
    }
    if(exist == false) {
        printf("System : Record doesn't exist!\n");
        printf("System : returning to main menu...\n");
        system("pause");
        system("cls");
    }
}

void editItem()
{
    bool exist = false;
    FILE *fp;
    fp = fopen("groceries.txt", "r+");
    int record;

    system("cls");
    printf("----------------- Edit data -----------------\n");
    printf("Choose record of data you want to edit : ");
    scanf("%d", &record);

    for (int i = 0; i <= globalCount; i++)
    {
        if(record == gData[i].record) {
            system("cls");
            printf("Input new record : ");
            scanf("%d", &gData[i].record);
            getchar();

            printf("Input new category : ");
            scanf("%s", gData[i].category);
            getchar();

            printf("Input new Groceries name : ");
            scanf("%[^\n]", gData[i].gName);
            getchar();

            printf("Input the new quantity : ");
            scanf("%d", &gData[i].quantity);
            getchar();

            printf("Input the new price : ");
            scanf("%f", &gData[i].price);
            getchar();

            printf("Input new aisle for the item : ");
            scanf("%d", &gData[i].aisle);
            getchar();
            
            fprintf(fp, "RECORD,CATEGORY,NAMA,QUANTITY,PRICE,AISLE\n");
            for(int j = i; j < globalCount; j++) {
                fprintf(fp, "%d,%s,%s,%d,%.3f,%d\n", gData[j].record, gData[j].category, gData[j].gName, gData[j].quantity, gData[j].price, gData[j].aisle);
            }
            fclose(fp);

            printf("System : Data succesfully got edited!");
            system("pause");
            exist = true;
            system("cls");
            
        }
    }
    if(exist == false){
        printf("System : Record doesn't exist!\n");
        printf("System : returning to main menu...\n");
        system("pause");
        system("cls");
    }
}

void deleteItem()
{
    FILE *fp;
    fp = fopen("groceries.txt", "w");
    int record;

    printf("Input record of data you want to delete : ");
    scanf("%d", &record);

    for (int i = 0; i < globalCount; i++)
    {
        if(record == gData[i].record) {
            gData[i] = gData[i + 1];
            break;
        }
    }
    globalCount--;

    fprintf(fp, "RECORD,CATEGORY,NAMA,QUANTITY,PRICE,AISLE\n");
    for (int i = 0; i < globalCount; i++)
    {
        fprintf(fp, "%d,%s,%s,%d,%.3f,%d\n", gData[i].record, gData[i].category, gData[i].gName, gData[i].quantity, gData[i].price, gData[i].aisle);
    }
    fclose(fp);
    system("cls");
}

void searchItem() {
    
    char itemName[100];
    printf("Input the name of grocery item : ");
    scanf("%[^\n]", itemName);

    bool exist = false;
    system("cls");
    for (int i = 0; i < globalCount; i++)
    {
        if(strcmp(itemName, gData[i].gName) == 0) {
            
            printf("--------- Item Found ---------\n");
            printf("Record      : %d\n", gData[i].record);
            printf("Category    : %s\n", gData[i].category);
            printf("Item Name   : %s\n", gData[i].gName);
            printf("Quantity    : %d\n", gData[i].quantity);
            printf("Price       : %.3f\n", gData[i].price);
            printf("Aisle       : %d\n", gData[i].aisle);
            exist = true;
            system("pause");
        }    
    }

    if(exist == false) {
        printf("System : item doesn't exist!\n");
        printf("System : returning to main menu...\n");
        system("pause");
        system("cls");
    }

}

// main function
int main()
{
    // program start with global index 0, to make sure the count was right...
    globalCount = 0;
    // checking data
    FILE *fp;
    fp = fopen("groceries.txt", "r");
    // if data not found
    if (fp == NULL)
    {
        printf("==============================================\n");
        printf("System : Error data not found!\n");
        printf("System : Creating a new one!\n");
        printf("System : Returning to main menu...\n");
        printf("==============================================\n");
        fp = fopen("groceries.txt", "w"); // creating a new data file
        fprintf(fp, "RECORD,CATEGORY,NAMA,QUANTITY,PRICE,AISLE\n");
        fclose(fp); // closing file
        system("pause");
        system("cls");
    }

    // dump variable for name in the data
    char a1[10], a2[10], a3[10], a4[10], a5[10], a6[10];
    // scanf the first line (name for the data)
    fscanf(fp, "%[^,],%[^,],%[^,],%[^,],%[^,],%s\r\n", a1, a2, a3, a4, a5, a6);
    // if data found, increment globalcount to count the record of the data
    while (fscanf(fp, "%d,%[^,],%[^,],%d,%f,%d\r\n", &gData[globalCount].record, gData[globalCount].category, gData[globalCount].gName, &gData[globalCount].quantity, &gData[globalCount].price, &gData[globalCount].aisle) != EOF)
    {
        globalCount++;
    }
    fclose(fp); // close the file...

    // Displaying Management Menu System
    int answer; // for choosing in switch case
    while (answer != 0)
    { // looping until the integer answer = 0
        printf("==============================================\n");
        printf("          Groceries Store Management          \n");
        printf("==============================================\n");
        printf("1. Show all available groceries items\n2. Add New Groceries Item\n3. Update quantity & price items\n4. Edit groceries items\n5. Delete a groceries item\n6. Search item\n0. Exit the program\n");
        printf("Choose => ");
        scanf("%d", &answer);
        getchar();

        // switch case method
        switch (answer)
        {
            case 1:
            {
                showItems();
                break;
            }
            case 2:
            {
                createItem();
                break;
            }
            case 3:
            {
                updateItem();
                break;
            }
            case 4:
            {
                editItem();
                break;
            }
            case 5:
            {
                deleteItem();
                break;
            }
            case 6:
            {
            searchItem();
                break;
            }
            case 0:
            {
                break;
            }
            default:
            { // if you choose number that not on the menu
                printf("system : Choose the right number!\n");
                system("pause");
                system("cls");
                break;
            }
        }
    }
    // if you leave the program...
    printf("You choose to exit the program, have a good day!");
    return 0;
}
