/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 17:16:09 by eunwolee          #+#    #+#             */
/*   Updated: 2023/04/06 19:28:36 by eunwolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	idx;
	size_t	h_len;
	size_t	n_len;

	idx = 0;
	if (!*needle)
		return ((char *)haystack);
	if (!len)
		return (0);
	h_len = ft_strlen(haystack);
	n_len = ft_strlen(needle);
	if (len < n_len || h_len < n_len)
		return (0);
	while (idx <= len - n_len && *haystack)
	{
		if (!ft_strncmp(haystack, needle, n_len))
			return ((char *)haystack);
		idx++;
		haystack++;
	}
	return (0);
}
