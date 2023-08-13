/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 07:51:04 by eunwolee          #+#    #+#             */
/*   Updated: 2023/08/11 10:29:43 by eunwolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *dest, char *src, int n)
{
	int		size;
	char	*res;
	int		i;
	int		j;

	if (!dest || !src)
		return (NULL);
	size = ft_strlen(dest) + n;
	res = (char *)ft_calloc(size + 1, sizeof(char));
	if (!res)
		return (NULL);
	i = 0;
	while (dest[i])
	{
		res[i] = dest[i];
		i++;
	}
	free(dest);
	j = 0;
	while (j < n)
	{
		res[i + j] = src[j];
		j++;
	}
	return (res);
}
