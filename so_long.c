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
		ft_printf("\n|| I love pudding eeeeee ||\n\n");
		exit(EXIT_SUCCESS);
	}
	else
		ft_printf("Please collect all remaining pudding before exiting.\n");
}

int	key_hook(int key, t_variables *data)
{
	// for (int z = 0; data->ori_arr[z] != 0; z++)
	// 	printf("[%s]\n", data->ori_arr[z]);
	if (key == ESC)
	{
		ft_printf("EXIT\n");
		exit(EXIT_SUCCESS);
	}
	if (key == W)
	{
		if (data->ori_arr[data->y - 1][data->x] != '1')
		{
			if (data->ori_arr[data->y - 1][data->x] == 'C')
			{
				data->collected++;
				data->ori_arr[data->y - 1][data->x] = '0';
			}
			if (data->ori_arr[data->y - 1][data->x] == 'E')
				game_over(data);
			else
			{
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->background, data->x*64, data->y*64);
				data->y--;
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->chibi_maruko, data->x*64, data->y*64);
				data->num_movement++;
				ft_printf("Number of movements: %d\n", data->num_movement);
			}
		}
	}
	if (key == A)
	{
		if (data->ori_arr[data->y][data->x - 1] != '1')
		{
			if (data->ori_arr[data->y][data->x - 1] == 'C')
			{
				data->collected++;
				data->ori_arr[data->y][data->x - 1] = '0';
			}
			if (data->ori_arr[data->y][data->x - 1] == 'E')
				game_over(data);
			else
			{
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->background, data->x*64, data->y*64);
				data->x--;
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->chibi_maruko, data->x*64, data->y*64);
				data->num_movement++;
				ft_printf("Number of movements: %d\n", data->num_movement);
			}
		}
	}
	if (key == S)
	{
		if (data->ori_arr[data->y + 1][data->x] != '1')
		{
			if (data->ori_arr[data->y + 1][data->x] == 'C')
			{
				data->collected++;
				data->ori_arr[data->y + 1][data->x] = '0';
			}
			if (data->ori_arr[data->y + 1][data->x] == 'E')
				game_over(data);
			else
			{
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->background, data->x*64, data->y*64);
				data->y++;
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->chibi_maruko, data->x*64, data->y*64);
				data->num_movement++;
				ft_printf("Number of movements: %d\n", data->num_movement);
			}
		}
	}
	if (key == D)
	{
		if (data->ori_arr[data->y][data->x + 1] != '1')
		{
			if (data->ori_arr[data->y][data->x + 1] == 'C')
			{
				data->collected++;
				data->ori_arr[data->y][data->x + 1] = '0';
			}
			if (data->ori_arr[data->y][data->x + 1] == 'E')
				game_over(data);
			else 
			{
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->background, data->x*64, data->y*64);
				data->x++;
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->chibi_maruko, data->x*64, data->y*64);
				data->num_movement++;
				ft_printf("Number of movements: %d\n", data->num_movement);
			}
		}
	}
	return (0);
}

int	main(int argc, char **argv)
{
	if (argc == 2)
	{
		t_variables	data;

		data.map = argv[1];
		data.collectibles = 0;
		data.collected = 0;
		data.num_movement = 0;
		data.mlx_ptr = mlx_init();
		if (data.mlx_ptr == NULL)
			return (1);
		data.background = mlx_xpm_file_to_image(data.mlx_ptr, "images/purple.xpm", &data.size, &data.size);
		data.chibi_maruko = mlx_xpm_file_to_image(data.mlx_ptr, "images/maruko.xpm", &data.size, &data.size);
		data.wall = mlx_xpm_file_to_image(data.mlx_ptr, "images/tree.xpm", &data.size, &data.size);
		data.exit = mlx_xpm_file_to_image(data.mlx_ptr, "images/exit.xpm", &data.size, &data.size);
		data.coll = mlx_xpm_file_to_image(data.mlx_ptr, "images/coll.xpm", &data.size, &data.size);

		int	fd;
		fd = open(data.map, O_RDONLY);
		if (fd == -1)
		{
			ft_printf("Error\n");
			ft_printf("Invalid map file.\n");
			exit(EXIT_FAILURE);
		}
		
		create_map(fd, &data);
		mlx_loop_hook(data.mlx_ptr, no_event, &data);
		mlx_key_hook(data.win_ptr, key_hook, &data);
		mlx_loop(data.mlx_ptr);
	
	}
	ft_printf("Error\n");
	ft_printf("Please execute the game as follow: [./so_long] [map]");
	exit(EXIT_FAILURE);
}