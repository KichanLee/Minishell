/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_update_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kichlee <kichlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 00:37:38 by eunwolee          #+#    #+#             */
/*   Updated: 2023/08/15 21:44:03 by kichlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void		ft_update_env_cd(t_data *data, char *key, char *value);
void		ft_update_env_export(t_data *data, char *key, char *value);
static char	*get_tmp_key(char *key, t_bool plus);
static void	is_not_plus(t_data *data, \
							char *key, char *value, t_list *search_list);
static void	is_plus(t_data *data, char **tmp, char *value, t_list *search_list);

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

void	ft_update_env_export(t_data *data, char *key, char *value)
{
	int		plus;
	char	*tmp;
	t_list	*search_list;

	plus = check_plus(key);
	tmp = get_tmp_key(key, plus);
	search_list = env_search(data, tmp, FALSE);
	if (plus == FALSE)
	{
		is_not_plus(data, key, value, search_list);
		free(tmp);
	}
	else
	{
		is_plus(data, &tmp, value, search_list);
		free(key);
	}
}

static char	*get_tmp_key(char *key, t_bool plus)
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
	}
	else if (check_equal(key) == TRUE)
		tmp = ft_strncat(tmp, key, ft_strlen(key) - 1);
	else
		tmp = ft_strncat(tmp, key, ft_strlen(key));
	return (tmp);
}

static void	is_not_plus(t_data *data, \
							char *key, char *value, t_list *search_list)
{
	if (check_equal(key) == FALSE)
	{
		if (search_list)
		{
			free(key);
			free(value);
		}
		else
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
	if (search_list)
	{
		search_list->env = \
			ft_strncat(search_list->env, value, ft_strlen(value));
		free(value);
		free(*tmp);
	}
	else
	{
		*tmp = ft_strncat(*tmp, "=", 1);
		ft_add_env_front(data, *tmp, value);
	}

}