#include "../../incs/minishell.h"

t_bool			heredoc(t_data *data, t_leaf *cur_root);
static int		fork_heredoc(t_data *data, t_leaf *cur_leaf);

//heredoc 여러개 들어올때 다 실행하긴 해야 함
t_bool	heredoc(t_data *data, t_leaf *cur_leaf)
{
	if (data->cmd[data->cmd_idx].infile_fd)
		close(data->cmd[data->cmd_idx].infile_fd); //에러처리
	if (fork_heredoc(data, cur_leaf))
		return (FALSE);
	return (TRUE);
}

static int	fork_heredoc(t_data *data, t_leaf *cur_leaf)
{
	int		status;

	data->cmd[data->input->pipe_num + 1].pid = fork(); //pid가 겹치지않게 가장 마지막 인덱스 부여해주기
	if (data->cmd[data->input->pipe_num + 1].pid == CHILD)
	{
		data->parent = 1;
		make_heredoc(data, cur_leaf);
		// exit (g_exit_status);// 전역변수 
	}
	else
	{
		// signal (SIGINT, SIG_IGN);
		waitpid(data->cmd[data->input->pipe_num + 1].pid, &status, 0);
		g_exit_status = WEXITSTATUS(status); // 정상종료일경우 exit코드 추출
		if (WIFSIGNALED(status)) // signal 에 의해 종료가 되었는지 아닌지 확인
		{
			g_exit_status = WTERMSIG (status);//시그널로 종료시 시그널 번호를 저장 예 ctrl +c경우 2 번 
			ft_putendl_fd("", STDERR_FILENO); // 빈문자열 출력을 위한 ctrl+c 이런거 눌렀을때 바로 새줄 
			return (1);
		}
	}
	return (1);
}
