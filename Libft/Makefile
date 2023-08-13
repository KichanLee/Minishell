# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eunwolee <eunwolee@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/17 12:21:51 by eunwolee          #+#    #+#              #
#    Updated: 2023/08/14 07:52:20 by eunwolee         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

INCS_DIR = incs
SRCS_DIR = srcs
OBJS_DIR = objs

CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs
RM = rm -rf

SRCS =	ft_isalpha.c \
		ft_isdigit.c \
		ft_isalnum.c \
		ft_isascii.c \
		ft_isprint.c \
		ft_toupper.c \
		ft_tolower.c \
		ft_memcmp.c \
		ft_memset.c \
		ft_memchr.c \
		ft_memcpy.c \
		ft_memmove.c \
		ft_calloc.c \
		ft_bzero.c \
		ft_strlen.c \
		ft_strlcpy.c \
		ft_strlcat.c \
		ft_strncat.c \
		ft_strchr.c \
		ft_strrchr.c \
		ft_strnstr.c \
		ft_strdup.c \
		ft_strncmp.c \
		ft_atoi.c \
		ft_substr.c \
		ft_strjoin.c \
		ft_strtrim.c \
		ft_split.c \
		ft_itoa.c \
		ft_strmapi.c \
		ft_striteri.c \
		ft_putchar_fd.c \
		ft_putstr_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		get_next_line.c \
		get_next_line_utils.c

SRCS_WITH_PATH = $(addprefix $(SRCS_DIR)/, $(SRCS))
OBJS = $(SRCS_WITH_PATH:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS)
	@echo "LIBFT BUILD DONE"
	@$(AR) $@ $^

${OBJS_DIR}/%.o: ${SRCS_DIR}/%.c | ${OBJS_DIR}
	@$(CC) $(CFLAGS) -c $^ -o $@ -I $(INCS_DIR)

${OBJS_DIR}:
	@echo "LIBFT BUILD"
	@mkdir ${OBJS_DIR}

clean:
	@$(RM) $(OBJS_DIR)

fclean:
	@$(MAKE) clean
	@$(RM) $(NAME)

re:
	@$(MAKE) fclean
	@$(MAKE) all

.PHONY: all clean fclean re
