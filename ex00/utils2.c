/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eokoshi <eokoshi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 11:24:06 by eokoshi           #+#    #+#             */
/*   Updated: 2023/08/27 21:11:54 by eokoshi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char			*trim(char *str);
char			*my_strtok(char *str, const char *delim, char **saveptr);
char			**ft_split(char *str, char *charset);
char			*read_dictionary(char *path);
int				ft_strlen(char *str);
unsigned int	ft_atoi(char *str);
char			*read_dictionary(char *path);
char			*eliminate_blank_line(char *original_str);

typedef struct dictionary
{
	long		*keys;
	char		**values;
	int			size;

}				t_dictionary;

// Counts the number of lines in a string by counting newline characters.
// args:
//   - str : The string in which lines are to be counted.
// returns:
//   - int : The number of lines in the string.
int	count_line(char *str)
{
	int	count;

	count = 0;
	while (*++str)
		if (*str == '\n')
			count++;
	return (count);
}

void	init_dictionary(t_dictionary *dictionary, int line_count)
{
	dictionary->keys = malloc(sizeof(long) * line_count);
	dictionary->values = malloc(sizeof(char *) * line_count);
	dictionary->size = line_count;
}

void	fill_dictionary(t_dictionary *dictionary, char *line, int *i)
{
	char	**key_value_pair;

	key_value_pair = ft_split(line, ":");
	dictionary->keys[*i] = ft_atoi(trim(key_value_pair[0]));
	dictionary->values[*i] = trim(key_value_pair[1]);
	free(key_value_pair);
	*i += 1;
}

// Parses a dictionary from a given string.
// The string should contain key-value pairs separated by a colon,
//  and each pair should be on a new line.
// args:
//   - str : The string containing the dictionary data.
// returns:
//   - t_dictionary : A struct containing the parsed keys and values.
t_dictionary	parse_dictionary(char *str)
{
	t_dictionary	dictionary;
	int				line_count;
	int				i;
	char			*line;
	char			*saveptr;

	line_count = count_line(str);
	i = 0;
	saveptr = NULL;
	init_dictionary(&dictionary, line_count);
	line = my_strtok(str, "\n", &saveptr);
	while (line)
	{
		fill_dictionary(&dictionary, line, &i);
		line = my_strtok(NULL, "\n", &saveptr);
	}
	return (dictionary);
}
