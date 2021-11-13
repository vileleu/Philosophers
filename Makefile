BLUE = 		\033[0;34m
GREEN = 	\033[0;32m
LIGHTBLUE = \033[1;34m
RED = 		\033[0;31m
YELLOW = 	\033[1;33m
ORANGE = 	\033[0;33m
MAGENTA = 	\033[0;35m
RESET = 	\033[0m

SRCS		= $(wildcard srcs/philo/srcs/*.c)

SRCS_BONUS	= $(wildcard srcs/philo_bonus/srcs/*.c)

OBJS		= ${SRCS:.c=.o}

OBJS_BONUS	= ${SRCS_BONUS:.c=.o}


NAME			= philo

HEADERS			= -I srcs/philo/includes/

HEADERS_BONUS	= -I srcs/philo_bonus/includes/

FLAGS		= -Wall -Wextra -Werror
.c.o:		
			@gcc ${FLAGS} ${HEADERS} ${HEADERS_BONUS} -c $< -o ${<:.c=.o} > /dev/null

${NAME}:	${OBJS}
			@printf "$(BLUE)\nCompiling files..."
			@gcc ${FLAGS} ${OBJS} -o philo -lpthread
			@printf "$(GREEN)[philo done][✔]$(RESET)"
			@printf "\n\n"

bonus:		${OBJS_BONUS}
			@printf "$(BLUE)\nCompiling files..."
			@gcc ${FLAGS} ${OBJS_BONUS} -o philo_bonus -lpthread
			@printf "$(GREEN)[philo_bonus done][✔]$(RESET)"
			@printf "\n\n"

all:		${NAME}

clean:
			@printf "\n"
			@printf "$(RED)Erase files '.o'\n"
			@rm -rf $(OBJS) $(OBJS_BONUS)
			@printf "\033[0m\n"

fclean:
			@printf "\n"
			@printf "$(RED)Erase files '.o'\n"
			@rm -rf $(OBJS) $(OBJS_BONUS)
			@printf "$(RED)Delete executable\n"
			@rm -rf philo philo_bonus
			@printf "$(RESET)\n"

re:			fclean all

.PHONY:		clean fclean re all