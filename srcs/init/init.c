/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 11:06:52 by eunwolee          #+#    #+#             */
/*   Updated: 2023/08/17 13:30:40 by eunwolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	init(t_data **data, char **envp);
void	env_init(t_data *data, char **envp);
void	pipe_init(t_pipe **pipe);
void	info_init(t_info **info);

void	init(t_data **data, char **envp)
{
	*data = (t_data *)ft_calloc(1, sizeof(t_data));
	if (!*data)
		program_error_exit("bash");
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
		new->env = ft_strdup(envp[i]);
		new->equal_flag = 0;
		if (!new->env)
			program_error_exit("bash");
		ft_lstadd_back(&data->envs, new);
	}
}

void	pipe_init(t_pipe **pipe)
{
	*pipe = (t_pipe *)ft_calloc(1, sizeof(t_pipe));
	if (!*pipe)
		program_error_exit("bash");
}

void	info_init(t_info **info)
{
	*info = (t_info *)ft_calloc(1, sizeof(t_info));
	if (!*info)
		program_error_exit("bash");
	(*info)->oristdin = dup(STDIN_FILENO);
	(*info)->oristdout = dup(STDOUT_FILENO);
}
