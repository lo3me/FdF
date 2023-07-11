# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmomeni <mmomeni@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/18 17:01:34 by mmomeni           #+#    #+#              #
#    Updated: 2023/07/11 15:56:03 by mmomeni          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=		fdf
CFLAGS=		-Wall -Wextra -Werror
GLFWFLAGS=	-framework Cocoa -framework OpenGL -framework IOKit
MLXFLAGS=	-L ~/.brew/cellar/glfw/3.3.8/lib -lglfw -L ./MLX42/build -lmlx42
FUNCS=		render.c utils.c parse.c transform.c line.c
SRCS=		main.c $(FUNCS)
LIBFT_DIR=	libft
LIBFT=		$(LIBFT_DIR)/libft.a
LIBFTFLAGS=	-L$(LIBFT_DIR) -lft

BONUS_DIR=	bonus
BONUS_NAME=	fdf
BONUS_SRCS=	$(BONUS_DIR)/fdf_bonus.c $(BONUS_DIR)/hooks_bonus.c

all: bonus

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(LIBFT) $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) $(LIBFTFLAGS) $(MLXFLAGS) $(GLFWFLAGS) -o $(NAME)

bonus: $(BONUS_DIR)/$(BONUS_NAME)

$(BONUS_DIR)/$(BONUS_NAME): $(LIBFT) $(BONUS_SRCS) $(FUNCS)
	@mkdir -p build
	$(CC) $(CFLAGS) $(BONUS_SRCS) $(FUNCS) $(LIBFTFLAGS) $(MLXFLAGS) $(GLFWFLAGS) -o build/$(BONUS_NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(RM) $(NAME)
	$(RM) $(BONUS_DIR)/$(BONUS_NAME)

re: fclean all

brew:
	curl -fsSL https://rawgit.com/kube/42homebrew/master/install.sh | zsh

mlx:
	cd MLX42;\
	cmake -B build;\
	make -C build -j4;\

debug: CFLAGS += -fsanitize=address -g
debug: all bonus

norm:
	norminette *.c bonus libft

.PHONY: all clean fclean re bonus brew mlx
