/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_dict.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eokoshi <eokoshi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 00:57:01 by eokoshi           #+#    #+#             */
/*   Updated: 2023/08/27 00:57:02 by eokoshi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

char	*read_dictionary(char *path)
{
	int		fd;
	off_t	size;
	char	*content;
	ssize_t	read_size;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (NULL);
	size = lseek(fd, 0, SEEK_END);
	lseek(fd, 0, SEEK_SET);
	content = (char *)malloc(size + 1);
	if (!content)
	{
		close(fd);
		return (NULL);
	}
	read_size = read(fd, content, size);
	if (read_size != size)
	{
		close(fd);
		free(content);
		return (NULL);
	}
	content[size] = '\0';
	close(fd);
	return (content);
}
