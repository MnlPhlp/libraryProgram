#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "../include/data.h"
#include "../include/menu.h"
#include "../include/utils.h"

bool isbnValidation(char isbn[])
{
  char c;
  int i = 0;
  while ((c = getchar()) != '\n' && c != EOF)
  {
    if (c != ' ' && c != '-')
    {
      if (i < 9 && !((c >= '0') && (c <= '9')))
      {
        clearInput();
        printf("First 9 characters have to be digits:\
                char[%d]\" %c\" is invalid\n",
               i, c);
        return true;
      }
      if (i < 10)
      {
        if (c == 'x')
        {
          isbn[i] = 'X';
        }
        else
        {
          isbn[i] = c;
        }
        i++;
      }
      else
      {
        clearInput();
        printf("to long\n");
        return true;
      }
    }
  }
  //add null byte to end string
  isbn[10]='\0';
  if (i != 10)
  {
    printf("to short\n");
    return true;
  }

  if (isbn[9] != 'x' && isbn[9] != 'X' && !(isbn[9] >= '0') && !(isbn[9] <= '9'))
  {
    printf("last digit is NaN or 'X'\n");
    return true;
  }

  //  ISBN Checksum
  int total = 0;
  for (int i = 0; i < 9; i++)
  {
    total += (isbn[i] - '0') * (10 - i);
  }
  if (isbn[9] == 'X')
  {
    total += 10;
  }
  else
  {
    total += isbn[9] - '0';
  }
  if (total % 11)
  {
    printf("Not an ISBN check checksum\n");
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
  //on linux and mac use escape sequence
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

void printBook(book *book, int count)
{
  printf(bookText,
         count, book->title, book->author, book->isbn, book->amount, book->amount - book->borrowed);
  //print list of people that borrowed this book
  if (book->borrowed > 0)
   printf("  Borrower:\n");
  for(int i = 0; i < book->borrowed; i++)
  {
    printf("   %d) %s\n",i+1,book->borrower[i]);
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
    printBook(pLib->books[i], i + 1);
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

bool getString(char *buffer, int length)
{
  int i = 0;
  char c;
  while ((c = getchar()) != '\n' && c != EOF && i < length)
  {
    buffer[i] = c;
    i++;
  }
  buffer[i] = '\0';
  //if the user enters a String longer than buffSize the remaining input has to be cleared
  if (c != '\n')
  {
    printf("input to long\n");
    clearInput();
    return true;
  }
  return false;
}
