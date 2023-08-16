/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_update_env_cd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 23:24:39 by eunwolee          #+#    #+#             */
/*   Updated: 2023/08/16 15:54:47 by eunwolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	ft_update_env_cd(t_data *data, char *key, char *value);

void	ft_update_env_cd(t_data *data, char *key, char *value)
{
	t_list	*tmp;

	if (!key || !value)
		program_error_exit("bash");
	tmp = env_search(data, key, TRUE);
	if (!tmp)
		ft_add_env_front(data, key, value);
	else
	{
		free(tmp->env);
		tmp->env = ft_strdup(key);
		tmp->env = ft_strncat(tmp->env, "=", 1);
		tmp->env = ft_strncat(tmp->env, value, ft_strlen(value));
		free(key);
		free(value);
	}
}
