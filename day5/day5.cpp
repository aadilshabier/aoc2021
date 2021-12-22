#include <iostream>
#include <fstream>
#include <array>
#include <vector>
#include <algorithm>
#include <cstdint>
#include <cstdio>
#include <cmath>

using std::ifstream;
using std::string;
using std::getline;
using std::array;
using std::vector;

// #define DEBUG
#ifdef DEBUG
constexpr size_t N = 10;
constexpr const char* FILENAME = "sample.txt";
#else
constexpr size_t N = 1000;
constexpr const char* FILENAME = "input.txt";
#endif
using Area = array<array<uint8_t, N>, N>;

struct Coord {
	int x, y;
	Coord(int x_=0, int y_=0): x(x_), y(y_) {}
};

struct Line
{
	Coord start, end;
};

Line coordsFromLine(const string& s)
{
	Coord start, end;
	std::sscanf(s.c_str(), "%d,%d -> %d,%d", &start.x, &start.y, &end.x, &end.y);
#ifdef DEBUG
	printf("(%d, %d);(%d, %d)\n", start.x, start.y, end.x, end.y);
#endif
	return {start, end};
}

vector<int> createRange(int x, int y)
{
	vector<int> result;
	result.reserve(abs(y-x)+1);
	if (x>y) {
		int temp = y;
		y = x;
		x = temp;
	}
	while (x<=y)
		result.push_back(x++);
	return result;
}

vector<Coord> getPoints(const Line& line, bool nonDiagonal)
{
	vector<Coord> result;
	auto [start, end] = line;
	auto [startX, startY] = start;
	auto [endX, endY] = end;
	
	vector<int> xRange, yRange;
	if (startX == endX && startY != endY) {
		yRange = createRange(startY, endY);
		xRange = vector<int>(yRange.size(), startX);
		if (startY>endY)
			std::reverse(yRange.begin(), yRange.end());
	}
	else if (startY == endY && startX != endX ) {
		xRange = createRange(startX, endX);
		yRange = vector<int>(xRange.size(), startY);
		if (startX>endX)
			std::reverse(xRange.begin(), xRange.end());
	} else if (!nonDiagonal) {
		if (startX != endX && startY != endY) {
			xRange = createRange(startX, endX);
			yRange = createRange(startY, endY);
			if (startX>endX)
				std::reverse(xRange.begin(), xRange.end());
			if (startY>endY)
				std::reverse(yRange.begin(), yRange.end());
		} else {
			xRange.push_back(startX);
			yRange.push_back(startY);
		}
	}

	result.reserve(xRange.size());
	for (size_t i=0; i<xRange.size(); ++i) {
		result.emplace_back(xRange[i], yRange[i]);
	}
	
	return result;
}

void part1(ifstream& ifile)
{
	string s;
	Area area{0};
	for (;;) {
		getline(ifile, s);
		if (s.size() == 0)
			break;
		Line line = coordsFromLine(s);
		for (auto& coord: getPoints(line, true)) {
			area[coord.y][coord.x]++;
		}
	}

	size_t count = 0;
	for (const auto& y: area) {
		for (const auto& x: y) {
			if (x>1)
				count++;
		}
	}
	std::cout << "Count: " << count << '\n';

#ifdef DEBUG
	for (const auto& y: area) {
		for (const auto& x: y) {
			if (x>0)
				std::cout << (int)x;
			else
				std::cout << '.';
		}
		std::cout << '\n';
	}
#endif
}

void part2(ifstream& ifile)
{
	string s;
	Area area{0};
	for (;;) {
		getline(ifile, s);
		if (s.size() == 0)
			break;
		Line line = coordsFromLine(s);
		for (auto& coord: getPoints(line, false)) {
			area[coord.y][coord.x]++;
		}
	}

	size_t count = 0;
	for (const auto& y: area) {
		for (const auto& x: y) {
			if (x>1)
				count++;
		}
	}
	std::cout << "Count: " << count << '\n';

#ifdef DEBUG
	for (const auto& y: area) {
		for (const auto& x: y) {
			if (x>0)
				std::cout << (int)x;
			else
				std::cout << '.';
		}
		std::cout << '\n';
	}
#endif
}

int main()
{
	std::ifstream ifile(FILENAME);

	//part1(ifile);
	part2(ifile);

	return 0;
}
