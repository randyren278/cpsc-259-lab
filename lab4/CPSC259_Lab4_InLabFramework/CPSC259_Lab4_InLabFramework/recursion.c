/*
 File:          recursion.c
 Purpose:       Exercises for CPSC259 lab 4
 Author:			 Randy Ren
 Student #s:		56695331
 CWLs:		      
 Date:				November 16th, 2024
*/
/******************************************************************
   PLEASE EDIT THIS FILE

   Comments that start with // have been replaced with code
   Comments that are surrounded by * are hints
   ******************************************************************/

/* Preprocessor directives */
#include "recursion.h"

/*
 Calculates the power.
 PARAM:     base is an integer
 PARAM:     power is an integer
 PRE:       power >= 0
 PRE:       base != 0
 RETURN:    base^power
 */
int calculate_power(int base, int power)
{
    if (power == 0) {
        // Any number to the power of 0 is 1
        return 1;
    } else {
        // Recursive case: base * base^(power-1)
        return base * calculate_power(base, power - 1);
    }
}

/*
 Returns the number of digits in an integer
 PARAM:     number is an integer
 PRE:       0 < number <= INT_MAX
 RETURN:    the number of digits in the number
 */
int count_digits(int number)
{
    if (number < 10) {
        // Base case: single digit
        return 1;
    } else {
        // Recursive case: 1 + number of digits in number/10
        return 1 + count_digits(number / 10);
    }
}

/*
 Returns the length of the specified string.
 PARAM:  string, a pointer to an array of char
 PRE:    the string pointer is not a dangling pointer
 RETURN: the length of the string passed as a parameter
 */
int string_length(char* string)
{
    if (*string == '\0') {
        // Base case: end of string
        return 0;
    } else {
        // Recursive case: 1 + length of the rest of the string
        return 1 + string_length(string + 1);
    }
}

/*
 Determines if a string is a palindrome.  DOES NOT skip spaces!
 For example,
 ""     -> returns 1 (an empty string is a palindrome)
 "the"  -> returns 0
 "abba" -> returns 1
 "Abba" -> returns 0
 "never odd or even" -> returns 0
 For the recursive call, be aware that both parameters can be modified.
 PARAM:  string, a pointer to an array of char
 PARAM:  string_length, the length of the string
 PRE:    the string pointer is not a dangling pointer
 PRE:    string_length is the correct length of the string
 RETURN: IF string is a palindrome
                     THEN 1
             END 0
 */
int is_palindrome(char* string, int string_length)
{
    if (string_length <= 1) {
        // Base case: empty string or single character is a palindrome
        return 1;
    }
    if (*string != *(string + string_length - 1)) {
        // Characters at the current ends do not match
        return 0;
    }
    // Recursive case: check the substring excluding the first and last characters
    return is_palindrome(string + 1, string_length - 2);
}

/*
 Draws a ramp. The ramp is symmetric: it decreases from 'number' asterisks down to 1,
 then increases back to 'number' asterisks.
 
 For example, draw_ramp(3, buffer) should produce:
 ***
 **
 *
 **
 ***
 
 PARAM:     number, an integer >= 1
 PARAM:     buffer, a character array of sufficient length
 PRE:       number >= 1
                buffer has sufficient length and contains null characters from the buffer
                address to the end of its length
 POST:      buffer contains the ramp pattern
 RETURN:    the number of characters written into buffer (excluding the null terminator)
 */
int draw_ramp(int number, char* buffer)
{
    if (number == 1) {
        // Base case: single asterisk without newline
        buffer[0] = '*';
        buffer[1] = '\0';
        return 1;
    }

    int chars_written = 0;

    // Append current row of 'number' asterisks
    for(int i = 0; i < number; i++) {
        buffer[chars_written++] = '*';
    }
    buffer[chars_written++] = '\n'; // Add newline

    // Recursive call for 'number - 1'
    int recursive_written = draw_ramp(number -1, buffer + chars_written);
    chars_written += recursive_written;

    // Append newline after recursive part
    buffer[chars_written++] = '\n';

    // Append current row of 'number' asterisks again
    for(int i = 0; i < number; i++) {
        buffer[chars_written++] = '*';
    }

    // Null-terminate the string
    buffer[chars_written] = '\0';

    return chars_written;
}

/*
 Draws a row of asterisks of the specified length
 For the recursive call, be aware that both parameters can be modified.
 PARAM:  size, an integer
 PARAM:  buffer, a character array of sufficient length
 PRE:    size >= 1
             buffer has sufficient length and contains null characters from the buffer
             address to the end of its length
 POST:   draws a row of asterisks of specified length to buffer
 RETURN: the number of characters drawn
 */
int draw_row(int size, char* buffer)
{
    if (size == 0) {
        // Base case: no asterisks to draw
        buffer[0] = '\0';
        return 0;
    }

    // Draw the row for size-1 first
    int chars_written = draw_row(size - 1, buffer);

    // Append the current asterisk
    buffer[chars_written++] = '*';

    // Null-terminate the string
    buffer[chars_written] = '\0';

    return chars_written;
}
