/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kichlee <kichlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 18:40:34 by kichlee           #+#    #+#             */
/*   Updated: 2023/07/15 19:56:41 by kichlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void    handle_sigint(int sig)
{
    printf("\n");
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
    (void) sig;
}

void    sig(char *command)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
    if(command)
        free(command);
}