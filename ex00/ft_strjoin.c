/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eokoshi <eokoshi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 00:42:03 by eokoshi           #+#    #+#             */
/*   Updated: 2023/08/27 14:18:36 by eokoshi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

int	calculate_total_length(char **strs, char *sep, int size)
{
	int	total_len;
	int	i;

	total_len = 0;
	i = 0;
	while (i < size)
		total_len += ft_strlen(strs[i++]);
	total_len += ft_strlen(sep) * (size - 1) + 1;
	return (total_len);
}

void	concatenate_strings(char *result, char **strs, char *sep, int size)
{
	int		sep_len;
	char	*current_pos;
	int		i;

	sep_len = ft_strlen(sep);
	current_pos = result;
	i = -1;
	while (++i < size)
	{
		while (*strs[i])
			*current_pos++ = *strs[i]++;
		if (i < size - 1)
		{
			while (*sep)
				*current_pos++ = *sep++;
			sep -= sep_len;
		}
	}
	*current_pos = '\0';
}

char	*ft_strjoin(int size, char **strs, char *sep)
{
	char	*empty_str;
	int		total_len;
	char	*result;

	if (size == 0)
	{
		empty_str = (char *)malloc(1);
		*empty_str = '\0';
		return (empty_str);
	}
	total_len = calculate_total_length(strs, sep, size);
	result = (char *)malloc(total_len);
	if (!result)
		return (NULL);
	concatenate_strings(result, strs, sep, size);
	return (result);
}
