#include <stdio.h>
#include <stdlib.h>

void route(int choice)
{
  switch (choice)
  {
  case 0:
    exit(0);
    break;
  case 1:
    createCustomer();
    break;
  case 2:
    depositMoney();
    break;
  case 3:
    addNewBook();
    break;
  case 4:
    bookRent();
    break;
  case 5:
    deliverBook();
    break;
  case 6:
    break;
  case 7:
    updateCustomer();
    break;
  case 8:
    updateBook();
    break;
  case 9:
    displayRentedBooks();
    break;
  case 10:
    displayCustomers();
    break;
  case 11:
    displayBooks();
    break;
  }
}

void navigate(int choice)
{
  char answer;
  printf("Do another? (y/n): ");
  scanf("%s", &answer);
  if (answer == 'y' || answer == 'Y')
  {
    route(choice);
  }
  else
  {
    system("cls");
    loadMenu();
  }
}

void backtoMenu()
{
  int choice;
  printf("\nEnter '0' to go back to menu: ");
  scanf("%d", &choice);

  while (choice != 0)
  {
    printf("Input unknown. Only 0 is accepted");
    printf("Selection: ");
    scanf("%d", &choice);
  }
  system("cls");
  loadMenu();
}