/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kichan <kichan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 16:24:31 by kichan            #+#    #+#             */
/*   Updated: 2023/07/20 00:31:25 by kichan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define BUF_SIZE 1024
#include "../incs/minishell.h"

void    ft_pwd()
{
    char    *buf;
    size_t  buf_size;

    buf = NULL;
    buf_size = BUF_SIZE;
    while (1)
    {
        buf = (char *)ft_calloc(buf_size, sizeof(char));
        if(!buf)
        {
            perror("ft_calloc fail!");
            // malloc 실패시에 프로그램 종료
            exit(1);
        }
        if(getcwd(buf, buf_size) != NULL)
        {
            printf("%s\n", buf);
            free(buf);
            return ;
        }
        free(buf);
        if(errno !=  ERANGE)
        {
            perror("getcwd error!");
            exit(1);
        }
        buf_size *= 2;
    }
}
