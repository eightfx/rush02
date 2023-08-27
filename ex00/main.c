/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eokoshi <eokoshi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 13:11:43 by eokoshi           #+#    #+#             */
/*   Updated: 2023/08/27 20:10:32 by eokoshi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define IVI "Invalid index.\n"
#define MAF "Memory allocation failed.\n"

typedef struct dictionary
{
	long		*keys;
	char		**values;
	int			size;

}				t_dictionary;

long			*decomposit_num(t_dictionary dict, long num);
char			*handle_args(int argc, char **argv);
int				is_valid_arg(int argc, char **argv);
int				is_valid_dict(char *str);
long			ft_atoi(char *str);

int				ft_strlen(char *str);
char			*ft_strjoin(int size, char **strs, char *sep);
char			*read_dictionary(char *path);
t_dictionary	parse_dictionary(char *str);

long			*insert(long *list, int size, int i, long num);

int	is_in_dict(t_dictionary dict, long num)
{
	int	i;

	i = -1;
	while (++i < dict.size)
		if (dict.keys[i] == num)
			return (1);
	return (0);
}

char	*find_value_by_key(t_dictionary dict, long key)
{
	int	i;

	i = -1;
	while (++i < dict.size)
		if (dict.keys[i] == key)
			return (dict.values[i]);
	return (NULL);
}

char	*convert_to_str(t_dictionary dict, long *num_list)
{
	char	*result;
	char	**temp_strs;
	int		i;
	int		count;

	result = NULL;
	i = 0;
	count = 0;
	while (num_list[count] != -1)
		count++;
	temp_strs = malloc((count + 1) * sizeof(char *));
	if (temp_strs == NULL)
		return (NULL);
	while (num_list[i] != -1)
	{
		temp_strs[i] = find_value_by_key(dict, num_list[i]);
		if (!temp_strs[i])
			return (NULL);
		i++;
	}
	temp_strs[i] = NULL;
	result = ft_strjoin(count, temp_strs, " ");
	free(temp_strs);
	return (result);
}

int	main(int argc, char **argv)
{
	char			*dict_str;
	t_dictionary	dict;
	long			num;
	long			*result;
	char			*str;

	dict_str = handle_args(argc, argv);
	if (!dict_str)
		return (0);
	dict = parse_dictionary(dict_str);
	num = ft_atoi(argv[argc - 1]);
	result = decomposit_num(dict, num);
	if (result == '\0')
	{
		write(1, "Error\n", 6);
		return (0);
	}
	str = convert_to_str(dict, result);
	write(1, str, ft_strlen(str));
	write(1, "\n", 1);
	free(result);
	return (0);
}
