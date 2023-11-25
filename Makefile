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

# File dirs
SRCDIR=./src
OBJDIR=./obj
# File names
NAME=minishell
HEADER=./inc/philo.h
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
	@printf "$(CYAN)\n\n\tMaking libmlx...$(RESET_ALL)\n\n"
	make -C ./mlx
	@printf "$(CYAN)\n\n\tlibmlx done!$(RESET_ALL)\n\n"

clean:
	@printf "$(YELLOW)\n\n\tRemoving objects...\n\n$(RESET_ALL)"
	rm -rf $(OBJDIR)
fclean: clean
	@printf "$(YELLOW)\n\n\tRemoving philo binary...\n\n$(RESET_ALL)"
	rm -f $(NAME)
re: fclean $(NAME)

.PHONY : all clean fclean re
