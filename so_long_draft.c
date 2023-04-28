#include "so_long.h"

int w_up(int keysym, t_ptr *ptr)
{
	printf("hihi\n");
	if (keysym == 13)
	{
		printf("yes\n");
		// mlx_put_image_to_window(ptr.mlx_ptr, ptr.win_ptr, chibi_maruko, (x-1)*100, 0*110);
	}	
	(void)ptr;
	return (0);
}

char	**chgarray(int i, int j)
{
	char **arr;
	char *string;
	int	x;
	int	fd;

	fd = open("map1.ber", O_RDONLY);
	x = 0;
	arr = ft_calloc(j + 1, sizeof(char * ));
	while ((string = get_next_line(fd)))
	{
		arr[x++] = ft_strtrim(string, "\n");
		free(string);
	}
	for (int z = 0; arr[z] != 0; z++)
	{
		printf("%s\n", arr[z]);
	}
	close (fd);
	return (arr);
}

// int	floodfill()

int	no_event(t_ptr *data)
{
	return (0);
}

// int	s_down(int keysym, t_ptr *ptr)

// int	a_left(int keysym, t_ptr *ptr)

// int	d_right(int keysym, t_ptr *ptr)

int check_walls(char *string)
{
    int i;
   	static int count;
    int len = ft_strlen(string);

	i = 0;
    if (string[len - 1] == '\n')
		len--;

    // check first line
    while (string[i] != '\n' && count == 0)
    {
		// printf("First while loop, string is [%s]\n", string);
		// printf("string[%c]\n", string[i]);
        if (string[i] != '1')
        {
			// printf("[%c]\n", string[i]);
            printf("11Error! Map should be surrounded by walls.\n");
            exit(EXIT_FAILURE);
        }
        i++;
		
    }
	count += 1;

	// printf("count %d\n", count);
	// printf("String[%c]\n", string[len]);
    // check subsequent lines
    if (string[len] == '\n' && count != 1)
    {
		// printf("Second while loop\n");
		// printf("String is [%s], length is [%d]\n", string, len);
		// printf("string[0] is [%c], string[len - 1] is [%c]\n", string[0], string[len - 1]);
        if (string[0] != '1' || string[len - 1] != '1')
        {
        	printf("22Error! Map should be surrounded by walls.\n");
        	exit(EXIT_FAILURE);
        }
        i++;
    }

	while (string[len] == '\0' && i < len)
	{
	// 	printf("Third while loop\n");
	// 	printf("string[i] in third if is [%c]\n", string[i]);
		if (string[i] != '1')
        {
			// printf("[%c]\n", string[i]);
            printf("33Error! Map should be surrounded by walls.\n");
            exit(EXIT_FAILURE);
        }
        i++;
	}
    return (0);
}

int	check_number(char *string) // check if there's only one exit, one player and at least one collectible.
{
	int	i;
	static int	n_exit;
	static int	n_player;
	static int	n_coll;

	i = 0;
	// ft_printf("String = [%s]\n", string);
	while (string[i] != '\0')
	{
		if (string[i] == '\n')
			break ;
		// ft_printf("hi\n");
		if (string[i] == 'E')
			n_exit += 1;
		if (string[i] == 'P')
			n_player += 1;
		if (string[i] == 'C')
			n_coll += 1;
		i++;
	}
	
	// ft_printf("E = %d, P = %d, C = %d\n", n_exit, n_player, n_coll);
	if (string[i] == '\0')
	{
		if (n_exit != 1 || n_player != 1 || n_coll < 1)
		{
			printf("Error! Map should consist of one exit, one player and at least one collectible.\n");
			exit(EXIT_FAILURE);
		}
	}
	return (0);
}

int check_rectangular(char *string)
{
    static size_t first_len;
	size_t len;

	len = ft_strlen(string);
	if (string[len - 1] == '\n')
		len -= 1;
	if (first_len == 0)
		first_len = len;
    else if (len != first_len)
	{
        ft_printf("Error! Map is not rectangular.\n");
        exit(EXIT_FAILURE);
    }
    return (0);
}

int		create_map(int	fd, t_ptr *ptr, void *background, void *chibi_maruko, void *wall)
{
	char	*string;
	int		i;
	int		j;
	int 	len;
	// char	**arr;

	printf("hiy\n");
	j = 0;
	while ((string = get_next_line(fd)))
	{
		// printf("String:[%s]", string);
		check_rectangular(string);
		check_walls(string);
		// check_number(string);
		len = ft_strlen(string);
		// i = 0;
		if (string[len - 1] == '\n')
			len -= 1;
		// while (i < len)
		// {
		// 	i++;
		// }
		i = len;
		j++;
	}
	printf("byebyeyes\n");
	close(fd);
	chgarray(i, j);
	ptr->win_ptr = mlx_new_window(ptr->mlx_ptr, i*50, j*50, "CHIBI MARUKO");
	if (ptr->win_ptr == NULL)
		return (1);

	fd = open("map1.ber", O_RDONLY);
	j = 0;
	while ((string = get_next_line(fd)))
	{
		len = ft_strlen(string);
		
		i = 0;
		if (string[len - 1] == '\n')
			len -= 1;
		while (i < len)
		{
			if (string[i] == '1')
				mlx_put_image_to_window(ptr->mlx_ptr, ptr->win_ptr, wall, i*50, j*50);
			if (string[i] == '0')
				mlx_put_image_to_window(ptr->mlx_ptr, ptr->win_ptr, background, i*50, j*50);
			if (string[i] == 'P')
				mlx_put_image_to_window(ptr->mlx_ptr, ptr->win_ptr, chibi_maruko, i*50, j*50);
			i++;
		}
		j++;
	}
	return (0);
}

int	main(void)
{
	t_ptr	ptr;
	int		size;
	void	*background;
	void	*chibi_maruko;
	void	*wall;

	ptr.mlx_ptr = mlx_init();
	if (ptr.mlx_ptr == NULL)
		return (1);
	background = mlx_xpm_file_to_image(ptr.mlx_ptr, "images/purple.xpm", &size, &size);
	if (background == NULL)
		return (1);
	chibi_maruko = mlx_xpm_file_to_image(ptr.mlx_ptr, "images/maruko.xpm", &size, &size);
	if (chibi_maruko == NULL)
		return (1);
	wall = mlx_xpm_file_to_image(ptr.mlx_ptr, "images/tree.xpm", &size, &size);
	if (wall == NULL)
		return (1);

	// printf("hi");
	// mlx_key_hook(ptr.win_ptr, w_up, &ptr);

	int	fd;
	fd = open("map1.ber", O_RDONLY);
	
	create_map(fd, &ptr, background, chibi_maruko, wall);
	mlx_loop_hook(ptr.mlx_ptr, no_event, &ptr);
	mlx_key_hook(ptr.win_ptr, w_up, &ptr);
	mlx_loop(ptr.mlx_ptr);

	// mlx_destroy_display(ptr.mlx_ptr);
	// mlx_destroy_window(ptr.mlx_ptr, ptr.win_ptr);
}