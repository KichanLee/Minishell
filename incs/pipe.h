/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 16:03:34 by eunwolee          #+#    #+#             */
/*   Updated: 2023/08/14 20:48:50 by eunwolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPE_H
# define PIPE_H

void	count_pipe(t_data*data);
int		check_bulitin(t_data *data);
void	check_file(int fd, t_data *data);
void	recover_std(t_data *data);
int		link_pipe(int i, t_pipe *base, t_data *data);
void	do_cmd(t_data *data);
void	exec_fork(t_data *data);
void	close_pipe(int i, t_pipe *base, t_data *data);
void	close_file(t_data *data);

#endif