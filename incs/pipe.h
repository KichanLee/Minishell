/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 19:06:40 by eunwolee          #+#    #+#             */
/*   Updated: 2023/08/07 19:07:50 by eunwolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPE_H
# define PIPE_H

//info init
void	info_init(t_info **info);
void	pipe_init(t_pipe **pipe);
void	count_pipe(t_data*data);
void	execute_cmd(t_data *data, int flag);
int		fork_heredoc(t_data *data);
int		check_bulitin(t_data *data);
void	heredoc_flag(t_leaf *leaf, t_data *data);
void	check_file(int fd, t_data *data);
void	check_redirect(t_leaf *leaf, t_data *data);
void	recover_std(t_data *data);
void	mk_heredoc_pipe(t_data *data);
void	link_pipe(int i, t_pipe *base, t_data *data);
void	check_redirect(t_leaf *leaf, t_data *data);
void	do_cmd(t_data *data);
void	exec_fork(t_data *data);
void	abs_path(t_data *data);
char	*set_path(t_data *data, t_leaf *leaf);
char	**join_cmd(t_leaf *com_leaf);
void	close_pipe(int i, t_pipe *base, t_data *data);
void	wait_child_processes(t_data *data);
char	*search_path(t_pipe *base);
void	execute(t_data *data);
void	get_input(t_data *data);

#endif