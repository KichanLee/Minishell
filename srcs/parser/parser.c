/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 18:35:07 by eunwolee          #+#    #+#             */
/*   Updated: 2023/07/14 07:52:10 by eunwolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void		parser(t_data *data);
static void	link_pipe_leaf(t_leaf **cur_leaf);
static void	check_token_type(t_leaf *cur_leaf, t_list *cur_token);

void	parser(t_data *data)
{
	t_list	*cur_token;
	t_leaf	*cur_leaf;

	cur_token = data->tokens;
	data->root = tree_create_leaf(NULL, T_PIPE);
	data->root->left_child = tree_create_leaf(data->root, T_CMD);
	cur_leaf = data->root->left_child;
	while (cur_token)
	{
		while (cur_token && cur_token->token->type != T_PIPE)
		{
			check_token_type(cur_leaf, cur_token);
			cur_token = cur_token->next;
		}
		if (!cur_token)
			break ;
		if (cur_token->token->type == T_PIPE)
			link_pipe_leaf(&cur_leaf);
		cur_token = cur_token->next;
	}
}

static void	link_pipe_leaf(t_leaf **cur_leaf)
{
	*cur_leaf = (*cur_leaf)->parent;
	(*cur_leaf)->exist = TRUE;
	(*cur_leaf)->right_child = tree_create_leaf(*cur_leaf, T_PIPE);
	*cur_leaf = (*cur_leaf)->right_child;
	(*cur_leaf)->left_child = tree_create_leaf(*cur_leaf, T_CMD);
	*cur_leaf = (*cur_leaf)->left_child;
}

static void	check_token_type(t_leaf *cur_leaf, t_list *cur_token)
{
	if (cur_token->token->type == T_REDIRECT)
		tree_add_left(cur_leaf, cur_token->token, T_REDIRECT);
	else if (cur_token->token->type == T_CMD)
		tree_add_right(cur_leaf, cur_token->token, T_CMD);
	else if (cur_token->token->type == T_ARG)
	{
		if (cur_token->pre->token->type == T_REDIRECT)
			tree_add_left(cur_leaf, cur_token->token, T_ARG);
		else if (cur_token->pre->token->type == T_CMD \
			|| cur_token->pre->token->type == T_ARG)
			tree_add_right(cur_leaf, cur_token->token, T_ARG);
	}
}
