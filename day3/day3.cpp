#include <cstdio>
#include <cstring>
#include <cstdbool>
#include <cstdint>
#include <vector>
#include <string>

using std::string;
using std::vector;

#define BUF_SIZE 32

#define LEN 12
#define INPUT_PATH "input.txt"

void part1(FILE* f) {
	char buffer[BUF_SIZE];
	int bit_count[LEN][2] = {0};
	int gamma, epsilon;

	while (fgets(buffer, BUF_SIZE-1, f) != NULL) {
		for (int i=0; i<LEN; ++i) {
			char c = buffer[i];
			bit_count[i][c-'0']++;
		}
	}

	gamma = 0;
	for (int i=0; i<LEN; ++i) {
		int value = (bit_count[i][1] > bit_count[i][0]);
		gamma |= (value << (LEN-i-1));
	}

	epsilon = ((1<<LEN)-1) & ~gamma;

	printf("%d\n", gamma*epsilon);
}

int parse_binary(const string& s) {
	int result = 0;

	for (int i=0; i<s.size(); ++i) {
		result |= (s[i]-'0') << (LEN-1-i);
	}

	return result;
}

void part2(FILE *f) {
	char buffer[BUF_SIZE];
	vector<string> lines_o2, lines_co2;

	while (fgets(buffer, BUF_SIZE-1, f) != NULL) {
		lines_o2.emplace_back(buffer);
		lines_o2[lines_o2.size()-1].pop_back();
	}
	lines_co2 = lines_o2;

	int len = lines_o2[0].size();

	int o2_rating;
	for (int i=0; i<len; ++i) {
		int count[256] = {0};
		for (const string& line: lines_o2)
			count[line[i]]++;
		char selected = (count['1']>=count['0']) + '0';
		for (int j=lines_o2.size()-1; j>=0; --j) {
			if (lines_o2[j][i] != selected)
				lines_o2.erase(lines_o2.begin()+j);
		}

		if (lines_o2.size()==1) {
			o2_rating = parse_binary(lines_o2[0]);
			break;
		}
	}

	int co2_rating;
	for (int i=0; i<len; ++i) {
		int count[256] = {0};
		for (const string& line: lines_co2)
			count[line[i]]++;
		char selected = (count['1']<count['0']) + '0';
		for (int j=lines_co2.size()-1; j>=0; --j) {
			if (lines_co2[j][i] != selected)
				lines_co2.erase(lines_co2.begin()+j);
		}

		if (lines_co2.size()==1) {
			co2_rating = parse_binary(lines_co2[0]);
			break;
		}
	}

	printf("%d\n", o2_rating);
	printf("%d\n", co2_rating);
	printf("%d\n", o2_rating*co2_rating);
}


int main() {
	FILE *f = fopen(INPUT_PATH, "r");

	//part1(f);
	part2(f);

	fclose(f);
	return 0;
}
