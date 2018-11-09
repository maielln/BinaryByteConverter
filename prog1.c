/*
    prog2.c
    Author: Nicole Maiello
    Date: 2/23/17

    Summary: Convert binary bytes to their unsigned, signed magnitude, 1's comp, and 2's comp

    This program is the second program in the Spring 2017 CS 220.
    The program expects a single command line argument, the file
    contains three types of lines: comments, blanks, or inputs.
    Comment and blank lines are to be ignored (comment lines begin
    with a '#').
    For each input line: output must be:
    1. The input line number
    2. Space
    3. Unsigned decimal value of the bit pattern (no + or -)
    4. Space
    5. Signed magnitude decimal value of the bit pattern (+ or - symbol required)
    6. Space
    7. 1's comp decimal value of the bit pattern (+ or - symbol required)
    8. Space
    9. 2's comp decimal value of the bit pattern (+ or - symbol required)

    This program will assume the file has no errors.
    */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

//  File stream for input
FILE *f = NULL;

//  NULL terminates buffer of the file contents
char *buffer = NULL;

// Keeps track of what line number the program is currently on
int line_num = 0;
