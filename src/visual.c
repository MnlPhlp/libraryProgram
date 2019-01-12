#include "structs.h"
#include "visual.h"
#include <stdio.h>

void printLib(library *lib)
{
  printf(LibText, lib->count);
  for (int i = 0; i < lib->count; i++)
  {
    printf(BookText, i+1, lib->books[i]->title, lib->books[i]->author, lib->books[i]->isbn, lib->books[i]->amount, lib->books[i]->borrowed);

    for (int j = 0; j < lib->books[i]->borrowed; j++)
    {
      printf("  %d: %s\n", j, lib->books[i]->borrower[j]);
    }
  }
}