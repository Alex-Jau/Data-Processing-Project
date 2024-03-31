#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <string>
#include <iomanip>
#include <cctype>
using namespace std;

enum Type {
    LITERAL,
    IDENTIFIER,
    SEPARATOR,
    OPERATOR,
    KEYWORD,
    ERROR,
};

const string typeStrings[] = {"LITERAL","IDENTIFIER","SEPARATOR","OPERATOR","KEYWORD","ERROR"};

class Token {
    public:
    Token(Type t, string l){token = t;lexxe = l;};
    string GetOutputString(){return "Token: "+typeStrings[token]+", Lexeme: "+lexxe;}
    Type GetType(){return token;}

    private:
    string lexxe;
    Type token;
};

class Lex{
    public:
    Lex(string f){textFile = f;engageLex();}
    vector<Token> getTokens(){return tokenVector;}
    void engageLex();

    private:
    vector<Token> tokenVector;
    string textFile;
};

//Function for checking for if something is a identifier
bool isIdentifier(char lexxe) {
    return tolower(lexxe) == '_' || (tolower(lexxe) >= 'a' && tolower(lexxe) <= 'z');
}

//Function for checking for if something is a digit
bool isNumber(char lexxe) {
    return std::isdigit(lexxe) || lexxe == '.';
}

//Function for checking for null Terminator/end of file
bool isNullTerm(char lexxe){
    return (lexxe == '\0');
}

//Function for space checking
bool isSpace(char lexeme){
    return (lexeme == ' ' || lexeme == '\t' || lexeme == '\r' || lexeme == '\n');
}

// Function to check if a string is a Operator
bool isOperator(char lexxe) {
    const std::string operators = "=+-*/%<>&|!";
    return operators.find(lexxe) != std::string::npos;
}

// Function to check if a string is a Separator
bool isSeparator(char lexxe) {
    const string separators = "(){}:;#[],";
    return separators.find(lexxe) != std::string::npos;
}

// Function to check if a string is a keyword
bool isKeyword(const string& word) {
    static const vector<string> keywords = {"true","false","void","while", "endwhile", "if", "else", "do", "for", "get", "put", "return", "int", "fi", "def", "print"}; // Add more keywords as needed
    for (const string& keyword : keywords) {
        if (word == keyword)
            return true;
    }
    return false;
}

void Lex::engageLex(){
    ifstream inputFile;
    inputFile.open(textFile+".txt");
    if (!inputFile.is_open()) {
        cerr << "Error: Could not open file " << textFile << endl;
        exit(1);
    }

    string line;
    bool inComment = false;

    while (getline(inputFile, line)) {
        for (size_t i = 0; i < line.length(); ++i) {
            char currentChar = line[i];

            // Skip comments
            if (currentChar == '/') {
                if (i + 1 < line.length() && line[i + 1] == '/')
                    break;  // Single-line comment
                else if (i + 1 < line.length() && line[i + 1] == '*') {
                    ++i;  // Skip the asterisk
                    while (i + 1 < line.length() && !(line[i] == '*' && line[i + 1] == '/'))
                        ++i;  // Multi-line comment
                    ++i;  // Skip the closing '/'
                    continue;
                }
            }

            // Check for string literals
            if (currentChar == '"') {
                string literal;
                literal += currentChar;
                while (i + 1 < line.length() && line[i + 1] != '"') {
                    literal += line[++i];
                }
                if (i + 1 < line.length())  // Avoid out-of-bounds access
                    literal += line[++i];  // Include the closing '"'
                tokenVector.emplace_back(LITERAL, literal);
            }

            // Check for identifiers and keywords
            else if (isalpha(currentChar) || currentChar == '_') {
                string word;
                word += currentChar;
                while (i + 1 < line.length() && (isalnum(line[i + 1]) || line[i + 1] == '_'))
                    word += line[++i];
                if (isKeyword(word))
                    tokenVector.emplace_back(KEYWORD, word);
                else
                    tokenVector.emplace_back(IDENTIFIER, word);
            }

            // Check for operators
            else if (isOperator(currentChar)) {
                string word;
                word += currentChar;
                if (i + 1 < line.length() && (isOperator(line[i + 1])))
                    word += line[++i];
                tokenVector.emplace_back(OPERATOR, string(word));
            }

            // Check for separators
            else if (isSeparator(currentChar)) {
                tokenVector.emplace_back(SEPARATOR, string(1, currentChar));
            }
        }
    }

//    tokenVector.emplace_back(IDENTIFIER, "word");
    inputFile.close();
}