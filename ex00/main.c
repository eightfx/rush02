/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eokoshi <eokoshi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 13:11:43 by eokoshi           #+#    #+#             */
/*   Updated: 2023/08/27 15:01:34 by eokoshi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include <unistd.h>
#define IVI "Invalid index.\n"
#define MAF "Memory allocation failed.\n"

typedef struct dictionary
{
	int			*keys;
	char		**values;
	int			size;

}				t_dictionary;

int				*decomposit_num(t_dictionary dict, int num);
char			*handle_args(int argc, char **argv);
int				is_valid_arg(int argc, char **argv);
int				is_valid_dict(char *str);
int				ft_atoi(char *str);
int				ft_strlen(char *str);
char			*ft_strjoin(int size, char **strs, char *sep);
char			*read_dictionary(char *path);
t_dictionary	parse_dictionary(char *str);

int	*insert(int *list, int size, int i, int num)
{
	int	*new_list;
	int	j;
	int	k;

	if (i < 0 || i > size)
	{
		write(1, IVI, ft_strlen(IVI));
		return (NULL);
	}
	new_list = malloc((size + 2) * sizeof(int));
	if (new_list == NULL)
	{
		write(1, MAF, ft_strlen(MAF));
		return (NULL);
	}
	j = 0;
	k = -1;
	while (++k < size + 1)
	{
		if (k == i)
			new_list[k] = num;
		else
			new_list[k] = list[j++];
	}
	new_list[size + 1] = -1;
	free(list);
	return (new_list);
}

int	is_in_dict(t_dictionary dict, int num)
{
	int	i;

	i = -1;
	while (++i < dict.size)
		if (dict.keys[i] == num)
			return (1);
	return (0);
}

char	*find_value_by_key(t_dictionary dict, int key)
{
	int	i;

	i = -1;
	while (++i < dict.size)
		if (dict.keys[i] == key)
			return (dict.values[i]);
	return (NULL);
}

char	*convert_to_str(t_dictionary dict, int *num_list)
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
	int				num;
	int				*result;
	char			*str;

	dict_str = handle_args(argc, argv);
	if (!dict_str)
		return (0);
	dict = parse_dictionary(dict_str);
	num = ft_atoi(argv[argc - 1]);
	result = decomposit_num(dict, num);
	str = convert_to_str(dict, result);
	write(1, str, ft_strlen(str));
	write(1, "\n", 1);
	free(result);
	return (0);
}
