# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmoucade <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/05 13:11:07 by jmoucade          #+#    #+#              #
#    Updated: 2017/01/25 12:06:42 by amazurie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

CC = gcc
AR = ar -rcs

CFLAGS = -Wall -Wextra -Werror

INC_PATH = includes
SRC_PATH = srcs
HANDLE_PATH = handle
LIB_PATH = libft
LIB_INC_PATH = $(LIB_PATH)/includes

LIBFT_SRC =		$(LIB_PATH)/ft_lennbase.c	\
				$(LIB_PATH)/ft_putchar.c	\
				$(LIB_PATH)/ft_putstr.c		\
				$(LIB_PATH)/ft_putnstr.c	\
				$(LIB_PATH)/ft_putnchar.c	\
				$(LIB_PATH)/ft_putnwstr.c	\
				$(LIB_PATH)/ft_putwchar.c	\
				$(LIB_PATH)/ft_strchr.c		\
				$(LIB_PATH)/ft_strlen.c		\
				$(LIB_PATH)/ft_strlen_chr.c	\
				$(LIB_PATH)/ft_wstrlen.c	\
				$(LIB_PATH)/ft_wstrnlen.c	\
				$(LIB_PATH)/ft_wstrnlen.c	\
				$(LIB_PATH)/ft_memalloc.c	\
				$(LIB_PATH)/ft_wstrnlen.c	\
				$(LIB_PATH)/ft_bzero.c		\
				$(LIB_PATH)/ft_memset.c		\
				$(LIB_PATH)/ft_strncat.c	\
				$(LIB_PATH)/ft_itoa_base.c	\
				$(LIB_PATH)/ft_lennb.c		\
				$(LIB_PATH)/ft_strcat.c

HANDLE_SRC =	$(SRC_PATH)/$(HANDLE_PATH)/handle_str.c	\
				$(SRC_PATH)/$(HANDLE_PATH)/handle_num.c	\
				$(SRC_PATH)/$(HANDLE_PATH)/print_num.c

SRC =	$(SRC_PATH)/ft_printf.c	\
		$(SRC_PATH)/parse.c		\
		$(SRC_PATH)/handle.c	\
		$(SRC_PATH)/buff_handle.c	\
		$(SRC_PATH)/getflags.c


OSRC = $(SRC:.c=.o)
OHSRC = $(HANDLE_SRC:.c=.o)
LIBFTSRC = $(LIBFT_SRC:.c=.o)

NO_COLOR=\x1b[0m
OK_COLOR=\x1b[32;01m

all: $(NAME)

$(NAME): $(OSRC) $(OHSRC) $(LIBFTSRC)
	@echo "Compiling..."
	@$(AR) $@ $^
	@ranlib $@
	@echo "$(OK_COLOR)$@ compiled.$(NO_COLOR)"

%.o: %.c
	@$(CC) $(CFLAGS) -I $(LIB_INC_PATH) -I $(INC_PATH) -c -o $@ $?
	@echo "Linking file $@"

clean:
	@make -C libft clean
	@/bin/rm -f $(OSRC)
	@/bin/rm -f $(OHSRC)
	@/bin/rm -f $(LIBFTSRC)
	@echo "Cleaning temporary files."

fclean: clean
	@make -C libft fclean
	@/bin/rm -f $(NAME)
	@/bin/rm -f a.out
	@echo "Delete $(NAME) file."

re: fclean all
