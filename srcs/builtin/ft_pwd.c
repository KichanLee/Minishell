/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kichlee <kichlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 16:24:31 by kichan            #+#    #+#             */
/*   Updated: 2023/08/07 14:29:41 by kichlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void    ft_pwd(t_data *data, t_leaf *cur_root);

void    ft_pwd(t_data *data, t_leaf *cur_root)
{
    (void)data;
    (void)cur_root;

    char    *buf;
    size_t  buf_size;

    buf = NULL;
    buf_size = BUF_SIZE;
    while (1)
    {
        buf = (char *)ft_calloc(buf_size, sizeof(char));
        if (!buf)
            program_error_exit("ft_calloc fail!");
        if (getcwd(buf, buf_size) != NULL)
        {
            printf("%s\n", buf);
            free(buf);
            return ;
        }
        free(buf);
        if (errno != ERANGE)
            program_error_exit("get_cwd fail!");
        buf_size *= 2;
    }
}
