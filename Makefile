NAME = minishell

L_DIR = Libft
L_NAME = libft.a

INCS_DIR = incs
SRCS_DIR = srcs

CC = cc
CFLAGS = -Wall -Wextra -Werror -I ~/.brew/opt/readline/include 

RM = rm -rf
MAKE = make

SRCS = $(SRCS_DIR)/minishell.c \
	$(SRCS_DIR)/init/init.c \
	$(SRCS_DIR)/lexer/lexer.c \
	$(SRCS_DIR)/lexer/tokenizer.c \
	$(SRCS_DIR)/lexer/quote.c \
	$(SRCS_DIR)/lexer/expand.c \
	$(SRCS_DIR)/parser/syntax.c \
	$(SRCS_DIR)/parser/parser.c \
	$(SRCS_DIR)/utils/env.c \
	$(SRCS_DIR)/utils/list.c \
	$(SRCS_DIR)/utils/list_clear.c \
	$(SRCS_DIR)/utils/tree.c \
	$(SRCS_DIR)/utils/utils.c \
	$(SRCS_DIR)/utils/temp.c \
	$(SRCS_DIR)/exec/sig.c \
	$(SRCS_DIR)/builtin/builtin.c \
	$(SRCS_DIR)/builtin/ft_cd.c \
	$(SRCS_DIR)/builtin/ft_echo.c \
	$(SRCS_DIR)/builtin/ft_exit.c \
	$(SRCS_DIR)/builtin/ft_pwd.c \
	$(SRCS_DIR)/builtin/ft_unset.c \
	$(SRCS_DIR)/builtin/ft_export.c \
	$(SRCS_DIR)/execute/checkbulitin.c \
	$(SRCS_DIR)/execute/execve.c \
	$(SRCS_DIR)/execute/freepipe.c \
	$(SRCS_DIR)/execute/heredoc.c \
	$(SRCS_DIR)/execute/heredocutils.c \
	$(SRCS_DIR)/execute/pipe.c \
	$(SRCS_DIR)/execute/pipeutils.c \
	$(SRCS_DIR)/execute/redirection.c \
	$(SRCS_DIR)/execute/setpath.c \

OBJS = $(SRCS:%.c=%.o)

%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@ -I $(INCS_DIR) 

all: $(NAME)

$(NAME): $(L_NAME) $(OBJS)
	$(CC) $^ -o $@ -I $(INCS_DIR)  -lreadline -L ~/.brew/opt/readline/lib

$(L_NAME):
	$(MAKE) re -C $(L_DIR)
	cp ./$(L_DIR)/$(L_NAME) .

clean:
	$(MAKE) fclean -C $(L_DIR)
	$(RM) $(OBJS)
	$(RM) $(SRCS_DIR_M)/*.o $(SRCS_DIR_B)/*.o $(L_NAME)

fclean:
	$(MAKE) fclean -C $(L_DIR)
	$(MAKE) clean
	$(RM) $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all

.PHONY: all clean fclean re