/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eokoshi <eokoshi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 14:15:09 by eokoshi           #+#    #+#             */
/*   Updated: 2023/08/27 20:23:54 by eokoshi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include <unistd.h>

char	*eliminate_blank_line(char *original_str);
long	arg_atoi(char *str);
char	*read_dictionary(char *path);

int		is_valid_dict(char *str);
long	is_valid_arg(int argc, char **argv)
{
	long	result;

	(void)argc;
	if (argc == 2)
	{
		result = arg_atoi(argv[1]);
		if (result == -1)
			return (-1);
	}
	else if (argc == 3)
	{
		result = arg_atoi(argv[2]);
		if (result == -1)
			return (-1);
	}
	else
		return (-1);
	return (result);
}

// Handles the command-line arguments and reads the dictionary file accordingly.
// args:
//   - argc : The number of command-line arguments.
//   - argv : The array of command-line arguments.
// returns:
//   - char* : A pointer to the string containing the content of
//     the dictionary. NULL if an error occurs.
char	*handle_args(int argc, char **argv)
{
	char	*dict_str;

	if (is_valid_arg(argc, argv) == -1)
	{
		write(1, "Error\n", 6);
		return (NULL);
	}
	if (argc == 2)
		dict_str = read_dictionary("numbers.dict");
	else
		dict_str = read_dictionary(argv[1]);
	dict_str = eliminate_blank_line(dict_str);
	if (!is_valid_dict(dict_str))
	{
		write(1, "Dict Error\n", 11);
		return (NULL);
	}
	return (dict_str);
}
