/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 10:32:09 by eunwolee          #+#    #+#             */
/*   Updated: 2023/08/15 00:38:27 by eunwolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "struct.h"

void	env_print(t_data *data);
t_list	*env_search(t_data *data, char *key, t_bool flag);
t_bool	env_remove(t_data *data, char *key);
char	**env_to_array(t_data *data);

t_list	*ft_lstnew(void);
void	ft_lstadd_back(t_list **lst, t_list *new);
t_list	*ft_lstlast(t_list *lst);
int		ft_lstsize(t_list *lst);
void	ft_lstdelone(t_list *lst);
void	ft_lstclear(t_list **lst);

t_leaf	*tree_create_leaf(t_leaf *parent, int leaf_type);
t_bool	tree_add_left(t_leaf *parent, t_token *new_token, int leaf_type);
t_bool	tree_add_right(t_leaf *parent, t_token *new_token, int leaf_type);
void	tree_clear(t_leaf *leaf);

t_bool	error_back_readline(t_data *data, char *str, int error_code, int flag);
void	program_error_exit(char *str);
void	input_free(t_data *data);
void	data_free(t_data *data);
void	init_base(int ac);

/*temp.c 임시 함수*/
void	tree_print(t_leaf *leaf);
void	print_token(t_data *data);
void	env_array_print(t_data *data);
void	check_leak(void);

#endif