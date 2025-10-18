NAME		=	libft.a

CC			=	cc

CFLAGS		=	-Wall -Werror -Wextra -I ./includes

SRCS_DIR	=	src/
OBJS_DIR	=	obj/

FTIS_DIR	=	ft_is/
FTIS		=	ft_isalnum ft_isalpha ft_isascii ft_isdigit ft_isprint ft_isspace

FTMEM_DIR	=	ft_mem/
FTMEM		=	ft_bzero ft_calloc ft_memchr ft_memcmp ft_memmove ft_memset

FTPUT_DIR	=	ft_put/
FTPUT		=	ft_putchar_fd ft_putendl_fd ft_putnbr_fd ft_putstr_fd

FTTO_DIR	=	ft_to/
FTTO		=	ft_atoi ft_itoa ft_tolower ft_toupper ft_atol ft_atoi_base

FTSTR_DIR	=	ft_str/
FTSTR		=	ft_split ft_strchr ft_strdup ft_striteri ft_strjoin \
				ft_strlcat ft_strlcpy ft_strlen ft_strmapi ft_strncmp \
				ft_strnstr ft_strrchr ft_strtrim ft_substr ft_strarr_free

FTLST_DIR	=	ft_lst/
FTLST		=	ft_lstadd_back ft_lstadd_front ft_lstclear ft_lstdelone \
				ft_lstiter ft_lstlast ft_lstmap ft_lstnew ft_lstsize

GNL_DIR		=	gnl/
GNL			=	get_next_line

FTGC_DIR	=	ft_gc/
FTGC		=	ft_malloc_lst ft_malloc_clear ft_malloc

FTPRINTF_DIR =	ft_printf/
FTPRINTF	=	ft_printf pf_format_str pf_puthex pf_putnbr pf_putptr pf_putunbr pf_utils

SRC_FILES	+=	$(addprefix $(FTIS_DIR),$(FTIS))
SRC_FILES	+=	$(addprefix $(FTMEM_DIR),$(FTMEM))
SRC_FILES	+=	$(addprefix $(FTPUT_DIR),$(FTPUT))
SRC_FILES	+=	$(addprefix $(FTTO_DIR),$(FTTO))
SRC_FILES	+=	$(addprefix $(FTSTR_DIR),$(FTSTR))
SRC_FILES	+=	$(addprefix $(FTLST_DIR),$(FTLST))
SRC_FILES	+=	$(addprefix $(GNL_DIR), $(GNL))
SRC_FILES	+=	$(addprefix $(FTPRINTF_DIR), $(FTPRINTF))
SRC_FILES	+=	$(addprefix $(FTGC_DIR), $(FTGC))

SRCS 		= 	$(addprefix $(SRCS_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJS 		= 	$(addprefix $(OBJS_DIR), $(addsuffix .o, $(SRC_FILES)))

${OBJS_DIR}%.o: ${SRCS_DIR}%.c
	@mkdir -p ${dir $@}
	${CC} ${CFLAGS} -c $< -o $@

all: ${NAME}

${NAME}: ${OBJS}
	@ar rcs ${NAME} ${OBJS}

clean: 
	rm -rf ${OBJS_DIR}
        
fclean: clean
	rm -rf ${NAME}

re: fclean all

.PHONY: all clean fclean re
