#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "../include/data.h"
#include "../include/menu.h"
#include "../include/utils.h"

bool isbnValidation(char *isbn)
{
  char c;
  int i = 0;
  while ((c = getchar()) != '\n' && c != EOF)
  {
    if (c == ' ' || c == '-'|| c == 9){
      //skip separation characters used in an ISBN
      continue;
    }

    if ((c == 'q' || c == 'Q') && i == 0){
      //quit isbn check if user enters a q as first/only character
      isbn[0]='Q';
      //clear input buffer
      clearInput();
      return false;
    } 

    //check if a character that's not a number is entered
    if (i < 13 && !((c >= '0') && (c <= '9')))
    {
      //clear input buffer
      clearInput();
      //notify user about the wrong character
      printf("Input has to be digits:\nchar[%d]\" %c\" is invalid\n",i, c);
      return true;
    }
    if(i > 12)
    {
      //clear input buffer
      clearInput();
      printf("Input to long\n");
      return true;
    }
    isbn[i] = c;
    i++;
  }
  //add null byte to end string
  isbn[13] = '\0';
  if (i != 13)
  {
    printf("Input to short\n");
    return true;
  }

  //  ISBN Checksum
  int total = 0;
  for(int i = 0; i<12; i++)
  {
    total += i%2 ? 3*(isbn[i]-'0') : (isbn[i]-'0');
  }
  if ((10 - total % 10) % 10 != isbn[12] - '0')
  {
    printf("Not an ISBN, check checksum\n");
    return true;
  }

  return false;
}

char menu(char *text, int options)
{
  char buff[2];
  char input = '\0';
  //print specific menu text
  printf("%s", text);

  while (input == '\0')
  {
    do
    {
      printf("choose option: ");
    } while (getString(buff, 1));
    if ((buff[0] > '0' && buff[0] <= '0' + options) || toupper(buff[0]) == 'Q')
    {
      input = toupper(buff[0]);
    }
    else
    {
      printf("invalid Input\n");
    }
  }
  return input;
}

void clearConsole()
{
#ifdef _WIN32
  //on windows use system call
  system("cls");
#else
  //on Linux and mac use escape sequence
  printf("\033c");
#endif
}

void clearInput()
{
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
  {
  }
}

void printBook(book *book)
{
  printf(bookText, book->title, book->author, book->isbn, book->amount, book->amount - book->borrowed);
  //print list of people that borrowed this book
  if (book->borrowed > 0)
    printf("\n  Borrower:\n");
  for (int i = 0; i < book->borrowed; i++)
  {
    printf("   %d) %s\n", i + 1, book->borrower[i]);
  }
  printf("\n");
}

void printLib(library *pLib)
{
  clearConsole();
  printf("\n Amount of different Books is %d: \n"
         "----------------------------------\n",
         pLib->count);
  for (int i = 0; i < pLib->count; i++)
  {
    printf("\n Book number (%d):\n"
           "------------------------\n",
           i + 1);
    printBook(pLib->books[i]);
  }
}

bool yesno(bool def)
{
  char buff;
  char *options;
  if (def)
    options = "[Y/n]";
  else
    options = "[y/N]";

  int input = -1;
  while (input == -1)
  {
    printf("%s: ", options);
    buff = getchar();
    switch (toupper(buff))
    {
    case 'Y':
      input = true;
      clearInput();
      break;
    case 'N':
      input = false;
      clearInput();
      break;
    case '\n':
      input = def;
      break;
    default:
      printf("invalid input, try again\n");
      break;
      clearInput();
    }
  }
  return input;
}

bool getString(char *str, int length)
{
  // 2 extra spaces are needed for newline an null termination
  char buffer[length+2];
  // read String from standard input
  fgets(buffer,length+2,stdin);
  //if the user enters a String longer than 'length' the remaining input has to be cleared
  if (buffer[strlen(buffer)-1]!='\n')
  {
    printf("input to long\n");
    clearInput();
    return true;
  }
  // remove newline at end of string
  buffer[strlen(buffer)-1]='\0';
  // copy string to buffer of calling function
  strncpy(str,buffer,length+1);
  return false;
}

void upperString(char *dest, char *src)
{
  while (*src)
  {
    // store upper character of src in dest
    *dest = toupper((unsigned char)*src);
    src++;
    dest++;
  }
  *dest = '\0';
}
