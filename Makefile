#<-------------------------------|VARIABLES|---------------------------------->#

NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror

#<---------------------------------|FILES|------------------------------------>#

LIBFT = ./Libft/libft.a

SRC_F = minishell.c clean.c token_utils.c token.c analize_tokens.c # main.c
SRC_D = ./sources/

OBJ_F = ${SRC_F:.c=.o}
OBJ_D = ./objects/
OBJ = ${addprefix ${OBJ_D}, ${OBJ_F}}

DEP_F = ${SRC_F:.c=.d}
DEP_D = ./dependencies/
DEP = ${addprefix ${DEP_D}, ${DEP_F}}

#<---------------------------------|COLORS|----------------------------------->#

DF = \033[0;39m#		Default
RED= \033[0;31m#		Red
BRED= \033[1;31m#		Bold Red
BBLUE= \033[1;34m#		Bold Blue
BYELLOW= \033[1;33m#	Bold Yellow
BIPRPL = \033[1;95m#	Purple
BCYAN= \033[1;36m#		Bold Cyan
BIRED= \033[1;91m#		Bold Intense Red
BIGREEN= \033[1;92m#	Bold Intense Green
BBLACK=\033[1;30m#		Bold Black

#<---------------------------------|RULES|------------------------------------>#

all: libftmake ${NAME}

${NAME}: ${OBJ_D} ${DEP_D} ${OBJ} ${LIBFT}
	@${CC} ${CFLAGS} ${OBJ} ${LIBFT} -o ${NAME}
	@echo "\n${RED}Compiling progam:${DF}"
	@echo "${BCYAN}${CC}${DF} ${BBLUE}${CFLAGS}${DF} ${BIGREEN}${OBJ_F}${DF} \
	${BIPRPL}${LIBFT}${DF} ${BCYAN}-o${DF} ${RED}${NAME}${DF}"

libftmake:
	@echo "${BCYAN}### LIBFT ###${DF}${BIGREEN}"
	@make -C Libft --no-print-directory
	@echo "${DF}${BCYAN}###${DF} ${BIPRPL}libft.a${DF} ${BCYAN}made ---${DF}\n"

${OBJ_D}%.o: ${SRC_D}%.c Makefile
	@${CC} ${CFLAGS} -MMD -c $< -o $@
	@mv ${@:.o=.d} ${DEP_D}
	@echo "${BCYAN}${CC}${DF} ${BBLUE}${CFLAGS} -MMD${DF} ${BCYAN}-c${DF} \
	${BIRED}$<${DF} ${BCYAN}-o${DF} ${BIGREEN}$@${DF}"
	@echo "${BCYAN}mv${DF} ${BYELLOW}${@:.o=.d}${DF} ${BCYAN}${DEP_D}${DF}"

${OBJ_D}:
	@mkdir ${OBJ_D}
	@echo "${BCYAN}mkdir${DF} ${BCYAN}${OBJ_D}${DF}"

${DEP_D}:
	@mkdir ${DEP_D}
	@echo "${BCYAN}mkdir${DF} ${BCYAN}${DEP_D}${DF}"

#<---------------------------------|PHONY|------------------------------------>#

clean:
	@echo "${BCYAN}### LIBFT fclean ###${DF}"
	@make fclean -C Libft --no-print-directory
	@echo "${BCYAN}### LIBFT cleaned ---${DF}\n"
	@rm -rf ${OBJ_D} ${DEP_D}
	@echo "${RED}rm -rf${DF} ${BIGREEN}OBJECTS: ${OBJ_F}${DF}"
	@echo "${RED}rm -rf${DF} ${BYELLOW}DEPENDENCIES: ${DEP_F}${DF}"

fclean: clean
	@rm -rf ${NAME}
	@echo "${RED}rm -rf${DF} ${RED}PROGRAM: ${NAME}${DF}\n"

re: fclean all

-include ${DEP}

.PHONY: all clean fclean re
#<---------------------------------------------------------------------------->#
