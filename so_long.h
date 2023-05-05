/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcheong <kcheong@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 12:44:06 by kcheong           #+#    #+#             */
/*   Updated: 2023/05/04 12:44:06 by kcheong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// // WINDOW
// #define W 119
// #define A 97
// #define S 115
// #define D 100
// #define ESC 65307

#ifndef SO_LONG_H
# define SO_LONG_H

# include <mlx.h>
# include "libft/libft.h"
# include "libft/get_next_line/get_next_line_bonus.h"
# include "libft/ft_printf/ft_printf.h"

# define W 13
# define A 0
# define S 1
# define D 2
# define ESC 53

typedef struct s_variables
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*background;
	void		*chibi_maruko;
	void		*wall;
	void		*exit;
	void		*coll;
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
	int			wy;
	int			wx;
	char		*string1;
}	t_variables;

int		no_event(t_variables *data);
void	create_map(int fd, t_variables *ptr);
void	game_over(t_variables *data);
void	display_num_movements(t_variables *data);
void	move_character(t_variables *data, int new_y, int new_x);
int		handle_close(void);
int		key_hook(int key, t_variables *data);
void	floodfill(char **temp_arr, int y, int x, t_variables *data);
void	check_valid_path(t_variables *data, char **temp_arr);
void	check_walls(char *string);
void	check_number(char *string);
void	check_rectangular(char *string);
void	check_invalid_char(char *string, t_variables *data);
void	print_map(int j, int i, t_variables *data);
int		checker(int j, char *string, char *newstring, int fd);
void	free_func(char **array);

#endif

// for (int z = 0; data->ori_arr[z] != 0; z++)
	// 	printf("[%s]\n", data->ori_arr[z]);