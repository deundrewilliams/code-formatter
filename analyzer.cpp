#include <iostream>
#include <list>

#include "data.h"

void analyze( std::list<Token> tokenlist ) {

    auto i = tokenlist.begin();

    int line_number = 1;

    while (i != tokenlist.end()) {

        // std::cout << i->description() << "\n";

        // Increase line number at newline character
        if (i->getType() == newlinesym) {
            // std::cout << "Increasing line number to " << line_number + 1 << "\n";
            line_number += 1;
        }

        // Line length <= 80
        else if (i->getType() == linelensym) {

            if (i->getValue() > 80) {
                std::cout << "(Line " << line_number << ") Error: Line longer than 80 characters.\n";
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
                }

            }

        }

        // No space between # and define/include

        // Comment should be on it's own line

        // Curly brace should be on its own line

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
                }

            }



        }

        // Indent 4 spaces at a time

        // When declaring a pointer, asterisk, should go next to identifier

        // Don't mix declaring and initializing variables

        i = std::next(i, 1);

    }

}
