/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 14:30:50 by eunwolee          #+#    #+#             */
/*   Updated: 2022/12/02 15:49:00 by eunwolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static const char	*from_front(char const *s1, char const *set, int *size)
{
	while (*s1)
	{
		if (!ft_strchr(set, *s1))
			break ;
		s1++;
		*size -= 1;
	}
	return (s1);
}

static void	from_back(char const *tmp, char const *set, int *size)
{
	while (*tmp)
	{
		if (!ft_strchr(set, *tmp))
			break ;
		tmp--;
		*size -= 1;
	}
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int			size;
	char		*dest;
	char const	*tmp;

	size = ft_strlen(s1);
	s1 = from_front(s1, set, &size);
	tmp = s1;
	tmp += size - 1;
	if (size)
		from_back(tmp, set, &size);
	dest = (char *)malloc(sizeof(char) * (size + 1));
	if (!dest)
		return (0);
	ft_strlcpy(dest, s1, size + 1);
	return (dest);
}
