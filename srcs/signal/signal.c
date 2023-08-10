/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 18:40:34 by kichlee           #+#    #+#             */
/*   Updated: 2023/08/11 06:30:57 by eunwolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void init_base(int ac)
{
	
    struct termios termi;
	
    if (ac != 1)
        exit(1);
    if(tcgetattr(STDIN_FILENO,&termi)== -1)
        exit(1);
    termi.c_lflag &= ~(ECHOCTL); 
    if (tcsetattr(STDIN_FILENO, TCSANOW, &termi) == (-1)
		|| tgetent (NULL, "xterm-256color") == -1)
        exit(1);
}

void    handle_sigint(int sig)
{
    printf("\n");
    rl_on_new_line();
    // rl_replace_line("", 0);
    rl_redisplay();
    (void) sig;
}

void child_handler(int signum)
{
    printf("\n");
    exit(EXIT_SUCCESS);
    (void) signum;
}


void    sig()
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}