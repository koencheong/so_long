#include "so_long.h"

// int w_up(int keysym, t_variables *data)
// {
// 	// printf("hihi\n");
// 	// if (keysym == 13)
// 	if (keysym == 119)
// 	{
// 		printf("yes\n");
// 		// mlx_put_image_to_window(data.mlx_data, data.win_data, chibi_maruko, (x-1)*100, 0*110);
// 	}	
// 	(void)data;
// 	return (0);
// }

int	no_event(t_variables *data)
{
	(void)data;
	return (0);
}

void	game_over(t_variables *data)
{
	if (data->collected == data->num_c)
	{
		ft_printf("You won the game!!\n");
		exit(EXIT_SUCCESS);
	}
}

int	key_hook(int key, t_variables *data)
{
	// for (int z = 0; data->ori_arr[z] != 0; z++)
	// 	printf("[%s]\n", data->ori_arr[z]);
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
			}
		}
	}
	return (0);
}

int	main(void)
{
	t_variables	data;

	data.mlx_ptr = mlx_init();
	if (data.mlx_ptr == NULL)
		return (1);
	data.background = mlx_xpm_file_to_image(data.mlx_ptr, "images/purple.xpm", &data.size, &data.size);
	data.chibi_maruko = mlx_xpm_file_to_image(data.mlx_ptr, "images/maruko.xpm", &data.size, &data.size);
	data.wall = mlx_xpm_file_to_image(data.mlx_ptr, "images/tree.xpm", &data.size, &data.size);
	data.exit = mlx_xpm_file_to_image(data.mlx_ptr, "images/exit.xpm", &data.size, &data.size);
	data.coll = mlx_xpm_file_to_image(data.mlx_ptr, "images/coll.xpm", &data.size, &data.size);

	int	fd;
	fd = open("map1.ber", O_RDONLY);
	
	create_map(fd, &data);
	mlx_loop_hook(data.mlx_ptr, no_event, &data);
	mlx_key_hook(data.win_ptr, key_hook, &data);
	mlx_loop(data.mlx_ptr);
}