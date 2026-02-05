CC 			= c++
CFLAGS		= -Wall -Wextra -Werror -g3
INCLUDES	= -I./includes/

NAME		= nPuzzle

SRCS_DIR 	= srcs
OBJS_DIR 	= objs
SRCS		= $(SRCS_DIR)/main.cpp \
              $(SRCS_DIR)/algo/AlgoStar.cpp \
              $(SRCS_DIR)/algo/heuristics.cpp \
              $(SRCS_DIR)/algo/setupHeuristics.cpp \
              $(SRCS_DIR)/algo/Node.cpp \
              $(SRCS_DIR)/parsing/parsing.cpp

OBJS 		= $(SRCS:$(SRCS_DIR)/%.cpp=$(OBJS_DIR)/%.o)

all: $(NAME)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.cpp
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)
	@echo "👌👌👌👌👌👌👌👌👌👌👌👌👌👌👌👌👌👌👌👌👌"

run: $(NAME)
	./$(NAME)

clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -rf $(NAME) puzzle.txt


re : fclean $(NAME)

.PHONY: all clean fclean re