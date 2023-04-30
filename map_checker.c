#include "so_long.h"

void	floodfill(char **temp_arr, int y, int x)
{
	if (temp_arr[y][x] == 'P' || temp_arr[y][x] == 'E' || 
		temp_arr[y][x] == 'C' || temp_arr[y][x] == '0')
	{
		temp_arr[y][x] = 'X';
		floodfill(temp_arr, (y - 1), x);
		floodfill(temp_arr, y, (x - 1));
		floodfill(temp_arr, (y + 1), x);
		floodfill(temp_arr, y, (x + 1));
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
				floodfill(temp_arr, y, x);
				data->x = x;
				data->y = y;
			}
			x++;
		}
		y++;
	}

	y = 0;	
	while (temp_arr[y] != NULL)
	{
		x = 0;
		while (temp_arr[y][x] != '\0')
		{
			if (temp_arr[y][x] != '1' && temp_arr[y][x] != 'X')
			{
				ft_printf("Map error: no valid path.\n");
				exit(EXIT_FAILURE);
			}
			x++;
		}
		y++;
	}
	// for (int z = 0; data->ff_arr[z] != 0; z++)
	// 	printf("%s\n", data->ff_arr[z]);	
	// for (int z = 0; data->ori_arr[z] != 0; z++)
	// 	printf("%s\n", data->ori_arr[z]);	
}

void	create_double_array(int j, t_variables *data)
{
	char	*string;
	int		x;
	int		fd;
	char	**temp_arr;
	
	fd = open("map1.ber", O_RDONLY);
	x = 0;
	data->ori_arr = ft_calloc(j + 1, sizeof(char *));
	temp_arr = ft_calloc(j + 1, sizeof(char *));
	while ((string = get_next_line(fd)))
	{
		data->ori_arr[x++] = ft_strtrim(string, "\n");
		free(string);
	}
	close(fd);

	fd = open("map1.ber", O_RDONLY);
	x = 0;
	while ((string = get_next_line(fd)))
	{
		temp_arr[x++] = ft_strtrim(string, "\n");
		free(string);
	}
	
	close (fd);
	num_collectibles(data);
	check_valid_path(data, temp_arr);
}

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
        if (string[i] != '1')
        {
            printf("11Error! Map should be surrounded by walls.\n");
            exit(EXIT_FAILURE);
        }
        i++;
		
    }
	count += 1;

    // check subsequent lines
    if (string[len] == '\n' && count != 1)
    {
        if (string[0] != '1' || string[len - 1] != '1')
        {
        	printf("22Error! Map should be surrounded by walls.\n");
        	exit(EXIT_FAILURE);
        }
        i++;
    }

	// check last line
	while (string[len] == '\0' && i < len)
	{
		if (string[i] != '1')
        {
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
	while (string[i] != '\0')
	{
		if (string[i] == '\n')
			break ;
		if (string[i] == 'E')
			n_exit += 1;
		if (string[i] == 'P')
			n_player += 1;
		if (string[i] == 'C')
			n_coll += 1;
		i++;
	}
	
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
	{
		first_len = len;
		if (string[0] == '\n')
		{
			ft_printf("Error! Map is not rectangular.\n");
     		exit(EXIT_FAILURE);
		}
	}
    else if (len != first_len)
	{
        ft_printf("Error! Map is not rectangular.\n");
        exit(EXIT_FAILURE);
    }
    return (0);
}

int		create_map(int	fd, t_variables  *data)
{
	char	*string;
	int		i;
	int		j;
	int 	len;

	j = 0;
	while ((string = get_next_line(fd)))
	{
		// printf("[%s]\n", string);
		check_rectangular(string);
		check_walls(string);
		check_number(string);
		len = ft_strlen(string);
		if (string[len - 1] == '\n')
			len -= 1;
		i = len;
		j++;
	}
	close(fd);
	create_double_array(j, data);
	data->win_ptr = mlx_new_window(data->mlx_ptr, i*64, j*64, "CHIBI MARUKO");
	if (data->win_ptr == NULL)
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
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->wall, i*64, j*64);
			if (string[i] == '0')
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->background, i*64, j*64);
			if (string[i] == 'P')
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->chibi_maruko, i*64, j*64);
			if (string[i] == 'E')
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->exit, i*64, j*64);
			if (string[i] == 'C')
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->coll, i*64, j*64);
			i++;
		}
		j++;
	}
	return (0);
}