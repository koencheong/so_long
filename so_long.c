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

	ptr.mlx_ptr = mlx_init();
	if (ptr.mlx_ptr == NULL)
		return (1);
	ptr.win_ptr = mlx_new_window(ptr.mlx_ptr, 900, 900, "Marukooo");
	if (ptr.win_ptr == NULL)
	{
		free(ptr.win_ptr);
		return (1);
	}

	background = mlx_xpm_file_to_image(ptr.mlx_ptr, "images/background.xpm", &size, &size);
	if (background == NULL)
		return (1);
	chibi_maruko = mlx_xpm_file_to_image(ptr.mlx_ptr, "images/maruko2.xpm", &size, &size);
	if (chibi_maruko == NULL)
		return (1);

	mlx_put_image_to_window(ptr.mlx_ptr, ptr.win_ptr, background, 0, 0);
	mlx_put_image_to_window(ptr.mlx_ptr, ptr.win_ptr, chibi_maruko, 0, 0);

	// mlx_key_hook(ptr.win_ptr, &w_up, &ptr);


	mlx_loop(ptr.mlx_ptr);

	mlx_destroy_display(ptr.mlx_ptr);
	mlx_destroy_window(ptr.mlx_ptr, ptr.win_ptr);
}