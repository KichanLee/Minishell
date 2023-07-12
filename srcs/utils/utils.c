/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 14:56:33 by eunwolee          #+#    #+#             */
/*   Updated: 2023/07/12 16:38:50 by eunwolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	syntax_error_exit(char *str)
{
	printf("%s\n", str);
	exit(2); //부모가 258로 받게 해야 함
}

void	error_exit(char *str)
{
	perror(str);
	exit(errno);
}