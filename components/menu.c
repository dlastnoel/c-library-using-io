// headers
#include <stdio.h>

void loadMenu()
{
  int choice;
  printf("----------------------------\n");
  printf("Welcome to the library!\n");
  printf("----------------------------\n\n");
  printf("Select the number of the function you wish to execute\n");
  printf("[1] Create new customer\n");
  printf("[2] Deposit money to a customer\n");
  printf("[3] Add new book\n");
  printf("[4] Rent a book\n");
  printf("[5] Deliver a book\n");
  printf("[6] Burn a book\n");
  printf("[7] Update customer information\n");
  printf("[8] Update book information\n");
  printf("[9] List of customers who rented a book\n");
  printf("[10] List of customers\n");
  printf("[11] List of books\n");
  printf("[0] Exit\n\n");

  printf("Selection: ");
  scanf("%d", &choice);

  while (choice < 0 || choice >= 12)
  {
    printf("Selection unknown. Please enter only what is shown from the menu\n");
    printf("Selection: ");
    scanf("%d", &choice);
  }
  route(choice);
}