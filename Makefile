NAME 		= microshell
CC 			= cc
CFLAGS 		= -Wall -Wextra -Werror
INCLUDES 	= -Iinclude -ILibft/inclu
LIBFT_DIR 	= Libft
LIBFT 		= $(LIBFT_DIR)/libft.a
SRC_DIR 	= src
OBJ_DIR 	= objs

# Source files
SRCS = 	$(SRC_DIR)/main.c \
		$(SRC_DIR)/parser.c \
		$(SRC_DIR)/tokens.c \
		$(SRC_DIR)/ast.c \
		$(SRC_DIR)/run.c

# Object files
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Targets
all: $(LIBFT) $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBFT)

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -rf $(OBJ_DIR)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re