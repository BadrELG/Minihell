# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: badr <badr@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/19 00:00:00 by badr              #+#    #+#              #
#    Updated: 2025/12/19 14:33:15 by badr             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell

CC			= cc
CFLAGS		= -Wall -Wextra -Werror
LDFLAGS		= -lreadline

LIBFT_DIR	= libft
LIBFT		= $(LIBFT_DIR)/libft.a

INCLUDE		= -I include -I $(LIBFT_DIR)

SRC_DIR		= src
OBJ_DIR		= obj

SRCS		= $(SRC_DIR)/main.c \
			  $(SRC_DIR)/parsing/lexer.c \
			  $(SRC_DIR)/parsing/lexer_utils.c \
			  $(SRC_DIR)/parsing/token_utils.c \
			  $(SRC_DIR)/parsing/parser.c \
			  $(SRC_DIR)/parsing/parser_utils.c \
			  $(SRC_DIR)/parsing/cmd_utils.c \
			  $(SRC_DIR)/parsing/expander.c \
			  $(SRC_DIR)/parsing/expand_utils.c \
			  $(SRC_DIR)/env/env.c

OBJS		= $(addprefix $(OBJ_DIR)/, $(notdir $(SRCS:.c=.o)))

# Colors
GREEN		= \033[0;32m
RED			= \033[0;31m
RESET		= \033[0m

vpath %.c $(sort $(dir $(SRCS)))

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LDFLAGS) -o $(NAME)
	@echo "$(GREEN)✓ $(NAME) created$(RESET)"

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
	@echo "$(GREEN)✓$(RESET) Compiled: $<"

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean --no-print-directory
	@rm -rf $(OBJ_DIR)
	@echo "$(RED)✗ Object files removed$(RESET)"

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory
	@rm -f $(NAME)
	@echo "$(RED)✗ $(NAME) removed$(RESET)"

re: fclean all

.PHONY: all clean fclean re
