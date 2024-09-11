// .cpp File

#include "grammar.h"
#include <fstream>
#include <sstream>

//******************************************************************************

Grammar::Grammar() { // Constructor to initialize startSymbol to an empty string
    startSymbol = "";
}
//******************************************************************************

void Grammar::readGrammar(ifstream& filename) {  
    if (filename.is_open()) {

        string line;
        while (getline(filename, line)) {
            istringstream token(line);  
            string lhs, arrow, rhs;

            token >> lhs >> arrow;  // Read non-terminal and the '->' symbol

            if (startSymbol.empty()) { // If startSymbol is empty, the first lhs is set to the startSymbol
                startSymbol = lhs;
            }

            if (find(nonTerminals.begin(), nonTerminals.end(), lhs) == nonTerminals.end()) { // lhs is added to the non-terminal list if it isnt there already
                nonTerminals.push_back(lhs);
            }

            getline(token, rhs, ';'); // rhs is read until the semicolon (this is the right-hand side)

            istringstream rhsToken(rhs); // rhs is split into individual productions (using spaces)
            string production;

            while (rhsToken >> production) {
                if (production != "|") {

                    addProduction(lhs, production); // production is added to the list for the current lhs

                    for (char c : production) { // production is broken into individual characters
                        if (isupper(c)) { // If the character is an uppercase letter, it's a non-terminal
                            string nt(1, c);
                            if (find(nonTerminals.begin(), nonTerminals.end(), nt) == nonTerminals.end()) {
                                nonTerminals.push_back(nt);
                            }
                        } else if (islower(c) || c == '&') { // If it's a lowercase letter or &, it's a terminal
                            string terminal(1, c);
                            if (find(terminals.begin(), terminals.end(), terminal) == terminals.end()) {
                                terminals.push_back(terminal);
                            }
                        }
                    }
                }
            }
        }
        filename.close();
    } else {
        cerr << "Error: Unable to open file." << endl;
        return;
    }
}
//******************************************************************************

void Grammar::addProduction(string nonTerminal, const string& production) {
    productions[nonTerminal].push_back(production); // the production is added to the list of productions for a given non-terminal
}
//******************************************************************************

void Grammar::printGrammar() const {
    cout << "Start Symbol: " << startSymbol << endl;

    cout << "Terminals: ";
    for (size_t i = 0; i < terminals.size(); ++i) {
        cout << terminals[i] << " ";
    }
    cout << endl;

    cout << "Non-Terminals: ";
    for (size_t i = 0; i < nonTerminals.size(); ++i) {
        cout << nonTerminals[i] << " ";
    }
    cout << endl;

    cout << "Productions:\n";
    for (auto it = productions.begin(); it != productions.end(); ++it) {
        cout << it->first << " -> ";

        // Loop through the productions and print each one
        for (size_t i = 0; i < it->second.size(); ++i) {
            cout << it->second[i];
            // Print " | " only between productions, not after the last one
            if (i < it->second.size() - 1) {
                cout << " | ";
            }
        }
        cout << endl;
    }
}

//******************************************************************************