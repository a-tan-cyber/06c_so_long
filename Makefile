# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amtan <amtan@student.42singapore.sg>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/04 21:04:39 by amtan             #+#    #+#              #
#    Updated: 2026/01/08 11:36:24 by amtan            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME      := so_long
CC        := cc
CFLAGS    := -Wall -Wextra -Werror

SRCDIR    := src
OBJDIR    := obj
INCDIR    := include
MLXDIR    := minilibx-linux

LIBFTDIR  := libft
LIBFT     := $(LIBFTDIR)/libft.a

CPPFLAGS  := -I$(INCDIR) -I$(MLXDIR) -I$(LIBFTDIR)
DEPFLAGS  := -MMD -MP

SRC_FILES := app_run.c app.c args.c blit.c error.c game.c game_move.c \
            	grid_dup.c img.c main.c map_free.c map_load.c \
            	map_validate_basic.c map_validate_charset.c \
            	map_validate_path.c pixel.c render.c tex.c

SRCS      := $(addprefix $(SRCDIR)/,$(SRC_FILES))
OBJS      := $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
DEPS      := $(OBJS:.o=.d)

HOSTTYPE  := $(shell uname -s)
MLXLIB    := $(MLXDIR)/libmlx_$(HOSTTYPE).a
MLXSYS    := -lXext -lX11 -lm -lz

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLXLIB)
	$(CC) $(CFLAGS) $(OBJS) -L$(LIBFTDIR) -lft $(MLXLIB) $(MLXSYS) -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFTDIR)

$(MLXLIB):
	$(MAKE) -C $(MLXDIR)

mlx: $(MLXLIB)

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
