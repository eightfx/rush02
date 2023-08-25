#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int			ft_strlen(char *str);

typedef struct
{
	int		*keys;
	char	**values;
}			Dictionary;

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

	i = 0;
	j = 0;
	len = ft_strlen(str);
	result = (char *)malloc(len + 1);
	is_prev_newline = 0;
	if (!result)
	{
		return (NULL); // Memory allocation failed
	}
	while (i < len)
	{
		if (str[i] == '\n')
		{
			if (!is_prev_newline)
			{
				result[j++] = str[i];
			}
			is_prev_newline = 1;
		}
		else
		{
			result[j++] = str[i];
			is_prev_newline = 0;
		}
		i++;
	}
	result[j] = '\0';
	return (result);
}

int	count_line(char *str)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\n')
		{
			count++;
		}
		i++;
	}
	return (count);
}

/* Dictionary	parse_dictionary(char *str) */
/* { */
/* 	char		**values; */
/* 	int			count; */
/* 	char		*line; */
/* 	char		*key_str; */
/* 	char		*value_str; */
/* 	Dictionary	dictionary; */
/* 	int			line_count; */
/* 	int			*keys; */

/* 	line_count = count_line(str); */
/* 	keys = malloc(sizeof(int) * line_count); */
/* 	values = malloc(sizeof(char *) * line_count); */
/* 	count = 0; */
/* 	line = strtok(str, "\n"); */
/* 	while (line != NULL) */
/* 	{ */
/* 		key_str = strtok(line, ":"); */
/* 		value_str = strtok(NULL, ":"); */
/* 		keys[count] = ft_atoi(trim(key_str)); */
/* 		values[count] = trim(value_str); */
/* 		line = strtok(NULL, "\n"); */
/* 		count++; */
/* 	} */
/* 	dictionary.keys = keys; */
/* 	dictionary.values = values; */
/* 	return (dictionary); */
/* } */
