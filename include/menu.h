#ifndef MENU
#define MENU

#include "structs.h"
/*
 * Function: yesno
 * ----------------------------
 *  parses single character yes or no input (Y or N) 
 *  user input is not case sensitive
 *  
 *  def: (0|1) default return value that is used if the user just presses enter
 *
 *  returns: 1 for 'y', 0 for 'n', <def> for 'enter'
 */
int yesno(int def);

void mainMenu(library *lib);

#endif