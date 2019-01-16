#ifndef STRUCTURES
#define STRUCTURES

typedef struct book
{
  int amount;
  int borrowed;
  char isbn[11];
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
