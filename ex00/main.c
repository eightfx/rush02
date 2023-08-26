#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct dictionary
{
	int			*keys;
	char		**values;
	int			size;

}				t_dictionary;

char			*read_dictionary(char *path);
t_dictionary	parse_dictionary(char *str);

int	*insert(int *list, int size, int i, int num)
{
	int	*newList;

	int j, k;
	if (i < 0 || i > size)
	{
		printf("Invalid index.\n");
		return (NULL);
	}
	newList = malloc((size + 2) * sizeof(int)); // size
	if (newList == NULL)
	{
		printf("Memory allocation failed.\n");
		return (NULL);
	}
	j = 0;
	k = 0;
	while (k < size + 1)
	{
		if (k == i)
		{
			newList[k] = num;
		}
		else
		{
			newList[k] = list[j];
			j++;
		}
		k++;
	}
	newList[size + 1] = -1; // Add end marker
	free(list);
	return (newList);
}

int	find_max_key(t_dictionary dict, int num)
{
	int	i;

	int max_key = -1; // Initialize to an invalid value
	i = 0;
	while (i < dict.size)
	{
		if (dict.keys[i] <= num && dict.keys[i] > max_key)
		{
			max_key = dict.keys[i];
		}
		i++;
	}
	return (max_key);
}

int	is_in_dict(t_dictionary dict, int num)
{
	int	i;

	i = 0;
	while (i < dict.size)
	{
		if (dict.keys[i] == num)
		{
			return (1);
		}
		i++;
	}
	return (0);
}

int	*decomposit_num(t_dictionary dict, int num)
{
	int	*list;
	int	list_size;
	int	i;
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
		for (int j = 0; j < list_size; j += 2)
		{
			if (!is_in_dict(dict, list[j]))
			{
				all_in_dict = 0;
				break ;
			}
		}
		if (all_in_dict)
			break ;
		if (!is_in_dict(dict, list[i]))
		{
			max_key = find_max_key(dict, list[i]);
			quotient = list[i] / max_key;
			remainder = list[i] % max_key;
			list[i] = max_key;
			list = insert(list, list_size, i, quotient);
			list_size += 1; // Update list_size after inserting quotient
			list = insert(list, list_size, i + 2, remainder);
			list_size += 1; // Update list_size after inserting remainder
		}
		else
		{
			i += 1; // Skip to the next pair
		}
	}
	return (list);
}

int	main(int argc, char **argv)
{
	char			*dict_str;
	t_dictionary	dict;
	int				num;
	int				*result;

	if (argc != 2 && argv != '\0')
	{
	}
	dict_str = read_dictionary("numbers.dict");
	dict = parse_dictionary(dict_str);
	num = 123456;
	result = decomposit_num(dict, 123456);
	// 結果を表示
	for (int i = 0; i < 12; ++i)
	{
		printf("%d ", result[i]);
	}
	printf("\n");
	free(result);
	return (0);
}
