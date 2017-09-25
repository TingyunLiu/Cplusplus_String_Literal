#include <iostream>                             // input and output
#include <fstream>                              // to choose the input source (stdin or command line infile)
#include <cstdlib>                              // exit
#include <string>                               // for string and getline
#include "coroutines.h"                         // coroutine header file
using namespace std;                            // direct access to std


//--------------------------------------------------------------------------------------------------------------------
// Program for usage error handling
//--------------------------------------------------------------------------------------------------------------------
static void usage(char *argv[]) {
    cerr << "Usage: " << argv[0] << " [infile-file]" << endl;
    exit( EXIT_FAILURE );                       // TERMINATE
} // usage


//--------------------------------------------------------------------------------------------------------------------
/* Program to print an appropriate message when the coroutine returns exception Match or Error,
    or if there are no more characters to send */
//--------------------------------------------------------------------------------------------------------------------
static void print_msg(string str, unsigned int index, bool is_valid){
    cout << "'" << str << "' : '";                                          // print original string
    cout << str.substr(0, index+1) << "' ";                                 // print processed part
    if (is_valid) {
        cout << "yes";                                                      // valid C++ string             
    } else {
        cout << "no";                                                       // invalid C++ string
    }
    /* print extra character that are not processed because of an exception, if not finished processing the string */
    if ((index+1) < str.length()) cout << " -- extraneous characters '" << str.substr(index+1) << "'";
    cout << endl;                                                           // print new line character
} // print_msg


//--------------------------------------------------------------------------------------------------------------------
// Main driver for the program.  Reads in the strings and calls the appropriate routines.
//--------------------------------------------------------------------------------------------------------------------
int main(int argc, char *argv[]) {
    istream *infile = &cin;                     // default value
    switch ( argc ) {
        case 2:
            try {
                infile = new ifstream(argv[1]);
            } catch( uFile::Failure ) {
                cerr << "Error! Could not open input file \"" << argv[1] << "\"" << endl;
                exit(EXIT_FAILURE);
            } // try
            // FALL THROUGH
        case 1:                                 // all defaults
            break;
        default:                                // wrong number of options
            usage(argv);
    } // switch

    *infile >> noskipws;                        // turn off white space skipping during input

    for (;;) {
        string line;
        getline(*infile, line);
        if (infile->fail()) break;              // failed ?
        int len = line.length();

        StringLiteral str;

        int cur_index = 0;                      /* Keep track of the index of current char in the line */
        
        try {
            _Enable <StringLiteral::Match> <StringLiteral::Error> { /* Allow non-local exceptions */
                for (int i = 0; i < len; i++) {
                    cur_index = i;
                    str.next(line[i]);          /* Pass one character at a time */
                } // for
                
                if (!len) {
                    /* Deal with empty input line */
                    cout << "'' : Warning! Blank line." << endl;
                } else {
                    /* Throw local exception because no more char and no Match yet */
                    _Throw StringLiteral::Error();
                } // if
            } // _Enable
        } catch (StringLiteral::Match) {        /* Valid C++ string literal */
            print_msg(line, cur_index, true);
        } // catch 
          catch (StringLiteral::Error) {        /* Invalid C++ string literal */
            print_msg(line, cur_index, false);
        } // catch
    } // for

    if (infile != &cin) delete infile;          // close file, do not delete cin!
} // main

