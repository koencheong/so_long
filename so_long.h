#include <mlx.h>
#include <X11/X.h>
#include <stdlib.h>
#include <stdio.h>
#include <X11/keysym.h>

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