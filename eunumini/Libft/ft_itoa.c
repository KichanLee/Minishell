/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 12:28:06 by eunwolee          #+#    #+#             */
/*   Updated: 2022/11/17 13:30:13 by eunwolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	cnt_digit(long n)
{
	int	cnt;

	cnt = 0;
	if (!n)
		return (1);
	if (n < 0)
	{
		cnt++;
		n *= -1;
	}
	while (n)
	{
		cnt++;
		n /= 10;
	}
	return (cnt);
}

char	*ft_itoa(int n)
{
	int		idx;
	int		size;
	long	num;
	char	*dest;

	num = (long)n;
	size = cnt_digit(num);
	dest = (char *)malloc(sizeof(char) * (size + 1));
	if (!dest)
		return (0);
	idx = size - 1;
	if (!num)
		dest[0] = '0';
	else if (num < 0)
	{
		dest[0] = '-';
		num *= -1;
	}
	while (num)
	{
		dest[idx--] = (num % 10) + '0';
		num /= 10;
	}
	dest[size] = '\0';
	return (dest);
}
