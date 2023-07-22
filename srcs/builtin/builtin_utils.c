/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 13:20:41 by eunwolee          #+#    #+#             */
/*   Updated: 2023/07/22 13:28:22 by eunwolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	count_args(char **args)
{
    int count = 0;

    while (*args != NULL)
    {
        count++;
        args++;
    }

    return count;
}

char **join_cmd(t_leaf * com_leaf)
{
	int cnt =1;

	t_leaf *temp = com_leaf;
	t_leaf *leaf = com_leaf;
	
	while(temp && temp->right_child)
	{
		temp= temp->right_child;
		cnt++;
	}
	char **str = (char **)ft_calloc(cnt + 1, sizeof(char *));
	if(!str)
		return NULL;
	int i=1;
	str[0]= leaf->token->str;
	while(leaf)
    {
        if (leaf->right_child)
        {
            str[i] = leaf->right_child->token->str;
            leaf = leaf->right_child;
            i++;
        }
        else
            break;
    }
	return str;
}

void update_env(t_data *data, char *key, char *value)
{
    t_list *tmp;
    char *key_equal;
    tmp = env_search(data->input, key);
    if (!tmp)
    {
        add_env_back(data, key, value);
    }
    else
    {
        free(tmp->env);
        key_equal = (char *)ft_calloc(sizeof(char), ft_strlen(key) + 2);
        key_equal = ft_strdup(key);
        key_equal[ft_strlen(key)] = '=';
        key_equal[ft_strlen(key) + 1] = '\0';
        tmp->env = ft_strjoin(key_equal, value);
    }
}
