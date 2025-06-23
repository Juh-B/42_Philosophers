NAME = philo_bonus

CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread

OBJDIR = objs

SRCS = main.c error_clean.c init.c message.c \
			simulation.c utils.c verif_input.c

OBJS = $(SRCS:.c=.o)

GREEN = \033[0;32m
GREEN_B = \033[1;32m
RESET = \033[0m


# VALGRIND = valgrind
# IGNRL = --leak-check=full --show-leak-kinds=all --track-fds=yes
# Clean old open process -> pkill -f philo_bonus
# Verif process after close -> pgrep philo_bonus
# fechar td qdo usar o ctrl+C kill -> -9 $(pgrep -f philo_bonus)


all: $(OBJDIR) $(NAME)

# val_fds:
# 	$(VALGRIND) $(IGNRL) $(FDS) ./$(NAME)

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
