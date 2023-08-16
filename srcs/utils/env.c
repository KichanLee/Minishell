/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 06:38:21 by eunwolee          #+#    #+#             */
/*   Updated: 2023/08/17 01:03:09 by eunwolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	env_print(t_data *data);
t_list	*env_search(t_data *data, char *key, t_bool flag);
t_bool	env_remove(t_data *data, char *key);
char	**env_to_array(t_data *data);

void	env_print(t_data *data)
{
	t_list	*cur;

	cur = data->envs;
	while (cur)
	{
		if (check_equal(cur->env) == TRUE)
			printf("%s\n", cur->env);
		cur = cur->next;
	}
}

t_list	*env_search(t_data *data, char *key, t_bool flag)
{
	char	*env;
	t_list	*cur;
	int		len;

	env = ft_strdup(key);
	if (flag == TRUE)
		env = ft_strncat(env, "=", 1);
	cur = data->envs;
	len = ft_strlen(env);
	while (cur)
	{
		if (!ft_strncmp(cur->env, env, len))
		{
			if (flag == FALSE \
				&& (cur->env[len] != '\0' && cur->env[len] != '='))
				break ;
			free(env);
			return (cur);
		}
		cur = cur->next;
	}
	free(env);
	return (NULL);
}

t_bool	env_remove(t_data *data, char *key)
{
	t_list	*env;

	env = env_search(data, key, TRUE);
	if (!env)
	{
		env = env_search(data, key, FALSE);
		if (!env)
			return (FALSE);
	}
	if (!env->pre)
		data->envs = env->next;
	else
		env->pre->next = env->next;
	ft_lstdelone(env);
	return (TRUE);
}

char	**env_to_array(t_data *data)
{
	t_list	*cur;
	char	**array;
	int		i;
	int		cnt;

	cnt = ft_lstsize(data->envs);
	array = (char **)ft_calloc(cnt, sizeof(char *));
	if (!array)
		return (NULL);
	i = -1;
	cur = data->envs;
	while (++i < cnt)
	{
		array[i] = cur->env;
		if (!array[i])
		{
			while (i--)
				free(array[i]);
			return (NULL);
		}
		cur = cur->next;
	}
	return (array);
}
