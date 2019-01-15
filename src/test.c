#include <stdlib.h>
#include "../include/structs.h"
#include "../include/data.h"
#include "../include/visual.h"


void runTests()
{
  library *lib = malloc(sizeof(library));
  addBook(lib,1,0,1235214,"Game of Thrones","Georege R. R. Martin",NULL);
  borrowBook(lib->books[0], "Manuel Philipp");
  saveData(lib,"bin/Test_Save");
  free(lib);
  lib = NULL;
  lib = loadData("bin/Test_Save");
  addBook(lib,2,0,12312412,"Harry Potter", "J.K. Rowling",NULL);
  deleteBook(lib,0);
  printLib(lib);
}
