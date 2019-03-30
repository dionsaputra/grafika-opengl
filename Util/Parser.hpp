#ifndef __PARSER__
#define __PARSER__

#include <bits/stdc++.h>
using namespace std;

class Parser {
private:
    static vector<string> split(string str, string sep);
    static vector<float> parsePoint(string pointString, bool randomizeColor, int varietyColor);
    static vector<unsigned int> parseIndex(string indexString);

public:
    static vector<float> loadPoints(string filename, bool randomizeColor=false, int varietyColor=0);
    static vector<unsigned int> loadIndices(string filename);
};

#endif