/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 10:29:44 by eunwolee          #+#    #+#             */
/*   Updated: 2023/08/15 00:45:00 by eunwolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

# include "struct.h"

void	init(t_data **data, char **envp);
void	env_init(t_data *data, char **envp);
void	pipe_init(t_pipe **pipe);
void	info_init(t_info **info);

#endif