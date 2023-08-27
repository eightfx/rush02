/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eokoshi <eokoshi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 17:55:17 by eokoshi           #+#    #+#             */
/*   Updated: 2023/08/27 17:59:18 by eokoshi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include <unistd.h>
#define IVI "Invalid index.\n"
#define MAF "Memory allocation failed.\n"

int		ft_strlen(char *str);

// メモリ確保とエラーチェック
long	*allocate_new_list(int size)
{
	long	*new_list;

	new_list = malloc((size + 2) * sizeof(long));
	if (new_list == NULL)
	{
		write(1, MAF, ft_strlen(MAF));
		return (NULL);
	}
	return (new_list);
}

// 既存のリストから新しいリストへ要素をコピー
void	copy_elements(long *new_list, long *old_list, int size,
		int insert_index)
{
	int	j;
	int	k;

	j = 0;
	k = 0;
	while (k < size + 1)
	{
		if (k == insert_index)
		{
			k++;
			continue ;
		}
		new_list[k++] = old_list[j++];
	}
}

// 新しい要素を挿入
long	*insert(long *list, int size, int i, long num)
{
	long	*new_list;

	if (i < 0 || i > size)
	{
		write(1, IVI, ft_strlen(IVI));
		return (NULL);
	}
	new_list = allocate_new_list(size);
	if (new_list == NULL)
	{
		return (NULL);
	}
	copy_elements(new_list, list, size, i);
	new_list[i] = num;
	new_list[size + 1] = -1;
	free(list);
	return (new_list);
}
