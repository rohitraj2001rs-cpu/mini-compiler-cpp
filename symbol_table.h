#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;

class SymbolTable {

private:
    unordered_map<string, string> symbols;

public:

    void insert(const string& name, const string& type) {
        symbols[name] = type;
    }

    bool contains(const string& name) const {
        return symbols.find(name) != symbols.end();
    }

    string getType(const string& name) const {

        auto it = symbols.find(name);

        if (it != symbols.end()) {
            return it->second;
        }

        return "undefined";
    }

    void display() const {

        cout << "\n--- SYMBOL TABLE ---\n";

        cout << "Identifier\tType\n";

        for (const auto& entry : symbols) {
            cout << entry.first
                 << "\t\t"
                 << entry.second
                 << endl;
        }
    }
};

#endif