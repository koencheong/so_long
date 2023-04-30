#include <mlx.h>
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
#define ESC 65307

// MAC
// #define W 13
// #define A 0
// #define S 1
// #define D 2
// #define ESC 53

typedef struct s_variables
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*background;
	void		*chibi_maruko;
	void		*wall;
	void		*exit;
	void		*coll;
	int			size;
	char		**ori_arr;
	int			x;
	int			y;
	int			collected;
	int			collectibles;
	int			num_movement;
	const char	*map;
} t_variables;

int		create_map(int	fd, t_variables *ptr);