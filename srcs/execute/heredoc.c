#include "../../incs/minishell.h"


int	fork_heredoc(t_data *data)
{
	int		status;

	data->pipe->com[data->info->pipe_num+1].pid =fork(); //인덱스 부여해주기 pid 갚곂치지않게 가장 마지막 인덱스 주기
	if (data->pipe->com[data->info->pipe_num+1].pid == 0)
	{
		data->info->parent=1;
		mk_heredoc(data);
		execute_cmd(data,1); // heredoc 실행후 다시 커맨드 확인해주러가기
		exit (g_exit_status);// 전역변수 
	}
	else
	{
		// signal (SIGINT, SIG_IGN);
		waitpid(data->pipe->com[data->info->pipe_num+1].pid,&status,0);
		g_exit_status = WEXITSTATUS(status); // 정상종료일경우 exit코 드 추출
		if (WIFSIGNALED(status)) // signal 에 의해 종료가 되었는지 아닌지 확인
		{
			g_exit_status = WTERMSIG (status);//시그널로 종료시 시그널 번호를 저장 예 ctrl +c경우 2 번 
			ft_putendl_fd("", STDERR_FILENO); // 빈문자열 출력을 위한 ctrl+c 이런거 눌렀을때 바로 새줄 
			return (1);
		}
	}
	return (1);
}