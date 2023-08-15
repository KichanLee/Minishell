/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 11:50:55 by kichlee           #+#    #+#             */
/*   Updated: 2023/08/15 22:43:47 by eunwolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

t_bool			ft_export(t_data *data);
static int		cnt_args(t_list *tmp);
static t_bool	start_export(t_data *data, t_list **cur);
static t_bool	separated_token(t_data *data, t_list **tmp);
static t_bool	combined_token(t_data *data, t_list **tmp);

t_bool	ft_export(t_data *data)
{
	int		args;
	t_list	*cur;

	args = cnt_args(data->tokens);
	cur = data->tokens->next;
	if (args == 0 || !cur)
	{
		print_export_order(data);
		return (TRUE);
	}
	while (args--)
		if (start_export(data, &cur) == FALSE)
			return (FALSE);
	data->env_array = env_to_array(data);
	if (!data->env_array)
		program_error_exit("bash");
	return (TRUE);
}

static int	cnt_args(t_list *tmp)
{
	int	args;

	args = 0;
	while (tmp)
	{
		if (tmp->token->blank == 1)
			++args;
		tmp = tmp->next;
	}
	return (args);
}

static t_bool	start_export(t_data *data, t_list **cur)
{
	if (check_equal((*cur)->token->str) == TRUE)
	{
		if ((*cur)->token->str[ft_strlen((*cur)->token->str) - 1] == '=')
		{
			if (separated_token(data, cur) == FALSE)
				return (FALSE);
		}
		else
		{
			if (combined_token(data, cur) == FALSE)
				return (FALSE);
		}
	}
	else
	{
		if (check_env(data, ft_strdup((*cur)->token->str), NULL) == FALSE)
			return (FALSE);
		*cur = (*cur)->next;
	}
	return (TRUE);
}

static t_bool	separated_token(t_data *data, t_list **cur)
{
	char	*tmp;

	if (!(*cur)->next)
	{
		if (check_env(data, ft_strdup((*cur)->token->str), NULL) == FALSE)
			return (FALSE);
	}
	else
	{
		tmp = ft_strdup((*cur)->next->token->str);
		if (!tmp)
			program_error_exit("bash");
		if (check_env(data, ft_strdup((*cur)->token->str), tmp) == FALSE)
			return (FALSE);
		*cur = (*cur)->next->next;
	}
	return (TRUE);
}

static t_bool	combined_token(t_data *data, t_list **cur)
{
	char	*str1;
	char	*str2;

	devide_equal((*cur)->token->str, &str1, &str2, TRUE);
	if (check_env(data, str1, str2) == FALSE)
		return (FALSE);
	*cur = (*cur)->next;
	return (TRUE);
}
