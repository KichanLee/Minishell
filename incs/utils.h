/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 10:32:09 by eunwolee          #+#    #+#             */
/*   Updated: 2023/07/11 17:18:56 by eunwolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//환경변수, 자료구조 및 기타 함수

#ifndef UTILS_H
# define UTILS_H

# include "struct.h"

void	env_print(t_data *data);
t_list	*env_search(t_data *data, char *key);
t_bool	env_remove(t_data *data, char *key);
char	**env_to_array(t_data *data);
void	env_array_print(t_data *data); //임시 변수

t_list	*ft_lstnew(void);
void	ft_lstadd_back(t_list **lst, t_list *new);
t_list	*ft_lstlast(t_list *lst);
int		ft_lstsize(t_list *lst);
void	ft_lstdelone(t_list *lst);
void	ft_lstclear(t_list **lst);

t_leaf	*t_create_leaf(t_token *token, t_bool exist);
t_bool	t_add_left(t_leaf *parent, t_leaf *new);
t_bool	t_add_right(t_leaf *parent, t_leaf *new);

void	error_exit(char *str);

#endif