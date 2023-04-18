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

int	main(void)
{
	t_ptr	ptr;
	int		size;
	void	*background;
	void	*chibi_maruko;
	// void	*wall;
	int		x;
	int		y;
	int		fd;
	char	buf[1024];
	ssize_t	bytes_read;

	bytes_read = 0;

	x = 0;
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

	while (x < 900)
	{
		y = 0;
		while (y < 900)
		{
			mlx_put_image_to_window(ptr.mlx_ptr, ptr.win_ptr, background, x, y);
			y += 50;
		}
		x += 50;
	}

	// mlx_put_image_to_window(ptr.mlx_ptr, ptr.win_ptr, wall, 0, 0);

	// mlx_key_hook(ptr.win_ptr, &w_up, &ptr);

	fd = open("map.ber", O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		exit(EXIT_FAILURE);
	}
	bytes_read = read(fd, buf, sizeof(buf) - 1);
	if (bytes_read == -1)
	{
		perror("Error reading file");
		exit(EXIT_FAILURE);
	}
	buf[bytes_read] = '\0';
	printf("%s\n", buf);
	close(fd);

	mlx_loop(ptr.mlx_ptr);

	mlx_destroy_display(ptr.mlx_ptr);
	mlx_destroy_window(ptr.mlx_ptr, ptr.win_ptr);
}