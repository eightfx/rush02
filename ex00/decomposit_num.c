/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decomposit_num.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eokoshi <eokoshi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 14:50:06 by eokoshi           #+#    #+#             */
/*   Updated: 2023/08/27 18:10:55 by eokoshi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct dictionary
{
	long	*keys;
	char	**values;
	int		size;

}			t_dictionary;

long		*insert(long *list, int size, int i, long num);

int			is_in_dict(t_dictionary dict, long num);

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

// Checks whether all numbers in the list exist in the dictionary.
// args:
//   - dict : The dictionary containing the keys.
//   - list : The list of integers to check.
//   - list_size : The size of the list.
// returns:
//   - int : 1 if all numbers are in the dictionary, 0 otherwise.
int	check_all_in_dict(t_dictionary dict, long *list, int list_size)
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

// Decomposes a number into smaller numbers based
// on the maximum keys in the dictionary,
// and inserts those smaller numbers into the list.
// args:
//   - dict : The dictionary containing the keys.
//   - list : A pointer to the list of integers.
//   - list_size : A pointer to the size of the list.
//   - i : The index of the number in the list to decompose.
void	decompose_and_insert(t_dictionary dict, long **list, int *list_size,
		int i)
{
	long	max_key;
	long	quotient;
	long	remainder;

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

// Processes the list to ensure all numbers in it exist in the dictionary,
// decomposing and inserting numbers as necessary.
// args:
//   - dict : The dictionary containing the keys.
//   - list : A pointer to the list of integers.
//   - list_size : A pointer to the size of the list.
void	process_list(t_dictionary dict, long **list, int *list_size)
{
	int	i;

	i = 0;
	while (i < *list_size)
	{
		if (((*list)[i] != 0) && ((*list)[i] == 100 || (*list)[i] % 1000 == 0)
			&& (i == 0 || (*list)[i - 1] % 1000 == 0) && *list_size != 1)
		{
			*list = insert(*list, *list_size, i, 1);
			(*list_size)++;
		}
		if (!is_in_dict(dict, (*list)[i]))
			decompose_and_insert(dict, list, list_size, i);
		i++;
	}
}

// Decomposes a number into a list of smaller
// numbers that exist in the dictionary.
// args:
//   - dict : The dictionary containing the keys.
//   - num : The number to decompose.
// returns:
//   - int* : A pointer to the list of decomposed numbers.
long	*decomposit_num(t_dictionary dict, long num)
{
	long	*list;
	int		list_size;

	list_size = 1;
	list = malloc(sizeof(long));
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
	if (list_size == 1 && list[0] % 10 == 0 && list[0] >= 100)
		list = insert(list, list_size, 0, 1);
	return (list);
}
