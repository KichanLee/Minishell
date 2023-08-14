	/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_three.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 11:59:34 by kichlee           #+#    #+#             */
/*   Updated: 2023/08/14 15:57:23 by eunwolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

char	**check_sort(char **res, int sorted)
{
	int		i;
	char	*tmp;

	i = 0;
	while (!sorted)
	{
		sorted = 1;
		i = -1;
		while (res[++i + 1])
		{
			if (ft_strncmp(res[i], res[i + 1], ft_strlen(res[i])) > 0)
			{
				tmp = res[i];
				res[i] = res[i + 1];
				res[i + 1] = tmp;
				sorted = 0;
			}
		}
	}
	return (res);
}

char	**sort_bubble(char **str, int size)
{
	char	**res;
	int		sorted;
	int		i;

	sorted = 0;
	i = -1;
	res = (char **)ft_calloc(sizeof(char *), (size + 1));
	if (!res)
		program_error_exit("Memory allocation error!");
	while (str[++i])
	{
		res[i] = ft_strdup(str[i]);
		if (!res[i])
			program_error_exit("Memory allocation error!");
	}
	res[i] = NULL;
	res = check_sort(res, sorted);
	return (res);
}

static	void	print_export_quote(char **order_set)
{
	int		i;
	char	**res_split;

	i = 0;
	while (order_set[i])
	{
		t_bool flag = check_equal(order_set[i]);
		res_split = ft_split(order_set[i], '=');
		printf("declare -x  ");
		if (flag == TRUE)
		{
			if (!res_split[1])
				printf("%s=\"\"\n", res_split[0]);
			else
				printf("%s=\"%s\"\n", res_split[0], res_split[1]);
		}
		else
			printf("%s\n", res_split[0]);
		++i;
	}
}

void	print_export_order(t_data *data)
{
	int		i;
	int		lst_size;
	char	**order_set;
	char	**order_copy;
	t_list	*cur;

	i = 0;
	lst_size = ft_lstsize(data->envs);
	cur = data->envs;
	order_copy = (char **)ft_calloc(lst_size + 1, sizeof(char *));
	while (cur)
	{
		order_copy[i] = ft_strdup(cur->env);
		cur = cur->next;
		++i;
	}
	order_set = sort_bubble(order_copy, lst_size);
	print_export_quote(order_set);
}
