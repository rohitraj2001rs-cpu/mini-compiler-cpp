#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <stdexcept>
#include <sstream>
#include <memory>
#include "ast.h"
#include "symbol_table.h"

using namespace std;

// =========================
// TOKEN
// =========================

enum class TokenType {
    IDENTIFIER,
    NUMBER,

    PLUS,
    MINUS,
    MULTIPLY,
    DIVIDE,

    ASSIGN,
    LPAREN,
    RPAREN,

    END
};

struct Token {
    TokenType type;
    string value;
};

// =========================
// LEXER
// =========================

class Lexer {
private:
    string input;
    size_t position;

public:
    Lexer(const string& source) {
        input = source;
        position = 0;
    }

    vector<Token> tokenize() {
        vector<Token> tokens;

        while (position < input.length()) {

            if (isspace(input[position])) {
                position++;
                continue;
            }

            // Identifier
            if (isalpha(input[position])) {
                string value;

                while (position < input.length() &&
                       isalnum(input[position])) {

                    value += input[position];
                    position++;
                }

                tokens.push_back({
                    TokenType::IDENTIFIER,
                    value
                });

                continue;
            }

            // Number
            if (isdigit(input[position])) {
                string value;

                while (position < input.length() &&
                       isdigit(input[position])) {

                    value += input[position];
                    position++;
                }

                tokens.push_back({
                    TokenType::NUMBER,
                    value
                });

                continue;
            }

            char current = input[position];

            switch (current) {

                case '+':
                    tokens.push_back({
                        TokenType::PLUS,
                        "+"
                    });
                    break;

                case '-':
                    tokens.push_back({
                        TokenType::MINUS,
                        "-"
                    });
                    break;

                case '*':
                    tokens.push_back({
                        TokenType::MULTIPLY,
                        "*"
                    });
                    break;

                case '/':
                    tokens.push_back({
                        TokenType::DIVIDE,
                        "/"
                    });
                    break;

                case '=':
                    tokens.push_back({
                        TokenType::ASSIGN,
                        "="
                    });
                    break;

                case '(':
                    tokens.push_back({
                        TokenType::LPAREN,
                        "("
                    });
                    break;

                case ')':
                    tokens.push_back({
                        TokenType::RPAREN,
                        ")"
                    });
                    break;

                default:
                    throw runtime_error(
                        "Invalid character: " +
                        string(1, current)
                    );
            }

            position++;
        }

        tokens.push_back({
            TokenType::END,
            ""
        });

        return tokens;
    }
};

// =========================
// PARSER
// =========================

class Parser {

private:

    vector<Token> tokens;
    size_t position;

    Token current() {
        return tokens[position];
    }

    void consume(TokenType expected) {

        if (current().type != expected) {
            throw runtime_error("Syntax error");
        }

        position++;
    }

    shared_ptr<ASTNode> expression() {

        auto node = term();

        while (
            current().type == TokenType::PLUS ||
            current().type == TokenType::MINUS
        ) {

            string op = current().value;
            position++;

            auto right = term();

            node = make_shared<ASTNode>(
                op,
                node,
                right
            );
        }

        return node;
    }

    shared_ptr<ASTNode> term() {

        auto node = factor();

        while (
            current().type == TokenType::MULTIPLY ||
            current().type == TokenType::DIVIDE
        ) {

            string op = current().value;
            position++;

            auto right = factor();

            node = make_shared<ASTNode>(
                op,
                node,
                right
            );
        }

        return node;
    }

    shared_ptr<ASTNode> factor() {

        if (current().type == TokenType::NUMBER ||
            current().type == TokenType::IDENTIFIER) {

            string value = current().value;

            position++;

            return make_shared<ASTNode>(value);
        }

        if (current().type == TokenType::LPAREN) {

            position++;

            auto node = expression();

            consume(TokenType::RPAREN);

            return node;
        }

        throw runtime_error("Invalid expression");
    }

public:

    Parser(const vector<Token>& input) {
        tokens = input;
        position = 0;
    }

    shared_ptr<ASTNode> parse() {

        if (current().type != TokenType::IDENTIFIER) {
            throw runtime_error(
                "Assignment must start with identifier"
            );
        }

        string variable = current().value;

        position++;

        consume(TokenType::ASSIGN);

        auto expressionTree = expression();

        if (current().type != TokenType::END) {
            throw runtime_error(
                "Unexpected token after expression"
            );
        }

        return make_shared<ASTNode>(
            "=",
            make_shared<ASTNode>(variable),
            expressionTree
        );
    }
};

// =========================
// TAC GENERATOR
// =========================

class TACGenerator {

private:

    int tempCount;

    string newTemp() {
        tempCount++;

        return "T" + to_string(tempCount);
    }

    string generate(
        shared_ptr<ASTNode> node,
        vector<string>& code
    ) {

        if (!node->left && !node->right) {
            return node->value;
        }

        if (node->value == "=") {

            string left =
                generate(node->left, code);

            string right =
                generate(node->right, code);

            code.push_back(
                left + " = " + right
            );

            return left;
        }

        string left =
            generate(node->left, code);

        string right =
            generate(node->right, code);

        string temp = newTemp();

        code.push_back(
            temp + " = " +
            left + " " +
            node->value + " " +
            right
        );

        return temp;
    }

public:

    TACGenerator() {
        tempCount = 0;
    }

    vector<string> generateTAC(
        shared_ptr<ASTNode> root
    ) {

        vector<string> code;

        generate(root, code);

        return code;
    }
};

// =========================
// MAIN
// =========================

int main() {

    cout << "=====================================\n";
    cout << "       MINI C++ COMPILER\n";
    cout << "=====================================\n\n";

    string input;

    cout << "Enter expression:\n";
    getline(cin, input);

    try {

        // -------------------------
        // LEXICAL ANALYSIS
        // -------------------------

        Lexer lexer(input);

        vector<Token> tokens =
            lexer.tokenize();

        cout << "\n--- TOKENS ---\n";

        for (const auto& token : tokens) {

            if (token.type == TokenType::END)
                break;

            cout << token.value << " ";
        }

        cout << "\n";

        // -------------------------
        // SYNTAX ANALYSIS
        // -------------------------

        Parser parser(tokens);

        auto ast = parser.parse();

        cout << "\nSyntax Analysis: SUCCESS\n";

        // -------------------------
        // TAC GENERATION
        // -------------------------

        TACGenerator generator;

        vector<string> tac =
            generator.generateTAC(ast);

        cout << "\n--- THREE ADDRESS CODE ---\n";

        for (const string& instruction : tac) {
            cout << instruction << endl;
        }

        cout << "\nCompilation completed successfully.\n";
    }

    catch (const exception& error) {

        cout << "\nCompilation Error: "
             << error.what()
             << endl;
    }

    return 0;
}