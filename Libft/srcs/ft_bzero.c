/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 15:33:02 by eunwolee          #+#    #+#             */
/*   Updated: 2022/11/26 16:38:32 by eunwolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void	*s, size_t	n)
{
	unsigned char	*str;

	str = (unsigned char *)s;
	while (n--)
		*str++ = 0;
}
