#include <stdlib.h>
#include "structs.h"
#include "data.h"
#include "visual.h"


void runTests()
{
  addBook(1,0,1235214,"Game of Thrones","Georege R. R. Martin",NULL);
  borrowBook(lib.books[0], "Manuel Philipp");
  saveData("bin/Test_Save");
  free(lib.books);
  lib.books = NULL;
  loadData("bin/Test_Save");
  addBook(2,0,12312412,"Harry Potter", "J.K. Rowling",NULL);
  deleteBook(0);
  printLib();
}
