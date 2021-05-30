#include <stdio.h>
#include <stdbool.h>

char *getCustomersFilePath()
{
  return "data/customers.txt";
}

char *getBooksFilePath()
{
  return "data/books.txt";
}

char *getRentsFilePath()
{
  return "data/rents.txt";
}

char *getCustomersTempPath()
{
  return "data/customers_temp.txt";
}

char *getBooksTempPath()
{
  return "data/books_temp.txt";
}

char *getRentsTempPath()
{
  return "data/rents_temp.txt";
}

bool fileEmpty(FILE *file)
{
  if (fgetc(file) == EOF)
  {
    return true;
  }
  else
  {
    return false;
  }
}

int countLines(FILE *file)
{
  char c;
  int count = 1;
  for (c = getc(file); c != EOF; c = getc(file))
  {
    if (c == '\n')
    {
      count = count + 1;
    }
  }
  return count;
}

int getStructureID(FILE *file)
{
  int id = 0;
  if (fileEmpty(file))
  {
    id = 1;
  }
  else
  {
    int count = countLines(file);
    id = count++;
  }
  return id;
}