// headers
#include <stdio.h>

// structures
#include "../structures/book.h";

void addNewBook()
{
  FILE *data = fopen(getBooksFilePath(), "r");
  struct book new_book;
  char answer;
  new_book.id = getStructureID(data);

  fclose(data);
  data = fopen(getBooksFilePath(), "a");
  printf("\n--------------------------\n");
  printf("Add new book loaded\n");
  printf("--------------------------\n");

  printf("Enter new book's name: ");
  scanf(" %[^\t\n]s", &new_book.name);
  printf("Author: ");
  scanf(" %[^\t\n]s", &new_book.author);
  printf("Age limit: ");
  scanf("%d", &new_book.age_limit);
  printf("Price per week: ");
  scanf("%d", &new_book.price);
  strcpy(new_book.is_rented, "false");

  fprintf(data, "%d %s %s %d %d false\n", new_book.id, new_book.name, new_book.author, new_book.age_limit, new_book.price);
  fclose(data);
  printf("Book %s added successfully\n", new_book.name);

  navigate(3);
}

void updateBook()
{
  FILE *dataRead = fopen(getBooksFilePath(), "r");
  FILE *dataWrite = fopen(getBooksTempPath(), "w");
  struct book my_book;
  int found;
  int id;
  printf("\n------------------\n");
  printf("Update book loaded\n");
  printf("------------------\n\n");
  printf("Enter book id: ");
  scanf("%d", &id);

  rewind(dataRead);
  while (fscanf(dataRead, "%d %s %s %d %d %s\n", &my_book.id, &my_book.name, &my_book.author, &my_book.age_limit, &my_book.price, &my_book.is_rented) != EOF)
  {
    if (id == my_book.id)
    {
      found = 1;
      printf("Enter new book's name: ");
      scanf(" %[^\t\n]s", &my_book.name);
      printf("Author: ");
      scanf(" %[^\t\n]s", &my_book.author);
      printf("Age Limit: ");
      scanf("%d", &my_book.age_limit);
      printf("Price per week: ");
      scanf("%d", &my_book.price);
      fprintf(dataWrite, "%d %s %s %d %d %s\n", my_book.id, my_book.name, my_book.author, my_book.age_limit, my_book.price, my_book.is_rented);
    }
    else
    {
      found = 0;
      fprintf(dataWrite, "%d %s %s %d %d %s\n", my_book.id, my_book.name, my_book.author, my_book.age_limit, my_book.price, my_book.is_rented);
    }
  }
  fclose(dataRead);
  fclose(dataWrite);
  dataRead = fopen(getBooksFilePath(), "w");
  dataWrite = fopen(getBooksTempPath(), "r");
  while (fscanf(dataWrite, "%d %s %s %d %d %s\n", &my_book.id, &my_book.name, &my_book.author, &my_book.age_limit, &my_book.price, &my_book.is_rented) != EOF)
  {
    fprintf(dataRead, "%d %s %s %d %d %s\n", my_book.id, my_book.name, my_book.author, my_book.age_limit, my_book.price, my_book.is_rented);
  }
  fclose(dataRead);
  fclose(dataWrite);
  if (found == 0)
  {
    printf("Book id not found\n");
  }
  else
  {
    printf("Book information updated successfully\n");
  }
  remove(getBooksTempPath());
  navigate(7);
}

void displayBooks()
{
  FILE *data = fopen(getBooksFilePath(), "r");
  int found = 1;
  struct book my_book;
  printf("\n-------------------\n");
  printf("List of Books\n");
  printf("------------------\n\n");

  printf("Book ID\t\tName\t\t\t\tAuthor\t\t\t\tAge Limit\tPrice per week\t\tIs Rented\n");
  while (fscanf(data, "%d %s %s %d %d %s\n", &my_book.id, &my_book.name, &my_book.author, &my_book.age_limit, &my_book.price, my_book.is_rented) != EOF)
  {
    found = 0;
    printf("%d\t\t%s\t\t\t\t%s\t\t\t\t%d\t\t%d\t\t\t%s\n", my_book.id, my_book.name, my_book.author, my_book.age_limit, my_book.price, my_book.is_rented);
  }
  if (found != 0)
  {
    printf("Books data empty\n");
  }
  fclose(data);
  backtoMenu();
}
