NAME		=	minishell

LIBFT		=	libft

CC			=	cc

CFLAGS		=	-Wall -Werror -Wextra -I ./includes

SRCS_DIR	=	src/
OBJS_DIR	=	obj/

PROMPT_DIR	=	prompt/
PROMPT		=	prompt

UTILS_DIR	=	utils/
UTILS		=	ft_isenvempty ft_error ft_envcpy ft_envops

ENTRY		=	main

SRC_FILES	+=	$(addprefix $(UTILS_DIR), $(UTILS))
SRC_FILES	+=	$(addprefix $(PROMPT_DIR), $(PROMPT))
SRC_FILES	+=  $(ENTRY)

SRCS 		= 	$(addprefix $(SRCS_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJS 		= 	$(addprefix $(OBJS_DIR), $(addsuffix .o, $(SRC_FILES)))

${OBJS_DIR}%.o: ${SRCS_DIR}%.c
	@mkdir -p ${dir $@}
	${CC} ${CFLAGS} -c $< -o $@

all: ${NAME}

${NAME}: ${OBJS}
	@make -C ${LIBFT}
	@$(CC) $(CFLAGS) $(OBJS) ./libft/libft.a -o $(NAME)

clean: 
	rm -rf ${OBJS_DIR}
	make clean -C ${LIBFT}

fclean: clean
	rm -rf ${NAME}
	make fclean -C ${LIBFT}

re: fclean all

.PHONY: all clean fclean re
