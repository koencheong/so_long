#include "so_long.h"

void	num_collectibles(t_variables *data)
{
	data->collected = 0;
	data->num_c = 0;
	data->y = 0;
	
	// for (int z = 0; ori_arr[z] != 0; z++)
	// 	printf("%s\n", ori_arr[z]);

	while (data->ori_arr[data->y] != NULL)
	{
		data->x = 0;
		while (data->ori_arr[data->y][data->x] != '\0')
		{
			if (data->ori_arr[data->y][data->x] == 'C')
				data->num_c += 1;			
			data->x++;
		}
		data->y++;
	}
}

// int	movement(char **ori_arr, t_variables *ptr)
// {
	// int	x;
	// int	y;
	// int	collected;
	// (void)ori_arr;

	// y = 0;
	// while (!ptr->game_over)
	// {
	// 	while (ori_arr[y] != NULL)
	// 	{
	// 		x = 0;
	// 		while (ori_arr[y][x] != '\0')
	// 		{
	// 			if (ori_arr[y][x] == 'P')
	// 			{
	// 				ft_printf("%c\n", ori_arr[y][x]);
	// 				ft_printf("Key being passed: %d\n", ptr->keysym);
	// 				if (ptr->keysym == 119)
	// 				{
	// 					ori_arr[y][x] = '0';
	// 					ori_arr[y - 1][x] = 'P';
	// 					ft_printf("yes\n");
	// 				}
	// 			}
	// 			x++;
	// 		}
	// 		y++;
	// 	}
	// }
// 	return (0);
// }