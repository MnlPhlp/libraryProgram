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

int menu(char *text, int options)
{
  int input = 0;
  char buff;
  //print specific menu text
  printf("%s", text);

  while (input == 0)
  {
    printf("choose option: ");
    buff = getchar();
    if (buff >= '1' && buff <= '0' + options)
      //save choosen option if in valid range
      input = buff - '0';
    else if (buff == 'm')
      //print specific menu text again
      //useful after many invalid inputs to see the valid options again
      printf("%s", text);
    else
      printf("invalid input, try again (enter 'm' to show menu again)\n");
  }
  clearConsole();
  return input;
}

void clearConsole()
{
  clearInput();
  for (int i = 0; i < 10; i++)
  {
    printf("\n\n\n\n\n");
  }
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
  printf("\n Book number (%d):\n"
         "------------------------\n"
         " Title: %s\n"
         " Author: %s\n"
         " ISBN: %s\n"
         " Amount: %d\n"
         " In stock: %d\n\n",
         count, book->title, book->author, book->isbn, book->amount, book->amount - book->borrowed);
}

void printLib(library* pLib)
{
  printf("Amount of different Books is %d: \n", lib.count);
  for (int i = 0; i < pLib->count; i++)
  {
    printBook(pLib->books[i], i + 1);
  }
  printf("Hit ENTER to continue...");
  clearConsole();
}

int yesno(bool def)
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
      break;
    case 'N':
      input = false;
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
  while ((c = getchar()) != '\n' && c != EOF && i < length) {
    buffer[i]=c;
    i++;
  }
  //if the user enters a String longer than buffSize the remaining input has to be cleared
  if (c != '\n'){
    printf("input to long\n");
    clearInput();
    return true;
  }
  return false;
}
