/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 07:51:04 by eunwolee          #+#    #+#             */
/*   Updated: 2023/07/11 11:23:09 by eunwolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *dest, char *src, int n)
{
	int		size;
	char	*res;
	int		i;

	size = ft_strlen(dest) + n;
	res = (char *)ft_calloc(size + 1, sizeof(char));
	i = 0;
	if (dest)
		while (*dest)
			res[i++] = *dest++;
	if (src)
		while (n--)
			res[i++] = *src++;
	return (res);
}
