/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 11:50:55 by kichlee           #+#    #+#             */
/*   Updated: 2023/08/15 00:37:50 by eunwolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void		ft_export(t_data *data);
static int	cnt_args(t_list *tmp);
static void separated_token(t_data *data, t_list **tmp);
static void combined_token(t_data *data, t_list **tmp);

void	ft_export(t_data *data)
{
	int		args;
	t_list	*tmp;

	args = cnt_args(data->tokens);
	if (args == 0)
		print_export_order(data);
	tmp = data->tokens->next;
	while (args--)
	{
		if (check_equal(tmp->token->str) == TRUE)
		{
			if (tmp->token->str[ft_strlen(tmp->token->str) - 1] == '=')
				separated_token(data, &tmp);
			else
				combined_token(data, &tmp);
		}
		else
		{
			check_env(data, tmp->token->str, NULL);
			tmp = tmp->next;
		}
	}
}

static int	cnt_args(t_list *tmp)
{
	int	args;

	args = 0;
	while (tmp)
	{
		if(tmp->token->blank == 1)
			++args;
		tmp = tmp->next;
	}
	return (args);
}

static void separated_token(t_data *data, t_list **tmp)
{
	if (!(*tmp)->next)
		check_env(data, (*tmp)->token->str, NULL);
	else
	{
		check_env(data, (*tmp)->token->str, (*tmp)->next->token->str);
		*tmp = (*tmp)->next->next;
	}
}

static void combined_token(t_data *data, t_list **tmp)
{
	int		i;
	char	*str1;
	char	*str2;

	i = 0;
	while ((*tmp)->token->str[i] != '=')
		i++;
	i++;
	str1 = (char *)ft_calloc(i, sizeof(char));
	ft_memmove(str1, (*tmp)->token->str, i);
	str2 = (char *)ft_calloc(ft_strlen(&(*tmp)->token->str[i]), sizeof(char));
	ft_memmove(str2, &(*tmp)->token->str[i], ft_strlen(&(*tmp)->token->str[i]));
	check_env(data, str1, str2);
	*tmp = (*tmp)->next;
}
