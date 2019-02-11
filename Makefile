##
## EPITECH PROJECT, 2019
## PSU_2018_nmobjdump
## File description:
## Makefile
##

GREEN	=	\e[1;32m

WHITE	=	\e[0m

ORANGE	=	\e[1;33m

RED	=	\e[91m

INC	=	-I includes/

NM_DIR	=	sources/nm/

OBJDUMP_DIR	=	sources/objdump/

NM_SRC	=	main.c

OBJDUMP_SRC	=	main.c

NM_SRCS	=	$(addprefix $(NM_DIR), $(NM_SRC))

OBJDUMP_SRCS	=	$(addprefix $(OBJDUMP_DIR), $(OBJDUMP_SRC))

NM_NAME	=	my_nm

OBJDUMP_NAME	=	my_objdump

CC	=	gcc

G	=	-g

CFLAGS	=	-Wall -Wextra $(INC)

NM_OBJ	=	$(NM_SRCS:.c=.o)

OBJDUMP_OBJ	=	$(OBJDUMP_SRCS:.c=.o)

auth:
	@printf "$(ORANGE)   ____  ____  __  __ _  _  _        __   _  _  _  _      ____   __    __  ___  \n$(WHITE)"
	@printf "$(ORANGE)  (_  _)(  _ \(  )(  ( \/ )( \ ___  /  \ / )( \( \/ )    (___ \ /  \  /  \/ _ \ \n$(WHITE)"
	@printf "$(ORANGE)    )(   )   / )( /    /) __ ((___)(  O )) \/ ( )  /____  / __/(  0 )(_/ /\__  )\n$(WHITE)"
	@printf "$(ORANGE)   (__) (__\_)(__)\_)__)\_)(_/      \__\)\____/(__/(____)(____) \__/  (__)(___/ \n$(WHITE)"

debug:	CFLAGS += $(G)

all:	$(NM_NAME) $(OBJDUMP_NAME)
	@printf "$(GREEN)MY_NM AND MY_OBJDUMP CREATED\n$(WHITE)"

$(NM_NAME):	$(NM_OBJ)
	$(CC) -o $@ $^

$(OBJDUMP_NAME):	$(OBJDUMP_OBJ)
	$(CC) -o $@ $^

debug:	$(NM_NAME) $(OBJDUMP_NAME) $(debug)
	@printf "$(GREEN)DEBUG BUILD COMPLETED$(WHITE)"

nm:	$(NM_NAME)

objdump: $(OBJDUMP_NAME)

clean:
	rm -f $(NM_OBJ) $(OBJDUMP_OBJ)
	@printf "$(RED)PROJECT CLEANED\n$(WHITE)"

fclean: clean
	rm -f $(NM_NAME) $(OBJDUMP_NAME)
	@printf "$(RED)PROJECT RESTORED\n$(WHITE)"

re:	fclean all

nmre:	fclean nm

objre:	fclean objdump

auth:
	@printf "$(ORANGE)   ____  ____  __  __ _  _  _        __   _  _  _  _      ____   __    __  ___  \n$(WHITE)"
	@printf "$(ORANGE)  (_  _)(  _ \(  )(  ( \/ )( \ ___  /  \ / )( \( \/ )    (___ \ /  \  /  \/ _ \ \n$(WHITE)"
	@printf "$(ORANGE)    )(   )   / )( /    /) __ ((___)(  O )) \/ ( )  /____  / __/(  0 )(_/ /\__  )\n$(WHITE)"
	@printf "$(ORANGE)   (__) (__\_)(__)\_)__)\_)(_/      \__\)\____/(__/(____)(____) \__/  (__)(___/ \n$(WHITE)"

.PHONY:	all clean fclean re objre nmre auth

