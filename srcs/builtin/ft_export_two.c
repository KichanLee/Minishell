/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_two.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kichlee <kichlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 19:33:40 by kichlee           #+#    #+#             */
/*   Updated: 2023/08/10 22:01:54 by kichlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int	check_underbar(char ch)
{
	if (ch == '_')
		return (1);
	return (0);
}

int	check_name(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
	{
		if (str[i] != '_' && ft_isalnum(str[i]))
			return (0);
		++i;
	}
	return (1);
}

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