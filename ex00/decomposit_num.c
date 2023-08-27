/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decomposit_num.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eokoshi <eokoshi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 14:50:06 by eokoshi           #+#    #+#             */
/*   Updated: 2023/08/27 15:24:21 by eokoshi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include <unistd.h>

typedef struct dictionary
{
	int		*keys;
	char	**values;
	int		size;

}			t_dictionary;

int			*insert(int *list, int size, int i, int num);

int			is_in_dict(t_dictionary dict, int num);

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

int	check_all_in_dict(t_dictionary dict, int *list, int list_size)
{
	int	j;

	j = 0;
	while (j < list_size)
	{
		if (!is_in_dict(dict, list[j]))
		{
			return (0);
		}
		j++;
	}
	return (1);
}

void	decompose_and_insert(t_dictionary dict, int **list, int *list_size,
		int i)
{
	int	max_key;
	int	quotient;
	int	remainder;

	max_key = find_max_key(dict, (*list)[i]);
	quotient = (*list)[i] / max_key;
	remainder = (*list)[i] % max_key;
	(*list)[i] = max_key;
	if (100 <= max_key)
	{
		*list = insert(*list, *list_size, i, quotient);
		(*list_size)++;
		if (remainder != 0)
		{
			*list = insert(*list, *list_size, i + 2, remainder);
			(*list_size)++;
		}
	}
	else if (remainder != 0)
	{
		*list = insert(*list, *list_size, i + 1, remainder);
		(*list_size)++;
	}
}

void	process_list(t_dictionary dict, int **list, int *list_size)
{
	int	i;

	i = 0;
	while (i < *list_size)
	{
		if (((*list)[i] != 0) && ((*list)[i] == 100 || (*list)[i] % 1000 == 0)
			&& (i == 0 || (*list)[i - 1] % 1000 == 0))
		{
			*list = insert(*list, *list_size, i, 1);
			(*list_size)++;
		}
		if (!is_in_dict(dict, (*list)[i]))
			decompose_and_insert(dict, list, list_size, i);
		i++;
	}
}

int	*decomposit_num(t_dictionary dict, int num)
{
	int	*list;
	int	list_size;

	list_size = 1;
	list = malloc(sizeof(int));
	list[0] = num;
	while (1)
	{
		if (check_all_in_dict(dict, list, list_size))
		{
			list[list_size] = -1;
			break ;
		}
		process_list(dict, &list, &list_size);
	}
	return (list);
}
