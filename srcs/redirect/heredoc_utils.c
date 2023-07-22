/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 10:08:39 by eunwolee          #+#    #+#             */
/*   Updated: 2023/07/22 15:30:02 by eunwolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	make_heredoc(t_data *data, t_leaf *heredoc);
char	*make_filename(void);
void	make_unique_num(char *str, int num);
void	read_heredoc(t_data *data, char *content, int fd);

void	make_heredoc(t_data *data, t_leaf *heredoc)
{
	char	*name;

	// herdoc_signal();
	name = make_filename();
	data->cmd[data->cmd_idx].infile_fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	// if (data->cmd[data->cmd_idx].infile_fd < 0) //open 실패 시 에러처리 해야함
	read_heredoc(data, heredoc->left_child->token->str, data->cmd[data->cmd_idx].infile_fd);
}

// 유니크한 파일명 생성
char	*make_filename(void)
{
	char *str;
	int exist;
	int i;

	str = ft_strdup("/tmp/here_doc000");
	i = 0;
	exist = 0;
	while(!exist)
	{
		make_unique_num(str,i++); // doc000 doc100 doc 200 순으로접근 유효성검사
		exist = access(str,F_OK); //access 가 가능하면 1리턴해줘서 while문 탈출 .
        if (!exist)
            unlink(str);
	}
    return (str);
}

void	make_unique_num(char *str, int num)
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

void	read_heredoc(t_data *data, char *content, int fd)
{
	char	*str;
	data->input->env_array = env_to_array(data->input); //환경변수 가져오기 추후에 필요할 수있음 

	while (TRUE)
	{
		str = readline ("> ");
		if (!str || !ft_strncmp (content, str, ft_strlen(str) + 1))
		{
			free (str);
			close (fd);
			return ;
		}
		// str = heredoc_parser(str, data->env_array);   heredoc $pwd 
		if (str)
			write(fd, str, ft_strlen(str));
		write (fd, "\n", 1);
		free(str);
	}
}
