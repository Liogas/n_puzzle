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

run: $(NAME)
	./$(NAME)

clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -rf $(NAME) puzzle.txt

re : fclean $(NAME)

.PHONY: all clean fclean re