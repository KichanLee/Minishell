/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donghong < donghong@student.42seoul.kr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 11:05:33 by eunwolee          #+#    #+#             */
/*   Updated: 2023/08/03 17:06:43 by donghong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
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