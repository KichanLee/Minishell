/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atolong.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kichlee <kichlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 16:41:29 by kichlee           #+#    #+#             */
/*   Updated: 2023/08/08 18:49:11 by kichlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// long long ft_atolong(const char *str, int *flag)
// {
//     unsigned long long res;
//     int sign;
    
//     res = 0;
//     sign = 1;
//     while ((*str >= 9 && *str <= 13) || *str == 32)
// 		str++;
//     if (*str == '+' || *str == '-')
// 	{
// 		if (*str == '-')
// 			sign *= -1;
// 		str++;
// 	}

//     while (*str >= '0' && *str <= '9')
// 	{
// 		res = (res * 10) + (*str++ - '0');

// 		if (((res > 9223372036854775807ULL) && (sign == 1))
// 		|| ((res > 9223372036854775808ULL) && (sign == -1)))
// 		*flag = 0;
// 	}
// 	return (res * sign);
// }
