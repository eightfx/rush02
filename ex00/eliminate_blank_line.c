/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eliminate_blank_line.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eokoshi <eokoshi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 13:21:25 by eokoshi           #+#    #+#             */
/*   Updated: 2023/08/27 13:29:11 by eokoshi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>

int			ft_strlen(char *str);

static int	is_newline(char c)
{
	return (c == '\n');
}

static void	add_to_result(char *result, int *result_idx, char current_char,
		int *is_prev_newline)
{
	if (is_newline(current_char))
	{
		if (!(*is_prev_newline))
		{
			result[(*result_idx)++] = current_char;
		}
		*is_prev_newline = 1;
	}
	else
	{
		result[(*result_idx)++] = current_char;
		*is_prev_newline = 0;
	}
}

char	*eliminate_blank_line(char *original_str)
{
	int		original_idx;
	int		result_idx;
	int		original_len;
	char	*result_str;
	int		is_prev_newline;

	original_idx = 0;
	result_idx = 0;
	original_len = ft_strlen(original_str);
	result_str = (char *)malloc(original_len + 1);
	is_prev_newline = 0;
	if (!result_str)
	{
		return (NULL);
	}
	while (original_idx < original_len)
	{
		add_to_result(result_str, &result_idx, original_str[original_idx],
			&is_prev_newline);
		original_idx++;
	}
	result_str[result_idx] = '\0';
	return (result_str);
}
