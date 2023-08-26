/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eokoshi <eokoshi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 11:25:10 by eokoshi           #+#    #+#             */
/*   Updated: 2023/08/26 11:25:11 by eokoshi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>

// charsetにchが含まれているかを確認する関数
int	is_delimiter(char ch, char *charset)
{
	while (*charset)
	{
		if (ch == *charset)
			return (1);
		charset++;
	}
	return (0);
}

// 分割後の文字列の数をカウントする関数
int	count_words(char *str, char *charset)
{
	int	count;

	count = 0;
	while (*str)
	{
		while (*str && is_delimiter(*str, charset))
			str++;
		if (*str && !is_delimiter(*str, charset))
		{
			count++;
			while (*str && !is_delimiter(*str, charset))
				str++;
		}
	}
	return (count);
}

// 分割された文字列をコピーする関数
char	*make_word(char *str, char *charset)
{
	int		len;
	char	*word;
	int		i;

	len = 0;
	while (str[len] && !is_delimiter(str[len], charset))
		len++;
	word = (char *)malloc(len + 1);
	i = 0;
	while (i < len)
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	**ft_split(char *str, char *charset)
{
	int		words_count;
	char	**result;
	int		i;

	words_count = count_words(str, charset);
	result = (char **)malloc((words_count + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	i = 0;
	while (*str)
	{
		while (*str && is_delimiter(*str, charset))
			str++;
		if (*str && !is_delimiter(*str, charset))
		{
			result[i] = make_word(str, charset);
			i++;
			while (*str && !is_delimiter(*str, charset))
				str++;
		}
	}
	result[i] = 0;
	return (result);
}
