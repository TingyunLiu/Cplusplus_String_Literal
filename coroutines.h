//--------------------------------------------------------------------------------------------------------------------
/* Header for the definition of a Coroutine StringLiteral which can verifies a string of characters corresponds
 to a C++ string-literal */
//--------------------------------------------------------------------------------------------------------------------

#define OCTAL_DIGIT_SEQUENCE_MAX 3      // maximum consecutive octal digit as part of octal-escape-sequence


/* Array of chars that are simple-escape-char */
const char simple_escape_chars[] = {
    '\'', '\"', '?', '\\', 'a', 'b', 'f', 'n', 'r', 't', 'v'
};


_Coroutine StringLiteral {          
    char ch;                            // current character that is processing
    void main();                        // coroutine main
    bool is_octal_digit();              // check if a char is an octal-digit
    bool is_simple_escape_char();       // check if a char is a simple-escape-char
    void octal_escape_sequence();       // check if a series of characters can be parsed as octal-escape-sequence
    /* check if a series of characters can be parsed as hexadecimal-escape-sequence */
    void hexadecimal_escape_sequence();
public:
    _Event Match {};                    // Exception for Match, last character match
    _Event Error {};                    // Exception for Error, last character invalid
    void next(char c);                  // Getting next character
};

