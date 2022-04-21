#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <string>
#include <fstream>

using namespace std;

void createOutputFile(string text, string fileName) {
    ofstream file;
    file.open((fileName + ".txt").c_str());
    file << text;
    file.close();
}

#endif