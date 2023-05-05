/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcheong <kcheong@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 12:23:34 by kcheong           #+#    #+#             */
/*   Updated: 2023/05/04 12:23:34 by kcheong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	call(int fd, t_variables *data)
{
	create_map(fd, data);
	display_num_movements(data);
	mlx_loop_hook(data->mlx_ptr, no_event, data);
	mlx_key_hook(data->win_ptr, key_hook, data);
	mlx_hook(data->win_ptr, 17, 0, handle_close, data);
}

int	no_event(t_variables *data)
{
	(void)data;
	return (0);
}

void	setup(int fd, t_variables *data)
{
	data->wy = 0;
	data->collectibles = 0;
	data->collected = 0;
	data->num_movement = 0;
	data->mlx_ptr = mlx_init();
	data->background = mlx_xpm_file_to_image(data->mlx_ptr, "images/purple.xpm",
			&data->size, &data->size);
	data->chibi_maruko = mlx_xpm_file_to_image(data->mlx_ptr,
			"images/maruko.xpm", &data->size, &data->size);
	data->wall = mlx_xpm_file_to_image(data->mlx_ptr, "images/tree.xpm",
			&data->size, &data->size);
	data->exit = mlx_xpm_file_to_image(data->mlx_ptr, "images/door2.xpm",
			&data->size, &data->size);
	data->coll = mlx_xpm_file_to_image(data->mlx_ptr, "images/pudding_bg.xpm",
			&data->size, &data->size);
	data->white = mlx_xpm_file_to_image(data->mlx_ptr, "images/white.xpm",
			&data->size, &data->size);
	call(fd, data);
}

int	main(int argc, char **argv)
{
	int			fd;
	t_variables	data;

	if (argc == 2)
	{
		data.map = argv[1];
		fd = open(data.map, O_RDONLY);
		if (fd == -1)
		{
			ft_printf("Error\nInvalid map file.\n");
			exit(EXIT_FAILURE);
		}
		setup(fd, &data);
		mlx_loop(data.mlx_ptr);
	}
	ft_printf("Error\n");
	ft_printf("Please execute the game as follow: [./so_long] [map]");
	exit(EXIT_FAILURE);
}
