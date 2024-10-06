/*
File:         lab1_inlab_exercises.c
Purpose:      Exercises for lab 1
Author:       Randy Ren
Student #s:   56695331
CS Accounts:  p1n6x
Date:         September 8th, 2024
*/

/* Preprocessor directives */
#include "lab1_inlab_exercises.h"
#include <stdlib.h> // For system command

/* See main.c for additional practices for C programming */

/*
Reverses the order of an array of integers
For example,
{ 1, 2, 3, 4 } -> {4, 3, 2, 1 }
{ 1, 2, 3 } -> { 3, 2, 1 }
{1} -> {1}
{} -> {}
PARAM:  array, an array of integers
PARAM:  length, the number of elements in array
PRE:    array is an array of integers
PRE:    length is the correct length of the array
POST:   the elements in array have been reversed in order
RETURN: N/A
*/
void reverse_array(int array[], int length) {
  int reversed_array[length];
  int i=0,j=(length-1);


  for (i,j;i<length;i++,j--){
    reversed_array[i]=array[j];
  }

  for(i=0;i<length;i++){
    array[i]=reversed_array[i];
  }


  // Implement this function here
}

/*
Returns the length of the specified C string (an array of
characters that ends with the null character '\0')
PARAM:  string is a standard C array of characters that terminates
with the null character '\0'
PRE:    string is a null-terminated array of characters
POST:   NULL (no side-effects)
RETURN: number of char (excluding the terminating null) in string
*/
int length(const char string[])
{

  int count=0;

  for (int i=0;string[i]!='\0';i++){
    count+=1;
  }

  return count; 






}

/*
Returns the number of occurrences of the specified char in the specified
char array (string)
PARAM:  string is a standard C array of characters that terminates
with the null character '\0'
PARAM:  letter_sought, a char
PRE:    string is a null-terminated array of characters
POST:   NULL (no side-effects)
RETURN: number of occurences of letter_sought in string
*/
int count_letters(const char string[], char letter)
{
  int count=0;

  for (int i=0;string[i]!='\0';i++){
    if (string[i]==letter){
      count+=1;
    }
  }

  return count;

  // Replace this return statement with your own implementation

}

/*
Determines if a string is a palindrome.  Skips spaces.
For example,
""     -> returns 1 (an empty string is a palindrome)
"the"  -> returns 0
"abba" -> returns 1
"Abba" -> returns 0
"never odd or even"
-> returns 1 ("neveroddoreven" reversed is the same!)
PARAM:  string is a standard C array of characters that terminates
with the null character '\0'
PRE:    string is a null-terminated array of characters
POST:   no side-effects, e.g., nothing is printed or changed
RETURN: IF string is a palindrome THEN 1
ELSE IF string is not a palindrome THEN 0
*/
int is_palindrome(const char string[]) 
{
  int i =0;
  int j= length(string)-1;

  while (i<j){

    if (string[i]==' '){
      i+=1;
      continue;
    }

    if (string[j]==' '){
      j-=1;
      continue;
    }

    if (string[i]!=string[j]){
      return 0;
    }
    i++;
    j--;
    }

    return 1; 

  }


  







