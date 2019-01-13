#include <stdlib.h>
#include "structs.h"
#include "data.h"
#include "visual.h"

void runTests()
{
  library *lib = malloc(sizeof(library));
  addBook(lib,1,0,1235214,"Game of Thrones","Georege R. R. Martin",NULL);
  borrowBook(lib->books[0], "manuel Philipp");
  printLib(lib);
}
