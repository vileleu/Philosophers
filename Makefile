BLUE = 		\033[0;34m
GREEN = 	\033[0;32m
LIGHTBLUE = \033[1;34m
RED = 		\033[0;31m
YELLOW = 	\033[1;33m
ORANGE = 	\033[0;33m
MAGENTA = 	\033[0;35m
RESET = 	\033[0m

SRCS_ONE	= $(wildcard srcs/philo_one/srcs/*.c)

SRCS_TWO	= $(wildcard srcs/philo_two/srcs/*.c)

SRCS_THREE	= $(wildcard srcs/philo_three/srcs/*.c)

OBJS_ONE	= ${SRCS_ONE:.c=.o}

OBJS_TWO	= ${SRCS_TWO:.c=.o}

OBJS_THREE	= ${SRCS_THREE:.c=.o}

NAME			= philo

HEADERS_ONE		= -I srcs/philo_one/includes/

HEADERS_TWO		= -I srcs/philo_two/includes/

HEADERS_THREE	= -I srcs/philo_three/includes/

FLAGS		= -Wall -Wextra -Werror

.c.o:		
			@gcc ${FLAGS} ${HEADERS} -c $< -o ${<:.c=.o} > /dev/null

${NAME}:	${OBJS_ONE} ${OBJS_TWO} ${OBJS_THREE}
			@echo "$(BLUE)"
			@echo "$(BLUE)Compiling files..."
			@gcc ${FLAGS} ${OBJS_ONE} -o philo_one -lpthread
			@echo "$(GREEN)[philo_one done][✔]$(RESET)"
			@echo ""
			@echo "$(BLUE)Compiling files..."
			@gcc ${FLAGS} ${OBJS_TWO} -o philo_two -lpthread
			@echo "$(GREEN)[philo_two done][✔]$(RESET)"
			@echo ""
			@echo "$(BLUE)Compiling files..."
			@gcc ${FLAGS} ${OBJS_THREE} -o philo_three -lpthread
			@echo "$(GREEN)[philo_three done][✔]$(RESET)"
			@echo ""

all:		${NAME}

clean:
			@echo ""
			@echo "$(RED)Erase files '.o'"
			@rm -rf $(OBJS_ONE)
			@rm -rf $(OBJS_TWO)
			@rm -rf $(OBJS_THREE)
			@echo "\033[0m"

fclean:
			@echo ""
			@echo "$(RED)Erase files '.o'"
			@rm -rf $(OBJS_ONE)
			@rm -rf $(OBJS_TWO)
			@rm -rf $(OBJS_THREE)
			@echo "$(RED)Delete executable file and libft"
			@rm -rf philo_one philo_two philo_three
			@echo "$(RESET)"

re:			fclean all

.PHONY:		clean fclean re all