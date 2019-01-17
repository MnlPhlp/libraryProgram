#include <stdlib.h>
#include <stdio.h>
#include "../include/structs.h"
#include "../include/data.h"
#include "../include/menu.h"
#include "../include/utils.h"

void runTests()
{
  /*addBook(1,0,"0000000000","Game of Thrones","Georege R. R. Martin",NULL);
  borrowBook(lib.books[0], "Manuel Philipp");
  saveData("bin/Test_Save");
  free(lib.books);
  lib.books = NULL;
  loadData("bin/Test_Save");
  addBook(2,0,"1000000001","Harry Potter", "J.K. Rowling",NULL);
  deleteBook(0);
  printLib();*/
  printf("%c",menu("test\n",2));
}
