/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kichlee <kichlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 11:05:33 by eunwolee          #+#    #+#             */
/*   Updated: 2023/08/07 14:53:16 by kichlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <term.h>
# include <stdio.h>
# include <unistd.h>
#include <stdlib.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/stat.h>
# include "init.h"
# include "parse.h"
# include "struct.h"
# include "utils.h"
# include "bulitin.h"
# include "pipe.h"
# include "message.h"
# include "../Libft/libft.h"
#include <readline/readline.h>
#include <readline/history.h>

#endif