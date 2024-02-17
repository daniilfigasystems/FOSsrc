/** @file string.h
 *  Copyright (c) 2023 FigaSystems
 *  String operations
 *  @author Daniil Dunaef
 *  @date 14-Nov-2023
 *  @bug No current bugs found
*/



#ifndef _STRING_
#define _STRING_

#include "stddef.h"

/** @brief Copies n bytes of source to destination
 *  @param dest The destination
 *  @param src The source
 *  @param count Number of bytes to copy
 *  @return Returns destination
*/
unsigned 
int
memcpy(
	void *dst, 
	void *src, 
	size_t count
);

/** @brief Get largest value from two values
 *  @param a First Value
 *  @param b Second Value
 *  @return Largest value from two values
*/
int 
max(
	int a, 
	int b
);

/** @brief Get smallest value from two values
 *  @param a First Value
 *  @param b Second Value
 *  @return Smallest value from two values
*/
int 
min(
	int a, 
	int b
);

/** @brief Get absolute value of value
 *  @param a Value
 *  @return Absolute value
*/
int 
abs(
	int a
);

/** @brief Swaps two values
 *  @param a First value
 *  @param b Second value
 *  @return Nothing
*/
void 
swap(
	int *a, 
	int *b
);

/** @brief Moves n bytes of source to destination
 *  @param dest The destination
 *  @param src The source
 *  @param count Number of bytes to move
 *  @return Returns destination
*/
void 
* 
memmove(
	void * restrict dest, 
	void * restrict src, 
	unsigned int count
);

/** @brief Converts string to integer
 *  @param str String to convert
 *  @return Returns converted string
*/
int 
atoi (
	const char * str
);

/** @brief Converts integer to string 
 *  @param res Value to convert
 *  @return Returns converted value
*/
char
* 
itoa(
	int res
);

/** @brief Compare two strings
 *  @param a First string to compare
 *  @param b Second string to compare
 *  @return If first string is less than second string it returns -1 else if second string is greater than first string it returns 1 else if first string or second string doesnt exist it returns 0
*/
int 
strcmp(
	const char * a, 
	const char * b
);

/** @brief Set n bytes of destination with specified value
 *  @param dest The destination
 *  @param val Specific value to set
 *  @param count Number of bytes to set
 *  @return Returns destination
*/
void
*
memset(
	void* dst,
	int val, 
	size_t count
);

/** @brief ((DEPRECATED) Use memset instead of this) Set n bytes of destination with specified value
 *  @param dest The destination
 *  @param val Specific value to set
 *  @param count Number of bytes to set
 *  @return Returns destination
*/
unsigned short * memsetw(unsigned short * dest, unsigned short val, int count) __attribute__((deprecated));

/** @brief Get length of a string
 *  @param str String to get length
 *  @return Returns Length of string
*/
unsigned int 
strlen(
	const char *str
);

#endif