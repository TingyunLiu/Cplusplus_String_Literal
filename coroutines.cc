#include "coroutines.h"					// Header for coroutine

//--------------------------------------------------------------------------------------------------------------------
// StringLiteral::is_octal_digit checks if a char is an octal-digit
//--------------------------------------------------------------------------------------------------------------------
bool StringLiteral::is_octal_digit() {
    return (this->ch >= '0') && (this->ch <= '7');	// check octal digit range [0, 7]
} // StringLiteral::is_octal_digit


//--------------------------------------------------------------------------------------------------------------------
// StringLiteral::is_simple_escape_char checks if a char is a simple-escape-char
//--------------------------------------------------------------------------------------------------------------------
bool StringLiteral::is_simple_escape_char() {
    int len = sizeof(simple_escape_chars)/sizeof(simple_escape_chars[0]);	// calculate len
    for (int i = 0; i < len; i++) {											
        if (this->ch == simple_escape_chars[i]) return true;						// found it
    } // for
    return false;															// not a simple escape char
} // StringLiteral::is_simple_escape_char


//--------------------------------------------------------------------------------------------------------------------
// StringLiteral::octal_escape_sequence verifies if a series of characters can be parsed as octal-escape-sequence
//--------------------------------------------------------------------------------------------------------------------
void StringLiteral::octal_escape_sequence() {
    for (int i = 1; i < OCTAL_DIGIT_SEQUENCE_MAX; i++) {
        if (!is_octal_digit()) break;										// break when it is not a octal digit
        suspend();
    } // for
} // StringLiteral::octal_escape_sequence


//--------------------------------------------------------------------------------------------------------------------
/* StringLiteral::hexadecimal_escape_sequence verifies if a series of characters can be parsed as
	hexadecimal-escape-sequence */
//--------------------------------------------------------------------------------------------------------------------
void StringLiteral::hexadecimal_escape_sequence() {
    for (;;) {
        if (!isxdigit(this->ch)) break;											// break when it is not a hex digit
        suspend();
    } // for
} // StringLiteral::hexadecimal_escape_sequence


//--------------------------------------------------------------------------------------------------------------------
// StringLiteral::main uses C++ string-literal grammars to verify if a string is valid in C++
//--------------------------------------------------------------------------------------------------------------------
void StringLiteral::main() {
	/* encoding-prefix-opt part */
    if (ch == 'u') { 								/* handle encoding-prefix-opt u */
        suspend();
        if (ch == '8') { 							/* handle encoding-prefix-opt u8 */
            suspend();
        } // if
    } else if ((ch == 'U') || (ch == 'L')) { 		/* handle encoding-prefix-opt U and L */
        suspend();
    } // if

    /* "s-char-sequence" part or empty encoding-prefix-opt */
    if (ch == '"') {
        suspend();
        for (;;){
            if (ch == '"') { 						/* handle double-quote character */
                _Resume Match() _At uThisTask();	/* Match */
            } else if (ch == '\\') { 				/* handle backslash character and escape-sequence */
                suspend();
                if (is_simple_escape_char()) { 	/* handle simple-escape-sequence */
                    /* Do nothing, go to suspend at the end of for loop */
                } else if (is_octal_digit()) { 	/* handle octal-escape-sequence */
                    suspend();
                    octal_escape_sequence();		/* handle octal-escape-sequence */
                    continue;						/* current character is not a octal digit */
                } else if (ch == 'x') { 			/* handle hexadecimal-escape-sequence */
                    suspend();
                    if (!isxdigit(ch)) _Resume Error() _At uThisTask(); /* must have at least one hex-digit */
                    suspend();
                    hexadecimal_escape_sequence();/* handle hexadecimal-escape-sequence */
                    continue;						/* current character is not a hexadecimal digit */
                } else { 							
                    _Resume Error() _At uThisTask();/* handle backslash character but not part of escape-sequence */
                } // if
            } else if (ch == '\0') { 				/* handle new line character */
                _Resume Error() _At uThisTask();
            } // if
            suspend();								/* suspend until next char to be read */
        } // for
	} else {										/* incorrect encoding-prefix-opt */
	    _Resume Error() _At uThisTask();
	    suspend();
	} // if
} // StringLiteral::main


//--------------------------------------------------------------------------------------------------------------------
// StringLiteral::next processes the next character, activate and transfer the control flow to coroutine main
//--------------------------------------------------------------------------------------------------------------------
void StringLiteral::next(char c) {
	ch = c;								// communication input				
	resume();							// activate
} // StringLiteral::next

