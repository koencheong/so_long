#include <mlx.h>
// #include <X11/X.h>
#include <stdlib.h>
#include <X11/keysym.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "libft/libft.h"
#include "libft/get_next_line/get_next_line_bonus.h"
#include "libft/ft_printf/ft_printf.h"

// WINDOW
#define W 119
#define A 97
#define S 115
#define D 100

typedef struct s_variables
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*background;
	void	*chibi_maruko;
	void	*wall;
	void	*exit;
	void	*coll;
	int		size;
	char	**ori_arr;
	int		x;
	int		y;
	int		collected;
	int		num_c;
} t_variables;

typedef	struct s_images
{
	int	width;
	int	height;
} t_img;

int		create_map(int	fd, t_variables *ptr);
void	num_collectibles(t_variables *ptr);
int		movement(char **arr, t_variables *ptr);