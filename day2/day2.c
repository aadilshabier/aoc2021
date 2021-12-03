#include <stdio.h>
#include <string.h>

void part1(FILE *f) {
	int depth = 0, horizontal = 0;
	
	char command[8];
	int value;
	while( fscanf(f, "%s %d", command, &value) == 2 ) {
		if ( strcmp( command, "up" ) == 0) {
			depth -= value;
		}
		else if ( strcmp( command, "down" ) == 0) {
			depth += value;
		}
		// Assume inputs are correct and it can only be "forward"
		else {
			horizontal += value;
		}
	}

	printf("%d\n", depth * horizontal);
}

void part2(FILE *f) {
	int aim = 0, depth = 0, horizontal = 0;
	
	char command[8];
	int value;
	while ( fscanf(f, "%s %d", command, &value) == 2 ) {
		if ( strcmp( command, "up" ) == 0) {
			aim -= value;
		}
		else if ( strcmp( command, "down" ) == 0) {
			aim += value;
		}
		// Assume inputs are correct and it can only be "forward"
		else {
			horizontal += value;
			depth += aim * value;
		}
	}

	printf("%d\n", depth * horizontal);
}

int main() {
	FILE *f = fopen("input.txt", "r");

	//part1(f);
	part2(f);
	
	fclose(f);
	return 0;
}
