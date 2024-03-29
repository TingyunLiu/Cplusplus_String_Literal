# Cplusplus_String_Literal

+--------+-----------------------------------------------------------------------+
| Test # | Purpose of Tests                                                      |
+--------+-----------------------------------------------------------------------+
| 1-3    | Tests the command line parsing                                        |
+--------+-----------------------------------------------------------------------+
| 4-10   | Tests that the strings are valid C++ string-literal (Match)           |
+--------+-----------------------------------------------------------------------+
| 11     | Tests that empty input line warning                                   |
+--------+-----------------------------------------------------------------------+
| 12-17  | Tests that the strings are NOT valid C++ string-literal (Error)       |
+--------+-----------------------------------------------------------------------+

+--------+-----------------+-----------------+-----------------------------------+-----------------------------------+
| Test # | Type of Test    | Line #s         | Reason for Test                   | Analysis of Test                  |
+--------+-----------------+-----------------+-----------------------------------+-----------------------------------+
| 1      | Invalid         | Part A, 1-2     | The program can only have 0 or 1  | Usage error is printed because we |
|        | command-line    |                 | optional command-line argument.   | passed 2 command-line arguments.  |
|        | argument #      |                 |                                   |                                   |
+--------+-----------------+-----------------+-----------------------------------+-----------------------------------+
| 2      | Invalid         | Part A, 3-4     | The program can only open an      | Error message is printed because  |
|        | command-line    |                 | existing file.                    | we passed a file that does not    |
|        | argument        |                 |                                   | exist in current directory.       |
+--------+-----------------+-----------------+-----------------------------------+-----------------------------------+
| 3      | Invalid         | Part A, 5-7     | The program can only open an      | Error message is printed because  |
|        | command-line    |                 | readable file.                    | we passed a file that is not      |
|        | argument        |                 |                                   | readable.                         |
+--------+-----------------+-----------------+-----------------------------------+-----------------------------------+
| 4      | Valid string    | Part B, 2, 12   | A valid C++ string-literal can    | Valid C++ string-literal because  |
|        | with encoding   |                 | only accept one of "u8", "u",     | the string has a valid encoding   |
|        | prefix opt      |                 | "U", "L" as an encoding prefix    | prefix opt u8.                    |
|        |                 |                 | opt.                              |                                   |
+--------+-----------------+-----------------+-----------------------------------+-----------------------------------+
| 5      | Valid string    | Part B, 3, 13   | A valid C++ string-literal can    | Valid C++ string-literal because  |
|        | but no encoding |                 | have empty encoding prefix opt.   | the string has no encoding prefix |
|        | prefix opt      |                 |                                   | opt.                              |
+--------+-----------------+-----------------+-----------------------------------+-----------------------------------+
| 6      | Valid string    | Part B, 4, 14   | s char sequence can be empty in a | Valid C++ string-literal because  |
|        | with empty s    |                 | valid C++ string-literal.         | the string has no s char          |
|        | char sequence   |                 |                                   | sequence.                         |
+--------+-----------------+-----------------+-----------------------------------+-----------------------------------+
| 7      | Valid string    | Part B, 5, 15   | simple escape sequence (as one of | Valid C++ string-literal because  |
|        | with simple     |                 | escape-sequence) is a valid       | the string are parsed in the      |
|        | escape sequence |                 | s-char. simeple escape sequence:  | following way: \\, \', \?, \",    |
|        |                 |                 | \', \", \?, \\, \a, \b, \f, \n,   | \v, where 5 simple escape         |
|        |                 |                 | \r, \t, \v.                       | sequences.                        |
+--------+-----------------+-----------------+-----------------------------------+-----------------------------------+
| 8      | Valid string    | Part B, 6, 16   | octal escape sequence (as one of  | Valid C++ string-literal because  |
|        | with octal      |                 | escape-sequence) is a valid       | the string are parsed in the      |
|        | escape sequence |                 | s-cahr. octal escape sequence:    | following way: \0 (matches        |
|        |                 |                 | \octal-digit, \octal-digit        | \octal-digit), \12 (matches       |
|        |                 |                 | octal-digit, \octal-digit         | \octal-digit octal-digit), \345   |
|        |                 |                 | octal-digit octal-digit (Each     | (matches \octal-digit octal-digit |
|        |                 |                 | octal escape sequence must be the | octal-digit), 6 (a single valid   |
|        |                 |                 | longest sequence of characters    | s-char), \7 (matches              |
|        |                 |                 | that can constitute the escape    | \octal-digit), 8, 9, a, b, c (5   |
|        |                 |                 | sequence).                        | single valid s-chars). Note: (1)  |
|        |                 |                 |                                   | The algorithm that parses an      |
|        |                 |                 |                                   | octal escape sequence is greedy   |
|        |                 |                 |                                   | so that \12 would not be parsed   |
|        |                 |                 |                                   | as \1 and 2, same rule applies on |
|        |                 |                 |                                   | \345. (2) The program would print |
|        |                 |                 |                                   | the same valid message when       |
|        |                 |                 |                                   | either there is an octal-digit    |
|        |                 |                 |                                   | s-char or a non octal-digit       |
|        |                 |                 |                                   | s-char after \octal-digit;        |
|        |                 |                 |                                   | however, the program parsed the   |
|        |                 |                 |                                   | string in a different way. These  |
|        |                 |                 |                                   | special notes can be checked by   |
|        |                 |                 |                                   | adding an output (to print        |
|        |                 |                 |                                   | characters that are parsed as     |
|        |                 |                 |                                   | part of octal escape sequence) at |
|        |                 |                 |                                   | the end of the loop where         |
|        |                 |                 |                                   | processes octal-escape-sequence.  |
+--------+-----------------+-----------------+-----------------------------------+-----------------------------------+
| 9      | Valid string    | Part B, 7, 17   | hexadecimal escape sequence (as   | Valid C++ string-literal because  |
|        | with            |                 | one of escape-sequence) is a      | the string are parsed in the      |
|        | hexadecimal     |                 | valid s-char. hexadecimal escape  | following way: \xa (matches \x    |
|        | escape sequence |                 | sequence: any number of           | hexadecimal-digit),               |
|        |                 |                 | consecutive hexadecimal-digits    | \xbCdE0123456789 (matches \x any  |
|        |                 |                 | after \x, but at least one        | number of consecutive             |
|        |                 |                 | hexadecimal-digit, hexadecimal    | hexadecimal-digits, including     |
|        |                 |                 | digits may have upper or lower    | upper and lower case alphabetic   |
|        |                 |                 | case alphabetic characters. (Each | characters), \xf (matches         |
|        |                 |                 | hexadecimal escape sequence must  | \hexadecimal-digit), g (a single  |
|        |                 |                 | be the longest sequence of        | valid s-char). Note: (1) The      |
|        |                 |                 | characters that can constitute    | algorithm that parses a           |
|        |                 |                 | the escape sequence).             | hexadecimal escape sequence is    |
|        |                 |                 |                                   | greedy so that \xBcDe0123456789   |
|        |                 |                 |                                   | would not be parsed as \xB and a  |
|        |                 |                 |                                   | series of single valid s-chars.   |
|        |                 |                 |                                   | (2) The program would print the   |
|        |                 |                 |                                   | same valid message when either    |
|        |                 |                 |                                   | there is an hexadecimal-digit     |
|        |                 |                 |                                   | s-char or a non hexadecimal digit |
|        |                 |                 |                                   | s-char after \x; however, the     |
|        |                 |                 |                                   | program parsed the string in a    |
|        |                 |                 |                                   | different way. These special      |
|        |                 |                 |                                   | notes can be checked by adding an |
|        |                 |                 |                                   | output (to print characters that  |
|        |                 |                 |                                   | are parsed as part of hexadecimal |
|        |                 |                 |                                   | escape sequence) at the end of    |
|        |                 |                 |                                   | the loop where processes          |
|        |                 |                 |                                   | hexadecimal escape sequence.      |
+--------+-----------------+-----------------+-----------------------------------+-----------------------------------+
| 10     | Valid string    | Part B, 8, 18   | A valid C++ string-literal will   | Valid C++ string-literal because  |
|        | with extraneous |                 | end with a double-quote(").       | when encoutering a second         |
|        | characters      |                 |                                   | double-quote("), it would treat   |
|        |                 |                 |                                   | the second double-quote as the    |
|        |                 |                 |                                   | closing double-quote("), so the   |
|        |                 |                 |                                   | rest of characters are treated as |
|        |                 |                 |                                   | extraneous.                       |
+--------+-----------------+-----------------+-----------------------------------+-----------------------------------+
| 11     | Empty input     | Part B, 9-10,   | The program would print warning   | Warning message is printed        |
|        | line            | 19-20           | message when there is a blank     | because the program read an empty |
|        |                 |                 | line.                             | line.                             |
+--------+-----------------+-----------------+-----------------------------------+-----------------------------------+
| 12     | Invalid         | Part C, 2, 9    | A valid encoding prefix opt can   | Invalid C++ string-literal the    |
|        | encoding prefix |                 | only be one of "u8", "u", "U",    | string has an invalid encoding    |
|        | opt             |                 | "L".                              | prefix opt U8.                    |
+--------+-----------------+-----------------+-----------------------------------+-----------------------------------+
| 13     | Invalid leading | Part C, 3, 10   | A valid encoding prefix opt can   | Invalid C++ string-literal        |
|        | space           |                 | only be one of "u8", "u", "U",    | becuase the program does not skip |
|        |                 |                 | "L".                              | whitespace, it would treat        |
|        |                 |                 |                                   | leading space as an optional      |
|        |                 |                 |                                   | encoding prefix, then string      |
|        |                 |                 |                                   | would have an invalid encoding    |
|        |                 |                 |                                   | prefix space character ( ).       |
+--------+-----------------+-----------------+-----------------------------------+-----------------------------------+
| 14     | Invalid s-char  | Part C, 4, 11   | A valid s-char cannot be a s-char | Invalid C++ string-literal        |
|        | backslash(\)    |                 | backslash(\) (and not part of an  | because the string has a          |
|        | and not part of |                 | escape-sequence).                 | backslash(\), and charcters after |
|        | escape-sequence |                 |                                   | 'c' would be extraneous           |
|        |                 |                 |                                   | characters because the program    |
|        |                 |                 |                                   | recognized "\c" cannot be parsed  |
|        |                 |                 |                                   | as a valid escape-sequence after  |
|        |                 |                 |                                   | reading 'c'.                      |
+--------+-----------------+-----------------+-----------------------------------+-----------------------------------+
| 15     | Invalid octal   | Part C, 5, 12   | A valid octal digit must be in    | Invalid C++ string-literal        |
|        | escape sequence |                 | the range [0, 7].                 | because the string has 9 after    |
|        |                 |                 |                                   | backslash(\), so does not make to |
|        |                 |                 |                                   | octal escape sequence. Thus, the  |
|        |                 |                 |                                   | program would treat this string   |
|        |                 |                 |                                   | the same as test 14, where the    |
|        |                 |                 |                                   | stirng contains a backslash (and  |
|        |                 |                 |                                   | not part of an escape-sequence).  |
+--------+-----------------+-----------------+-----------------------------------+-----------------------------------+
| 16     | Invalid         | Part C, 6, 13   | A valid hexadecimal escape        | Invalid C++ string-literal        |
|        | hexadecimal     |                 | sequence must have at least one   | because the stirng has no         |
|        | escape sequence |                 | hexadecimal digit after \x.       | hexadecimal digit after \x, then  |
|        | with no         |                 |                                   | the program would treat this      |
|        | hexadecimal     |                 |                                   | string the same as test 14, where |
|        | digit           |                 |                                   | the string contains a backslash   |
|        |                 |                 |                                   | (and not part of an               |
|        |                 |                 |                                   | escape-sequence).                 |
+--------+-----------------+-----------------+-----------------------------------+-----------------------------------+
| 17     | Invalid string  | Part C, 7, 14   | A valid C++ string-literal should | Invalid C++ string-literal        |
|        | without second  |                 | have at least 2 double-quote("):  | becuase it does not have second   |
|        | double-quote(") |                 | one opening and one closing.      | double-quote(") but read until    |
|        |                 |                 |                                   | the end of the line.              |
+--------+-----------------+-----------------+-----------------------------------+-----------------------------------+

PART A
------
1 @ubuntu1604-008% ./stringliteral valid.in invalid.in
2 Usage: ./stringliteral [infile-file]
3 @ubuntu1604-008% ./stringliteral doesnotexist
4 Error! Could not open input file "doesnotexist"
5 @ubuntu1604-008% chmod a-r valid.in
6 @ubuntu1604-008% ./stringliteral valid.in
7 Error! Could not open input file "valid.in"

PART B
------
1 @ubuntu1604-008% cat valid.in
2 u8"abc"
3 "abc  123"
4 ""
5 "\\\'\?\"\v"
6 "\0\12\3456\789abc"
7 "\xa\xcCdE0123456789\xfg"
8 "abc"123"
9 
10 "Above line is an empty input line, print warning"
11 @ubuntu1604-008% ./stringliteral valid.in
12 'u8"abc"' : 'u8"abc"' yes
13 '"abc  123"' : '"abc  123"' yes
14 '""' : '""' yes
15 '"\\\'\?\"\v"' : '"\\\'\?\"\v"' yes
16 '"\0\12\3456\789abc"' : '"\0\12\3456\789abc"' yes
17 '"\xa\xcCdE0123456789\xfg"' : '"\xa\xcCdE0123456789\xfg"' yes
18 '"abc"123"' : '"abc"' yes -- extraneous characters '123"'
19 '' : Warning! Blank line.
20 '"Above line is an empty input line, print warning"' : '"Above line is an empty input line, print warning"' yes

PART C
------
1 @ubuntu1604-008% cat invalid.in
2 U8"123"
3  "123"
4 "\cs343"
5 "\9"
6 "\x"
7 "abc123
8 @ubuntu1604-008% ./stringliteral invalid.in
9 'U8"123"' : 'U8' no -- extraneous characters '"123"'
10 ' "123"' : ' ' no -- extraneous characters '"123"'
11 '"\cs343"' : '"\c' no -- extraneous characters 's343"'
12 '"\9"' : '"\9' no -- extraneous characters '"'
13 '"\x"' : '"\x"' no
14 '"abc123' : '"abc123' no

