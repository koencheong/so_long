/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcheong <kcheong@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 12:39:08 by kcheong           #+#    #+#             */
/*   Updated: 2023/05/04 17:22:31 by kcheong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	game_over(t_variables *data)
{
	if (data->collected == data->collectibles)
	{
		ft_printf("\n|| CONGRATS!! ||\n\n");
		exit(EXIT_SUCCESS);
	}
	else
		ft_printf("Please collect all remaining pudding before exiting.\n");
}

void	display_num_movements(t_variables *data)
{
	int		i;
	char	*num_movements_str;
	char	*msg;

	i = 0;
	num_movements_str = ft_itoa(data->num_movement);
	msg = ft_strjoin("Number of movements: ", num_movements_str);
	while (i < data->wx)
	{
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->white,
			i * 64, data->wy * 64);
		i++;
	}
	mlx_string_put(data->mlx_ptr, data->win_ptr, 15,
		data->wy * 64 + 20, 0, msg);
	free(num_movements_str);
	free(msg);
}

void	move_character(t_variables *data, int new_y, int new_x)
{
	if (data->ori_arr[new_y][new_x] == '1')
		return ;
	if (data->ori_arr[new_y][new_x] == 'C')
	{
		data->collected++;
		data->ori_arr[new_y][new_x] = '0';
	}
	if (data->ori_arr[new_y][new_x] == 'E')
		game_over(data);
	else
	{
		mlx_put_image_to_window (data->mlx_ptr, data->win_ptr,
			data->background, data->x * 64, data->y * 64);
		data->y = new_y;
		data->x = new_x;
		mlx_put_image_to_window (data->mlx_ptr, data->win_ptr,
			data->chibi_maruko, data->x * 64, data->y * 64);
		data->num_movement++;
		display_num_movements(data);
	}
}

int	handle_close(void)
{
	ft_printf("Program closed.\n");
	exit(EXIT_SUCCESS);
	return (0);
}

int	key_hook(int key, t_variables *data)
{
	if (key == ESC)
	{
		ft_printf("Program closed by ESC.\n");
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
