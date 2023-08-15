/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 16:16:07 by eunwolee          #+#    #+#             */
/*   Updated: 2023/08/15 22:55:06 by eunwolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void		check_redirect(t_leaf *leaf, t_data *data);
static void	do_input_redirect(t_leaf *leaf, t_data *data);
static void	do_output_redirect(t_leaf *leaf, t_data *data);

void	check_redirect(t_leaf *leaf, t_data *data)
{
	t_leaf	*temp;

	temp = leaf->left_child->left_child;
	while (temp)
	{
		if (temp->token->redirect_type == T_INPUT \
		||temp->token->redirect_type == T_HEREDOC)
			do_input_redirect(temp, data);
		else if (temp->token->redirect_type == T_OUTPUT \
		||temp->token->redirect_type == T_APPEND)
			do_output_redirect(temp, data);
		temp = temp->left_child;
	}
	if (leaf->left_child->left_child != NULL)
	{
		check_file (data->info->fd, data);
		dup2 (data->info->fd, STDIN_FILENO);
		close (data->info->fd);
	}
}

static void	do_input_redirect(t_leaf *leaf, t_data *data)
{
	t_leaf	*temp;

	temp = leaf;
	if (temp->token->redirect_type == T_HEREDOC)
	{
		data->info->fd = open (data->info->heredoc_file[data->info->index - 1], \
		O_RDONLY);
		dup2 (data->info->fd, STDIN_FILENO);
		return ;
	}
	else if (temp->token->redirect_type == T_INPUT)
		data->info->fd = open (temp->left_child->token->str, O_RDONLY);
}

static void	do_output_redirect(t_leaf *leaf, t_data *data)
{
	t_leaf	*temp;

	temp = leaf;
	if (temp->token->redirect_type == T_APPEND)
	{
		data->info->fd = open (temp->left_child->token->str, \
		O_WRONLY | O_APPEND | O_CREAT, 0644);
	}
	else if (temp->token->redirect_type == T_OUTPUT)
	{
		data->info->fd = open (temp->left_child->token->str, \
		O_WRONLY | O_TRUNC | O_CREAT, 0644);
	}
}
