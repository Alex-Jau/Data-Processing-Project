/*This thing is to test the comment 
ignoring capabilities*/

#include "lexer.h"

// Function to print tokens
void printTokens(vector<Token>& tokens) {
    for (Token& token : tokens) {
        cout << token.GetOutputString() << endl;
    }
}

int main() {
    string filename;
    cout << "Enter the name of the file: ";
    getline(cin, filename);
//    filename = "sampleText";
    //if to demonstrated operators.
    if (false || true == false){
        cout << "Gregstack";
    }

    Lex lex(filename);
    vector<Token> tokens = lex.getTokens();
    printTokens(tokens);

    return 0;
}