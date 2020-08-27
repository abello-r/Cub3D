
NAME= mini.a
SRC= eventos.c utils.c 
SRC+= 
OBJ1=$(SRC:.c=.o)
OBJ=$(OBJ1:.m=.o)

$(NAME):	$(OBJ)
	@make -sC ./opengl/
		@cp opengl/libmlx.a .
	@make -sC ./libft/
		@cp libft/libft.a .
	@ar -rc $(NAME) $(OBJ)
	@ranlib $(NAME)

run:
	@clear
	@echo "\n\033[32m"*------------------------------------------------------------------------------------*\\nTienes ejecutando los archivos :" \033[33m"$(SRC) libft.a libmlx.a"\033[0m\n"
	@echo "\n\033[32m"Pulsa \(CTRL + C\) para detener.\\n*------------------------------------------------------------------------------------*"\033[0m\n"
	@gcc -Wall -Wextra -Werror -lmlx -framework OpenGL -framework AppKit $(SRC) libft.a libmlx.a && ./a.out
	

all: $(NAME)

clean:
	@rm -f $(NAME) $(OBJ) ./a.out *~
	@rm -rf minilibx_opengl_20191021 libmlx.a libft.a
	@make -sC ./opengl/ clean
	@make -sC ./libft/ fclean
	@clear
	@echo "\n\033[32m"*------------------------------------------------------------------------------------*\\nBorrando los siguientes ficheros :" \033[33m"$(NAME) $(OBJ) libft.a libmlx.a ./a.out"\033[0m\n"
	@echo "\n\033[32m"Todo depurado correctamente ✅\\n*------------------------------------------------------------------------------------*\\n"\033[0m\n"
	
re: clean all

.PHONY: all clean re run