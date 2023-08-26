/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eokoshi <eokoshi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 11:24:06 by eokoshi           #+#    #+#             */
/*   Updated: 2023/08/27 01:00:06 by eokoshi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include <string.h>

char			**ft_split(char *str, char *charset);
char			*read_dictionary(char *path);
int				ft_strlen(char *str);
int				ft_atoi(char *str);
char			*read_dictionary(char *path);

typedef struct dictionary
{
	int			*keys;
	char		**values;
	int			size;

}				t_dictionary;

char	*trim(char *str)
{
	int	start;
	int	end;

	start = 0;
	end = ft_strlen(str) - 1;
	while (str[start] == ' ' && str[start] != '\0')
		start++;
	while (str[end] == ' ' && end >= start)
		end--;
	str[end + 1] = '\0';
	return (str + start);
}

char	*eliminate_blank_line(char *str)
{
	int		i;
	int		len;
	char	*result;
	int		is_prev_newline;
	int		j;

	i = -1;
	j = 0;
	len = ft_strlen(str);
	result = (char *)malloc(len + 1);
	is_prev_newline = 0;
	if (!result)
		return (NULL);
	while (++i < len)
	{
		if (str[i] == '\n')
		{
			if (!is_prev_newline)
				result[j++] = str[i];
			is_prev_newline = 1;
		}
		else
		{
			result[j++] = str[i];
			is_prev_newline = 0;
		}
	}
	result[j] = '\0';
	return (result);
}

int	count_line(char *str)
{
	int	count;

	count = 0;
	while (*++str)
		if (*str == '\n')
			count++;
	return (count);
}

t_dictionary	parse_dictionary(char *str)
{
	t_dictionary	dictionary;
	int				line_count;
	int				i;
	char			*line;
	char			**key_value_pair;

	str = eliminate_blank_line(str);
	line_count = count_line(str);
	dictionary.keys = malloc(sizeof(int) * line_count);
	dictionary.values = malloc(sizeof(char *) * line_count);
	dictionary.size = line_count;
	i = 0;
	line = strtok(str, "\n");
	while (line)
	{
		key_value_pair = ft_split(line, ":");
		dictionary.keys[i] = ft_atoi(trim(key_value_pair[0]));
		dictionary.values[i] = trim(key_value_pair[1]);
		free(key_value_pair);
		line = strtok(NULL, "\n");
		i++;
	}
	return (dictionary);
}
