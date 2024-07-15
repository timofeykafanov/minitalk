#------------------------------------------------------------------------------#
#----------------------------------PROPERTIES----------------------------------#
#------------------------------------------------------------------------------#

CC			= cc
RM			= rm -rf
CFLAGS		= -Wall -Wextra -Werror -MD -MP -g -I $(INCLUDES)
MAKEFLAGS	= -j$(nproc) --no-print-directory

NAME		= client
NAME_S		= server
NAME_B		= client_bonus
NAME_S_B	= server_bonus

SRCSDIR		= srcs
INCLUDES	= includes

SRCS		= \
			$(SRCSDIR)/client.c \
			$(SRCSDIR)/client_utils.c \

SRCS_S		= \
			$(SRCSDIR)/server.c \
			$(SRCSDIR)/server_utils.c \

SRCS_BONUS	= \
			$(SRCSDIR)/client.c \
			$(SRCSDIR)/client_utils.c \

SRCS_S_BONUS	= \
			$(SRCSDIR)/server.c \
			$(SRCSDIR)/server_utils.c \


OBJSDIR		= objs_client
OBJS		= $(addprefix $(OBJSDIR)/, $(SRCS:.c=.o))
DEPS		= $(addprefix $(OBJSDIR)/, $(SRCS:.c=.d))

OBJSDIR_S	= objs_server
OBJS_S		= $(addprefix $(OBJSDIR_S)/, $(SRCS_S:.c=.o))
DEPS_S		= $(addprefix $(OBJSDIR_S)/, $(SRCS_S:.c=.d))

OBJSDIR_B	= objs_client_bonus
OBJS_B		= $(addprefix $(OBJSDIR_B)/, $(SRCS_BONUS:.c=.o))
DEPS_b		= $(addprefix $(OBJSDIR_B)/, $(SRCS_BONUS:.c=.d))

OBJSDIR_S_B	= objs_server_bonus
OBJS_S_B	= $(addprefix $(OBJSDIR_S_B)/, $(SRCS_S_BONUS:.c=.o))
DEPS_S_B	= $(addprefix $(OBJSDIR_S_B)/, $(SRCS_S_BONUS:.c=.d))

#------------------------------------------------------------------------------#
#------------------------------------LIBFT-------------------------------------#
#------------------------------------------------------------------------------#

LIBDIR		= ./libft
LIBFT		= ${LIBDIR}/libft.a

#------------------------------------------------------------------------------#
#------------------------------------RULES-------------------------------------#
#------------------------------------------------------------------------------#

all		: $(NAME) $(NAME_S)

bonus	: $(NAME_B) $(NAME_S_B)

$(NAME)	: ${OBJS}
		$(MAKE) -C ${LIBDIR} all
		$(CC) ${CFLAGS} -o $@ $^ -L. ${LIBFT}

$(NAME_S)	: ${OBJS_S}
		$(MAKE) -C ${LIBDIR} all
		$(CC) ${CFLAGS} -o $@ $^ -L. ${LIBFT}

$(NAME_B)	: ${OBJS_B}
		$(MAKE) -C ${LIBDIR} all
		$(CC) ${CFLAGS} -o $@ $^ -L. ${LIBFT}

$(NAME_S_B)	: ${OBJS_S_B}
		$(MAKE) -C ${LIBDIR} all
		$(CC) ${CFLAGS} -o $@ $^ -L. ${LIBFT}

${OBJSDIR}/%.o	: %.c
		@mkdir -p $(dir $@)
		${CC} ${CFLAGS} -c $< -o $@

${OBJSDIR_S}/%.o	: %.c
		@mkdir -p $(dir $@)
		${CC} ${CFLAGS} -c $< -o $@

${OBJSDIR_B}/%.o	: %.c
		@mkdir -p $(dir $@)
		${CC} ${CFLAGS} -c $< -o $@

${OBJSDIR_S_B}/%.o	: %.c
		@mkdir -p $(dir $@)
		${CC} ${CFLAGS} -c $< -o $@

clean	:
		$(MAKE) -C ${LIBDIR} clean
		$(RM) $(OBJSDIR) $(OBJSDIR_S) $(OBJSDIR_B) $(OBJSDIR_S_B)

fclean	:
		$(MAKE) -C ${LIBDIR} fclean
		$(RM) $(OBJSDIR) $(NAME) $(OBJSDIR_S) $(NAME_S) $(OBJSDIR_B) $(NAME_B) $(OBJSDIR_S_B) $(NAME_S_B)

re		:
		$(MAKE) -C ${LIBDIR} fclean
		$(RM) $(OBJSDIR) $(NAME) $(OBJSDIR_S) $(NAME_S)
		$(MAKE) all

reb		:
		$(MAKE) -C ${LIBDIR} fclean
		$(RM) $(OBJSDIR_B) $(NAME_B) $(OBJSDIR_S_B) $(NAME_S_B)
		$(MAKE) bonus

-include $(DEPS)

.PHONY	: all clean fclean re bonus reb
