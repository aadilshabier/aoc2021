#include <stdio.h>

void part1(FILE *f) {
	int curr, prev, count = 0;
	fscanf(f, "%d", &prev);
	while (fscanf(f, "%d", &curr) == 1) {
		if (curr > prev)
			++count;
		prev = curr;
	}

	printf("%d\n", count);
}

void part2(FILE *f) {
	int a, b, c, new;
	int last_biggest = 0, count = 0;

	fscanf(f, "%d", &a);
	fscanf(f, "%d", &b);
	fscanf(f, "%d", &c);

	last_biggest = a + b + c;

	while (fscanf(f, "%d", &new) == 1) {
		if (new > a)
			++count;
		a = b;
		b = c;
		c = new;
	}
	
	printf("%d\n", count);
}

int main() {
	FILE *f = fopen("input.txt", "r");
	
	//part1(f);
	part2(f);
	
	fclose(f);
	return 0;
}
