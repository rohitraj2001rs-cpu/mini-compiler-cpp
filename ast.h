#ifndef AST_H
#define AST_H

#include <memory>
#include <string>

using namespace std;

struct ASTNode {

    string value;

    shared_ptr<ASTNode> left;
    shared_ptr<ASTNode> right;

    ASTNode(
        const string& val,
        shared_ptr<ASTNode> l = nullptr,
        shared_ptr<ASTNode> r = nullptr
    ) {

        value = val;
        left = l;
        right = r;
    }
};

#endif