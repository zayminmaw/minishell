NAME		=	minishell

LIBFT		=	libft

CC			=	cc

READLINE_PATH	=	$(shell brew --prefix readline)
READFLAG	=	-lreadline -L$(READLINE_PATH)/lib
READINCLUDE	=	-I$(READLINE_PATH)/include

CFLAGS		=	-Wall -Werror -Wextra -g3 -I ./includes $(READINCLUDE)
# CFLAGS		=	-I ./includes $(READINCLUDE)

SRCS_DIR	=	src/
OBJS_DIR	=	obj/

PROMPT_DIR	=	prompt/
PROMPT		=	prompt prompt_sig prompt_utils

LEXER_DIR	=	lexer/
LEXER		=	lexer lexer_pad_str lexer_tokenize lexer_expand_var lexer_check_quote \
				lexer_expand_utils lexer_expand_wildcards lexer_wildcard_utils \
				lexer_wildcard_match lexer_wildcard_expand lexer_wildcard_split \
				lexer_wildcard_components lexer_wildcard_process

VALIDATION_DIR	=	validation/
VALIDATION		=	validate_inout validate_parens validate_utils validate_checks

PARSER_DIR	=	parser/
PARSER		=	parser parser_count_nodes parser_init_nodes parser_build_nodes \
				parser_set_inout parser_resolve_nodes parser_build_path \
				parser_count_args parser_set_fullcmd parser_count_cmd \
				parser_inout_utils

EXIT_DIR	=	exit_status/
EXIT		=	exit_status

UTILS_DIR	=	utils/
UTILS		=	ft_isenvempty ft_error ft_envcpy ft_envops ft_skipquotes ft_appendchar \
				ft_validvarchar ft_cleanquotes ft_getenv ft_freeenv ft_freenodes ft_env_match \
				ft_count_tokens ft_perror

BUILDINS_DIR=	buildins/
BUILDINS	=	buildins ft_unset ft_echo ft_pwd ft_env ft_exit ft_export ft_cd ft_dot

EXEC_DIR	=	executor/
EXEC		=	executor heredoc heredoc_utils pipes redirections logical_operator executor_auxiliary \
				pipeline_executor subshell subshell_auxiliary pipeline_helpers pipeline_more exec_child_utils \
				redirections_helpers pipes_helpers executor_helpers executor_helpers2 executor_runs executor_wait

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
