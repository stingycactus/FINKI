//
// Created by cactus on 19/05/2026.
//
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
int main() {
    ifstream file("input.txt");
    ofstream outputFile("output.txt");
    if (!file.is_open()) {
        cout<<"Cannot open input file"<<'\n';
        return -1;
    }
    if (!outputFile.is_open()) {
        cout<<"Cannot open output file"<<'\n';
        return -1;
    }
    string line;
    while (getline(file, line)) {
        int lineLength = line.length();
        outputFile<<lineLength<<'\n';
        outputFile<<line<<'\n';
    }
    file.close();
    outputFile.close();
    return 0;
}