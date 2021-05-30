#include <stdio.h>

// structures
#include "../structures/customer.h"
#include "../structures/book.h"
#include "../structures/rent.h"

void bookRent()
{
  FILE *customerData = fopen(getCustomersFilePath(), "r");
  FILE *customerTemp = fopen(getCustomersTempPath(), "w");
  FILE *bookData = fopen(getBooksFilePath(), "r");
  FILE *bookTemp = fopen(getBooksTempPath(), "w");
  FILE *rentData = fopen(getRentsFilePath(), "r");
  FILE *appendRentData = fopen(getRentsFilePath(), "a");
  int customer_id;
  int book_id;

  struct book my_book;
  struct customer my_customer;
  struct rent new_rent;
  new_rent.id = getStructureID(rentData);

  printf("\n------------------\n");
  printf("Rent a book loaded");
  printf("\n------------------\n");
  printf("Enter book id: ");
  scanf("%d", &book_id);

  while (fscanf(bookData, "%d %s %s %d %d %s\n", &my_book.id, &my_book.name, &my_book.author, &my_book.age_limit, &my_book.price, &my_book.is_rented) != EOF)
  {
    if (book_id == my_book.id)
    {
      break;
    }
  }
  rewind(bookData);

  if (book_id != 0)
  {
    if (!strcmp(my_book.is_rented, "false"))
    {
      printf("Enter customer id: ");
      scanf("%d", &customer_id);

      while (fscanf(customerData, "%d %s %s %d %d\n", &my_customer.id, &my_customer.firstname, &my_customer.surname, &my_customer.age, &my_customer.wallet) != EOF)
      {
        if (customer_id == my_customer.id)
        {
          break;
        }
      }
      rewind(customerData);

      if (customer_id != 0)
      {
        if (my_book.age_limit < my_customer.age)
        {
          if (my_customer.wallet >= my_book.price)
          {
            new_rent.book_id = my_book.id;
            new_rent.customer_id = my_customer.id;
            printf("Rent date: ");
            scanf(" %[^\t\n]s", &new_rent.date);
            printf("How long? (in weeks): ");
            scanf("%d", &new_rent.weeks);
            if (my_customer.wallet >= (my_book.price * new_rent.weeks))
            {
              fprintf(appendRentData, "%d %d %d %s %d\n", new_rent.id, new_rent.customer_id, new_rent.book_id, new_rent.date, new_rent.weeks);
              fclose(appendRentData);
              printf("Book %s is rented by %s %s\n", my_book.name, my_customer.firstname, my_customer.surname);

              // update customer wallet
              while (fscanf(customerData, "%d %s %s %d %d\n", &my_customer.id, &my_customer.firstname, &my_customer.surname, &my_customer.age, &my_customer.wallet) != EOF)
              {
                if (customer_id == my_customer.id)
                {
                  my_customer.wallet -= (my_book.price * new_rent.weeks);
                  fprintf(customerTemp, "%d %s %s %d %d\n", my_customer.id, my_customer.firstname, my_customer.surname, my_customer.age, my_customer.wallet);
                }
                else
                {
                  fprintf(customerTemp, "%d %s %s %d %d\n", my_customer.id, my_customer.firstname, my_customer.surname, my_customer.age, my_customer.wallet);
                }
              }
              fclose(customerData);
              fclose(customerTemp);
              customerData = fopen(getCustomersFilePath(), "w");
              customerTemp = fopen(getCustomersTempPath(), "r");
              while (fscanf(customerTemp, "%d %s %s %d %d\n", &my_customer.id, &my_customer.firstname, &my_customer.surname, &my_customer.age, &my_customer.wallet) != EOF)
              {
                fprintf(customerData, "%d %s %s %d %d\n", my_customer.id, my_customer.firstname, my_customer.surname, my_customer.age, my_customer.wallet);
              }
              fclose(customerData);
              fclose(customerTemp);

              // update book rented
              while (fscanf(bookData, "%d %s %s %d %d %s\n", &my_book.id, &my_book.name, &my_book.author, &my_book.age_limit, &my_book.price, &my_book.is_rented) != EOF)
              {
                if (book_id == my_book.id)
                {
                  strcpy(my_book.is_rented, "true");
                  fprintf(bookTemp, "%d %s %s %d %d %s\n", my_book.id, my_book.name, my_book.author, my_book.age_limit, my_book.price, my_book.is_rented);
                }
                else
                {
                  fprintf(bookTemp, "%d %s %s %d %d %s\n", my_book.id, my_book.name, my_book.author, my_book.age_limit, my_book.price, my_book.is_rented);
                }
              }

              fclose(bookData);
              fclose(bookTemp);
              bookData = fopen(getBooksFilePath(), "w");
              bookTemp = fopen(getBooksTempPath(), "r");
              while (fscanf(bookTemp, "%d %s %s %d %d %s\n", &my_book.id, &my_book.name, &my_book.author, &my_book.age_limit, &my_book.price, &my_book.is_rented) != EOF)
              {
                fprintf(bookData, "%d %s %s %d %d %s\n", my_book.id, my_book.name, my_book.author, my_book.age_limit, my_book.price, my_book.is_rented);
              }
              fclose(bookData);
              fclose(bookTemp);
            }
            else
            {
              printf("Customer hasa insufficient balance to rent this book.\n");
            }
          }
          else
          {
            printf("Customer hasa insufficient balance to rent this book.\n");
          }
        }
        else
        {
          printf("Customer is not allowed to rent this book.\n");
        }
      }
      else
      {
        printf("Customer id is unknown\n");
      }
    }
    else
    {
      printf("Book is currently rented\n");
    }
  }
  else
  {
    printf("Book id is unknown\n");
  }
  remove(getBooksTempPath);
  remove(getCustomersTempPath);
  navigate(4);
}

void deliverBook()
{

  FILE *customerData = fopen(getCustomersFilePath(), "r");
  FILE *customerTemp = fopen(getCustomersTempPath(), "w");
  FILE *bookData = fopen(getBooksFilePath(), "r");
  FILE *bookTemp = fopen(getBooksTempPath(), "w");
  FILE *rentData = fopen(getRentsFilePath(), "r");

  struct book my_book;
  struct customer my_customer;
  struct rent my_rent;

  int customer_id;
  int book_id;
  int book_price;
  int rent_id;
  int remaining_weeks;

  printf("\n---------------------\n");
  printf("Deliver a book loaded\n");
  printf("---------------------\n\n");

  printf("Enter rent id: ");
  scanf("%d", &rent_id);

  while (fscanf(rentData, "%d %d %d %s %d\n", &my_rent.id, &my_rent.customer_id, &my_rent.book_id, &my_rent.date, &my_rent.weeks) != EOF)
  {
    if (rent_id == my_rent.id)
    {
      customer_id = my_rent.customer_id;
      book_id = my_rent.book_id;
      break;
    }
    else
    {
      rent_id = 0;
    }
  }

  if (rent_id != 0)
  {
    printf("Remaining weeks: ");
    scanf("%d", &remaining_weeks);

    // update book not rented
    while (fscanf(bookData, "%d %s %s %d %d %s\n", &my_book.id, &my_book.name, &my_book.author, &my_book.age_limit, &my_book.price, &my_book.is_rented) != EOF)
    {
      if (book_id == my_book.id)
      {
        strcpy(my_book.is_rented, "false");
        book_price = my_book.price;
        fprintf(bookTemp, "%d %s %s %d %d %s\n", my_book.id, my_book.name, my_book.author, my_book.age_limit, my_book.price, my_book.is_rented);
      }
      else
      {
        fprintf(bookTemp, "%d %s %s %d %d %s\n", my_book.id, my_book.name, my_book.author, my_book.age_limit, my_book.price, my_book.is_rented);
      }
    }

    fclose(bookData);
    fclose(bookTemp);
    bookData = fopen(getBooksFilePath(), "w");
    bookTemp = fopen(getBooksTempPath(), "r");
    while (fscanf(bookTemp, "%d %s %s %d %d %s\n", &my_book.id, &my_book.name, &my_book.author, &my_book.age_limit, &my_book.price, &my_book.is_rented) != EOF)
    {
      fprintf(bookData, "%d %s %s %d %d %s\n", my_book.id, my_book.name, my_book.author, my_book.age_limit, my_book.price, my_book.is_rented);
    }
    fclose(bookData);
    fclose(bookTemp);
    remove(getBooksTempPath());

    if (remaining_weeks != 0)
    {
      // update customer wallet
      while (fscanf(customerData, "%d %s %s %d %d\n", &my_customer.id, &my_customer.firstname, &my_customer.surname, &my_customer.age, &my_customer.wallet) != EOF)
      {
        if (customer_id == my_customer.id)
        {
          my_customer.wallet += (book_price * remaining_weeks);
          fprintf(customerTemp, "%d %s %s %d %d\n", my_customer.id, my_customer.firstname, my_customer.surname, my_customer.age, my_customer.wallet);
        }
        else
        {
          fprintf(customerTemp, "%d %s %s %d %d\n", my_customer.id, my_customer.firstname, my_customer.surname, my_customer.age, my_customer.wallet);
        }
      }
      fclose(customerData);
      fclose(customerTemp);
      customerData = fopen(getCustomersFilePath(), "w");
      customerTemp = fopen(getCustomersTempPath(), "r");
      while (fscanf(customerTemp, "%d %s %s %d %d\n", &my_customer.id, &my_customer.firstname, &my_customer.surname, &my_customer.age, &my_customer.wallet) != EOF)
      {
        fprintf(customerData, "%d %s %s %d %d\n", my_customer.id, my_customer.firstname, my_customer.surname, my_customer.age, my_customer.wallet);
      }
      fclose(customerData);
      fclose(customerTemp);
      remove(getCustomersTempPath());
    }
  }
  else
  {
    printf("Rent ID is unknown\n");
  }
  navigate(5);
}

void displayRentedBooks()
{
  FILE *rentData = fopen(getRentsFilePath(), "r");
  FILE *bookData = fopen(getBooksFilePath(), "r");
  FILE *customerData = fopen(getCustomersFilePath(), "r");

  int found = 1;
  struct rent my_rent;
  struct book my_book;
  struct customer my_customer;
  printf("\n-------------------\n");
  printf("List of customers who rented a book\n");
  printf("------------------\n\n");

  printf("Rent ID\t\tBook name\t\t\tCustomer Name\t\t\t\tSurname\t\t\t\tDate Rented\t\t\tHow long?\n");
  while (fscanf(rentData, "%d %d %d %s %d\n", &my_rent.id, &my_rent.customer_id, &my_rent.book_id, &my_rent.date, &my_rent.weeks) != EOF)
  {
    found = 0;
    printf("%d\t\t", my_rent.id);
    while (fscanf(bookData, "%d %s %s %d %d %s", &my_book.id, &my_book.name, &my_book.author, &my_book.age_limit, &my_book.is_rented))
    {
      if (my_rent.book_id == my_book.id)
      {
        printf("%s\t\t\t\t", my_book.name);
        break;
      }
    }
    while (fscanf(customerData, "%d %s %s %d %d", &my_customer.id, &my_customer.firstname, &my_customer.surname, &my_customer.age, &my_customer.wallet))
    {
      if (my_rent.book_id == my_customer.id)
      {
        printf("%s\t\t\t\t\t%s\t\t\t\t%s\t\t\t%d week(s)\n", my_customer.firstname, my_customer.surname, my_rent.date, my_rent.weeks);
        break;
      }
    }
  }
  if (found != 0)
  {
    printf("records are empty\n");
  }
  fclose(rentData);
  fclose(bookData);
  fclose(customerData);
  backtoMenu();
}