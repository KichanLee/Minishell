/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 06:38:21 by eunwolee          #+#    #+#             */
/*   Updated: 2023/08/13 16:49:27 by eunwolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	env_print(t_data *data);
t_list	*env_search(t_data *data, char *key);
t_bool	env_remove(t_data *data, char *key);
char	**env_to_array(t_data *data);

void	env_print(t_data *data)
{
	t_list	*cur;

	cur = data->envs;
	while (cur)
	{
		printf("%s\n", cur->env);
		cur = cur->next;
	}
}

//환경변수 이름에 해당하는 노드를 반환하는 함수입니다
t_list	*env_search(t_data *data, char *key)
{
	char	*tmp;
	char	*env;
	t_list	*cur;

	tmp = ft_strdup(key);
	if (!tmp)
		program_error_exit("bash");
	env = ft_strncat(tmp, "=", 1);
	if (!env)
		program_error_exit("bash");
	cur = data->envs;
	while (cur)
	{
		if (!ft_strncmp(cur->env, env, ft_strlen(env)))
			return (cur);
		cur = cur->next;
	}
	return (NULL);
}

t_bool	env_remove(t_data *data, char *key)
{
	t_list	*env;

	env = env_search(data, key);
	if (!env)
		return (FALSE);
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
