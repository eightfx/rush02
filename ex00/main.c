/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eokoshi <eokoshi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 13:11:43 by eokoshi           #+#    #+#             */
/*   Updated: 2023/08/27 14:13:36 by eokoshi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include <unistd.h>
#define IVI "Invalid index.\n"
#define MAF "Memory allocation failed.\n"

int				is_valid_arg(int argc, char **argv);
int				ft_atoi(char *str);

typedef struct dictionary
{
	int			*keys;
	char		**values;
	int			size;

}				t_dictionary;

int				ft_strlen(char *str);
char			*ft_strjoin(int size, char **strs, char *sep);
char			*read_dictionary(char *path);
t_dictionary	parse_dictionary(char *str);

int	*insert(int *list, int size, int i, int num)
{
	int	*newList;
	int	j;
	int	k;

	if (i < 0 || i > size)
	{
		write(1, IVI, ft_strlen(IVI));
		return (NULL);
	}
	newList = malloc((size + 2) * sizeof(int));
	if (newList == NULL)
	{
		write(1, MAF, ft_strlen(MAF));
		return (NULL);
	}
	j = 0;
	k = -1;
	while (++k < size + 1)
	{
		if (k == i)
			newList[k] = num;
		else
			newList[k] = list[j++];
	}
	newList[size + 1] = -1;
	free(list);
	return (newList);
}

int	find_max_key(t_dictionary dict, int num)
{
	int	i;
	int	max_key;

	max_key = -1;
	i = -1;
	while (++i < dict.size)
		if (dict.keys[i] <= num && dict.keys[i] > max_key)
			max_key = dict.keys[i];
	return (max_key);
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

int	*decomposit_num(t_dictionary dict, int num)
{
	int	*list;
	int	list_size;
	int	i;
	int	j;
	int	quotient;
	int	remainder;
	int	max_key;
	int	all_in_dict;

	list = malloc(sizeof(int));
	list[0] = num;
	list_size = 1;
	i = 0;
	while (1)
	{
		all_in_dict = 1;
		j = 0;
		while (j < list_size)
		{
			if (!is_in_dict(dict, list[j]))
			{
				all_in_dict = 0;
				break ;
			}
			if ((list[j] != 0) && (list[j] == 100 || list[j] % 1000 == 0)
				&& (j == 0 || list[j - 1] % 1000 == 0))
			{
				list = insert(list, list_size, j, 1);
				list_size++;
				j += 1;
			}
			j += 1;
		}
		if (all_in_dict)
		{
			list[list_size] = -1;
			break ;
		}
		if (!is_in_dict(dict, list[i]))
		{
			max_key = find_max_key(dict, list[i]);
			quotient = list[i] / max_key;
			remainder = list[i] % max_key;
			list[i] = max_key;
			if (100 <= max_key)
			{
				list = insert(list, list_size, i, quotient);
				list_size += 1;
				if (remainder != 0)
				{
					list = insert(list, list_size, i + 2, remainder);
					list_size += 1;
				}
			}
			else
			{
				list = insert(list, list_size, i + 1, remainder);
				list_size += 1;
			}
		}
		else
			i++;
	}
	return (list);
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

int	is_valid_dict(char *str)
{
	if (str)
		return (1);
	else
		return (1);
}
int	is_valid_arg(int argc, char **str)
{
	if (argc > 0 || str)
		return (1);
	else
		return (1);
}

int	main(int argc, char **argv)
{
	char			*dict_str;
	t_dictionary	dict;
	int				num;
	int				*result;
	char			*str;
	char			*path;

	if (!is_valid_arg(argc, argv))
	{
		write(1, "Error\n", 6);
	}
	if (argc == 2)
		path = "numbers.dict";
	else
		path = argv[1];
	dict_str = read_dictionary(path);
	if (!is_valid_dict(dict_str))
	{
		write(1, "Dict Error\n", 11);
		return (0);
	}
	dict = parse_dictionary(dict_str);
	num = ft_atoi(argv[argc - 1]);
	result = decomposit_num(dict, num);
	str = convert_to_str(dict, result);
	write(1, str, ft_strlen(str));
	write(1, "\n", 1);
	free(result);
	return (0);
}
