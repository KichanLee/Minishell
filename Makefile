NAME = minishell

L_DIR = Libft
L_NAME = libft.a

INCS_DIR = incs
SRCS_DIR = srcs
OBJS_DIR = objs
READ_DIR = ~/.brew/opt/readline

CC = cc
CFLAGS = -Wall -Wextra -Werror  -I $(READ_DIR)/include 
RLFLAGS = -lreadline -ltermcap

RM = rm -rf
MAKE = make

SRCS =	minishell.c \
		init/init.c \
		input/get_input.c \
		lexer/lexer.c \
		lexer/tokenizer.c \
		lexer/quote.c \
		lexer/expand.c \
		lexer/expand_check.c \
		lexer/lexer_utils.c \
		parser/syntax.c \
		parser/parser.c \
		builtin/builtin.c \
		builtin/ft_cd.c \
		builtin/ft_echo.c \
		builtin/ft_exit.c \
		builtin/ft_pwd.c \
		builtin/ft_unset.c \
		builtin/ft_export.c \
		builtin/ft_export_print.c \
		builtin/ft_export_check.c \
		builtin/ft_env.c \
		builtin/ft_atolong.c \
		builtin/ft_join_cmd.c \
		builtin/ft_cnt_args.c \
		builtin/ft_update_env_cd.c \
		builtin/ft_update_env_export.c \
		builtin/ft_add_env_front.c \
		execute/execve.c \
		execute/execve_utils.c \
		execute/child.c \
		execute/parent.c \
		execute/pipe.c \
		execute/path.c \
		execute/file.c \
		redirect/heredoc.c \
		redirect/heredoc_parser.c \
		redirect/redirect.c \
		signal/signal.c \
		utils/error.c \
		utils/env.c \
		utils/list.c \
		utils/list_clear.c \
		utils/tree.c \
		utils/free.c \
		utils/temp.c \
		Libft/ft_isalpha.c \
		Libft/ft_isalnum.c \
		Libft/ft_isdigit.c \
		Libft/ft_itoa.c \
		Libft/ft_split.c \
		Libft/ft_substr.c \
		Libft/ft_strjoin.c \
		Libft/ft_strncmp.c \
		Libft/ft_strncat.c \
		Libft/ft_strdup.c \
		Libft/ft_strlen.c \
		Libft/ft_strlcat.c \
		Libft/ft_strlcpy.c \
		Libft/ft_calloc.c \
		Libft/ft_memset.c \
		Libft/ft_putendl_fd.c \

SRCS_WITH_PATH = $(addprefix $(SRCS_DIR)/, $(SRCS))
OBJS = $(SRCS_WITH_PATH:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)

all: $(NAME)

${OBJS_DIR}/%.o: ${SRCS_DIR}/%.c | ${OBJS_DIR}
	@$(CC) $(CFLAGS) -c $^ -o $@ -I $(INCS_DIR)

${OBJS_DIR}:
	@echo "*---MINISHELL BUILD---*"
	@mkdir ${OBJS_DIR}
	@mkdir ${OBJS_DIR}/init
	@mkdir ${OBJS_DIR}/input
	@mkdir ${OBJS_DIR}/lexer
	@mkdir ${OBJS_DIR}/parser
	@mkdir ${OBJS_DIR}/utils
	@mkdir ${OBJS_DIR}/builtin
	@mkdir ${OBJS_DIR}/execute
	@mkdir ${OBJS_DIR}/redirect
	@mkdir ${OBJS_DIR}/signal
	@mkdir ${OBJS_DIR}/Libft

$(NAME): $(OBJS)
	@echo "MINISHELL DONE"
	@$(CC) $(RLFLAGS) $^ -o $@ -I $(INCS_DIR) -L $(READ_DIR)/lib

clean:
	@echo "MINISHELL CLEAN"
	@$(RM) $(OBJS_DIR)
	@$(RM) $(L_NAME)

fclean:
	@$(MAKE) clean
	@echo "MINISHELL FCLEAN"
	@$(RM) $(NAME)

re:
	@echo "*------RE_BUILD-------*"
	@$(MAKE) fclean
	@$(MAKE) all

.PHONY: all clean fclean re