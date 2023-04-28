#include <mlx.h>
// #include <X11/X.h>
#include <stdlib.h>
#include <stdio.h>
// #include <X11/keysym.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "libft/libft.h"
#include "libft/get_next_line/get_next_line_bonus.h"
#include "libft/ft_printf/ft_printf.h"

#define MAX_ROWS 1000
#define MAX_COLS 1000

typedef struct s_connections
{
	void	*mlx_ptr;
	void	*win_ptr;
} t_ptr;

typedef	struct s_images
{
	int	width;
	int	height;
} t_img;