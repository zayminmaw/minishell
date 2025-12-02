NAME		=	minishell

LIBFT		=	libft

CC			=	cc

READLINE_PATH	=	$(shell brew --prefix readline)
READFLAG	=	-lreadline -L$(READLINE_PATH)/lib
READINCLUDE	=	-I$(READLINE_PATH)/include

CFLAGS		=	-Wall -Werror -Wextra -I ./includes $(READINCLUDE)

SRCS_DIR	=	src/
OBJS_DIR	=	obj/

PROMPT_DIR	=	prompt/
PROMPT		=	prompt prompt_sig

LEXER_DIR	=	lexer/
LEXER		=	lexer lexer_pad_str lexer_tokenize lexer_expand_var lexer_check_quote

VALIDATION_DIR	=	validation/
VALIDATION		=	validate_inout

PARSER_DIR	=	parser/
PARSER		=	parser parser_count_nodes parser_init_nodes parser_build_nodes \
				parser_set_inout parser_resolve_nodes parser_build_path \
				parser_count_args parser_set_fullcmd parser_count_cmd

EXIT_DIR	=	exit_status/
EXIT		=	exit_status

UTILS_DIR	=	utils/
UTILS		=	ft_isenvempty ft_error ft_envcpy ft_envops ft_skipquotes ft_appendchar \
				ft_validvarchar ft_cleanquotes ft_getenv ft_freeenv ft_freenodes

BUILDINS_DIR=	buildins/
BUILDINS	=	buildins ft_unset ft_echo ft_pwd ft_env ft_exit

EXEC_DIR	=	executor/
EXEC		=	executor heredoc pipes redirections

ENTRY		=	main

SRC_FILES	+=	$(addprefix $(UTILS_DIR), $(UTILS))
SRC_FILES	+=	$(addprefix $(PROMPT_DIR), $(PROMPT))
SRC_FILES	+=	$(addprefix $(LEXER_DIR), $(LEXER))
SRC_FILES	+=	$(addprefix $(VALIDATION_DIR), $(VALIDATION))
SRC_FILES	+=	$(addprefix $(PARSER_DIR), $(PARSER))
SRC_FILES	+=	$(addprefix $(EXIT_DIR), $(EXIT))
SRC_FILES	+=	$(addprefix $(BUILDINS_DIR), $(BUILDINS))
SRC_FILES	+=	$(addprefix $(EXEC_DIR), $(EXEC))
SRC_FILES	+=  $(ENTRY)

SRCS 		= 	$(addprefix $(SRCS_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJS 		= 	$(addprefix $(OBJS_DIR), $(addsuffix .o, $(SRC_FILES)))

${OBJS_DIR}%.o: ${SRCS_DIR}%.c
	@mkdir -p ${dir $@}
	${CC} ${CFLAGS} -c $< -o $@

all: ${NAME}

${NAME}: ${OBJS}
	@make -C ${LIBFT}
	@$(CC) $(CFLAGS) $(OBJS) ./libft/libft.a -o $(NAME) $(READFLAG)

clean: 
	rm -rf ${OBJS_DIR}
	make clean -C ${LIBFT}

fclean: clean
	rm -rf ${NAME}
	make fclean -C ${LIBFT}

re: fclean all

.PHONY: all clean fclean re
