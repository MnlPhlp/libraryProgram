struct book {
  int   amount;
  int   borrowed;
  long  isbn;
  char  *title;
  char  *author;
  char* borrower[0];

};  

struct library
{
  int count;
  struct book *books[0];
};

