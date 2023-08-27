/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eokoshi <eokoshi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 11:24:06 by eokoshi           #+#    #+#             */
/*   Updated: 2023/08/27 20:22:41 by eokoshi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include <string.h>

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

// Trims leading and trailing white spaces from a string.
// args:
//   - str : The string to be trimmed.
// returns:
//   - char* : A pointer to the trimmed string.
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
	char			**key_value_pair;

	line_count = count_line(str);
	dictionary.keys = malloc(sizeof(long) * line_count);
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

// Finds the largest key in the dictionary that is
//  less than or equal to a given number.
// args:
//   - dict : The dictionary containing the keys.
//   - num : The given number.
// returns:
//   - int : The largest key that is less than or equal to the given number.
int	find_max_key(t_dictionary dict, long num)
{
	int		i;
	long	max_key;

	max_key = -1;
	i = -1;
	while (++i < dict.size)
		if (dict.keys[i] <= num && dict.keys[i] > max_key)
			max_key = dict.keys[i];
	return (max_key);
}
