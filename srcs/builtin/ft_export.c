/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 11:50:55 by kichlee           #+#    #+#             */
/*   Updated: 2023/08/17 00:41:03 by eunwolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

t_bool			ft_export(t_data *data, t_leaf *arg);
static int		cnt_args(t_leaf *tmp);
static t_bool	start_export(t_data *data, t_leaf **cur);
static t_bool	separated_token(t_data *data, t_leaf **tmp);
static t_bool	combined_token(t_data *data, t_leaf **tmp);

t_bool	ft_export(t_data *data, t_leaf *cmd)
{
	int		args_cnt;

	args_cnt = cnt_args(cmd);
	if (!cmd || args_cnt == 0)
	{
		print_export_order(data);
		return (TRUE);
	}
	cmd = cmd->right_child;
	while (args_cnt--)
		if (start_export(data, &cmd) == FALSE)
			return (FALSE);
	update_env_double_char(data);
	return (TRUE);
}

static int	cnt_args(t_leaf *tmp)
{
	int	args;

	args = 0;
	while (tmp)
	{
		if (tmp->token->blank == 1)
			++args;
		tmp = tmp->right_child;
	}
	return (args);
}

static t_bool	start_export(t_data *data, t_leaf **cur)
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
		*cur = (*cur)->right_child;
	}
	return (TRUE);
}

static t_bool	separated_token(t_data *data, t_leaf **cur)
{
	char	*tmp;

	if (!(*cur)->right_child || (*cur)->token->blank == TRUE)
	{
		if (check_env(data, ft_strdup((*cur)->token->str), NULL) == FALSE)
			return (FALSE);
		*cur = (*cur)->right_child;
	}
	else
	{
		tmp = ft_strdup((*cur)->right_child->token->str);
		if (!tmp)
			program_error_exit("bash");
		if (check_env(data, ft_strdup((*cur)->token->str), tmp) == FALSE)
			return (FALSE);
		*cur = (*cur)->right_child->right_child;
	}
	return (TRUE);
}

static t_bool	combined_token(t_data *data, t_leaf **cur)
{
	char	*str1;
	char	*str2;

	devide_equal((*cur)->token->str, &str1, &str2, TRUE);
	if (check_env(data, str1, str2) == FALSE)
		return (FALSE);
	*cur = (*cur)->right_child;
	return (TRUE);
}
