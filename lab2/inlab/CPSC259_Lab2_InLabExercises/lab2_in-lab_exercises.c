/*
 File:				lab2_in-lab_exercises.c
 Purpose:			Implementation of functions for lab 2 in-lab exercises
 Author:			Randy Ren
 Student #s:	56695331
 CWLs:	      rren05  
 Date:				October 6, 2024 
 */

#include "lab2_in-lab_exercises.h"
#include <stdlib.h>
#include <string.h> 

/*
 * Let's start with something easy.  There are 3 unit tests
 * for this function.
 *
 * Swaps the contents of two integer variables using pointers
 *
 * PARAM:     first_int is a pointer to an int
 * PARAM:     second_int is a pointer to an int
 * PRE:       both pointers are valid pointers to int
 * POST:      the contents of two integer variables are swapped
 * RETURN:    VOID
 */
void swap_ints(int* first_int, int* second_int)
{
  int temp = *first_int;
  *first_int = *second_int;
  *second_int = temp;
}

/*
 * Now let's try something a little more challenging.
 *
 * Reverses the contents of the string passed to the
 * function.  Does not move the terminating null '\0'
 * character.
 *
 * PARAM:     string is a pointer to an array of char (a string)
 * PRE:       the array of char terminates with a null '\0'
 * POST:      the char array has been reversed
 * RETURN:    VOID
 */
void reverse_string(char* string)
{
  for (int i = 0; i < strlen(string) / 2; i++)
  {
    char temp = string[i];
    string[i] = string[strlen(string) - i - 1];
    string[strlen(string) - i - 1] = temp;
  }
}

/*
 * Determines if candidate contains sample, and returns
 * 1 if it does, and 0 if it does not.
 *
 * PARAM:     candidate is a pointer to an array of char (a string)
 * PARAM:     sample is a pointer to an array of char (a string)
 * PRE:       the arrays of char terminate with a null '\0'
 * PRE:       candidate != NULL; sample != NULL
 * POST:      N/A
 * RETURN:    IF candidate contains sample THEN 1
 *            ELSE 0.
 */
int contains_sample(char* candidate, char* sample)
{
  int candidate_len = strlen(candidate);
  int sample_len = strlen(sample);
  
  // Iterate through candidate until the point where sample could still fit
  for (int i = 0; i <= candidate_len - sample_len; i++)
  {
    int j = 0;

    // Compare the substring with sample
    while (j < sample_len && candidate[i + j] == sample[j])
    {
      j++;
    }

    // If the entire sample has matched, return 1
    if (j == sample_len)
    {
      return 1;
    }
  }

  // If we didn't find the sample, return 0
  return 0;
}


/*
 * Returns the first index where sample is located inside the
 * candidate.  For example:
 * IF candidate = "Hello", sample = "Hello", RETURNS 0
 * IF candidate = "soupspoon", sample = "spoon", RETURNS 4
 * IF candidate = "ACGTACGTA", sample = "CGT", RETURNS 1
 * IF candidate = "CGTACGTA", sample = "CGTT", returns -1
 *
 * PARAM:     candidate is a pointer to an array of char (a string)
 * PARAM:     sample is a pointer to an array of char (a string)
 * PRE:       the arrays of char terminate with a null '\0'
 * POST:      N/A
 * RETURN:    IF candidate contains sample
 *            THEN the index where the first letter of sample is inside candidate
 *            ELSE -1.
 */
int find_index(char* candidate, char* sample)
{
  int candidate_len = strlen(candidate);
  int sample_len = strlen(sample);

  // Iterate through candidate until the point where sample could still fit
  for (int i = 0; i <= candidate_len - sample_len; i++)
  {
    int j = 0;

    // Compare the substring with sample
    while (j < sample_len && candidate[i + j] == sample[j])
    {
      j++;
    }

    // If the entire sample has matched, return the index
    if (j == sample_len)
    {
      return i;
    }
  }

  // If we didn't find the sample, return -1
  return -1;
}
