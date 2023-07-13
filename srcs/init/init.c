/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 11:06:52 by eunwolee          #+#    #+#             */
/*   Updated: 2023/07/14 08:45:25 by eunwolee         ###   ########.fr       */
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
		error_exit("bash");
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
			error_exit("bash");
		new->env = ft_strdup(envp[i]);
		if (!new->env)
			error_exit("bash");
		ft_lstadd_back(&data->envs, new);
	}
}
