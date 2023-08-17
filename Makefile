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
		utils/env.c \
		utils/list.c \
		utils/list_clear.c \
		utils/tree.c \
		utils/utils.c \
		utils/temp.c \
		builtin/builtin.c \
		builtin/ft_join_cmd.c \
		builtin/ft_cnt_args.c \
		builtin/ft_update_env_cd.c \
		builtin/ft_update_env_export.c \
		builtin/ft_add_env_front.c \
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
		execute/execve.c \
		execute/execve_utils.c \
		execute/child.c \
		execute/parent.c \
		execute/pipe.c \
		execute/path.c \
		execute/file.c \
		redirect/heredoc_parser.c \
		redirect/heredoc.c \
		redirect/redirect.c \
		signal/signal.c

SRCS_WITH_PATH = $(addprefix $(SRCS_DIR)/, $(SRCS))
OBJS = $(SRCS_WITH_PATH:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)

all: $(NAME)

${OBJS_DIR}/%.o: ${SRCS_DIR}/%.c | ${OBJS_DIR}
	@$(CC) $(CFLAGS) -c $^ -o $@ -I $(INCS_DIR)
	# @$(CC) $(RLFLAGS) $^ -o $@ -I $(INCS_DIR) -L ~/.brew/opt/readline/lib -fsanitize=address -g3

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

$(NAME): $(L_NAME) $(OBJS)
	@echo "MINISHELL DONE"
	@$(CC) $(RLFLAGS) $^ -o $@ -I $(INCS_DIR) -L $(READ_DIR)/lib

$(L_NAME):
	@$(MAKE) -C $(L_DIR)
	@cp ./$(L_DIR)/$(L_NAME) .

clean:
	@echo "MINISHELL CLEAN"
	@$(MAKE) fclean -C $(L_DIR)
	@$(RM) $(OBJS_DIR)
	@$(RM) $(L_NAME)

fclean:
	@$(MAKE) fclean -C $(L_DIR)
	@$(MAKE) clean
	@echo "MINISHELL FCLEAN"
	@$(RM) $(NAME)

re:
	@echo "*------RE_BUILD-------*"
	@$(MAKE) fclean
	@$(MAKE) all

.PHONY: all clean fclean re