#pragma once

#include <string>
#include <vector>

void CreateRandSeq(std::string* oput, int Length);

bool MonobitTest(const std::string &input, const int RangeLeft = 9654, const int RangeRight = 10346, bool Debug=true);
bool MaxSeriesLenTest(const std::string &input, const int MaxSeriesSz = 36, bool Debug = true);
bool PockerTest(const std::string &input, const float RangeLeft, const float RangeRight, bool Debug = true	);
bool SeriesLenTest(const std::string &input, const std::vector<std::vector<int>>& CheckRanges, bool Debug = true);