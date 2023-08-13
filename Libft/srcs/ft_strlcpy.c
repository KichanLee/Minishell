/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 16:08:41 by eunwolee          #+#    #+#             */
/*   Updated: 2022/11/17 15:37:54 by eunwolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	len;

	len = ft_strlen(src);
	if (!dstsize)
		return (len);
	while (*src && dstsize > 1)
	{
		*dst++ = *src++;
		dstsize--;
	}
	*dst = '\0';
	return (len);
}
