#include "../../incs/minishell.h"

void link_pipe(int i, t_pipe *base, t_data *data)
{
	if (i == data->info->pipe_num)
	{
		if (dup2(base->com[i - 1].fd[0], STDIN_FILENO) == -1 || close(base->com[i - 1].fd[0]) == -1)
			error_back_readline(data, "Bad file descriptor", EBADF, 1);
	}
	else if (i == 0)
	{
		if (close(base->com[i].fd[0]) == -1 || dup2(base->com[i].fd[1], STDOUT_FILENO) == -1 || close(base->com[i].fd[1]) == -1)
			error_back_readline(data, "Bad file descriptor", EBADF, 1);
	}
	else
	{
		if (close(base->com[i].fd[0]) == -1 || dup2(base->com[i - 1].fd[0], STDIN_FILENO) == -1 || dup2(base->com[i].fd[1], STDOUT_FILENO) == -1)
			error_back_readline(data, "Bad file descriptor", EBADF, 1);
	}
}

// 정상 종료 확인해주고 수정;
void wait_child_processes(t_data *data)
{
	int i;
	int status;

	i = 0;
	while (i < data->info->pipe_num + 1)
	{
		waitpid(-1, &status, 0);

		i++;
	}
	if (WIFSIGNALED(status)) // signal 에 의해 종료가 되었는지 아닌지 확인
	{
		data->error_code = WTERMSIG(status); // 시그널로 종료시 시그널 번호를 저장 예 ctrl +c경우 2 번
		ft_putendl_fd("", STDERR_FILENO);	 // 빈문자열 출력을 위한 ctrl+c 이런거 눌렀을때 바로 새줄
	}
}
