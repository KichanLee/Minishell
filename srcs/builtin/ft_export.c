/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 11:50:55 by kichlee           #+#    #+#             */
/*   Updated: 2023/08/15 13:58:41 by eunwolee         ###   ########.fr       */
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
	t_list	*cur;

	args = cnt_args(data->tokens);
	if (args == 0)
		print_export_order(data);
	cur = data->tokens->next;
	while (args--)
	{
		if (check_equal(cur->token->str) == TRUE)
		{
			if (cur->token->str[ft_strlen(cur->token->str) - 1] == '=')
				separated_token(data, &cur);
			else
				combined_token(data, &cur);
		}
		else
		{
			check_env(data, ft_strdup(cur->token->str), NULL);
			cur = cur->next;
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

static void separated_token(t_data *data, t_list **cur)
{
	char	*tmp;
	
	if (!(*cur)->next)
		check_env(data, ft_strdup((*cur)->token->str), NULL);
	else
	{
		tmp = ft_strdup((*cur)->next->token->str);
		if (!tmp)
			program_error_exit("bash");
		check_env(data, ft_strdup((*cur)->token->str), tmp);
		*cur = (*cur)->next->next;
	} 
}

static void combined_token(t_data *data, t_list **cur)
{
	int		equal_len;
	int		value_len;
	char	*str1;
	char	*str2;

	equal_len = 0;
	while ((*cur)->token->str[equal_len] != '=')
		equal_len++;
	equal_len++;
	value_len = ft_strlen(&(*cur)->token->str[equal_len]);
	str1 = ft_substr((*cur)->token->str, 0, equal_len);
	str2 = ft_substr((*cur)->token->str, equal_len, value_len);
	if (!str1 || !str2)
		program_error_exit("bash");
	check_env(data, str1, str2);
	*cur = (*cur)->next;
}
