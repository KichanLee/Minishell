/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 10:24:15 by eunwolee          #+#    #+#             */
/*   Updated: 2023/08/17 21:25:58 by eunwolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# define BUF_SIZE 1024

int	g_error_code;

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
	T_SINGLE,
	T_DOUBLE
}t_type;

typedef struct s_token
{
	int		type;
	int		redirect_type;
	char	*str;
	t_bool	blank;
	int		quote;
}t_token;

typedef struct s_list
{
	struct s_list	*pre;
	struct s_list	*next;
	t_token			*token;
	char			*env;
	int				equal_flag;
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
}t_pid;

typedef struct s_pipe
{
	t_pid	*com;
	char	**cmd_path;
	char	*command;
	char	**cmd_abs;
}t_pipe;

typedef struct s_info
{
	int			index;
	int			heredoc_flag;
	char		**heredoc_file;
	int			oristdin;
	int			oristdout;
	int			pipe_num;
	int			parent;
	int			pipe_index;
}t_info;

typedef struct s_data
{
	char		*input;
	t_list		*tokens;
	t_list		*envs;
	char		**env_array;
	t_leaf		*root;
	t_pipe		*pipe;
	t_info		*info;
	char		*abs_home;
}t_data;

#endif