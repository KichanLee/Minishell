/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 16:27:27 by eunwolee          #+#    #+#             */
/*   Updated: 2022/11/14 20:29:15 by eunwolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	int		cnt;
	size_t	dst_len;
	size_t	src_len;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	if (dst_len >= dstsize)
		return (src_len + dstsize);
	dst += dst_len;
	cnt = dstsize - dst_len - 1;
	while (*src && cnt--)
		*dst++ = *src++;
	*dst = '\0';
	return (dst_len + src_len);
}
