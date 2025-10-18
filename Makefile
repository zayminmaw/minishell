NAME		=	minishell

LIBFT		=	libft

CC			=	cc

CFLAGS		=	-Wall -Werror -Wextra -I ./includes

SRCS_DIR	=	src/
OBJS_DIR	=	obj/

LOGICS      =	

ENTRY		=	main

SRC_FILES	+=  $(ENTRY)
SRC_FILES	+=  $(LOGICS)

SRCS 		= 	$(addprefix $(SRCS_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJS 		= 	$(addprefix $(OBJS_DIR), $(addsuffix .o, $(SRC_FILES)))

${OBJS_DIR}%.o: ${SRCS_DIR}%.c
	@mkdir -p ${dir $@}
	${CC} ${CFLAGS} -c $< -o $@

all: ${NAME}

${NAME}: ${OBJS}
	@make -C ${LIBFT}
	@make -C ${MLX}
	@$(CC) $(CFLAGS) $(OBJS) ./libft/libft.a -o $(NAME)

clean: 
	rm -rf ${OBJS_DIR}
	make clean -C ${LIBFT}

fclean: clean
	rm -rf ${NAME}
	make fclean -C ${LIBFT}

re: fclean all

.PHONY: all clean fclean re
