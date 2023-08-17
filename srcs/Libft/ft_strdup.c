/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 18:07:32 by eunwolee          #+#    #+#             */
/*   Updated: 2023/08/17 13:33:05 by eunwolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

char	*ft_strdup(const char *s1)
{
	size_t		len;
	char		*dest;

	len = ft_strlen(s1);
	dest = (char *)ft_calloc((len + 1), sizeof(char));
	if (!dest)
		program_error_exit("bash");
	ft_strlcpy(dest, s1, len + 1);
	return (dest);
}
