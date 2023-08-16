/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 17:49:19 by eunwolee          #+#    #+#             */
/*   Updated: 2023/08/16 19:15:52 by eunwolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "struct.h"

t_bool	get_input(t_data *data);

void	execute(t_data *data);
void	execute_cmd(t_data *data, int flag);

/*execve utils*/
int		check_builtin(t_data *data);
void	recover_std(t_data *data);
void	heredoc_flag(t_leaf *leaf, t_data *data);
void	error_print(char *cmd, char *option, int flag);

/*child*/
void	do_cmd(t_data *data);
void	exec_fork(t_data *data);

/*parent*/
void	wait_child_processes(t_data *data);

void	check_redirect(t_leaf *leaf, t_data *data);

int		fork_heredoc(t_data *data);

/*heredoc_uilts*/
void	write_str(t_data *data, char *content, int fd);

char	*set_path(t_data *data, t_leaf *leaf);
void	abs_path(t_data *data);

void	check_file(int fd, t_data *data);
void	close_file(t_data *data);

void	sig(void);
void	handle_sigint(int sig);
void	init_base(int ac);
void	child_handler(int signum);

int		link_pipe(int i, t_pipe *base, t_data *data);
void	close_pipe(int i, t_pipe *base, t_data *data);
void	count_pipe(t_data *data);

#endif