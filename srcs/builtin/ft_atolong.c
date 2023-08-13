/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atolong.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 20:31:59 by kichlee           #+#    #+#             */
/*   Updated: 2023/08/13 16:10:44 by eunwolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

char	*pass_blank_sign(char *str, int *sign)
{
	while ((*str >= 9 && *str <= 13) || *str == 32)
		++str;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			*sign *= -1;
		str++;
	}
	return (str);
}

int	check_overflow(long long result, char ch)
{
	if (result > LLONG_MAX / 10 || \
	(result == LLONG_MAX / 10 && (ch - '0') > LLONG_MAX % 10))
		return (1);
	return (0);
}

int	check_underflow(long long result, char ch)
{
	if (result > -(LLONG_MIN / 10) || \
		(result == -(LLONG_MIN / 10) && (ch - '0') > -(LLONG_MIN % 10)))
		return (1);
	return (0);
}

long long	char_to_long_long(char *str, int *flag)
{
	long long	result;
	int			sign;
	int			i;

	result = 0;
	sign = 1;
	i = -1;
	str = pass_blank_sign(str, &sign);
	while (ft_isdigit(str[++i]))
	{
		if (check_overflow(result, str[i]))
		{
			if ((sign == 1 && check_overflow(result, str[i])) || \
			(sign == -1 && check_underflow(result, str[i])))
			{
				*flag = 0;
				return (0);
			}
		}
		result = result * 10 + (str[i] - '0');
	}
	*flag = 1;
	return (result * sign);
}
