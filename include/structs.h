#ifndef STRUCTURES
#define STRUCTURES

typedef struct book
{
  int amount;
  int borrowed;
  long isbn;
  char *title;
  char *author;
  char **borrower;
}book;

typedef struct library
{
  int count;
  book **books;
}library;

#endif