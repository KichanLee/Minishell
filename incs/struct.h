/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 10:24:15 by eunwolee          #+#    #+#             */
/*   Updated: 2023/07/22 13:25:48 by eunwolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include <sys/types.h>

# define CHILD 0
# define BUF_SIZE 1024

typedef enum e_bool
{
	FALSE,
	TRUE
}t_bool;

typedef enum e_type
{
	T_PIPE,
	T_WORD,
	T_CMD,
	T_ARG,
	T_REDIRECT,
	T_INPUT,
	T_OUTPUT,
	T_HEREDOC,
	T_APPEND,
}t_type;

typedef struct s_token
{
	int		type;
	int		redirect_type;
	char	*str;
}	t_token;

//tokens와 envs에서 통용되는 리스트 구조체
typedef struct s_list
{
	struct s_list	*pre;
	struct s_list	*next;
	t_token			*token;
	char			*env;
}t_list;

typedef struct s_leaf
{
	struct s_leaf	*parent;
	struct s_leaf	*left_child;
	struct s_leaf	*right_child;
	int				leaf_type;
	t_token			*token;
	t_bool			exist;
}t_leaf;

typedef struct s_cmd
{
	pid_t	pid;
	int		fd[2];
	char	**cmd_path;//명령어 +옵션 
	char	*command;
	char	**cmd_abs; // 절대경로 
	int		infile_fd;
	int		outfile_fd;
}	t_cmd;

typedef struct s_input
{
	char		*line;
	t_list		*tokens;
	t_list		*envs;
	char		**env_array;
	t_leaf		*root;
	int			error_code;
	int 		pipe_num; // fork 를 해주기위해서 갯수가 필요함
}	t_input;

typedef struct s_data
{
	// 항상 기준은 파이프  한커맨드라는건 파이프 기준으로 <<a <<b <<c 로들어올수가있음
	t_cmd		*cmd;
	int			cmd_idx;
	int			oristdin; // 이놈은 redirection이 나오면 fd 가변경 되는데 안돌려주면 계속 그 fd 를 사용 
	int			oristdout; // 같은이유 
	int			parent;
	t_input		*input;
}	t_data;

#endif