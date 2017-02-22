#include <stdio.h>
#include <cstdlib>

/*

Author: Davide Russo [davexrusso@gmail.com]

Example of Brainfuck (https://en.wikipedia.org/wiki/Brainfuck) interpreter written in C.

The algorithm ignores symbols that do not belong to the language, with the exception for '_'
that can be used in order to print the integer representation of the char instead of its ASCII symbol.

See the examples in the main program.

*/

void brainfuckInterpreter(const char *program) {
	#define TAPE_SIZE 1000
	char command, *const tape = (char *const)calloc(TAPE_SIZE, sizeof(char));
	int brackets, activeCell = 0, programIndex = 0;
	do {
		command = program[programIndex];
		if(command == '>') activeCell++;
		else if(command == '<') activeCell--;
		else if(command == '+') tape[activeCell]++;
		else if(command == '-') tape[activeCell]--;
		else if(command == '.') printf("%c", tape[activeCell]);
		else if(command == '_') printf("%d", tape[activeCell]); /* Command to print the char as int (not in the language) */
		else if(command == ',') scanf("%d", tape + activeCell);
		else if(command == '[') {
			if(!tape[activeCell]) {
				brackets = 1;
				while(++programIndex < TAPE_SIZE && program[programIndex])
					if(program[programIndex] == ']' && !--brackets) break;
					else if(program[programIndex] == '[') brackets++;
			}
		}
		else if(command == ']') {
			if(tape[activeCell]) {
				brackets = 1;
				while(--programIndex >= 0)
					if(program[programIndex] == '[' && !--brackets) break;
					else if(program[programIndex] == ']') brackets++;
			}
		}
	} while(0 <= programIndex && programIndex < TAPE_SIZE && program[++programIndex]);
	free(tape);
}

int main() {
	char nonDestructiveCopy[] = "[>+>+<<-]>>[<<+>>-]<<";
	char helloWorld[] =
	"\
		++++++++++\
		[\
		   >+++++++>++++++++++>+++>+<<<<-\
		]\
		>++. H\
		>+. e\
		+++++++. l\
		. l\
		+++. o\
		>++.\
		<<+++++++++++++++.\
		>.\
		+++.\
		------.\
		--------.\
		>+.\
		>.\
	";
	char mult[] = ", >, <[> ([>+>+<<-]>[<+>-]>) [>+<-] <<<-] >>>>_";
	brainfuckInterpreter(nonDestructiveCopy);
	brainfuckInterpreter(helloWorld);
	printf("Insert your numbers:\n-> ");
	brainfuckInterpreter(mult);
	return 0;
}
