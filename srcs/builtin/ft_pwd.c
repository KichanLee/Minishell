/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 16:24:31 by kichlee           #+#    #+#             */
/*   Updated: 2023/08/17 12:02:00 by eunwolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	ft_pwd(void);

void	ft_pwd(void)
{
	char	*buf;
	size_t	buf_size;

	buf = NULL;
	buf_size = BUF_SIZE;
	while (1)
	{
		buf = (char *)ft_calloc(buf_size, sizeof(char));
		if (!buf)
			program_error_exit("bash");
		if (getcwd(buf, buf_size) != NULL)
		{
			printf("%s\n", buf);
			free(buf);
			return ;
		}
		free(buf);
		if (buf_size > SIZE_MAX / 2)
			program_error_exit("bash");
		buf_size *= 2;
	}
}
