// main.cpp

#include "grammar.h"
#include <iostream>
#include <fstream>

int main() {
    Grammar grammar;

    string filename = "grammar.txt"; 

    ifstream file(filename);

    grammar.readGrammar(file);

    grammar.printGrammar();

    return 0;
}
