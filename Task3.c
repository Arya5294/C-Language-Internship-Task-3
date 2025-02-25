/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_IDENTIFIER_LEN 31  // Maximum length for identifiers
#define MAX_KEYWORDS 32        // Total number of C keywords to check

// Array of C keywords for comparison
const char *keywords[] = {
    "auto", "break", "case", "char", "const", "continue", "default", "do",
    "double", "else", "enum", "extern", "float", "for", "goto", "if",
    "int", "long", "register", "return", "short", "signed", "sizeof", "static",
    "struct", "switch", "typedef", "union", "unsigned", "void", "volatile", "while"
};

// Function to check if a string matches a keyword
int is_keyword(const char *str) {
    for (int i = 0; i < MAX_KEYWORDS; i++) {
        if (strcmp(str, keywords[i]) == 0) {  // Compare the string with each keyword
            return 1;  // Return true if a match is found
        }
    }
    return 0;  // Return false if no match is found
}

// Function to check if a character is an operator
int is_operator(char ch) {
    return (strchr("+-*/%=<>!&|^~", ch) != NULL);  // Check if the character is in the list of operators
}

// Function to analyze and classify a token
void analyze_token(char *token) {
    if (strlen(token) == 0) return;  // Skip empty tokens

    if (is_keyword(token)) {  // Check if the token is a keyword
        printf("Keyword: %s\n", token);
    } else if (isdigit(token[0])) {  // Check if the token starts with a digit
        printf("Number: %s\n", token);
    } else if (isalpha(token[0]) || token[0] == '_') {  // Check if the token starts with a letter or underscore
        printf("Identifier: %s\n", token);
    }
}

int main() {
    char ch, token[MAX_IDENTIFIER_LEN + 1];  // `ch` stores the current character; `token` stores the current token
    int token_pos = 0;  // Current position in the token array

    printf("Enter your code (press Ctrl+D or Ctrl+Z to end):\n");

    // Loop to process input character by character
    while ((ch = getchar()) != EOF) {
        if (isspace(ch)) {  // If the character is a space or newline
            token[token_pos] = '\0';  // Terminate the token string
            analyze_token(token);  // Analyze the completed token
            token_pos = 0;  // Reset the token position
        } else if (is_operator(ch)) {  // If the character is an operator
            if (token_pos > 0) {  // Analyze the current token if it exists
                token[token_pos] = '\0';
                analyze_token(token);
                token_pos = 0;  // Reset the token position
            }
            printf("Operator: %c\n", ch);  // Print the operator
        } else if (isalnum(ch) || ch == '_') {  // If the character is alphanumeric or an underscore
            if (token_pos < MAX_IDENTIFIER_LEN) {  // Add the character to the token if it's within length limits
                token[token_pos++] = ch;
            }
        } else {  // For other special characters (e.g., delimiters)
            if (token_pos > 0) {  // Analyze the current token if it exists
                token[token_pos] = '\0';
                analyze_token(token);
                token_pos = 0;  // Reset the token position
            }
            // Print delimiters like ';', ',', '(', ')', etc.
            if (ch == ';' || ch == ',' || ch == '(' || ch == ')' || 
                ch == '{' || ch == '}' || ch == '[' || ch == ']') {
                printf("Delimiter: %c\n", ch);
            }
        }
    }

    // Analyze any remaining token after the loop ends
    if (token_pos > 0) {
        token[token_pos] = '\0';
        analyze_token(token);
    }

    return 0;  // Exit the program
}
