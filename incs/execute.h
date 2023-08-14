/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 17:49:19 by eunwolee          #+#    #+#             */
/*   Updated: 2023/08/14 18:58:06 by eunwolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "struct.h"

t_bool	get_input(t_data *data);

/*execve*/
void	execute(t_data *data);
void	execute_cmd(t_data *data, int flag);

/*execve utils*/
int		check_bulitin(t_data *data);
void	recover_std(t_data *data);
void	heredoc_flag(t_leaf *leaf, t_data *data);

/*child*/
void	do_cmd(t_data *data);
void	exec_fork(t_data *data);

/*parent*/
void	wait_child_processes(t_data *data);

/*redirect*/
void	check_redirect(t_leaf *leaf, t_data *data);

/*heredoc*/
int		fork_heredoc(t_data *data);

/*heredoc_uilts*/
void	write_str(t_data *data, char *content, int fd);

/*path*/
char	*set_path(t_data *data, t_leaf *leaf);
void	abs_path(t_data *data);

/*file*/
void	check_file(int fd, t_data *data);
void	close_file(t_data *data);

/*signal*/
void	sig(void);
void	handle_sigint(int sig);
void	init_base(int ac);
void	child_handler(int signum);

#endif