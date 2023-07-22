#include "../../incs/minishell.h"

t_bool			heredoc(t_data *data, t_leaf *cur_root);
static t_leaf	*find_heredoc(t_data *data, t_leaf *cur_leaf);
static int		 fork_heredoc(t_data *data, t_leaf *heredoc);

t_bool	heredoc(t_data *data, t_leaf *cur_root)
{
	t_leaf	*heredoc;

	heredoc = find_heredoc(data, cur_root->left_child->left_child);
	// data->cmd[i].heredoc_file = (char **)ft_calloc(data->input->pipe_num + 1, sizeof(char *));
	// if (!data->cmd[i].heredoc_file)
	// 	program_error_exit("bash");
	// if (!data->input->pipe_num && data->heredoc_flag == FALSE)//단일 커맨드고 히어독도 없으면
	// 	if(check_bulitin(data, cur_root) == TRUE) // bulitin 일때는 바로 실행하고 종료 아닌경우에는 sigle command fork 해야함
	// 		return (FALSE);


	// heredoc 일 경우에는 무조건 fork 를 해줘야함
	// 시그널 함수  때문인거같음 ctrl +d 눌렀을때 종료가되면안되는데 포크안햇을시 종료가됨 
	if (heredoc)
		if (fork_heredoc(data, heredoc))
			return (FALSE);
	return (TRUE);
}

static t_leaf	*find_heredoc(t_data *data, t_leaf *cur_leaf) 
{
	t_leaf	*heredoc;

	heredoc = NULL;
	while (cur_leaf)
	{
		if (cur_leaf->token->redirect_type == T_HEREDOC)
			heredoc = cur_leaf;
		cur_leaf = cur_leaf->left_child;
	}
	if (cur_leaf->parent->token->redirect_type != T_HEREDOC) //output이 있을 수 있으니 수정해야함
		return (NULL);
	return (heredoc);
}

static int	fork_heredoc(t_data *data, t_leaf *heredoc)
{
	int		status;

	data->cmd[data->input->pipe_num + 1].pid = fork(); //pid가 겹치지않게 가장 마지막 인덱스 부여해주기
	if (data->cmd[data->input->pipe_num + 1].pid == CHILD)
	{
		data->parent = 1;
		make_heredoc(data, heredoc);
		execute_cmd(data, CHILD); // heredoc 실행후 다시 커맨드 확인해주러가기
		exit (g_exit_status);// 전역변수 
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
