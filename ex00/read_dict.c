/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_dict.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eokoshi <eokoshi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 13:12:56 by eokoshi           #+#    #+#             */
/*   Updated: 2023/08/27 13:18:54 by eokoshi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

ssize_t	get_file_size(int fd)
{
	ssize_t	total_size;
	ssize_t	read_size;
	char	buffer[1024];

	total_size = 0;
	while (1)
	{
		read_size = read(fd, buffer, sizeof(buffer));
		if (read_size <= 0)
		{
			break ;
		}
		total_size += read_size;
	}
	return (total_size);
}

char	*read_file_content(int fd, off_t size)
{
	char	*content;
	ssize_t	read_size;

	content = (char *)malloc(size + 1);
	if (!content)
		return (NULL);
	read_size = read(fd, content, size);
	if (read_size != size)
	{
		free(content);
		return (NULL);
	}
	content[size] = '\0';
	return (content);
}

char	*read_dictionary(char *path)
{
	int		fd;
	off_t	size;
	char	*content;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (NULL);
	size = get_file_size(fd);
	close(fd);
	if (size <= 0)
		return (NULL);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (NULL);
	content = read_file_content(fd, size);
	close(fd);
	return (content);
}
