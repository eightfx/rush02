/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eokoshi <eokoshi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 11:25:16 by eokoshi           #+#    #+#             */
/*   Updated: 2023/08/27 16:00:52 by eokoshi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
char	*remove_spaces(char *str)
{
	while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\v'
		|| *str == '\f' || *str == '\r')
		str++;
	return (str);
}

char	*calculate_sign(char *str, int *sign)
{
	int	minus_count;

	minus_count = 0;
	while (*str == '+' || *str == '-')
		if (*str++ == '-')
			minus_count++;
	if (minus_count % 2 == 0)
		*sign = 1;
	else
		*sign = -1;
	return (str);
}

char	*remove_non_digits(char *str)
{
	char		*p;
	static char	s[1000];

	p = s;
	while (*str >= '0' && *str <= '9')
		*p++ = *str++;
	*p = '\0';
	return (s);
}

int	ft_atoi(char *str)
{
	int	sign;
	int	result;

	str = remove_spaces(str);
	str = calculate_sign(str, &sign);
	str = remove_non_digits(str);
	result = 0;
	while (*str)
		result = result * 10 + (*str++ - '0');
	return (sign * result);
}

int	arg_atoi(char *str)
{
	long	result;

	if (*str++ == '-')
		return (-1);
	while (*str)
	{
		if (*str < '0' || '9' < *str)
			return (-1);
		result = result * 10 + *str - '0';
		str++;
	}
	if (0 <= result && result <= 4294967295)
		return (result);
	else
		return (-1);
}
