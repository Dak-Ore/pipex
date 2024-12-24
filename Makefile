NAME = pipex
FLAGS = -Wall -Wextra -Werror -ggdb

SOURCES = pipex.c ft_split.c ft_strjoin.c pathfinder.c

OBJS = $(SOURCES:.c=.o)

$(NAME): $(OBJS)
	cc $(FLAGS) -o $(NAME) $(OBJS)

%.o: %.c
	cc $(FLAGS) -c $< -o $@

all: $(NAME)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all