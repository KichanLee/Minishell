/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 11:05:33 by eunwolee          #+#    #+#             */
/*   Updated: 2023/07/22 08:27:15 by eunwolee         ###   ########.fr       */
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
# include "init.h"
# include "exec.h"
# include "pipe.h"
# include <readline/readline.h>
# include <readline/history.h>
# include "parse.h"
# include "utils.h"
# include "struct.h"
# include "message.h"
# include "../Libft/libft.h"

//signal
// void	child_handler(int signo);
// void	herdoc_signal(void);

#endif