#include <stdbool.h>
#include <string.h>

bool xo (const char* str)
{
  
  unsigned int counter = 0;
  
  for (int i = 0; i < strlen(str); i++)
    if (str[i] == 120 || str[i] == 88){counter++;}
    else if (str[i] == 111 || str[i] == 79){counter--;}
  
  if(counter != 0)
    return false;
  
  return true;
}


// speed = 44.45ms
// mem = ??
// not best practice
// it uses str library to length the char array, not necessary?
// #include <stdbool.h>
//
// bool xo (const char* str)
// {
//  unsigned x = 0, o = 0;
//  for (char *p = str; *p; p++) {
//      if      (tolower(*p)=='x') x++;
//      else if (tolower(*p)=='o') o++;
/  }
//  return x == o;
// }
//
//
//
//
//
//
//
