/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 10:24:15 by eunwolee          #+#    #+#             */
/*   Updated: 2023/08/12 15:57:40 by eunwolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

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
	t_bool	blank;
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

typedef struct s_pid
{
	pid_t	pid;
	int		fd[2];
}				t_pid;

typedef struct s_pipe
{
	t_pid	*com;
	
	char	**cmd_path;//명령어 +옵션 
	char	*command;
	char	**cmd_abs; // 절대경로 
}	t_pipe;

typedef struct s_info
{
	// 항상 기준은 파이프  한커맨드라는건 파이프 기준으로 <<a <<b <<c 로들어올수가있음
	int			index; //이거는 heredocfile[index] open 할때 접근 할수 있어야함
	int			heredoc_flag;// 히어독이있는지 판별해줘야함 -> 히어독은 포크로 진행되기때문에
	char		**heredoc_file; // 한 커맨드에 여러개 리다이렉션이 들어올수 있다  
	int			oristdin; // 이놈은 redirection이 나오면 fd 가변경 되는데 안돌려주면 계속 그 fd 를 사용 
	int			oristdout; // 같은이유 
	int 		pipe_num; // fork 를 해주기위해서 갯수가 필요함
	int			parent;
	int			pipe_index;
}	t_info;

typedef struct s_data
{
	char		*input;
	t_list		*tokens;
	t_list		*envs;
	char		**env_array;
	t_leaf		*root;
	t_pipe		*pipe;
	t_info		*info;
	int			error_code;
	char		*abs_home;
}	t_data;


#endif