/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 06:38:21 by eunwolee          #+#    #+#             */
/*   Updated: 2023/07/11 17:18:51 by eunwolee         ###   ########.fr       */
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

t_list	*env_search(t_data *data, char *key)
{
	char	*tmp;
	t_list	*cur;

	tmp = ft_strncat(key, "=", 1);
	cur = data->envs;
	while (cur)
	{
		if (!ft_strncmp(cur->env, tmp, ft_strlen(tmp)))
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
	if (env->pre)//지우려는게 첫번째 노드일때 처리
	env->pre->next = env->next;
	ft_lstdelone(env);
	return (TRUE);
}

//data->env_array에 담아서 사용, 쓰고 나서 더블포인터만 free해주면 됨
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
	while(++i < cnt)
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

//배열에 넣은 환경변수 출력용 임시 변수
void	env_array_print(t_data *data)
{
	char **array = env_to_array(data);

	for(int i=0; array[i]; i++)
		printf("%s\n", array[i]);
}
