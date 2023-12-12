# Terminal colors
BLACK=\e[30m
RED=\e[31m
GREEN=\e[32m
YELLOW=\e[33m
BLUE=\e[34m
PURPLE=\e[35m
CYAN=\e[36m
WHITE=\e[37m
GREY=\e[90m
RESET_FG=\e[39m
RESET_BG=\e[49m
RESET_ALL=\e[0m

# Compiler options
CFLAGS= -Wall -Wextra -Werror
# Linker options
LDFLAGS= -lreadline -L./inc -lft

# File dirs
SRCDIR=./src_2/main
OBJDIR=./obj
# File names
NAME=minishell
HEADER=./include_2/minishell.h ./include_2/lexer_utils.h ./include_2/main.h
LIB=./inc/libft.a
SRC=$(wildcard $(SRCDIR)/*.c)
OBJ=$(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRC))


$(OBJDIR)/%.o: $(SRCDIR)/%.c $(HEADER) | $(OBJDIR) $(LIB)
	@printf "$(CYAN)\nCompiling $@...$(RESET_ALL)\n"
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ) $(HEADER)
	@printf "$(CYAN)\n\n\tLinking...$(RESET_ALL)\n\n"
	$(CC) $(OBJ) $(LDFLAGS) -o $(NAME)

$(OBJDIR):
	@printf "$(CYAN)\n\n\tNo obj directory found, creating it...$(RESET_ALL)\n\n"
	mkdir -p $(OBJDIR)

$(LIB):
	@printf "$(CYAN)\n\n\tMaking libft...$(RESET_ALL)\n\n"
	@make -C ./inc/libft
	@printf "$(CYAN)\n\n\tlibft done!$(RESET_ALL)\n\n"

clean:
	@printf "$(YELLOW)\n\n\tRemoving objects...\n\n$(RESET_ALL)"
	rm -rf $(OBJDIR)
	make -C ./inc/libft clean
fclean: clean
	@printf "$(YELLOW)\n\n\tRemoving minishell binary...\n\n$(RESET_ALL)"
	rm -f $(NAME)
	make -C ./inc/libft fclean
re: fclean $(NAME)

.PHONY : all clean fclean re
