#ifndef BOOK_H
#define BOOK_H

struct book
{
  int id;
  char name[100];
  char author[100];
  int age_limit;
  int price;
  char is_rented[6];
} book;

#endif