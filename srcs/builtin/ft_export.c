/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 11:50:55 by kichlee           #+#    #+#             */
/*   Updated: 2023/08/14 22:13:38 by eunwolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	ft_export(t_data *data);
void	update_env_export(t_data *data, char *key, char *value);

void	ft_export(t_data *data)
{
	int		arg_cnt;
	t_list	*tmp;
	int		i;

	tmp = data->tokens;
	arg_cnt = 0;
	while (tmp)
	{
		if(tmp->token->blank == 1)
			++arg_cnt;
		tmp = tmp->next;
	}
	if (arg_cnt == 0)
		print_export_order(data);
	i = 0;
	tmp = data->tokens->next;
	while (arg_cnt--)
	{
		if (check_equal(tmp->token->str) == TRUE)
		{
			if (tmp->token->str[ft_strlen(tmp->token->str) - 1] == '=')
			{
				if (!tmp->next)
					check_env(data, tmp->token->str, NULL);
				else
				{
					check_env(data, tmp->token->str, tmp->next->token->str);
					tmp = tmp->next->next;
				}
			}
			else
			{
				while (tmp->token->str[i] != '=')
					i++;
				i++;
				char *tmp1 = (char *)ft_calloc(i, sizeof(char));
				ft_memmove(tmp1, tmp->token->str, i);
				char *tmp2 = (char *)ft_calloc(ft_strlen(&tmp->token->str[i]), sizeof(char));
				ft_memmove(tmp2, &tmp->token->str[i], ft_strlen(&tmp->token->str[i]));
				check_env(data, tmp1, tmp2);
				tmp = tmp->next;
			}
		}
		else
		{
			check_env(data, tmp->token->str, NULL);
			tmp = tmp->next;
		}
	}
	
}

// int	ft_isalpha_str(char *str)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i])
// 	{
// 		if (!((ft_isalnum(str[i]) || check_underbar(str[i]))))
// 			return (0);
// 		++i;
// 	}
// 	return (1);
// }

void	update_env_export(t_data *data, char *key, char *value)
{
	int		plus;
	char	*tmp;
	t_list	*search_list;

	plus = check_plus(key);
	if (plus == TRUE)
	{
		int i = 0;
		while (key[i] != '+')
			i++;
		tmp = ft_strdup("");
		tmp = ft_strncat(tmp, key, i);
		search_list = env_search(data, tmp, FALSE);
	}
	else if(check_equal(key) == TRUE)
	{
		tmp = ft_strdup("");
		tmp = ft_strncat(tmp, key, ft_strlen(key) - 1);
		search_list = env_search(data, tmp, FALSE);
	}
	else
	{
		tmp = ft_strdup(key);
		search_list = env_search(data, tmp, FALSE);
	}
	if(plus == FALSE)
	{
		if(check_equal(key) == FALSE)
		{
			if (search_list)
				return ;
			ft_add_env_front(data, key, value);
		}
		else
		{
			if (search_list)
			{
				free(search_list->env);
				if (value)
					search_list->env = ft_strjoin(key, value);
				else
					search_list->env = ft_strdup(key);
			}
			else
				ft_add_env_front(data, key, value);
		}
	}
	else
	{
		if(search_list)
			search_list->env = ft_strjoin(search_list->env, value);
		else
		{
			tmp = ft_strncat(tmp, "=", 1);
			ft_add_env_front(data, tmp, value);
		}
	}
	free(tmp);
}
