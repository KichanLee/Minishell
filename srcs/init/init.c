/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 11:06:52 by eunwolee          #+#    #+#             */
/*   Updated: 2023/07/22 08:20:41 by eunwolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	init(t_data **data, char **envp);
void	init_env(t_input *input, char **envp);

void	init(t_data **data, char **envp)
{
	*data = (t_data *)ft_calloc(1, sizeof(t_data));
	if (!*data)
		program_error_exit("bash");
	(*data)->input = (t_input *)ft_calloc(1, sizeof(t_input));
	if (!(*data)->input)
		program_error_exit("bash");
	(*data)->oristdin = dup(STDIN_FILENO);
	(*data)->oristdout = dup(STDOUT_FILENO);
	init_env((*data)->input, envp);
}

void	init_env(t_input *input, char **envp)
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
		ft_lstadd_back(&input->envs, new);
	}
}
