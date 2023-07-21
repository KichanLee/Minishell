#include "../../incs/minishell.h"

void	write_str(char *content, int fd, t_data *data)
{
	char	*str;
	data->env_array=env_to_array(data);//환경변수 가져오기 추후에 필요할 수있음 

	while (1)
	{
		str = readline ("> ");
		if (!str)
		{
			free(str);
			close(fd);
			return ;
		}	
		if (!ft_strncmp (content, str, ft_strlen(str) + 1))
		{
			free (str);
			close (fd);
			return ;
		}
		// str = heredoc_parser(str, data->env_array);   heredoc $pwd 
		if (str)
			write (fd, str, ft_strlen (str));
		write (fd, "\n", 1);
		free (str);
	}
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
			fd = open(data->info->heredoc_file[data->info->index], O_WRONLY | O_CREAT | O_TRUNC, 0644);//임시파일오픈
			write_str(temp->left_child->token->str,fd,data); //limiter 들고가서 작성하기 
		}
		temp = temp ->left_child; //순회하기 
	}
}


void mk_heredoc(t_data *data)
{
	t_leaf *temp;

	// herdoc_signal();
	temp =data->root;
	while(temp)
	{
		data->info->heredoc_file[data->info->index] = mk_filename(); //설명했듯이 이중 배열 
		if(temp->left_child->left_child->token->redirect_type == T_HEREDOC)
			do_heredoc(temp->left_child->left_child,data); // 실제 here _doc 이 나왔을경우  만들러가기
		data->info->index++; 
		temp= temp -> right_child;//순회하면서 heredoc 찾기 
	}
}