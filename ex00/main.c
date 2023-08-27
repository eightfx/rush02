/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eokoshi <eokoshi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 13:11:43 by eokoshi           #+#    #+#             */
/*   Updated: 2023/08/27 13:11:45 by eokoshi          ###   ########.fr       */
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
		j = -1;
		while (++j < list_size)
			if (!is_in_dict(dict, list[j]))
			{
				all_in_dict = 0;
				break ;
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
				list = insert(list, list_size++, i, quotient);
				if (remainder)
					list = insert(list, list_size++, i + 2, remainder);
			}
			else
				list = insert(list, list_size++, i + 1, remainder);
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

int	main(void)
{
	char			*dict_str;
	t_dictionary	dict;
	int				num;
	int				*result;
	char			*str;

	// if (argc != 2 && argv != '\0')
	//{
	//}
	dict_str = read_dictionary("numbers.dict");
	dict = parse_dictionary(dict_str);
	num = 123456;
	result = decomposit_num(dict, 123456);
	str = convert_to_str(dict, result);
	write(1, str, ft_strlen(str));
	free(result);
	return (0);
}
