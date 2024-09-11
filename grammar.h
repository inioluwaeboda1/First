#ifndef GRAMMAR_H
#define GRAMMAR_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;


class Grammar {
private:
    vector<string> terminals;        // vector to store terminal symbols
    vector<string> nonTerminals;     // vector to store non-terminal symbols
    map<string, vector<string>> productions; // Map to store productions
    string startSymbol;                // Start symbol of the grammar

public:
    Grammar(); // Constructor

    void readGrammar(ifstream& filename); // Function to read grammar from a file

    void addProduction(string nonTerminal, const string& production);  // Function to print the grammar

    void printGrammar() const; // Function to print the grammar
};

#endif // GRAMMAR_H
