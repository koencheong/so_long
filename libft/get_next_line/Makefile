SRC = get_next_line_bonus.c \
		get_next_line_utils_bonus.c \
		
OBJ = ${SRC:.c=.o}

NAME = libftgnl.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror -I ./
RM = rm -f
AR = ar rcs

all: $(NAME)

$(NAME): $(OBJ)
	$(AR) $(NAME) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all
	
.PHONY: all clean fclean re