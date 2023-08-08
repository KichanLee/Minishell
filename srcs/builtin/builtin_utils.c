/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 13:20:41 by eunwolee          #+#    #+#             */
/*   Updated: 2023/08/06 14:35:21 by eunwolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	count_args(char **args)
{
    int count;
    
    count = 0;
    while (*args != NULL)
    {
        count++;
        args++;
    }
    return (count);
}

char **join_cmd(t_leaf * com_leaf)
{
    int     i;
    char    **str;
	t_leaf  *temp;
	t_leaf  *leaf;
	
    i = 1;
    temp = com_leaf;
    leaf = com_leaf;
	while(temp && temp->right_child)
	{
		temp = temp->right_child;
		i++;
	}
	str = (char **)ft_calloc(i + 1, sizeof(char *));
	if (!str)
		return (NULL);
	str[0] = leaf->token->str;
	i = 1;
	while (leaf)
    {
        if (leaf->right_child)
        {
            str[i] = leaf->right_child->token->str;
            leaf = leaf->right_child;
            i++;
        }
        else
            break ;
    }
	return (str);
}

t_list *create_env_node(char *key, char *value)
{
    printf("\ncreate env_node start!\n");
    t_list *new_node = (t_list *)malloc(sizeof(t_list));
    char *key_equal;

    if (!new_node)
        return NULL;

    new_node->pre = NULL;
    new_node->next = NULL;
    new_node->token = (t_token *)malloc(sizeof(t_token));
    if (!new_node->token)
    {
        free(new_node);
        return NULL;
    }
    new_node->token->type = T_CMD;      // 환경 변수는 T_CMD로 설정
    new_node->token->redirect_type = 0; // 환경 변수의 리다이렉션 타입은 0으로 설정
    new_node->token->str = key;         // key 값을 환경 변수 노드의 token의 str에 할당
    key_equal = (char *)ft_calloc(sizeof(char), ft_strlen(key) + 2);
    key_equal = ft_strdup(key);
    key_equal[ft_strlen(key)] = '=';
    key_equal[ft_strlen(key) + 1] = '\0';
    printf("\n===========keyequl=======%s\n", key_equal);
    new_node->env = ft_strjoin(key_equal, value);

    return new_node;
}

void add_env_back(t_data *head, char *key, char *value)
{
    if (head->envs == NULL)
    {
        printf("\nenv dose not exit!\n");
        head->envs = create_env_node(key, value);
    }
    else
    {
        printf("\nenv exit!\n");
        ft_lstadd_back(&(head->envs), create_env_node(key, value));
    }
}

void update_env(t_data *data, char *key, char *value)
{
    t_list *tmp;
    char *key_equal;
    tmp = env_search(data, key);
    if (!tmp)
        add_env_back(data, key, value);
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
