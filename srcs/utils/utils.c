/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 19:40:44 by eunwolee          #+#    #+#             */
/*   Updated: 2023/07/21 21:48:40 by eunwolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

t_bool	error_back_readline(t_input *input, char *str, int error_code);
void	program_error_exit(char *str);
void	free_input(t_input *input);
void	free_data(t_data *data);

//input 관련 에러일 때 사용
t_bool	error_back_readline(t_input *input, char *str, int error_code)
{
	printf("%s\n", str);
	input->error_code = error_code;
	return (FALSE);
}

//system 관련 에러일 때
void	program_error_exit(char *str)
{
	perror(str);
	exit(errno);
}

//input 한번 끝났을 때 사용
void	free_input(t_input *input)
{
	ft_lstclear(&input->tokens);
	input->tokens = NULL;
	free(input->line);
	input->line = NULL;
	tree_clear(input->root);	
	input->root = NULL;
}

//정상종료 시 사용
void	free_data(t_data *data)
{
	ft_lstclear(&data->input->envs);
	free(data->input);
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
