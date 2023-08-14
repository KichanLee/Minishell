/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_two.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 19:33:40 by kichlee           #+#    #+#             */
/*   Updated: 2023/08/14 17:50:41 by eunwolee         ###   ########.fr       */
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
	int	plus;
	int j;

	j = 0;
	i = 0;
	plus = 0;
	if(str[0] != '_' && ft_isalpha(str[0]) != 1)
		return (0);
	while (str[j] && str[j] != '+')
		++j;
	if(str[j] == '+')
	{
		printf("plus : %d\n", plus);
		printf("str[j - 1] : %c\n", str[j - 1]);
		printf("str[j] : %c\n", str[j]);
		if(str[j + 1] != '=')
		{
			printf("plus condition\n");
			return (0);
		}
	}
	plus = 0;
 	while (str[i] && str[i] != '=')
	{
		if(str[i] == '+')
			++plus;
		if (str[i] != '+' && str[i] != '_' && !ft_isalnum(str[i]))
		{
			return (0);
		}
		if(plus > 1)
			return (0);
		++i;
	}
	return (1);
}

void	update_env_export(t_data *data, char *key, char *value)
{
	int		flag;
	char	*tmp;
	t_list	*search_list;

	printf("key val : %s\n", key);
	flag = plus_flag(key);
	printf("flag %d\n", flag);
	if (flag == TRUE)
	{
		int i = 0;
		while (key[i] != '+')
			i++;
		tmp = ft_strdup("");
		tmp = ft_strncat(tmp, key, i);
		printf("tmp  first : %s\n", tmp);
		search_list = env_search(data, tmp, FALSE);
	}
	else if(check_equal(key) == TRUE)
	{
		tmp = ft_strdup("");
		tmp = ft_strncat(tmp, key, ft_strlen(key) - 1);
		search_list = env_search(data, tmp, FALSE);
	}
	else
	{
		tmp = ft_strdup(key);
		printf("tmp %s\n", tmp);
		search_list = env_search(data, tmp, FALSE);
	}
	if(flag == FALSE)
	{
		if(check_equal(key) == FALSE)
		{
			if (search_list)
			{
				printf("----------------------\n");
				return ;
			}
			printf("+ 가 없고 = 도 없는데, 기존에 환경변수가 없는 지점\n");
			add_env_front(data, key, value);
		}
		else
		{
			printf("+ 가 없고 = 는 있는 지점\n");
			if (search_list)
			{
				printf("search_list %s\n", search_list->env);
				free(search_list->env);
				if (value)
					search_list->env = ft_strjoin(key, value);
				else
					search_list->env = ft_strdup(key);
			}
			else
				add_env_front(data, key, value);
		}
	}
	else
	{
		if(search_list)
			search_list->env = ft_strjoin(search_list->env, value);
		else
		{
			tmp = ft_strncat(tmp, "=", 1);
			add_env_front(data, tmp, value);
		}
	}
	free(tmp);
}

//a -> a=b