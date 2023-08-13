/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 11:06:52 by eunwolee          #+#    #+#             */
/*   Updated: 2023/08/13 17:07:19 by eunwolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	init(t_data **data, char **envp);
void	env_init(t_data *data, char **envp);

//필요하신 초기화 내용 여기 넣어주시면 됩니당
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
		if (!new)
			program_error_exit("bash");
		new->env = ft_strdup(envp[i]);
		if (!new->env)
			program_error_exit("bash");
		ft_lstadd_back(&data->envs, new);
	}
}

void	pipe_init(t_pipe **pipe)
{
	*pipe = (t_pipe *)malloc(sizeof(t_pipe));
	if (!*pipe)
		program_error_exit("bash");
	(*pipe)->cmd_path = NULL;
	(*pipe)->command = NULL;
	(*pipe)->cmd_abs = NULL;
}

t_bool	get_input(t_data *data)
{
	data->input = readline("minishell$ ");
	if (!data->input)
		program_error_exit("bash");
	if (!data->input[0])
	{
		free(data->input);
		return (FALSE);
	}
	add_history(data->input);
	lexer(data);
	if (syntax(data) == FALSE)
	{
		tree_clear(data->root);
		ft_lstclear(&data->tokens);
		free(data->input);
		return (FALSE);
	}
	parser(data);
	pipe_init(&data->pipe);
	info_init(&data->info);
	return (TRUE);
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
	(*info)->pipe_index = 0;
	(*info)->parent = 0;
}
