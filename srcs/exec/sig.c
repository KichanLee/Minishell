/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kichan <kichan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 18:40:34 by kichlee           #+#    #+#             */
/*   Updated: 2023/07/17 23:26:37 by kichan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"


#include <stdio.h>
#include <termios.h>

// void set_terminal_print_off() {
//     struct termios old_term, new_term;
//     tcgetattr(fileno(stdin), &old_term); // 기존의 터미널 설정 가져오기

//     new_term = old_term;
//     new_term.c_lflag &= ~(ECHOCTL); // 시그널표식 출력이 true 라면 false로 변경

//     tcsetattr(fileno(stdin), TCSANOW, &new_term); // 변경한 설정을 터미널에 적용
// }


// void	set_terminal_print_off(void)
// {
// 	struct termios	term; // 터미널 설정이 담겨있는 termios 구조체

// 	tcgetattr(1, &term); // 현재 터미널의 설정을 term에 가져옴
// 	term.c_lflag &= ~(ECHOCTL); // 시그널표식 출력이 true 라면 false로 변경
// 	tcsetattr(1, 0, &term); // 변경한 term 설정을 현재 터미널에 적용
// }


void    handle_sigint(int sig)
{
    printf("\n");
    // rl_on_new_line();
    // rl_replace_line("", 0);
    // rl_redisplay();
    (void) sig;
}

void    sig(char *command)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
    if(command)
        free(command);
}