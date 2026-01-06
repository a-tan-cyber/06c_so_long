# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amtan <amtan@student.42singapore.sg>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/04 21:04:39 by amtan             #+#    #+#              #
#    Updated: 2026/01/06 16:12:45 by amtan            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME      := so_long
CC        := cc
CFLAGS    := -Wall -Wextra -Werror

SRCDIR    := src
OBJDIR    := obj
INCDIR    := include

MLXDIR    := mlx_linux
MLXLIB    = $(firstword $(wildcard $(MLXDIR)/libmlx_Linux.a $(MLXDIR)/libmlx.a))
MLXSYS    := -lXext -lX11 -lm -lz

LIBFTDIR  := libft
LIBFT     := $(LIBFTDIR)/libft.a

CPPFLAGS  := -I$(INCDIR) -I$(MLXDIR) -I$(LIBFTDIR)
DEPFLAGS  := -MMD -MP

SRCS      := $(SRCDIR)/main.c

OBJS      := $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
DEPS      := $(OBJS:.o=.d)

all: $(NAME)

mlx:
	$(MAKE) -C $(MLXDIR)

$(NAME): $(OBJS) $(LIBFT) mlx
	$(CC) $(CFLAGS) $(OBJS) -L$(LIBFTDIR) -lft $(MLXLIB) $(MLXSYS) -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFTDIR)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(DEPFLAGS) -c $< -o $@

clean:
	$(MAKE) -C $(LIBFTDIR) clean
	$(MAKE) -C $(MLXDIR) clean
	rm -f $(OBJS) $(DEPS)
	rm -rf $(OBJDIR)

fclean: clean
	$(MAKE) -C $(LIBFTDIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re mlx

-include $(DEPS)
