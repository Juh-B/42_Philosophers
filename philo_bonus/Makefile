NAME = philo_bonus

CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread

OBJDIR = objs

SRCS = main.c error_clean.c init.c mensagem.c \
			simulation.c utils.c verif_input.c

OBJS = $(SRCS:.c=.o)

GREEN = \033[0;32m
GREEN_B = \033[1;32m
RESET = \033[0m

all: $(OBJDIR) $(NAME)

$(NAME): $(addprefix $(OBJDIR)/, $(OBJS)) philo_bonus.h
	@$(CC) $(CFLAGS) $(addprefix $(OBJDIR)/, $(OBJS)) -o $(NAME)
	@echo "-------------------------------"
	@echo "|   $(GREEN_B) Philo Bonus is Ready! $(RESET)   |"
	@echo "-------------------------------"

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJDIR)
	@echo "$(GREEN)Clean done!$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(GREEN)Full clean done!$(RESET)"

re: fclean all

.PHONY: all clean fclean re
