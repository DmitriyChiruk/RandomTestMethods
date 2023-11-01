#include <iostream>

#include "TestMethods.h"

using namespace std;

int main() {
	string data = "";
	/*
	data += 0b00001111;
	data += 0b11111111;
	data += 0b11111111;
	data += 0b11111111;
	data += 0b11111111;
	data += 0b10110010;
	*/

	vector<vector<int>> CheckRanges;
	CheckRanges.push_back(vector<int>({ 2267, 2733 }));
	CheckRanges.push_back(vector<int>({ 1079, 1421}));
	CheckRanges.push_back(vector<int>({ 502, 748}));
	CheckRanges.push_back(vector<int>({ 223, 402}));
	CheckRanges.push_back(vector<int>({ 90, 223 }));
	CheckRanges.push_back(vector<int>({ 90, 223}));
	
	// data = "";
	CreateRandSeq(&data, 2500);
	// cout << "Data: " << data << endl;
	// cout << "Length: " << data.length() << endl << endl;

	int TestChecker = 0;
	bool tmp = 0;

	cout << "Monobit test: " << endl;
	tmp = MonobitTest(data, true);
	cout << "Result: " << (tmp? "Passed": "Failed") << endl << endl;
	TestChecker += tmp;

	cout << "Max series len test: " << endl;
	tmp = MaxSeriesLenTest(data, 36, false);
	cout << "Result: " << (tmp ? "Passed" : "Failed") << endl << endl;
	TestChecker += tmp;

	cout << "Pocker's test: " << endl;
	tmp = PockerTest(data, 1.03f, 57.4f, true);
	cout << "Result: " << (tmp ? "Passed" : "Failed") << endl << endl;
	TestChecker += tmp;

	cout << "Series len test: " << endl;
	tmp = SeriesLenTest(data, CheckRanges, true);
	cout << "Result: " << (tmp ? "Passed" : "Failed") << endl << endl;
	TestChecker += tmp;

	if (TestChecker == 4) 
	{
		cout << "Data IS random." << endl;
	}
	else
	{
		cout << "Data is NOT random." << endl;
	}

	return 0;
}