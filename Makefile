GNL= gnl/get_next_line_bonus.c
NAME= mini.a
SRC= $(GNL) cub3d.c utils.c check_rutas_lines.c check_sfc_lines.c check_mapa_lines.c check_mapa_lines2.c sprites.c screenshot.c
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
	@echo "\n\033[32m"Pulsa \(ESCAPE\) para detener.\\n*------------------------------------------------------------------------------------*"\033[0m\n"
	@gcc -Wall -Wextra -Werror -fsanitize=address -g3 -lmlx -framework OpenGL -framework AppKit $(SRC) libft.a libmlx.a -o cub3D
	@rm -rf cub3D.dSYM

all: $(NAME)

clean:
	@rm -f $(NAME) $(OBJ) ./cub3D
	@rm -rf minilibx_opengl_20191021 libmlx.a libft.a cub3D.dSYM
	@make -sC ./opengl/ clean
	@make -sC ./libft/ fclean
	@clear
	@echo "\n\033[32m"*------------------------------------------------------------------------------------*\\nBorrando los siguientes ficheros :\\n"\033[33m"$(NAME) $(OBJ) libft.a libmlx.a ./cub3D cub3D.dSYM"\033[0m\n"
	@echo "\n\033[32m"Todo depurado correctamente ✅\\n*------------------------------------------------------------------------------------*\\n"\033[0m\n"

fclean: clean
	
re: clean all

.PHONY: all clean re run
