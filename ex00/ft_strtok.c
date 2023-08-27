/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eokoshi <eokoshi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 21:07:17 by eokoshi           #+#    #+#             */
/*   Updated: 2023/08/27 21:08:50 by eokoshi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strchr(const char *str, int c)
{
	while (*str)
	{
		if (*str == c)
		{
			return ((char *)str);
		}
		str++;
	}
	if (c == '\0')
	{
		return ((char *)str);
	}
	return (NULL);
}

char	*skip_leading_delimiters(char *str, const char *delim)
{
	while (*str && ft_strchr(delim, *str))
	{
		++str;
	}
	return (str);
}

char	*find_token_end(char *str, const char *delim)
{
	while (*str && !ft_strchr(delim, *str))
	{
		++str;
	}
	return (str);
}

void	update_saveptr(char **saveptr, char *new_position)
{
	if (*new_position)
	{
		*new_position = '\0';
		*saveptr = new_position + 1;
	}
	else
	{
		*saveptr = NULL;
	}
}

char	*my_strtok(char *str, const char *delim, char **saveptr)
{
	char	*token_start;

	if (str == NULL)
	{
		str = *saveptr;
	}
	if (str == NULL)
	{
		return (NULL);
	}
	str = skip_leading_delimiters(str, delim);
	if (*str == '\0')
	{
		*saveptr = NULL;
		return (NULL);
	}
	token_start = str;
	str = find_token_end(str, delim);
	update_saveptr(saveptr, str);
	return (token_start);
}
