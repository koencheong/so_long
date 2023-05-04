/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_valid_path_checker.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcheong <kcheong@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 13:21:46 by kcheong           #+#    #+#             */
/*   Updated: 2023/05/04 20:35:05 by kcheong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	floodfill(char **temp_arr, int y, int x, t_variables *data)
{
	if (temp_arr[y][x] == 'P' || temp_arr[y][x] == 'E' ||
		temp_arr[y][x] == 'C' || temp_arr[y][x] == '0')
	{
		if (temp_arr[y][x] == 'C')
			data->collectibles += 1;
		temp_arr[y][x] = 'X';
		floodfill(temp_arr, (y - 1), x, data);
		floodfill(temp_arr, y, (x - 1), data);
		floodfill(temp_arr, (y + 1), x, data);
		floodfill(temp_arr, y, (x + 1), data);
	}
}

void	after_floodfill(char **temp_arr)
{
	int	x;
	int	y;

	y = 0;
	while (temp_arr[y] != NULL)
	{
		x = 0;
		while (temp_arr[y][x] != '\0')
		{
			if (temp_arr[y][x] == 'P' || temp_arr[y][x] == 'E'
				|| temp_arr[y][x] == 'C')
			{
				ft_printf("Error\n");
				ft_printf("Map has no valid path.\n");
				system("leaks so_long");
				exit(EXIT_FAILURE);
			}
			x++;
		}
		y++;
	}
}

void	check_valid_path(t_variables *data, char **temp_arr)
{
	int	x;
	int	y;

	y = 0;
	while (temp_arr[y] != NULL)
	{
		x = 0;
		while (temp_arr[y][x] != '\0')
		{
			if (temp_arr[y][x] == 'P')
			{
				floodfill(temp_arr, y, x, data);
				data->x = x;
				data->y = y;
			}
			x++;
		}
		y++;
	}
	after_floodfill(temp_arr);
}
