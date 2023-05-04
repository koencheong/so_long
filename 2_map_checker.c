/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_map_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcheong <kcheong@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 13:09:50 by kcheong           #+#    #+#             */
/*   Updated: 2023/05/04 21:00:04 by kcheong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	check_walls2(int i, int len, int count, char *string)
{
	if (string[len] == '\n' && count != 1)
	{
		if (string[0] != '1' || string[len - 1] != '1')
		{
			ft_printf("Error\nMap should be surrounded by walls.\n");
			system("leaks so_long");
			exit(EXIT_FAILURE);
		}
		i++;
	}
	while (string[len] == '\0' && i < len)
	{
		if (string[i++] != '1')
		{
			ft_printf("Error\nMap should be surrounded by walls.\n");
			system("leaks so_long");
			exit(EXIT_FAILURE);
		}
	}
}

void	check_walls(char *string)
{
	int			i;
	static int	count;
	int			len;

	i = 0;
	len = ft_strlen(string);
	if (string[len - 1] == '\n')
		len--;
	while (string[i] != '\n' && count == 0)
	{
		if (string[i] != '1')
		{
			ft_printf ("Error\nMap should be surrounded by walls.\n");
			system("leaks so_long");
			exit(EXIT_FAILURE);
		}
		i++;
	}
	count += 1;
	check_walls2(i, len, count, string);
}

void	check_number(char *string)
{
	int			i;
	static int	n_exit;
	static int	n_player;
	static int	n_coll;

	i = -1;
	while (string[++i] != '\0')
	{
		if (string[i] == '\n')
			break ;
		if (string[i] == 'E')
			n_exit += 1;
		if (string[i] == 'P')
			n_player += 1;
		if (string[i] == 'C')
			n_coll += 1;
	}
	if (string[i] == '\0')
	{
		if (n_exit != 1 || n_player != 1 || n_coll < 1)
		{
			ft_printf("Error\nOnly 1E, 1P and at least 1C are allowed.\n");
			system("leaks so_long");
			exit(EXIT_FAILURE);
		}
	}
}

void	check_rectangular(char *string)
{
	static size_t	first_len;
	size_t			len;

	len = ft_strlen(string);
	if (string[len - 1] == '\n')
		len -= 1;
	if (first_len == 0)
	{
		first_len = len;
		if (string[0] == '\n')
		{
			ft_printf("Error\n");
			ft_printf("Map is not rectangular.\n");
			system("leaks so_long");
			exit(EXIT_FAILURE);
		}
	}
	else if (len != first_len)
	{
		ft_printf("Error\n");
		ft_printf("Map is not rectangular.\n");
		system("leaks so_long");
		exit(EXIT_FAILURE);
	}
}

void	check_invalid_char(char *string, t_variables *data)
{
	int	x;

	x = 0;
	while (string[x] != '\0' && string[x] != '\n')
	{
		if (string[x] == '1' || string[x] == '0' || string[x] == 'P'
			|| string[x] == 'E' || string[x] == 'C')
				x++;
		else
		{
			ft_printf("Error\nMap contains invalid character.\n");
			free(string);
			free_func(data->ori_arr);
			exit (EXIT_FAILURE);
		}
	}
}

// void	check_walls_11(t_variables *data)
// {
// 	int	i;
// 	int	j;
// 	int	len;

// 	i = 0;
// 	j = 0;
// 	len = ft_strlen(data->ori_arr[j]);

// 	if (data->ori_arr[data->wy - 1] == NULL)
// 	{
// 		ft_printf("Error\nMap should be surrounded by walls.\n");
// 		exit (EXIT_FAILURE);
// 	}
// 	ft_printf("[%s]\n", data->ori_arr[5]);
// 	while (data->ori_arr[0][i] != '\0'
// 			&& data->ori_arr[data->wy - 1][i] != '\0')
// 	{
// 		if (data->ori_arr[0][i] != '1'
// 			|| data->ori_arr[data->wy - 1][i] != '1')
// 		{
// 			ft_printf("Error\nMap should be surrounded by walls.\n");
// 			exit (EXIT_FAILURE);
// 		}
// 		i++;
// 	}
// 	i = 0;
// 	j = 1;
// 	while (j < (data->wy - 1))
// 	{
// 		while (data->ori_arr[j][i] != '\0')
// 		{
// 			if (data->ori_arr[j][0] != '1' || data->ori_arr[j][len] != '1')
// 			{
// 				ft_printf("222Error\nMap should be surrounded by walls.\n");
// 				exit (EXIT_FAILURE);
// 			}
// 			i++;
// 		}
// 		j++;
// 	}
// }