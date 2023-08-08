/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kichlee <kichlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 18:40:34 by kichlee           #+#    #+#             */
/*   Updated: 2023/08/07 18:06:52 by kichlee          ###   ########.fr       */
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
    if (tcsetattr(STDIN_FILENO,TCSANOW, &termi)  == -1) 
        exit(1);
}


void    handle_sigint(int sig)
{
    // printf("handle function !");
    printf("\n");
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
    // printf("after sig\n");
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