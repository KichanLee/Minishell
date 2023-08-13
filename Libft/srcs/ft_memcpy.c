/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 14:09:56 by eunwolee          #+#    #+#             */
/*   Updated: 2022/11/23 22:50:36 by eunwolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*dest;
	const unsigned char	*source;

	if (!dst && !src)
		return (0);
	dest = (unsigned char *)dst;
	source = (const unsigned char *)src;
	while (n--)
		*dest++ = *source++;
	return (dst);
}
