
#include "../incs/minishell.h"

static void	check_env(t_data *data, int arg_cnt);
static void	print_export_order(t_data *data);

int		check_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if(str[i] == '=')
			return (1);
		++i;
	}
	return (0);
}

int	plus_flag(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if(str[i] == '+')
			return (i);
		i++;
	}
	return (0);
}

void shiftStringLeft(char *str) 
{
    int length = (int) ft_strlen(str);
    int i = 0;

    while (i < length - 1) 
	{
        str[i] = str[i + 1];
        i++;
    }
    str[length - 1] = '\0';
}


void	update_env_export(t_data *data)
{
	t_list	*tmp;
	// t_list	*tmp_two;
	t_list	*tmp_three;
	t_list	*search_list;
	char	**key_val_is_plus;
	char	**key_val_not_plus;
	char	*key_equal;
	int		flag;


	tmp = data->tokens;
	tmp_three = data->tokens;
	while(tmp_three)
	{
		printf("tmp->token->str %s\n", tmp_three->token->str);
		tmp_three = tmp_three->next;
	}
	// tmp_two = data->tokens;
	tmp = tmp->next;
	printf("mp->token->str %s\n", tmp->token->str);
	key_val_not_plus = ft_split(tmp->token->str, '=');

	if(key_val_not_plus[1] == NULL && tmp->next && !tmp->token->blank)
		key_val_not_plus[1] = tmp->next->token->str;
	
	printf("key_val_not_plus[0] : %s\n", key_val_not_plus[0]);
	printf("key_val_not_plus[1] : %s\n", key_val_not_plus[1]);
	key_val_is_plus = NULL;
	flag = plus_flag(key_val_not_plus[0]);

	if(!flag)
	{
		printf("flag start\n");
		printf("check_equal : %d\n",check_equal(tmp->token->str));
		printf("key_val_not_plus[0] %s\n", key_val_not_plus[0]);
		printf("key_val_not_plus[1] %s\n", key_val_not_plus[1]);

		if(!check_equal(tmp->token->str))
		{
			printf("= 이 없을때!\n");
			search_list = env_search(data, key_val_not_plus[0], FALSE);
			printf("search : %p\n", search_list);
			if (search_list)
			{
				printf("test\n");
				return ;
			}
		}
		else
		{
			printf("= 이 있을때\n");
			data->envs->equal_flag = 1;
			printf("env_search 해준 값 : %p\n", env_search(data, key_val_not_plus[0], TRUE));
			search_list = env_search(data, key_val_not_plus[0], TRUE);
		}

		if(!search_list)
		{
			printf("+ 가 없고 = 있을수도, 없을수도, 기존에 환경변수가 없는 지점\n");
			printf("tmp_two->token->blank , %d\n", tmp->token->blank);
			printf("key_val_not_plus[1]  , %s\n", key_val_not_plus[1]);

			if(tmp->token->blank || !key_val_not_plus[1])
			{
				printf("tmp if start!\n");
				add_env_front(data, key_val_not_plus[0], """");
			}
			else
			{
				printf("else if start!\n");
				key_equal = (char *)ft_calloc(sizeof(char), ft_strlen(key_val_not_plus[0]) + 2);
				key_equal = ft_memmove(key_equal, key_val_not_plus[0], ft_strlen(key_val_not_plus[0]));	
				key_equal[ft_strlen(key_val_not_plus[0])] = '=';
				key_equal[ft_strlen(key_val_not_plus[0]) + 1] = '\0';
				printf("key_equal 완성 %s\n", key_equal);
				printf("key_equal 완성 두번째 : %s\n", ft_strjoin(key_equal, key_val_not_plus[1]));
				add_env_front(data, key_val_not_plus[0], key_val_not_plus[1]);
			}
		}
		else if(search_list)
		{
			printf("+ 가 없고 = 는 있는데, 기존에 환경변수가 있는 지점\n");
			printf("first :  ifcon!\n");
			printf("key not plus [1] : %s\n", key_val_not_plus[1]);
			free(search_list->env);
			if(key_val_not_plus[1])
			{
				printf("second : ifcon!\n");
				key_equal = (char *)ft_calloc(sizeof(char), ft_strlen(key_val_not_plus[0]) + 2);
				// key_equal = (char *)ft_calloc(sizeof(char), ft_strlen(key_val_not_plus[0]) + 4);
				// key_equal[1] = '\"';
				// key_equal[ft_strlen(key_val_not_plus[0]) + 2] = '\"';
				key_equal = ft_memmove(key_equal, key_val_not_plus[0], ft_strlen(key_val_not_plus[0]));	
				key_equal[ft_strlen(key_val_not_plus[0])] = '=';
				key_equal[ft_strlen(key_val_not_plus[0]) + 1] = '\0';
				printf("key_equal 완성 %s\n", key_equal);
				printf("key_equal 완성 두번째 : %s\n", ft_strjoin(key_equal, key_val_not_plus[1]));
				search_list->env = ft_strjoin(key_equal, key_val_not_plus[1]);
			}
			else
			{
				printf("+ 가 없고 = 는 있는데, 기존에 환경변수가 없는 지점\n");
				printf("final else start!\n");
				// printf("key_equal %s\n" , key_equal);
				// printf("ft_strjoin %s\n" ,ft_strjoin(key_equal, """"));
				key_equal = (char *)ft_calloc(sizeof(char), ft_strlen(key_val_not_plus[0]) + 2);
				key_equal = ft_memmove(key_equal, key_val_not_plus[0], ft_strlen(key_val_not_plus[0]));	
				key_equal[ft_strlen(key_val_not_plus[0])] = '=';
				key_equal[ft_strlen(key_val_not_plus[0]) + 1] = '\0';
				key_val_not_plus[1] = ft_strdup("");
				search_list->env = ft_strjoin(key_equal, key_val_not_plus[1]);
			}

		}
	}
	else
	{
		key_val_is_plus = ft_split(tmp->token->str, '+');
		key_val_is_plus[0][ft_strlen(key_val_is_plus[0])] = '\0';
		shiftStringLeft(key_val_is_plus[1]);
		search_list = env_search(data, key_val_is_plus[0], TRUE);
		if(!search_list)
		{
			if(tmp->token->blank || !key_val_is_plus[1])
				add_env_front(data, key_val_is_plus[0], " ");
			else
				add_env_front(data, key_val_is_plus[0], key_val_is_plus[1]);
		}
		else
		{
			char *tmp = search_list->env;
			search_list->env = ft_strjoin(search_list->env, key_val_is_plus[1]);
			free(tmp);
		}
		
	}
}


void	ft_export(t_data *data, t_leaf *cur_root)
{
	int		arg_cnt;
	(void) cur_root;

	t_list *tmp = data->tokens;

	arg_cnt = 0;
	while(tmp)
	{
		++arg_cnt;
		tmp = tmp->next;
	}
	if (arg_cnt == 1)
		print_export_order(data);
	else
		check_env(data, arg_cnt);
}

int	ft_isalpha_str(char *str)
{
	int	i;
	
	i = 0;
	while (str[i])
	{
		if (!((ft_isalnum(str[i]) || check_underbar(str[i]))))
			return (0);
		++i;
	}
	return (1);
}


static void	check_env(t_data *data, int arg_cnt)
{
	int		i;
	t_list	*tmp;

	tmp = data->tokens;
	tmp = tmp->next;
	i = 1;

	(void) arg_cnt;

	if(!check_name(tmp->token->str))
	{
		printf("enter checkname!\n");
		printf("bash: export: `%s': not a valid identifier\n", tmp->token->str);
		data->error_code = 1;
		return ;
	}
	tmp = tmp->next;
	if(!tmp)
	{
		printf("first if condition\n");
		update_env_export(data);
	}
	else
	{
		while(i < arg_cnt)
		{
			if(!ft_isalpha_str(tmp->token->str))
			{
				printf("bash: export: `%s': not a valid identifier\n", tmp->token->str);
				data->error_code = 1;
				return ;
			}
			++i;
		}
		update_env_export(data);
	}
}

static void	print_export_order(t_data *data)
{
	int		i;
	int		lst_size;
	char	**order_set;
	char	**order_copy;
	t_list	*cur;

	i = 0;
	lst_size = ft_lstsize(data->envs);
	cur = data->envs;
	order_copy = (char **)ft_calloc(lst_size + 1, sizeof(char *));
	while (cur)
	{
		order_copy[i] = ft_strdup(cur->env);
		cur = cur->next;
		++i;
	}
	order_set = sort_bubble(order_copy, lst_size);
	i = -1;

	while (order_set[++i]) {
		char **res_split = ft_split(order_set[i], '=');
		printf("declare -x  ");
		printf("%s=", *res_split++);
		printf("\"");
		while (*res_split) 
		{
			printf("%s", *res_split);
			res_split++;
		}
			printf("\"");
			printf("\n");
		}
	}
	// while (order_set[++i])
	// 	printf("declare -x  %s\n", order_set[i]);
