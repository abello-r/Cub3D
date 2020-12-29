#! /bin/bash

make re
make run
./cub3D map.cub
make clean
clear
printf "\e[32mHas salido correctamente.\e[m\n"

