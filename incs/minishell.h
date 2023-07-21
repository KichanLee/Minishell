/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 11:05:33 by eunwolee          #+#    #+#             */
/*   Updated: 2023/07/21 17:31:49 by eunwolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <unistd.h>
# include <signal.h>
# include <readline/history.h>
# include <readline/readline.h>
# include "exec.h"
# include "pipe.h"
# include "parse.h"
# include "utils.h"
# include "struct.h"
# include "message.h"
# include "../Libft/libft.h"

void	init(t_data **data, char **envp);
void	env_init(t_data *data, char **envp);

//signal
void	child_handler(int signo);
void	herdoc_signal(void);

#endif