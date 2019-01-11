#define PrintLibText "The library contains %d Books\n"\
                     "-----------------------------------\n\n"

#define PrintBookText "This is Book number %d\n"\
                      "------------------------\n"\
                      " title: %s\n"\
                      " author: %s\n"\
                      " isbn: %ld\n"\
                      " amount: %d\n"\
                      " borrowed: %d\n"
//prints the whole library to the console
void printLib(struct library *lib);