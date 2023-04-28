NAME = so_long
CC = gcc
CFLAGS = #-Wall -Wextra -Werror
SRC = so_long_draft.c
# LIB = -L/usr/local/lib/libmlx.a 
# INC = -lmlx -lGL -lX11 -lXext
INC = -lmlx -framework OpenGL -framework AppKit

ALIB = ./libft/libft.a ./libft/ft_printf/libftprintf.a ./libft/get_next_line/libftgnl.a

all: libft1 print gnl $(NAME)

libft1: libft
	make -C libft

print:
	make -C libft/ft_printf

gnl: 
	make -C libft/get_next_line

$(NAME): $(SRC)
	$(CC) $(CFLAGS) $(SRC) $(ALIB) $(INC) -o $(NAME)

clean:
	rm -f libft/ft_printf/*.o libft/get_next_line/*.o libft/*.o
	rm -f *.o 

fclean: clean
	rm -f $(NAME) *.a

re: fclean all