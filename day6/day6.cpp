#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <string>
#include <sstream>
#include <cstdint>

using std::ifstream;
using std::vector;
using std::string;
using std::array;

// #define DEBUG
#ifdef DEBUG
constexpr const char* FILENAME = "sample.txt";
#else
constexpr const char* FILENAME = "input.txt";
#endif

using T = size_t;

vector<T> readNums(ifstream& ifile)
{
	vector<T> result;
	string s;
	std::getline(ifile, s);
	std::istringstream iss(s);

	for (T i; iss >> i;) {
		result.push_back(i);
		if (iss.peek()==',')
			iss.ignore();
	}

	return result;
}

void updateWorldVec(vector<T>& ages)
{
	const size_t N = ages.size();
	for (size_t i=0; i<N; i++) {
		if (ages[i] == 0) {
			ages.push_back(8);
			ages[i] = 6;
		} else {
			ages[i]--;
		}
	}
}

void updateWorldArray(array<T, 9>& ages)
{
	size_t new_fishes = ages[0];
	for (size_t i=1; i<ages.size(); ++i)
		ages[i-1] = ages[i];
	ages[6] += new_fishes;
	ages[8] = new_fishes;
}

void part1(ifstream& ifile)
{
	auto ages = readNums(ifile);

	for(T i=0; i<80; i++)
		updateWorldVec(ages);

	std::cout << ages.size();
}

void part2(ifstream& ifile)
{
	auto initialAges = readNums(ifile);
	array<T, 9> ages{0};
	for (const auto& x: initialAges) {
		ages[x]++;
	}

	for(size_t i=0; i<256; i++)
		updateWorldArray(ages);

	size_t sum = 0;
	for (auto x: ages)
		sum += x;
	std::cout << sum;
}

int main()
{
	ifstream ifile(FILENAME);
	//part1(ifile);
	part2(ifile);	
}
