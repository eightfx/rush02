/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_dict.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eokoshi <eokoshi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 20:16:40 by eokoshi           #+#    #+#             */
/*   Updated: 2023/08/27 20:20:38 by eokoshi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>

int	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r');
}

int	is_printable(char c)
{
	return (c >= 32 && c <= 126);
}

int	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

int	is_valid_dict(char *str)
{
	while (*str)
	{
		// [a number]
		if (!is_digit(*str))
			return (0);
		while (is_digit(*str))
			str++;
		// [0 to n spaces]
		while (is_space(*str))
			str++;
		// :
		if (*str != ':')
			return (0);
		str++;
		// [0 to n spaces]
		while (is_space(*str))
			str++;
		// [any printable characters]
		if (!is_printable(*str))
			return (0);
		while (is_printable(*str))
			str++;
		// \n
		if (*str != '\n')
			return (0);
		str++;
	}
	return (1);
}
