/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 11:31:19 by eunwolee          #+#    #+#             */
/*   Updated: 2023/08/08 11:51:34 by eunwolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int	fork_heredoc(t_data *data)
{
	int	status;

	data->pipe->com[data->info->pipe_index].pid = fork(); //인덱스 부여해주기 pid가 겹치지않게 가장 마지막 인덱스 주기
	if (data->pipe->com[data->info->pipe_index].pid == 0)
	{
		signal(SIGINT, child_handler);
		mk_heredoc_pipe(data);
		execute_cmd(data, 1); // heredoc 실행후 다시 커맨드 확인해주러가기
		program_error_exit("bash");// 전역변수 
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		data->info->pipe_index++;
		waitpid(data->pipe->com[data->info->pipe_index].pid, &status, 0);
		if (WIFSIGNALED(status)) // signal 에 의해 종료가 되었는지 아닌지 확인
		{
			data->error_code = WTERMSIG(status); //시그널로 종료시 시그널 번호를 저장 예 ctrl +c경우 2 번 
			ft_putendl_fd("", STDERR_FILENO); // 빈문자열 출력을 위한 ctrl+c 이런거 눌렀을때 바로 새줄 
			return (1);
		}
	}
	return (1);
}

void	do_heredoc(t_leaf *leaf, t_data *data)
{
	int		fd;
	t_leaf	*temp;

	temp = leaf;
	while (temp)
	{
		if (temp->token->redirect_type == T_HEREDOC)
		{
			fd = open(data->info->heredoc_file[data->info->index], \
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
			write_str(temp->left_child->token->str, fd, data);
		}
		temp = temp ->left_child;
	}
}
