#include "so_long.h"

// int	handle_no_event()
// {
// 	return (0);
// }

// int	w_up(int keysym, t_ptr *ptr)
// {
// 	(void)ptr;
// 	if (keysym == XK_W)
// 		mlx_put_image_to_window(ptr.mlx_ptr, ptr.win_ptr, chibi_maruko, (x-1)*100, 0*110);
// 	return (0);
// }

// int	s_down(int keysym, t_ptr *ptr)

// int	a_left(int keysym, t_ptr *ptr)

// int	d_right(int keysym, t_ptr *ptr)

// int	split_buf_to_2d_array(char *buf)
// {
// 	int		i;
// 	int		x;
// 	int		y;
// 	char	**map;

// 	i = 0;
// 	while (buf[i] != '\0')
// 	{

// 	}
// }

int	check_1(char *buf) // check if there's only one exit, one player and at least one collectible.
{
	int	i;
	int	n_exit;
	int	n_player;
	int	n_coll;

	i = 0;
	n_exit = 0;
	n_player = 0;
	n_coll = 0;
	
	while (buf[i])
	{

		if (buf[i] == 'E')
			n_exit += 1;
		if (buf[i] == 'P')
			n_player += 1;
		if (buf[i] == 'C')
			n_coll += 1;
		i++;
	}

	if (n_exit != 1 || n_player != 1 || n_coll < 1)
	{
		printf("Map errors\n");
		exit(EXIT_FAILURE);
	}
	return (0);
}

int	check_2(char *buf) // check if the map is rectangular.
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	
	while (buf[i] != '\0')
	{
		c += 1;
		i++;
	}
	// temp = c;
	// if 
	return (0);
}

// void	read_map()
// {
// 	int		fd;
// 	char	buf[1024];
// 	ssize_t	bytes_read;
	
// 	bytes_read = 0;
// 	fd = open("map.ber", O_RDONLY);
// 	if (fd == -1)
// 	{
// 		perror("Error opening file");
// 		exit(EXIT_FAILURE);
// 	}
// 	bytes_read = read(fd, buf, sizeof(buf));
// 	if (bytes_read == -1)
// 	{
// 		perror("Error reading file");
// 		exit(EXIT_FAILURE);
// 	}
// 	buf[bytes_read] = '\0';
// 	close(fd);

// 	check_1(buf);
// 	check_2(buf);
// }	

int		create_map(int	fd, t_ptr *ptr, void *background)
{
	char *string;
	int	i;
	int	j;
	int len;

	j = 0;
	while ((string = get_next_line(fd)))
	{
		ft_printf("string = [%s]\n", string);
		len = ft_strlen(string);
		ft_printf("len = %i\n", len);
		
		i = 0;
		while (i <= len)
		{
			if (string[len] == '\n')
				break ;
			else
			{
				mlx_put_image_to_window(ptr->mlx_ptr, ptr->win_ptr, background, i*50, j*50);
				i++;
				ft_printf("i = %i\n", i);
			}
		}
		j++;
		ft_printf("j = %i\n", j);
		free (string);
	}
	return (0);
}

int	main(void)
{
	t_ptr	ptr;
	int		size;
	void	*background;
	void	*chibi_maruko;
	// void	*wall;
	// int		x;
	// int		y;
	
	// x = 0;
	ptr.mlx_ptr = mlx_init();
	if (ptr.mlx_ptr == NULL)
		return (1);
	ptr.win_ptr = mlx_new_window(ptr.mlx_ptr, 900, 900, "Marukooo");
	if (ptr.win_ptr == NULL)
	{
		free(ptr.win_ptr);
		return (1);
	}

	background = mlx_xpm_file_to_image(ptr.mlx_ptr, "images/purple.xpm", &size, &size);
	if (background == NULL)
		return (1);
	chibi_maruko = mlx_xpm_file_to_image(ptr.mlx_ptr, "images/maruko.xpm", &size, &size);
	if (chibi_maruko == NULL)
		return (1);
	// wall = mlx_xpm_file_to_image(ptr.mlx_ptr, "images/brick.xpm", &size, &size);
	// if (wall == NULL)
	// 	return (1);

	// while (x < 900)
	// {
	// 	y = 0;
	// 	while (y < 900)
	// 	{
	// 		mlx_put_image_to_window(ptr.mlx_ptr, ptr.win_ptr, background, x, y);
	// 		y += 50;
	// 	}
	// 	x += 50;
	// }

	// mlx_put_image_to_window(ptr.mlx_ptr, ptr.win_ptr, wall, 0, 0);

	// mlx_key_hook(ptr.win_ptr, &w_up, &ptr);
	// read_map();
	int	fd;
	fd = open("map1.ber", O_RDONLY);
	// while ((string = get_next_line(fd)))
	// {
	// 	col = ft_strlen(string);
	// 	row = 0;

	// 	char	map[row][col];

	// 	while (string[x] != '\0')
	// 	{
	// 		x = 0;
	// 		map[row][col] = string[col];
	// 		col++;
	// 	}
	// 	row++;
	// }
	create_map(fd, &ptr, background);

	mlx_loop(ptr.mlx_ptr);

	mlx_destroy_display(ptr.mlx_ptr);
	mlx_destroy_window(ptr.mlx_ptr, ptr.win_ptr);
}