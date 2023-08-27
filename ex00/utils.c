/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eokoshi <eokoshi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 21:10:06 by eokoshi           #+#    #+#             */
/*   Updated: 2023/08/27 21:11:30 by eokoshi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
