/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_print_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcheong <kcheong@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 18:34:11 by kcheong           #+#    #+#             */
/*   Updated: 2023/05/04 20:42:18 by kcheong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	print_map(int j, int i, t_variables *data)
{
	j = 0;
	while (data->ori_arr[j] != NULL)
	{
		i = 0;
		while (data->ori_arr[j][i] != '\0')
		{
			if (data->ori_arr[j][i] == '1')
				mlx_put_image_to_window (data->mlx_ptr,
					data->win_ptr, data->wall, i * 64, j * 64);
			if (data->ori_arr[j][i] == '0')
				mlx_put_image_to_window (data->mlx_ptr,
					data->win_ptr, data->background, i * 64, j * 64);
			if (data->ori_arr[j][i] == 'P')
				mlx_put_image_to_window (data->mlx_ptr,
					data->win_ptr, data->chibi_maruko, i * 64, j * 64);
			if (data->ori_arr[j][i] == 'E')
				mlx_put_image_to_window (data->mlx_ptr,
					data->win_ptr, data->exit, i * 64, j * 64);
			if (data->ori_arr[j][i] == 'C')
				mlx_put_image_to_window (data->mlx_ptr,
					data->win_ptr, data->coll, i * 64, j * 64);
			i++;
		}
		j++;
	}
}

void	free_func(char **array)
{
	char	**tmp;

	tmp = array;
	while (tmp && *tmp)
	{
		free(*tmp);
		tmp++;
	}
	free(array);
}
