#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct dictionary
{
	int			*keys;
	char		**values;
	int			size;

}				t_dictionary;

char			*ft_strjoin(int size, char **strs, char *sep);
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
	newList = malloc((size + 2) * sizeof(int));
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
	newList[size + 1] = -1;
	free(list);
	return (newList);
}

int	find_max_key(t_dictionary dict, int num)
{
	int	i;
	int	max_key;

	max_key = -1;
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
			list_size += 1;
			list = insert(list, list_size, i + 2, remainder);
			list_size += 1;
		}
		else
		{
			i += 1;
		}
	}
	return (list);
}

char	*find_value_by_key(t_dictionary dict, int key)
{
	int	i;

	i = 0;
	while (i < dict.size)
	{
		if (dict.keys[i] == key)
		{
			return (dict.values[i]);
		}
		i++;
	}
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
	// Count the size of num_list (up to -1)
	while (num_list[count] != -1)
	{
		count++;
	}
	// Allocate memory for temporary string array
	temp_strs = malloc((count + 1) * sizeof(char *));
	if (temp_strs == NULL)
	{
		return (NULL);
	}
	// Convert keys to corresponding values and store them in temp_strs
	while (num_list[i] != -1)
	{
		temp_strs[i] = find_value_by_key(dict, num_list[i]);
		i++;
	}
	temp_strs[i] = NULL; // Null-terminate the array
	// Join the temporary strings into one string
	result = ft_strjoin(count, temp_strs, " ");
	// Assuming a space is the separator between numbers
	free(temp_strs);
	// Free the allocated memory for temp_strs
	return (result);
}

int	main(int argc, char **argv)
{
	char			*dict_str;
	t_dictionary	dict;
	int				num;
	int				*result;
	char			*str;

	if (argc != 2 && argv != '\0')
	{
	}
	dict_str = read_dictionary("numbers.dict");
	dict = parse_dictionary(dict_str);
	num = 123456;
	result = decomposit_num(dict, 123456);
	str = convert_to_str(dict, result);
	printf("%s", str);
	free(result);
	return (0);
}
