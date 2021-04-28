CC = g++ -std=c++11

SRC_CODE = app/token.cpp app/lexer.cpp app/analyzer.cpp app/driver.cpp

all: $(SRC_CODE)
		$(CC) $(SRC_CODE) -lm
