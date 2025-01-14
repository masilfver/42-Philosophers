NAME = philo
CC = cc
CFLAGS = -Werror -Wextra -Wall -pthread -g
SRCS =	src/philo.c \
		src/checks.c \
		src/dining.c \
		src/init.c   \
		src/init_2.c \
		src/tasks.c  \
		src/tasks_eat.c \
		src/utils.c  \
		src/deaths.c \
		
OBJS = ${SRCS:.c=.o}

all: ${NAME}

${NAME}: ${OBJS}
	${CC} ${OBJS} ${CFLAGS} -o ${NAME}

clean:
	rm -rf ${OBJS}

fclean:
	rm -rf ${NAME} ${OBJS}

re: fclean all
	
.PHONY: all, clean, fclean, re