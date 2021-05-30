// headers
#include <stdio.h>

// structure
#include "../structures/customer.h"

void createCustomer()
{
  FILE *data = fopen(getCustomersFilePath(), "r");
  struct customer new_customer;
  new_customer.id = getStructureID(data);

  fclose(data);
  data = fopen(getCustomersFilePath(), "a");
  printf("\n--------------------------\n");
  printf("Create new customer loaded\n");
  printf("--------------------------\n");

  printf("Enter new customer's name: ");
  scanf(" %[^\t\n]s", &new_customer.firstname);
  printf("Surname: ");
  scanf(" %[^\t\n]s", &new_customer.surname);
  printf("Age: ");
  scanf("%d", &new_customer.age);
  new_customer.wallet = 0;

  fprintf(data, "%d %s %s %d %d\n", new_customer.id, new_customer.firstname, new_customer.surname, new_customer.age, new_customer.wallet);
  fclose(data);
  printf("Customer %s %s added successfully\n", new_customer.firstname, new_customer.surname);

  navigate(1);
}

void depositMoney()
{
  FILE *dataRead = fopen(getCustomersFilePath(), "r");
  FILE *dataWrite = fopen(getCustomersTempPath(), "w");
  struct customer my_customer;
  int found = 0;
  int id;
  int wallet;
  printf("\n--------------------\n");
  printf("Deposit money loaded\n");
  printf("--------------------\n\n");
  printf("Enter customer id: ");
  scanf("%d", &id);

  rewind(dataRead);
  while (fscanf(dataRead, "%d %s %s %d %d\n", &my_customer.id, &my_customer.firstname, &my_customer.surname, &my_customer.age, &my_customer.wallet) != EOF)
  {
    if (id == my_customer.id)
    {
      found = 1;
      printf("Amount to deposit: ");
      scanf("%d", &wallet);
      my_customer.wallet += wallet;
      fprintf(dataWrite, "%d %s %s %d %d\n", my_customer.id, my_customer.firstname, my_customer.surname, my_customer.age, my_customer.wallet);
    }
    else
    {
      fprintf(dataWrite, "%d %s %s %d %d\n", my_customer.id, my_customer.firstname, my_customer.surname, my_customer.age, my_customer.wallet);
    }
  }

  fclose(dataRead);
  fclose(dataWrite);
  dataRead = fopen(getCustomersFilePath(), "w");
  dataWrite = fopen(getCustomersTempPath(), "r");
  while (fscanf(dataWrite, "%d %s %s %d %d\n", &my_customer.id, &my_customer.firstname, &my_customer.surname, &my_customer.age, &my_customer.wallet) != EOF)
  {
    fprintf(dataRead, "%d %s %s %d %d\n", my_customer.id, my_customer.firstname, my_customer.surname, my_customer.age, my_customer.wallet);
  }
  fclose(dataRead);
  fclose(dataWrite);

  if (found == 0)
  {
    printf("Customer id not found\n");
  }
  else
  {
    printf("Money deposit was successful");
  }
  remove(getCustomersTempPath());
  navigate(2);
}

void updateCustomer()
{
  FILE *dataRead = fopen(getCustomersFilePath(), "r");
  FILE *dataWrite = fopen(getCustomersTempPath(), "w");
  struct customer my_customer;
  int found = 0;
  int id;
  printf("\n----------------------\n");
  printf("Update customer loaded\n");
  printf("----------------------\n\n");
  printf("Enter customer id: ");
  scanf("%d", &id);

  rewind(dataRead);
  while (fscanf(dataRead, "%d %s %s %d %d\n", &my_customer.id, &my_customer.firstname, &my_customer.surname, &my_customer.age, &my_customer.wallet) != EOF)
  {
    if (id == my_customer.id)
    {
      found = 1;
      printf("Enter new customer's name: ");
      scanf(" %[^\t\n]s", &my_customer.firstname);
      printf("Surname: ");
      scanf(" %[^\t\n]s", &my_customer.surname);
      printf("Age: ");
      scanf("%d", &my_customer.age);
      fprintf(dataWrite, "%d %s %s %d %d\n", my_customer.id, my_customer.firstname, my_customer.surname, my_customer.age, my_customer.wallet);
    }
    else
    {
      fprintf(dataWrite, "%d %s %s %d %d\n", my_customer.id, my_customer.firstname, my_customer.surname, my_customer.age, my_customer.wallet);
    }
  }

  fclose(dataRead);
  fclose(dataWrite);
  dataRead = fopen(getCustomersFilePath(), "w");
  dataWrite = fopen(getCustomersTempPath(), "r");
  while (fscanf(dataWrite, "%d %s %s %d %d\n", &my_customer.id, &my_customer.firstname, &my_customer.surname, &my_customer.age, &my_customer.wallet) != EOF)
  {
    fprintf(dataRead, "%d %s %s %d %d\n", my_customer.id, my_customer.firstname, my_customer.surname, my_customer.age, my_customer.wallet);
  }
  fclose(dataRead);
  fclose(dataWrite);
  if (found == 0)
  {
    printf("Customer id not found\n");
  }
  else
  {
    printf("Customer information updated successfully");
  }
  remove(getBooksTempPath());
  navigate(7);
}

void displayCustomers()
{
  FILE *data = fopen(getCustomersFilePath(), "r");
  int found = 0;
  struct customer my_customer;
  printf("\n-------------------\n");
  printf("List of Customers\n");
  printf("------------------\n\n");

  printf("Customer ID\tFirstname\t\t\t\tSurname\t\t\t\t\tAge\t\tWallet\n");
  while (fscanf(data, "%d %s %s %d %d\n", &my_customer.id, &my_customer.firstname, &my_customer.surname, &my_customer.age, &my_customer.wallet) != EOF)
  {
    found = 1;
    printf("%d\t\t%s\t\t\t\t\t%s\t\t\t\t\t%d\t\t%d\n", my_customer.id, my_customer.firstname, my_customer.surname, my_customer.age, my_customer.wallet);
  }
  if (found == 0)
  {
    printf("records are empty\n");
  }
  fclose(data);
  backtoMenu();
}