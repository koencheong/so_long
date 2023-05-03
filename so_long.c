#include "so_long.h"

int	no_event(t_variables *data)
{
	(void)data;
	return (0);
}

void	game_over(t_variables *data)
{
	if (data->collected == data->collectibles)
	{
		ft_printf("\n|| I love pudding ||\n\n");
		exit(EXIT_SUCCESS);
	}
	else
		ft_printf("Please collect all remaining pudding before exiting.\n");
}

void	display_num_movements(t_variables *data)
{
    char	*num_movements_str;
    char	*message;

    num_movements_str = ft_itoa(data->num_movement);
    message = ft_strjoin("Number of movements: ", num_movements_str);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->white, 89, data->window_y);
    mlx_string_put(data->mlx_ptr, data->win_ptr, 15, data->window_y + 20, 0, message);
    free(num_movements_str);
    free(message);
}

void	move_character(t_variables *data, int new_y, int new_x)
{
	if (data->ori_arr[new_y][new_x] == '1')
		return;
	
	if (data->ori_arr[new_y][new_x] == 'C')
	{
		data->collected++;
		data->ori_arr[new_y][new_x] = '0';
	}
	
	if (data->ori_arr[new_y][new_x] == 'E')
		game_over(data);
	else
	{
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->background, data->x*64, data->y*64);
		data->y = new_y;
		data->x = new_x;
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->chibi_maruko, data->x*64, data->y*64);
		data->num_movement++;
		display_num_movements(data);
	}
}

// int	handle_close(int key, t_variables	*data)
// {
// 	if (key == 17)
// 	{
// 		ft_printf("EXIT\n");
// 		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
// 		exit(EXIT_SUCCESS);
// 	}
// 	return (0);
// }

int	key_hook(int key, t_variables *data)
{
	if (key == ESC)
	{
		ft_printf("EXIT\n");
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		exit(EXIT_SUCCESS);
	}
	if (key == W)
		move_character(data, data->y - 1, data->x);
	else if (key == A)
		move_character(data, data->y, data->x - 1);
	else if (key == S)
		move_character(data, data->y + 1, data->x);
	else if (key == D)
		move_character(data, data->y, data->x + 1);
	return (0);
}

void	setup(int	fd, t_variables *data)
{
	data->window_y = 0;
	data->collectibles = 0;
	data->collected = 0;
	data->num_movement = 0;
	data->mlx_ptr = mlx_init();
	data->background = mlx_xpm_file_to_image(data->mlx_ptr, "images/purple.xpm", &data->size, &data->size);
	data->chibi_maruko = mlx_xpm_file_to_image(data->mlx_ptr, "images/maruko.xpm", &data->size, &data->size);
	data->chibi_marukob4 = mlx_xpm_file_to_image(data->mlx_ptr, "images/marukob4.xpm", &data->size, &data->size);
	data->wall = mlx_xpm_file_to_image(data->mlx_ptr, "images/tree.xpm", &data->size, &data->size);
	data->exit = mlx_xpm_file_to_image(data->mlx_ptr, "images/door2.xpm", &data->size, &data->size);
	data->coll = mlx_xpm_file_to_image(data->mlx_ptr, "images/pudding_bg.xpm", &data->size, &data->size);
	data->enemy = mlx_xpm_file_to_image(data->mlx_ptr, "images/enemy.xpm", &data->size, &data->size);
	data->white = mlx_xpm_file_to_image(data->mlx_ptr, "images/white.xpm", &data->size, &data->size);

	
	create_map(fd, data);
	display_num_movements(data);
	mlx_loop_hook(data->mlx_ptr, no_event, data);
	mlx_key_hook(data->win_ptr, key_hook, data);
	// mlx_hook(data->win_ptr, 17, 0, handle_close, data);
}

int	main(int argc, char **argv)
{
	if (argc == 2)
	{
		int			fd;
		t_variables	data;

		data.map = argv[1];
		fd = open(data.map, O_RDONLY);
		if (fd == -1)
		{
			ft_printf("Error\n");
			ft_printf("Invalid map file.\n");
			exit(EXIT_FAILURE);
		}
		setup(fd, &data);
		mlx_loop(data.mlx_ptr);
	
	}
	ft_printf("Error\n");
	ft_printf("Please execute the game as follow: [./so_long] [map]");
	exit(EXIT_FAILURE);
}