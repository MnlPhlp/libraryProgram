#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <time.h>
#include "../include/structs.h"
#include "../include/data.h"
#include "../include/menu.h"
#include "../include/utils.h"

void randomString(char * str, int len){
  for(int i = 0; i < len; i++)
  {
    *str++ = (char) (97+rand()%26);
  }
  *str = '\00';
}

void runTests()
{
  //generate random books
  library oldLib = lib;
  int amount;
  int borrowed;
  char isbn[14];
  char title[32];
  char author[32];
  char **borrower ;
  int generatedAmount;
  bool stopTests = false;
  while (!stopTests)
  {
    for(int i = 0; i < lib.count; i++)
    {
      freeBook(lib.books[i]);
    }
    free (lib.books);
    lib.books=NULL;
    lib.count=0;
    printf("Amount to generate: ");
    scanf("%d",&generatedAmount);
    clearInput();
    printf("start library generation\ngenerating %d books..\n",generatedAmount);
    time_t start,stop;
    float overallTime = 0;
    for(int i = 0; i < generatedAmount; i++)
    {
      amount = 1+rand()%20;
      borrowed = amount - rand()%(amount+1);
      randomString(isbn,13);
      randomString(title,31);
      randomString(author,31);
      borrower= malloc(borrowed*sizeof(char*));
      for(int j = 0; j < borrowed; j++)
      {
        borrower[j] = malloc(32);
        randomString(borrower[j],31);
      }
      start = clock();
      addBook(amount,isbn,title,author);
      lib.books[i]->borrowed=borrowed;
      lib.books[i]->borrower=borrower;
      stop = clock();
      overallTime	+= (float)(stop - start)/CLOCKS_PER_SEC;
    }

    float average = (overallTime*1000000)/generatedAmount;
    printf("adding books took %.2f seconds\nthat is %.2f microseconds per book\n",overallTime,average);
    start = clock();
    hashLib();
    stop = clock();
    printf("hash took %.2f milliseconds\n",(float)(stop-start)/(CLOCKS_PER_SEC/1000));
    printf("print lib?");
    if (yesno(false))
      printLib(&lib);

    printf("stop tests?");
    stopTests = yesno(false);
  }
  printf("Reload old Library?");
  if (yesno(true))
    lib = oldLib;

}
