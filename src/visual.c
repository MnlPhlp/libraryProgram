#include "structs.h"
#include "visual.h"
#include <stdio.h>

extern library lib;

void printLib() {
  printf("Amount of Books is %d: \n",lib.count);
  for(int i = 0;i<lib.count;i++){
    printBook(lib.books[i],i+1);
  }
  printf("Hit ENTER to continue...");
  clearConsole();
}

// void printLib()
// {
//   printf(LibText, lib.count);
//   for (int i = 0; i < lib.count; i++)
//   {
//     printf(BookText, i+1, lib.books[i]->title, lib.books[i]->author, lib.books[i]->isbn, lib.books[i]->amount, lib.books[i]->borrowed);
//
//     for (int j = 0; j < lib.books[i]->borrowed; j++)
//     {
//       printf("  %d: %s\n", j+1, lib.books[i]->borrower[j]);
//     }
//   }
// }
