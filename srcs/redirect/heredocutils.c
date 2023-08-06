#include "../../incs/minishell.h"

void	heredoc_parser(t_data *data, int fd, char *str);
char	*heredoc_expand(t_data *data, char *str, char *tmp, int *i);

void	write_str(char *content, int fd, t_data *data)
{
	char	*str;
	data->env_array=env_to_array(data); //환경변수 가져오기 추후에 필요할 수있음 

	while (1)
	{
		str = readline ("> ");
		if (!str \
			|| (!ft_strncmp (content, str,ft_strlen(content)) && \
			(ft_strlen(content) == (ft_strlen(str)))))
		{
			free (str);
			close (fd);
			return ;
		}
		heredoc_parser(data, fd, str);
	}
}

void	heredoc_parser(t_data *data, int fd, char *str)
{
	int		i;
	char	*tmp;

	i = -1;
	tmp = ft_strdup("");
	while (str[++i])
	{
		if (str[i] == '$')
			tmp = heredoc_expand(data, str, tmp, &i);
		else
			tmp = ft_strncat(tmp, &str[i], 1);
	}
	write (fd, tmp, ft_strlen(tmp));
	write (fd, "\n", 1);
	free (str);
}

char	*heredoc_expand(t_data *data, char *str, char *tmp, int *i)
{
	char	*name;
	t_list	*env;
	int		j;

	*i += 1;
	name = ft_strdup("");
	while (str[*i] != '\0' && str[*i] != ' ' && str[*i] != '\t')
	{
		name = ft_strncat(name, &str[*i], 1);
		*i += 1;
	}
	env = env_search(data, name);
	if (!env)
	{
		tmp = ft_strncat(tmp, "$", 1);
		if (!tmp)
			program_error_exit("bash");
		tmp = ft_strncat(tmp, name, ft_strlen(name));
		if (!tmp)
			program_error_exit("bash");
	}
	else
	{
		j = 0;
		while (env->env[j] != '=')
			j++;
		tmp = ft_strncat(tmp, \
			&env->env[j + 1], ft_strlen(&env->env[j + 1]));
		if (!tmp)
			program_error_exit("bash");
	}
	if (str[*i] != '\0')
		*i -= 1;
	return (tmp);
}

void mk_num(char *str, int num)
{

	int i=0;
    int j=1;
	while(i<3)
	{
		if (i ==0)
		{
			str[13+i++]= num/100 +'0';
            num %=100;
		}
		str[13+ i++] = num /(100/(j *10)) + '0'; 
        num%= (100 / (j*10));
        j*=10;
	}

}

char *mk_filename() // 파일이름 유니크줘서만들어주기 
{
	char *str;
	int exist;
	int i;

	str = ft_strdup("/tmp/here_doc000");
	i=0;
	exist=0;
	while(exist ==0)
	{
		mk_num(str,i++); // doc000 doc100 doc 200 순으로접근 유효성검사
		exist =access(str,F_OK); //access 가 가능하면 1리턴해줘서 while문 탈출 .
        if (!exist)
            unlink(str);
	}
    return (str);
}



void	do_heredoc(t_leaf *leaf,t_data *data)
{
	int			fd;
	t_leaf		*temp;
	temp = leaf;

	while(temp)
	{
		
		if(temp->token->redirect_type==T_HEREDOC)
		{
			fd = open(data->info->heredoc_file[data->info->index], O_WRONLY | O_CREAT | O_TRUNC, 0644); //임시파일오픈
			write_str(temp->left_child->token->str,fd,data); //limiter 들고가서 작성하기 
		}
		temp = temp ->left_child; //순회하기 
	}
	
}


// void mk_heredoc(t_data *data)
// {
// 	t_leaf *temp;
// 	int fd;
// 	// herdoc_signal();
// 	temp =data->root->left_child -> left_child;
// 	while(temp)
// 	{
// 		data->info->heredoc_file[data->info->index] = mk_filename(); //설명했듯이 이중 배열 
// 		if(temp->token->redirect_type == T_HEREDOC)
// 		{
// 			fd = open(data->info->heredoc_file[data->info->index], O_WRONLY | O_CREAT | O_TRUNC, 0644); //임시파일오픈
// 			write_str(temp->left_child->str,fd,data); //limiter 들고가
// 			// do_heredoc(temp,data); // 실제 here _doc 이 나왔을경우  만들러가기
// 			data->info->index++; //순회하면서 heredoc 찾기 
// 		}
// 		temp = temp ->left_child;
// 	}
// }


void mk_heredoc_pipe(t_data *data)
{
	

	// herdoc_signal();

	t_leaf *pipe = data->root;
	while(pipe)
	{
		data->info->heredoc_file[data->info->index] = mk_filename(); //설명했듯이 이중 배열 
		if(pipe->left_child->left_child && pipe->left_child->left_child->token->redirect_type == T_HEREDOC)
		{
			do_heredoc(pipe->left_child->left_child,data); // 실제 here _doc 이 나왔을경우  만들러가기
			data->info->index++; //순회하면서 heredoc 찾기 
		}
		pipe = pipe->right_child;
	}
}
