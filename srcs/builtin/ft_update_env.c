/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_update_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 00:37:38 by eunwolee          #+#    #+#             */
/*   Updated: 2023/08/15 13:54:37 by eunwolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void		ft_update_env_cd(t_data *data, char *key, char *value);
void		ft_update_env_export(t_data *data, char *key, char *value);
static char	*get_tmp_key(t_data *data, char *key, t_bool plus, t_list **search_list);
static void	is_not_plus(t_data *data, char *key, char *value, t_list *search_list);
static void	is_plus(t_data *data, char **tmp, char *value, t_list *search_list);

void	ft_update_env_cd(t_data *data, char *key, char *value)
{
	t_list	*tmp;
	char	*key_equal;

	tmp = env_search(data, key,TRUE);
	if (!tmp)
		ft_add_env_front(data, key, value);
	else
	{
		free(tmp->env);
		key_equal = ft_strdup(key);
		key_equal = ft_strncat(key_equal, "=", 1);
		tmp->env = ft_strjoin(key_equal, value);
	}
}

void	ft_update_env_export(t_data *data, char *key, char *value)
{
	int		plus;
	char	*tmp;
	t_list	*search_list;

	plus = check_plus(key);
	tmp = get_tmp_key(data, key, plus, &search_list);
	if(plus == FALSE)
		is_not_plus(data, key, value, search_list);
	else
		is_plus(data, &tmp, value, search_list);
	free(tmp);
}

static char	*get_tmp_key(t_data *data, char *key, t_bool plus, t_list **search_list)
{
	int		i;
	char	*tmp;
	
	tmp = ft_strdup("");
	if (plus == TRUE)
	{
		i = 0;
		while (key[i] != '+')
			i++;
		tmp = ft_strncat(tmp, key, i);
		*search_list = env_search(data, tmp, FALSE);
	}
	else if(check_equal(key) == TRUE)
	{
		tmp = ft_strncat(tmp, key, ft_strlen(key) - 1);
		*search_list = env_search(data, tmp, FALSE);
	}
	else
	{
		tmp = ft_strncat(tmp, key, ft_strlen(key));
		*search_list = env_search(data, tmp, FALSE);
	}
	return (tmp);
}

static void	is_not_plus(t_data *data, char *key, char *value, t_list *search_list)
{
	if(check_equal(key) == FALSE)
	{
		if (search_list)
		{
			free(key);
			free(value);
			return ;
		}
		ft_add_env_front(data, key, value);
	}
	else
	{
		if (search_list)
		{
			free(search_list->env);
			if (value)
			{
				search_list->env = ft_strncat(key, value, ft_strlen(value));
				free(value);
			}
			else
				search_list->env = key;
		}
		else
			ft_add_env_front(data, key, value);
	}
}

static void	is_plus(t_data *data, char **tmp, char *value, t_list *search_list)
{
	if(search_list)
		search_list->env = ft_strjoin(search_list->env, value);
	else
	{
		*tmp = ft_strncat(*tmp, "=", 1);
		ft_add_env_front(data, *tmp, value);
	}
}
