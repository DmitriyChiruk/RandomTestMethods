#include "TestMethods.h"

#include <iostream>
#include <bitset>
#include <vector>
#include <random>

void CreateRandSeq(std::string* oput, int Length)
{
	std::srand(std::time(NULL));

	for (int i = 0; i < Length; i++)
	{
		*oput += rand() % 256;
	}
}

bool MonobitTest(const std::string &input, const int RangeLeft, const int RangeRight, bool Debug)
{
	int zeros = 0, ones = 0;

	// Check each byte
	for (auto symbol : input)
	{
		// Check each bit
		std::bitset<8> BitSymbol(symbol);
		for (char i = 0; i < 8; i++)
		{
			if (BitSymbol[i]) { ++ones; }
			else { ++zeros; }
		}
	}

	if (Debug)
	{
		std::cout << "Zeros: " << zeros << "\nOnes: " << ones << std::endl;
	}

	if ((ones > RangeLeft && ones < RangeRight) && (zeros > RangeLeft && zeros < RangeRight))
	{
		return true;
	}

	return false;
}

bool MaxSeriesLenTest(const std::string &input, const int MaxSeriesSz, bool Debug)
{
	bool Res = true;

	bool SeriesBorder = input[0]>>7;
	bool CurrentBit;
	int len = 1;

	int TotalSz = input.length() * 8;

	for (int i = 1; i <= TotalSz; i++)
	{
		// Calculate current bit
		CurrentBit = input[i / 8] >> (7 - (i % 8)) & 1;

		if ( CurrentBit == SeriesBorder && i != TotalSz)
		{
			// If the series continues
			++len;
		}
		else 
		{
			// If the series is over
			if (Debug)
			{
				std::cout << "Len of '" << SeriesBorder << "' = " << len << std::endl;
			}

			// If reached maximum series length => test failed
			if (len > MaxSeriesSz) 
			{
				Res = false; 
				if (!Debug) { return Res; }
			}

			// Change border value to oposit (aka CurrentBit)
			SeriesBorder = !SeriesBorder;
			len = 1;
		}
	}

	return Res;
}

std::vector<char> CreatePockerValues(const int m)
{
	std::vector<char> Res(pow(2, m), 0);

	for (int i = 0; i < Res.size(); i++)
	{
		Res[i] = i;
	}

	return Res;
}

bool PockerTest(const std::string &input, const float RangeLeft, const float RangeRight, bool Debug)
{
	bool CurrentBit;
	char CurrentBlock = 0;

	int Y = (input.length() * 8);
	const int m = 4;
	int k = (Y % m)? Y/m: Y/m + 1;
	
	std::vector<char> PockerVals = CreatePockerValues(m);
	std::vector<int> n(PockerVals.size(), 0);

	// Iterate over each possible block
	for (int j = 0; j < n.size(); j++)
	{
		// Iterate over each bit
		for (int i = 0; i < Y; i++)
		{
			// Create CurrentBlock
			CurrentBit = input[i / 8] >> (7 - (i % 8)) & 1;
			CurrentBlock |= CurrentBit;

			// When CurrentBlock is formed - compare it to Current PockerVal block
			if (i % m == m - 1)
			{
				n[j] += (PockerVals[j] == CurrentBlock);
				CurrentBlock = 0;
			}
			else
			{
				CurrentBlock <<= 1;
			}
		}
	}

	// Calculate X_3
	float X_3;
	unsigned long sum = 0;
	for (auto val : n)
	{
		sum += pow(val, 2);
	}
	X_3 = pow(2, m) / k * sum - k;

	// Show how much of each block were found
	if (Debug)
	{
		for (int i = 0; i < n.size(); i++)
		{
			std::cout << std::bitset<m>(PockerVals[i]).to_string() << ": " << n[i] << std::endl;
		}

		std::cout << "X_3: " << X_3 << std::endl;
	}

	if (X_3 > RangeLeft && X_3 < RangeRight) { return true; }

	return false;
}

bool SeriesLenTest(const std::string &input, const std::vector<std::vector<int>> &CheckRanges, bool Debug)
{
	bool Res = true;

	bool SeriesBorder = input[0] >> 7;
	bool CurrentBit;
	int len = 1;

	int TotalSz = input.length() * 8;

	// SeriesStats are vectors that stores number of series of specific length,
	// where SeriesStats[][i - 1] = number of series of either '0' or '1', which length = i.
	// SeriesStats[][CheckRanges.size() - 1] stores amount of series with length >= CheckRanges.size().
	// SeriesStats[0] stores stas for '0', SeriesStats[1] - for '1'
	std::vector<std::vector<int>> SeriesStats(2, std::vector<int>(CheckRanges.size(), 0));

	for (int i = 1; i <= TotalSz; i++)
	{
		// Calculate current bit
		CurrentBit = input[i / 8] >> (7 - (i % 8)) & 1;

		if (CurrentBit == SeriesBorder && i != TotalSz)
		{
			// If the series continues
			++len;
		}
		else
		{
			// If the series is over
			// std::cout << "Len of '" << SeriesBorder << "' = " << len << std::endl;

			// Update SeriesStats
			++SeriesStats[CurrentBit][(len < CheckRanges.size()) ? (len - 1) : CheckRanges.size() - 1];

			// Change border value to oposit (aka CurrentBit)
			SeriesBorder = !SeriesBorder;
			len = 1;
		}
	}

	// Check SeriesStats
	for (int j = 0; j <= 1; j++)
	{
		if (Debug) { std::cout << std::endl << "Stats for '" << j << "': " << std::endl; }

		for (int i = 0; i < CheckRanges.size();i++)
		{
			if (Debug)
			{
				std::cout << "Len = " << i + 1 << ": " << SeriesStats[j][i] << std::endl;
			}

			if (SeriesStats[j][i] < CheckRanges[i][0] || SeriesStats[j][i] > CheckRanges[i][1])
			{
				Res = false;

				if (!Debug) { return Res; }
			}
		}
	}

	return Res;
}
