#ifndef __PARSER__
#define __PARSER__

#include <bits/stdc++.h>
using namespace std;

class Parser {
private:
    static vector<string> split(string str, string sep);
    static vector<float> parsePoint(string pointString);
    static vector<unsigned int> parseIndex(string indexString);

public:
    static vector<float> loadPoints(string filename);
    static vector<unsigned int> loadIndices(string filename);
};

#endif