/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcheong <kcheong@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 12:45:00 by kcheong           #+#    #+#             */
/*   Updated: 2023/05/04 12:45:00 by kcheong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	create_temp_arr(int fd, int x, int j, t_variables *data)
{
	char	**temp_arr;
	char	*string;

	fd = open(data->map, O_RDONLY);
	x = 0;
	temp_arr = ft_calloc(j + 1, sizeof(char *));
	string = get_next_line(fd);
	while (string)
	{
		temp_arr[x++] = ft_strtrim(string, "\n");
		free(string);
		string = get_next_line(fd);
	}
	close (fd);
	check_valid_path(data, temp_arr);
	j = 0;
	while (temp_arr[j] != NULL)
	{
		free(temp_arr[j]);
		j++;
	}
	free(temp_arr);
}

void	create_double_array(int j, t_variables *data)
{
	char	*string;
	int		x;
	int		fd;

	fd = open(data->map, O_RDONLY);
	x = 0;
	data->ori_arr = ft_calloc(j + 1, sizeof(char *));
	string = get_next_line(fd);
	while (string)
	{
		check_invalid_char(string, data);
		data->ori_arr[x++] = ft_strtrim(string, "\n");
		free(string);
		string = get_next_line(fd);
	}
	close(fd);
	create_temp_arr(fd, x, j, data);
}

void	create_map_helper(int i, int j, int len, t_variables *data)
{
	create_double_array(j, data);
	data->wy = j;
	data->wx = i * 64;
	data->win_ptr = mlx_new_window(data->mlx_ptr,
			i * 64, (j + 1) * 64, "CHIBI MARUKO");
	i = 0;
	while (i < len)
	{
		mlx_put_image_to_window(data->mlx_ptr,
			data->win_ptr, data->white, i * 64, j * 64);
		i++;
	}
	print_map(i, j, data);
}

void	to_check(int i, int j, int fd, t_variables *data)
{
	int		len;

	len = 0;
	j = 0;
	data->string1 = get_next_line(fd);
	while (data->string1)
	{
		check_rectangular(data->string1);
		check_walls(data->string1);
		check_number(data->string1);
		len = ft_strlen(data->string1);
		if (data->string1[len - 1] == '\n')
			len -= 1;
		i = len;
		j++;
		free(data->string1);
		data->string1 = get_next_line(fd);
		ft_printf("[%s]\n", data->string1);
		if (!data->string1)
		{
			ft_printf ("Error\nEmpty line.");
			exit(EXIT_FAILURE);
		}
	}
	create_map_helper(i, j, len, data);
}

void	create_map(int fd, t_variables *data)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	to_check(i, j, fd, data);
	close(fd);
}
