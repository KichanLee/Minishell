NAME = minishell

L_DIR = Libft
L_NAME = libft.a

INCS_DIR = incs
SRCS_DIR = srcs
OBJS_DIR = objs

CC = cc
# CC = cc -g3
CFLAGS = -Wall -Wextra -Werror  -I ~/.brew/opt/readline/include 
RLFLAGS = -lreadline -ltermcap

RM = rm -rf
MAKE = make

SRCS =	minishell.c \
		init/init.c \
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
		builtin/builtin_utils.c \
		builtin/ft_cd.c \
		builtin/ft_echo.c \
		builtin/ft_exit.c \
		builtin/ft_exit_two.c \
		builtin/ft_pwd.c \
		builtin/ft_unset.c \
		builtin/ft_export.c \
		builtin/ft_export_two.c \
		builtin/ft_env.c \
		builtin/ft_atolong.c \
		execute/checkbulitin.c \
		execute/execve.c \
		execute/freepipe.c \
		execute/pipe.c \
		execute/pipeutils.c \
		execute/setpath.c \
		redirect/heredocutils.c \
		redirect/heredoc.c \
		redirect/redirection.c \
		signal/signal.c

SRCS_WITH_PATH = $(addprefix $(SRCS_DIR)/, $(SRCS))
OBJS = $(SRCS_WITH_PATH:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)

all: $(NAME)

${OBJS_DIR}/%.o: ${SRCS_DIR}/%.c | ${OBJS_DIR}
	@$(CC) $(CFLAGS) -c $^ -o $@ -I $(INCS_DIR)

${OBJS_DIR}:
	@echo "MINISHELL BUILD"
	@mkdir ${OBJS_DIR}
	@mkdir ${OBJS_DIR}/init
	@mkdir ${OBJS_DIR}/lexer
	@mkdir ${OBJS_DIR}/parser
	@mkdir ${OBJS_DIR}/utils
	@mkdir ${OBJS_DIR}/builtin
	@mkdir ${OBJS_DIR}/execute
	@mkdir ${OBJS_DIR}/redirect
	@mkdir ${OBJS_DIR}/signal

$(NAME): $(L_NAME) $(OBJS)
	@echo "MINISHELL DONE"
	@$(CC) $(RLFLAGS) $^ -o $@ -I $(INCS_DIR) -L ~/.brew/opt/readline/lib
	# $(CC) $^ -o $@ -I $(INCS_DIR) -fsanitize=address

$(L_NAME):
	@echo "LIBFT BUILD"
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
	@echo "RE_BUILD"
	@$(MAKE) fclean
	@$(MAKE) all

.PHONY: all clean fclean re