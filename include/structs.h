#ifndef STRUCTURES
#define STRUCTURES

typedef unsigned char uint8;
typedef struct book
{
  uint8 amount;
  uint8 borrowed;
  char isbn[11];
  char *title;
  char *author;
  char **borrower;
}book;

typedef struct library
{
  uint8 count;
  book **books;
}library;

#endif
