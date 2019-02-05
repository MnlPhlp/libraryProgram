#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include "../include/structs.h"
#include "../include/data.h"
#include "../include/menu.h"
#include "../include/utils.h"

void runTests()
{
  printf("offsetof: %ld\n",offsetof(book,title));
  for(int i = 0; i < lib.count; i++)
  {
    printf("offset: %ld",(void*)lib.books[i]->title-(void*)lib.books[i]);
  }
  clearInput();
}
