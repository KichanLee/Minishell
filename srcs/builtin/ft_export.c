/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 11:50:55 by kichlee           #+#    #+#             */
/*   Updated: 2023/08/14 17:47:10 by eunwolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

static void	check_env(t_data *data, char *key, char *value);

int	check_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		++i;
	}
	return (0);
}

int	plus_flag(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '+')
			return (1);
		i++;
	}
	return (0);
}

void	shiftstringleft(char *str)
{
	int	length;
	int	i;

	i = 0;
	length = (int) ft_strlen(str);
	while (i < length - 1)
	{
		str[i] = str[i + 1];
		i++;
	}
	str[length - 1] = '\0';
}

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

int	ft_isalpha_str(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!((ft_isalnum(str[i]) || check_underbar(str[i]))))
			return (0);
		++i;
	}
	return (1);
}

static void	check_env(t_data *data, char *key, char *value)
{
	int	i;

	i = 1;
	printf("check %s %s\n", key, value);
	if (!check_name(key))
	{
		printf("bash: export: '%s': not a valid identifier\n", key);
		data->error_code = 1;
		return ;
	}
	update_env_export(data, key, value);
}
