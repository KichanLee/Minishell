/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 11:06:52 by eunwolee          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/07/21 17:40:23 by eunwolee         ###   ########.fr       */
=======
/*   Updated: 2023/07/21 08:50:37 by eunwolee         ###   ########.fr       */
>>>>>>> 568d9f62bcec9cbc64147565fd0f66fcf8aaab4e
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	init(t_data **data, char **envp);
void	env_init(t_data *data, char **envp);

//필요하신 초기화 내용 여기 넣어주시면 됩니당
void	init(t_data **data, char **envp)
{
	t_pipe *pipe;
	t_info *info;
		
	*data = (t_data *)ft_calloc(1, sizeof(t_data));
	if (!*data)
		program_error_exit("bash");
<<<<<<< HEAD
	pipe_init(&pipe);
	info_init(&info);
	(*data)->pipe= pipe;
	(*data)->info= info;
=======
>>>>>>> 568d9f62bcec9cbc64147565fd0f66fcf8aaab4e
	env_init(*data, envp);
}

void	env_init(t_data *data, char **envp)
{
	int		i;
	t_list	*new;

	i = -1;
	while (envp[++i])
	{
		new = ft_lstnew();
		if (!new)
			program_error_exit("bash");
		new->env = ft_strdup(envp[i]);
		if (!new->env)
			program_error_exit("bash");
		ft_lstadd_back(&data->envs, new);
	}
}

void pipe_init(t_pipe **pipe)
{
	*pipe = (t_pipe *)malloc(sizeof(t_pipe));
	if (!*pipe)
		program_error_exit("bash");
	(*pipe)->cmd_path = NULL;
	(*pipe)->command = NULL;
	(*pipe)->cmd_abs = NULL;
	
}

void	info_init(t_info **info)
{
	*info = (t_info *)malloc(sizeof(t_info));
	if (!*info)
		program_error_exit("bash");
	(*info)->index = 0;
	(*info)->heredoc_flag = 0;
	(*info)->heredoc_file = NULL;
	(*info)->oristdin = dup(STDIN_FILENO);
	(*info)->oristdout = dup(STDOUT_FILENO);
	(*info)->pipe_num = 0;
	(*info)->parent  =0;
}
