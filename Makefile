NAME = so_long
CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRC = so_long.c
LIB = -L/usr/local/lib/libmlx.a 
INC = -lmlx -lGL -lX11 -lXext

all: $(NAME)

$(NAME):
	$(CC) $(CFLAGS) $(SRC) $(LIB) $(INC) -o $(NAME)

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)

re: fclean all