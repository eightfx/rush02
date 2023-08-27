/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eokoshi <eokoshi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 14:15:09 by eokoshi           #+#    #+#             */
/*   Updated: 2023/08/27 14:35:36 by eokoshi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>

char	*read_dictionary(char *path);

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

	if (!is_valid_arg(argc, argv))
	{
		write(1, "Error\n", 6);
		return (NULL);
	}
	if (argc == 2)
		dict_str = read_dictionary("numbers.dict");
	else
		dict_str = read_dictionary(argv[1]);
	if (!is_valid_dict(dict_str))
	{
		write(1, "Dict Error\n", 11);
		return (NULL);
	}
	return (dict_str);
}
