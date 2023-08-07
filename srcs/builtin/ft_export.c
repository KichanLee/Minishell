/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 16:25:07 by kichan            #+#    #+#             */
/*   Updated: 2023/08/06 22:34:57 by eunwolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void        ft_export(t_data *data, t_leaf *cur_root);
static int  check_underbar(char ch);
static int  check_name(char *str);
static char **sort_bubble(char **str, int size);
static void print_export_order(t_data *data);

void ft_export(t_data *data, t_leaf *cur_root)
{
    char **cmd;
    char **tmp;
    int arg_cnt;
    int i;

    i = 1;
    cmd = join_cmd(cur_root->left_child->right_child);
    arg_cnt = count_args(cmd);
    if (arg_cnt == 1)
        print_export_order(data);
    else
    {
        while (i < arg_cnt)
        {
            printf("\nft_export while loop start!\n");
            if (!ft_isalpha(cmd[1][0]) && !check_underbar(cmd[1][0]) && !check_name(cmd[i]))
                printf("bash: export: `%s': not a valid identifier\n", cmd[i]);
            else if (!ft_strchr(cmd[i], '=')) // = 가 없는 경우
            {
                ++i;
                continue;
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
}

int check_underbar(char ch)
{
    if (ch == '_')
        return (1);
    return (0);
}

int check_name(char *str)
{
    int i;

    i = 0;
    while (str[i] && str[i] != '=')
    {
        if (str[i] != '_' && ft_isalnum(str[i]))
            return (0);
        ++i;
    }
    return (1);
}
/**
 * @brief bash 환경변수 명명 규칙
 *
 *  변수 이름은 문자 (a-z, A-Z) 또는 밑줄(_)로 시작해야 합니다.
    첫 문자 이후에는 문자, 숫자 (0-9), 또는 밑줄(_)을 포함할 수 있습니다.
    변수 이름은 대소문자를 구분합니다. 예를 들어, MY_VAR와 my_var는 서로 다른 변수로 간주됩니다.
    변수 이름에 공백이나 특수 문자 (예: !, @, #, $ 등)는 사용할 수 없습니다.
    환경 변수 이름의 길이에는 제한이 있으며, 일반적으로 많은 시스템에서는 최대 길이가 있습니다.
 *
 */
// int     split_export(char *str, t_data *data)
// {
//     int     key_len;
//     int     value_len;
//     char    *key;
//     char    *value;
//     key_len = 0;
//     value_len = 0;
//     while(str[key_len] != '=')
//         ++key_len;
//     key = (char *)ft_calloc(sizeof(char), key_len + 1);
//     if(!key)
//     {
//         perror("ft_calloc error!");
//         exit(1);
//     }
//     value_len = ft_strlen(str) - key_len;
//     value = (char *)ft_calloc(sizeof(char), value_len + 1);
//     if(!value)
//     {
//         perror("ft_calloc error!");
//         exit(1);
//     }
//     return (0);
// }

char    **sort_bubble(char **str, int size)
{
    char **res = (char **)ft_calloc(sizeof(char *), (size + 1));
    int sorted = 0;
    int i = 0;
    char *tmp;
    tmp = NULL;
    if (!res)
    {
        perror("Memory allocation error!");
        exit(1);
    }
    while (str[i])
    {
        res[i] = ft_strdup(str[i]);
        if (!res[i])
        {
            perror("Memory allocation error!");
            exit(1);
        }
        ++i;
    }
    res[i] = NULL;

    while (!sorted)
    {
        sorted = 1;
        i = 0;
        while (res[i + 1])
        {
            if (ft_strncmp(res[i], res[i + 1], ft_strlen(res[i])) > 0)
            {
                tmp = res[i];
                res[i] = res[i + 1];
                res[i + 1] = tmp;
                sorted = 0;
            }
            ++i;
        }
    }
    return res;
}

static void print_export_order(t_data *data)
{
    int i;
    int lst_size;
    char **order_set;
    char **order_copy;
    t_list *cur;

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
    int j = 0;
    while (order_set[j])
    {
        printf("%s\n", order_set[j]);
        ++j;
    }
}

