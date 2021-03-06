#include <iostream>
#include <list>

#include "data.h"

int analyze( std::list<Token> tokenlist ) {

    auto i = tokenlist.begin();
    std::list<Token>::iterator next;
    std::list<Token>::iterator prev;

    int line_number = 1;
    int nest_level = 0;

    int error_count = 0;

    while (i != tokenlist.end()) {

        // std::cout << i->description() << "\n";

        // Increase line number at newline character
        if (i->getType() == newlinesym) {
            // std::cout << "Increasing line number to " << line_number + 1 << "\n";
            line_number += 1;

            next = std::next(i, 1);

            // If this line is indented
            if (next->getType() == spacesym) {

                // If the indentation is not equal to 4 spaces
                if (next->getValue() != (nest_level * 4)) {

                    next = std::next(next, 1);

                    if (next->getType() != rbracesym) {
                        std::cout << "(Line " << line_number << ") Error: Indent by " << nest_level * 4 << " spaces.\n";
                        error_count++;
                    }


                }

            }

        }

        // Line length <= 80
        else if (i->getType() == linelensym) {

            if (i->getValue() > 80) {
                std::cout << "(Line " << line_number << ") Error: Line longer than 80 characters.\n";
                error_count++;
            }

        }

        // Space after // when writing a comment
        else if (i->getType() == slashsym) {

            // Move forward
            i = std::next(i, 1);

            // If slash symbol
            if (i->getType() == slashsym) {

                // Move forward
                i = std::next(i, 1);

                // If not a space, output error
                if (i->getType() != spacesym) {
                    std::cout << "(Line " << line_number << ") Error: Space should follow inline comment start.\n";
                    error_count++;
                }

                // Go back until newline character, if find a nonspace before newline, throw error
                std::list<Token>::iterator rev = std::prev(i, 3);

                while (rev->getType() != newlinesym) {

                    if (rev->getType() != spacesym) {
                        std::cout << "(Line " << line_number << ") Error: Comment must begin on new line.\n";
                        error_count++;
                        break;
                    }

                    rev = std::prev(rev, 1);

                }

            } else {
                i = std::prev(i, 1);
            }

        }

        // No space between # and define/include
        else if (i->getType() == poundsym) {

            next = std::next(i, 1);

            if (next->getType() == spacesym) {
                std::cout << "(Line " << line_number << ") Error: There should be no space between preprocessor directives.\n";
                error_count++;
            }

        }

        // Curly brace should be on its own line
        else if (i->getType() == lbracesym) {

            std::list<Token>::iterator prev = std::prev(i, 1);

            while (prev->getType() != newlinesym) {

                if (prev->getType() != spacesym) {
                    std::cout << "(Line " << line_number << ") Error: Curly brace must begin on new line.\n";
                    error_count++;
                    break;
                }

                prev = std::prev(prev, 1);

            }

            nest_level++;

        }

        // Curly brace should be left aligned

        // Do not do int main()
        else if (i->getType() == identnumsym && i->getText() == "main") {

            // Move forward
            i = std::next(i, 1);

            // If left parenthesis
            if (i->getType() == lparensym) {

                int main_param_chars = 0;

                i = std::next(i, 1);

                // Move forward until right parenthesis
                while (i->getType() != rparensym) {

                    // Increment main param characters
                    main_param_chars++;

                    i = std::next(i, 1);
                }

                if (main_param_chars == 0) {
                    std::cout << "(Line " << line_number << ") Error: main() parameters cannot be empty.\n";
                    error_count++;
                }

            } else {
                i = std::prev(i, 1);
            }



        }

        // Indent 4 spaces at a time

        // When declaring a pointer, asterisk, should go next to identifier
        else if (i->getType() == typespecsym) {

            // Get next token
            next = std::next(i, 1);

            // If space
            if (next->getType() == spacesym) {

                // Get next token
                next = std::next(next, 1);

                // If asterisk
                if (next->getType() == astsym) {

                    // std::cout << "Here\n";

                    // Get next token
                    next = std::next(next, 1);

                    // If not identifier
                    if (next->getType() != identnumsym) {

                        // Throw error
                        std::cout << "(Line " << line_number << ") Error: Asterisk should be next to identifer in pointer declaration.\n";
                        error_count++;

                    }
                }
            }
            // If asterisk
            if (next->getType() == astsym) {

                // Throw error
                std::cout << "(Line " << line_number << ") Error: Asterisk should be next to identifer in pointer declaration.\n";
                error_count++;

            }

        }

        // Don't mix declaring and initializing variables

        else if (i->getType() == rbracesym) {

            nest_level--;
            // std::cout << "Nest level is " << nest_level << " on line " << line_number << "\n";

        }

        i = std::next(i, 1);

    }


    return error_count;
}
