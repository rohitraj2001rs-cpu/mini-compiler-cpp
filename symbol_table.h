#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;

class SymbolTable {

private:

    unordered_map<string, string> table;

public:

    void insert(
        const string& name,
        const string& type
    ) {

        table[name] = type;
    }

    bool exists(
        const string& name
    ) {

        return table.find(name)
               != table.end();
    }

    string getType(
        const string& name
    ) {

        if (!exists(name)) {
            return "undefined";
        }

        return table[name];
    }

    void display() {

        cout << "\n--- SYMBOL TABLE ---\n";

        for (auto& entry : table) {

            cout << entry.first
                 << " : "
                 << entry.second
                 << endl;
        }
    }
};

#endif