/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcheong <kcheong@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 20:38:43 by kcheong           #+#    #+#             */
/*   Updated: 2023/05/04 13:44:20 by kcheong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*join_free(char *storage, char *buffer)
{
	char	*temp;

	temp = ft_strjoin(storage, buffer);
	free(storage);
	return (temp);
}

char	*store_extra(char *storage)
{
	int		i;
	int		j;
	char	*extra;

	i = 0;
	while (storage[i] != '\0' && storage[i] != '\n')
		i++;
	if (!storage[i])
	{
		free(storage);
		return (NULL);
	}
	extra = malloc((ft_strlen(storage) - i + 1) * sizeof(char));
	i++;
	j = 0;
	while (storage[i] != '\0')
		extra[j++] = storage[i++];
	extra[j] = 0;
	free(storage);
	return (extra);
}

char	*return_line(char *storage)
{
	int		i;
	char	*line;

	i = 0;
	if (!storage[i])
		return (NULL);
	while (storage[i] != '\0' && storage[i] != '\n')
		i++;
	line = malloc((i + 2) * sizeof(char));
	i = 0;
	while (storage[i] != '\0' && storage[i] != '\n')
	{
		line[i] = storage[i];
		i++;
	}
	if (storage[i] != '\0' && storage[i] == '\n')
		line[i++] = '\n';
	line[i] = 0;
	return (line);
}

char	*read_join(int fd, char *storage, char *buffer)
{
	int	byteread;

	byteread = 1;
	while (byteread > 0)
	{
		byteread = read(fd, buffer, BUFFER_SIZE);
		if (byteread == -1 || (byteread == 0 && storage == NULL))
		{
			free(buffer);
			return (NULL);
		}
		buffer[byteread] = 0;
		if (!storage)
			storage = ft_strdup(buffer);
		else
			storage = join_free(storage, buffer);
		if (ft_strchr(storage, '\n'))
			break ;
	}
	free(buffer);
	return (storage);
}

char	*get_next_line(int fd)
{
	static char	*storage[1024];
	char		*line;
	char		*buffer;

	if (fd < 0 || fd > 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	storage[fd] = read_join(fd, storage[fd], buffer);
	if (!storage[fd] || *storage[fd] == '\0')
		return (NULL);
	line = return_line(storage[fd]);
	storage[fd] = store_extra(storage[fd]);
	return (line);
}

// int	main(void)
// {
// 	char *res;
// 	int	fd1 = open("big_line_no_nl.txt", O_RDONLY);
// 	int	fd2 = open("text2.txt", O_RDONLY);
// 	res = get_next_line(fd1);
// 	printf("Result 1 = [%s]\n", res);
// 	free(res);
// 	res = get_next_line(fd2);
// 	printf("Result 2 = [%s]\n", res);
// 	free(res);
// 	res = get_next_line(fd1);
// 	printf("Result 3 = [%s]\n", res);
// 	free(res);
// 	res = get_next_line(fd2);
// 	printf("Result 4 = [%s]\n", res);
// 	free(res);
// 	res = get_next_line(fd1);
// 	printf("Result 5 = [%s]\n", res);
// 	free(res);
// 	res = get_next_line(fd2);
// 	printf("Result 6 = [%s]\n", res);
// 	free(res);
// 	res = get_next_line(fd1);
// 	printf("Result 7 = [%s]\n", res);
// 	free(res);
// 	res = get_next_line(fd2);
// 	printf("Result 8 = [%s]\n", res);
// 	free(res);
// 	res = get_next_line(fd1);
// 	printf("Result 9 = [%s]\n", res);
// 	free(res);
// 	res = get_next_line(fd2);
// 	printf("Result 10 = [%s]\n", res);
// 	free(res);
// 	// printf("%s", get_next_line(fd));
// 	// get_next_line(fd);
// 	// get_next_line(fd);
// 	// get_next_line(fd);
// 	system("leaks a.out");
// }
