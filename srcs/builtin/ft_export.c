/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 16:25:07 by kichlee           #+#    #+#             */
/*   Updated: 2023/08/12 20:46:31 by eunwolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

static void	check_env(t_data *data, char **cmd, int arg_cnt);
static void	print_export_order(t_data *data);

void	ft_export(t_data *data, t_leaf *cur_root)
{
	char	**cmd;
	int		arg_cnt;

	cmd = join_cmd(cur_root->left_child->right_child);
	arg_cnt = count_args(cmd);
	if (arg_cnt == 1)
		print_export_order(data);
	else
		check_env(data, cmd, arg_cnt);
}

static void	check_env(t_data *data, char **cmd, int arg_cnt)
{
	int		i;
	char	**tmp;

	i = 0;
	while (i < arg_cnt)
	{
		if (!ft_isalpha(cmd[1][0]) && \
		!check_underbar(cmd[1][0]) && !check_name(cmd[i]))
			data->error_code = 1;
		else if (!ft_strchr(cmd[i], '='))
		{
			++i;
			continue ;
		}
		else
		{
			tmp = ft_split(cmd[i], '=');
			update_env(data, tmp[0], tmp[1]);
			free(tmp);
		}
		++i;
	}
}

static void	print_export_order(t_data *data)
{
	int		i;
	int		lst_size;
	char	**order_set;
	char	**order_copy;
	t_list	*cur;

	i = 0;
	lst_size = ft_lstsize(data->envs);
	cur = data->envs;
	order_copy = (char **)ft_calloc(sizeof(char *), lst_size + 1);
	while (cur)
	{
		order_copy[i] = ft_strdup(cur->env);
		cur = cur->next;
		++i;
	}
	order_set = sort_bubble(order_copy, lst_size);
	i = -1;
	while (order_set[++i])
		printf("declare -x  %s\n", order_set[i]);
}
