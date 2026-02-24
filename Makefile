CXX 		= g++
CXXFLAGS	= -Wall -Wextra -Werror -g3 -std=c++20
INCLUDES	= -I./includes/

NAME		= nPuzzle

SRCS_DIR 	= srcs
OBJS_DIR 	= objs
SRCS		= $(SRCS_DIR)/main.cpp \
              $(SRCS_DIR)/parsing/parsing.cpp \
              $(SRCS_DIR)/algo/nPuzzle.cpp

OBJS 		= $(SRCS:$(SRCS_DIR)/%.cpp=$(OBJS_DIR)/%.o)

all: $(NAME)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS)
	@echo "👌👌👌👌👌👌👌👌👌👌👌👌👌👌👌👌👌👌👌👌👌"

gen3puzzle:
	./npuzzle-gen.py -s 3 > puzzle3.txt

gen4puzzle:
	./npuzzle-gen.py -s 4 > puzzle4.txt

gen5puzzle:
	./npuzzle-gen.py -s 5 > puzzle5.txt

run3manhattan: $(NAME)
	./$(NAME) puzzle3.txt manhattan

run3linearConflict: $(NAME)
	./$(NAME) puzzle3.txt linearConflict

run3pdb: $(NAME)
	./$(NAME) puzzle3.txt pdb

run4manhattan: $(NAME)
	./$(NAME) puzzle4.txt manhattan

run4linearConflict: $(NAME)
	./$(NAME) puzzle4.txt linearConflict

run5manhattan: $(NAME)
	./$(NAME) puzzle5.txt manhattan

run5linearConflict: $(NAME)
	./$(NAME) puzzle5.txt linearConflict


clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -rf $(NAME) *.out *.txt

re : fclean $(NAME)

.PHONY: all clean fclean re