/*
    prog2.c
    Author: Nicole Maiello
        Used William Confer's solution for prog1.c to create this program.
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

//file stream for input
FILE *file = NULL;

//NULL terminated buffer of the file contents
char *buffer = NULL;

//Data line counter
int line_num = 0;

 //atexit callback function
void cleanup();

//Copies a file's contents to a newly allocated buffer
void load_file_to_buffer(char *filename, char **buffer);


//Reads a data line from the input and prints the converted
//result along with the data line counter.
 void process_data_line(char **line);


//Prints out the binary string in decimal for unsigned magnitude
void dec(char **str);


//Prints out the binary string in decimal for signed magnitude
char to_SM(char **str, int trace);

//Flips the binary bits and prints them out for 1's and 2's comp
void to_Comp(char **str);

int main(int argc, char *argv[]) {

	bool done;
	char *c = NULL;

	if(argc != 2) {
		fprintf(stderr, "Usage:  prog1 <input file>\n");
		exit(EXIT_FAILURE);
	}

	atexit(cleanup);

	load_file_to_buffer(argv[1], &buffer);

	/* Assuming file is correctly formatted (for this assignment) */
	c = buffer;
	done = false;
	while(!done) {
		switch(*c) {
		case '\0':
			/* end of file */
			done = true;
			break;
		case '#':
			/* consume comment until end of line */
			do {
				c++;
			} while(*c != '\n' && *c != '\r' && *c != '\0');
			break;
		case '\n':
		case '\r':
			/* Treating each as skipable for *nix/Windows support */
			c++;
			break;
		default:
			/* should be the beginning of an input line */
			process_data_line(&c);
			break;
		}
	}

	return EXIT_SUCCESS;
}


void cleanup() {

	if(file) {
		fclose(file);
		file = NULL;
	}

	if(buffer) {
		free(buffer);
		buffer = NULL;
	}

	return;
}


void load_file_to_buffer(char *filename, char **buffer) {

	long tell_size;
	size_t size;
	bool all_good = false;

	if(buffer == NULL || *buffer != NULL) {
		fprintf(stderr, "Buffer is not safe to use\n");
		exit(EXIT_FAILURE);
	}

	file = fopen(filename, "rb");
	if(file) {
		if(fseek(file, 0, SEEK_END) == 0) {
			if((tell_size = ftell(file)) != EOF) {
				rewind(file);
				all_good = true;
			}
		}
	}
	if(!all_good) {
		fprintf(stderr, "Error with input file\n");
		perror("");
		exit(EXIT_FAILURE);
	}

	all_good = false;
	size = (size_t)tell_size;
	*buffer = (char *)malloc(sizeof(char) * (size + 1));
	if(*buffer != NULL) {
		(*buffer)[size] = '\0'; /* the NULL terminator is how we'll detect EOF */
		if(fread(*buffer, sizeof(char), size, file) == size) {
			all_good = true;
		}
	}

	if(!all_good) {
		fprintf(stderr, "Error buffering input file\n");
		perror("");
		exit(EXIT_FAILURE);
	}

	fclose(file);

	return;
}


void process_data_line(char **line) {
    char sign;
    int trace = 0;
	line_num++;

	printf("%d ", line_num);
	dec(line);
	sign = to_SM(line, trace);
	if(sign == '+'){
        to_SM(line, trace);
        trace++;
        to_SM(line, trace);
	}
	else{
        to_Comp(line);
	}
	trace = 0;
	printf("\n");

	return;
}


void dec(char **str) {

	int result = 0;
	char *c = *str;
	while(isalnum(*c)) {
		result *= 2;
		if(isdigit(*c)) {
			result += *c - '0';
		}
		c++;
	}
	printf("%d ", result);
	return;
}

char to_SM(char **str,int trace){
    int result = 0;
    char sig;
    char *c = *str;
    int sign = *c - '0';
    c++;
    while(isalnum(*c)){
        result *= 2;
        if(isdigit(*c)){
            result += *c - '0';
        }
        c++;
    }
    if(sign == 0){
        trace++;
        printf("+%d ", result);
        sig = '+';
    }
    else{
        printf("-%d ", result);
        sig = '-';
    }
    if(trace == 2)
        *str = c;
    return sig;
}

void to_Comp(char **str){
    int result = 0;
    char *c = *str;
    int sign = *c - '0';
    c++;
    while(isalnum(*c)){
        result *= 2;
        if(isdigit(*c)){
            if((*c - '0') == 0)
                *c = '1';
            else
                *c = '0';
            result += *c - '0';
        }
        c++;
    }
    printf("-%d ", result);
    printf("-%d", result + 1);
    *str = c;
    return;
}
