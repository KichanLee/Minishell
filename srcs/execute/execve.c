#include "../../incs/minishell.h"


void	do_cmd(t_data *data)
{
	int builtnum;

	builtnum = check_bulitin_func(data->root->left_child->right_child->token->str);
	if (data->root->left_child->left_child != NULL)
		check_redirect (data->root,data); // redirect가 있는거는 먼저실행 
	if (data->root->left_child->right_child== NULL) //커맨드가 없을때  종료하기
		exit(0);
	if (builtnum != 0)
	{
		exec_bulitin(builtnum,data,data->root);
		exit(0); // 실행 후 종료돼야함
	}
	else
		exec_fork(data);
}

void	execute(t_data *data)
{
	count_pipe(data);
	heredoc_flag(data->root,data); //heredoc 이 있는 지판별해준다 
	data->info->heredoc_file= (char **)ft_calloc(data->info->heredoc_flag+1,sizeof(char *));
	if (!data->info->heredoc_file) // 파이프 기준으로 <<a <<b | 여러개 생성할 수있음덮어씌우는개념
		program_error_exit("bash");
	if (!data->info->pipe_num && !data->info->heredoc_flag)//단일 커맨들일때 히어독도 x
		if(check_bulitin(data) == TRUE) // bulitin 일때는 바로 실행하고 종료 아닌경우에는 sigle command frok 해야함
			return ;
	if(data->info->heredoc_flag) // heredoc 일 경우에는 무조건 fork 를 해줘야함 
	{ // 시그널 함수  때문인거같음 ctrl +d 눌렀을때 종료가되면안되는데 포크안햇을시 종료가됨 
		if (fork_heredoc (data))
		{
			// free(data);
			return ;
		}
	}
	execute_cmd(data,0); //그 외일경우 실행해 주기
	// free(data);
}

void exec_fork(t_data *data) // 이제경로 찾고 하던 대로해주면됨 
{
	t_pipe *base = data->pipe;
	if(!data->root->left_child->right_child)
		return ;
    data->env_array = env_to_array(data);
    abs_path(data);
	base->command = set_path(data ,data->root->left_child->right_child);
	if (!base->command)
		program_error_exit("bash");
	execve(base->command, base->cmd_path, data->env_array);
	// if (execve(base->command, base->cmd_path, data->env_array) == -1)
	// 	exit(1);
}

void	execute_cmd(t_data *data,int flag) // flag 는 자식이랑 부모 차이를 두기위해서 주는거임 
{ // 부모에서 exit 하면 return  자식에서 하면 exit
	int	i;

	i = data->info->pipe_index;
    t_pipe *base = data->pipe;
    t_leaf *head = data->root;

	while (i < data->info->pipe_num + 1)
	{
		signal (SIGINT, SIG_IGN);
		if (i < data->info->pipe_num)
			if (pipe(base->com[i].fd) < 0)
				error_back_readline(data,"bash",EPIPE,1);
		base->com[i].pid = fork();
		if (base->com[i].pid == -1)
		{
			if (flag)
				program_error_exit("bash"); // 자식일때는 exit ;
			else
				error_back_readline(data,"bash",ENOMEM ,1);
		}
		if (base->com[i].pid == 0)
		{
			signal (SIGINT, child_handler); 
			data->info->parent =1;
			if (data->info->pipe_num !=0)
				link_pipe(i, base,data);
            do_cmd(data);
		}
        else
            data->root = data->root->right_child; // pipepe 순회하기 root 바꿔주기
		if (data->info->pipe_num)
			close_pipe(i, base,data);
		signal(SIGQUIT, SIG_IGN);
		i++;
	}
	data->root = head; // root 는 원래 root 로 다시 돌려주기 
	wait_child_processes(data);
	
	// free_cmd(base);
}