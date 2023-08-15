/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 21:42:23 by eunwolee          #+#    #+#             */
/*   Updated: 2023/08/15 14:00:54 by eunwolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int		check_plus(char *str);
int		check_equal(char *str);
int		check_name(char *str);
int		check_underbar(char ch);
t_bool	check_env(t_data *data, char *key, char *value);

int	check_plus(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '+')
			return (1);
		i++;
	}
	return (0);
}

int	check_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		++i;
	}
	return (0);
}

int	check_name(char *str)
{
	int	i;
	int	j;
	int	plus;

	j = 0;
	i = 0;
	plus = 0;
	if (str[0] != '_' && ft_isalpha(str[0]) != 1)
		return (0);
	while (str[j] && str[j] != '+')
		++j;
	if (str[j] == '+')
		if (str[j + 1] != '=')
			return (0);
	plus = 0;
 	while (str[i] && str[i] != '=')
	{
		if (str[i] == '+')
			++plus;
		if ((str[i] != '+' && str[i] != '_' && !ft_isalnum(str[i])) \
			|| plus > 1)
			return (0);
		++i;
	}
	return (1);
}

int	check_underbar(char ch)
{
	if (ch == '_')
		return (1);
	return (0);
}

t_bool	check_env(t_data *data, char *key, char *value)
{
	printf("key %p, value %p\n", key, value);
	if (!key)
		program_error_exit("bash");
	if (!check_name(key))
	{
		printf("bash: export: '%s': not a valid identifier\n", key);
		data->error_code = 1;
		free(key);
		if (value)
			free(value);
		return (FALSE); //에러처리중
	}
	ft_update_env_export(data, key, value);
}
