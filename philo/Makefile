SRC =	main.c philosophers.c routine.c errors.c utils.c

OBJ =	${SRC:.c=.o}

CFLAGS =	-Wall -Wextra -Werror

NAME =	philo

CC =	gcc
RM =	rm -f

all: ${NAME}

.c.o:
		${CC} ${CFLAGS} -I /usr/include -c $< -o ${<:.c=.o}

$(NAME): $(OBJ)
		${CC} -pthread ${CFLAGS} ${OBJ} -o ${NAME}

clean:
		${RM} ${OBJ}

fclean:	clean
		${RM} ${NAME}

re:	fclean all

.PHONY:	all clean fclean re
