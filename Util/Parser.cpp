#include "Parser.hpp"

vector<string> Parser::split(string str, string sep){
    char* cstr=const_cast<char*>(str.c_str());
    char* current;
    std::vector<std::string> arr;
    current=strtok(cstr,sep.c_str());
    while(current!=NULL){
        arr.push_back(current);
        current=strtok(NULL,sep.c_str());
    }
    return arr;
}

// parse (x,y,z,r,g,b) to vector of float
vector<float> Parser::parsePoint(string pointString, bool randomizeColor, int varietyColor) {
    // ["x", "y", "z", "r", "g", "b"]
    vector<string> pointComponentString = Parser::split(pointString.substr(1, pointString.length()-2), ",");
    vector<float> pointComponent;
    
    // take coordinat component [x,y,z]
    for (int i=0; i<3; i++) {
        pointComponent.push_back(strtof(pointComponentString[i].c_str(), NULL));
    }

    // take color component [r,g,b]
    if (randomizeColor) {
        for (int i=0; i<3; i++) {
            int randInt = rand()%varietyColor;
            double randDouble = (1.0*randInt)/(varietyColor*1.0);
            pointComponent.push_back(randDouble);
        }
    } else {
        for (int i=3; i<pointComponentString.size(); i++) {
            pointComponent.push_back(strtof(pointComponentString[i].c_str(), NULL));
        }   
    }

    // [x,y,z,r,g,b]
    return pointComponent;
}

// parse ("idx1", "idx2", "idx3") to vector of float
vector<unsigned int> Parser::parseIndex(string indexString) {
    // ["idx1", "idx2", "idx3"]
    vector<string> indexComponentString = Parser::split(indexString.substr(1, indexString.length()-2), ",");
    vector<unsigned int> indexComponent;
    for (int i=0; i<indexComponentString.size(); i++) {
        indexComponent.push_back(stoi(indexComponentString[i]));
    }

    // [idx1, idx2, idx3]
    return indexComponent;
}

vector<float> Parser::loadPoints(string filename, bool randomizeColor, int varietyColor) {
    ifstream file;
    vector<float> points;
    file.open(filename);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            if (line != "") {
                vector<float> point = Parser::parsePoint(line, randomizeColor, varietyColor);
                for (int i=0; i<point.size(); i++) {
                    points.push_back(point[i]);
                }
            }
        }
    }

    file.close();
    return points;
}

vector<unsigned int> Parser::loadIndices(string filename) {
    ifstream file;
    vector<unsigned int> indices;
    file.open(filename);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            if (line != "") {
                vector<unsigned int> index = Parser::parseIndex(line);
                for (int i=0; i<index.size(); i++) {
                    indices.push_back(index[i]);
                }
            }
        }
    }

    file.close();
    return indices;
}