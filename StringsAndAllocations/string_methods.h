#ifndef STRING_METHODS_H
#define STRING_METHODS_H

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

/*
 * ReverseStr
 * Input:  _str - pointer to a null-terminated string (modified in place)
 * Output: 1 on success, 0 if the string is empty
 * Error:  returns 0 for empty string; undefined behavior if _str is NULL
 */
int ReverseStr(char *_str);

/*
 * IsPalindrome
 * Input:  _str - pointer to a null-terminated string
 * Output: 1 if the string is a palindrome, 0 otherwise
 * Error:  returns 1 for an empty string (vacuously a palindrome)
 */
int IsPalindrome(char *_str);

/*
 * MyAToI
 * Input:  _str - pointer to a null-terminated string representing an integer
 *                (optional leading '+' or '-', then digits only)
 *         _num - pointer to an int where the result will be stored
 * Output: 1 on success; _num is set to the parsed integer value
 * Error:  returns 0 if _str or _num is NULL, string is empty,
 *         or string contains non-digit characters (after optional sign)
 */
int MyAToI(char *_str, int *_num);

/*
 * MyIToA
 * Input:  _num    - the integer to convert
 *         _buffer - pointer to a char buffer large enough to hold the result
 *                   (must fit the digits + optional '-' + null terminator)
 * Output: 1 on success; _buffer contains the null-terminated string representation
 * Error:  returns 0 if _buffer is NULL
 */
int MyIToA(int _num, char *_buffer);

/*
 * ReverseWordsInString
 * Input:  _str - pointer to a null-terminated string (modified in place)
 *                words are separated by single spaces
 * Output: 1 on success; words in _str are reversed in order
 * Error:  returns 0 if _str is NULL or empty
 */
int ReverseWordsInString(char *_str);

/*
 * CountWordsInString
 * Input:  _str - pointer to a null-terminated string
 *                words are separated by any whitespace characters
 * Output: number of words found in the string (>= 0)
 * Error:  returns 0 if _str is NULL or the string contains no words
 */
int CountWordsInString(char *_str);


#endif