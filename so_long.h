#include <mlx.h>
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
	void		*enemy;
	void		*white;
	int			size;
	char		**ori_arr;
	int			x;
	int			y;
	int			collected;
	int			collectibles;
	int			num_movement;
	char		*message;
	const char	*map;
	int			window_y;
} t_variables;

int		create_map(int	fd, t_variables *ptr);

// for (int z = 0; data->ori_arr[z] != 0; z++)
	// 	printf("[%s]\n", data->ori_arr[z]);