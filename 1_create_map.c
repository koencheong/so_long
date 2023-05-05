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

// 5) Same process as the previous function but this array is for floodfill,
//    which is to check if there's a valid path.
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
	free_func(temp_arr);
}

// 4) Until now only i started using double array, and i check if there's
// 	  invalid character string by string before storing it in the 2D array. 
// 	  Then i create another temporary 2D array for floodfill.
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

// 3) Create a window according to the size of my map (len for x-axis and
// 	  j for the y-axis),  but extra one row for the movement number bar.
//    Then put images to the window using the 2D array.
void	create_map_helper(int j, int len, t_variables *data)
{
	int	i;

	create_double_array(j, data);
	data->wy = j;
	data->wx = len * 64;
	data->win_ptr = mlx_new_window(data->mlx_ptr,
			data->wx, (data->wy + 1) * 64, "CHIBI MARUKO");
	i = 0;
	while (i < len)
	{
		mlx_put_image_to_window(data->mlx_ptr,
			data->win_ptr, data->white, i * 64, j * 64);
		i++;
	}
	print_map(i, j, data);
}

// 1)
void	create_map(int fd, t_variables *data)
{
	int		j;
	int		len;
	char	*string;
	char	*newstring;

	j = 0;
	string = get_next_line(fd);
	newstring = NULL;
	len = ft_strlen(string) - 1;
	j = checker(j, string, newstring, fd);
	create_map_helper(j, len, data);
	free(newstring);
	close(fd);
}

// 2)
int	checker(int j, char *string, char *newstring, int fd)
{
	int		i;

	while (string)
	{
		check_rectangular(string);
		check_walls(string);
		check_number(string);
		j++;
		newstring = get_next_line(fd);
		if (newstring == NULL)
		{
			i = -1;
			while (string[++i] != '\0')
			{
				if (string[i] != '1')
					exit(ft_printf("Invalid map.\n"));
			}
			free(string);
			break ;
		}
		free(string);
		string = newstring;
	}
	return (j);
}
