#!/bin/sh

while [[ "$1" =~ ^- && ! "$1" == "--" ]]; do case $1 in
  -t | --test )
	rm -fr std.txt ft.txt && make fclean
	make DEF="-D NS=std" vector_test && make DEF="-D NS=std" map_test \
	&& make DEF="-D NS=std" stack_test && make DEF="-D NS=std" set_test
	./vector_test >> std.txt && ./map_test >> std.txt && ./stack_test >> std.txt \
	&& ./set_test >> std.txt

	make clean
	make DEF="-D NS=ft" vector_test && make DEF="-D NS=ft" map_test \
	&& make DEF="-D NS=ft" stack_test && make DEF="-D NS=ft" set_test
	./vector_test >> ft.txt && ./map_test >> ft.txt && ./stack_test >> ft.txt \
	&& ./set_test >> ft.txt

	diff std.txt ft.txt
    exit
    ;;
  -m | --main )

	rm -fr std.txt ft.txt && make fclean
	make DEF="-D NS=1" ft_containers && ./ft_containers 0 > std.txt

	make clean
	make DEF="-D NS=0" ft_containers && ./ft_containers 0 > ft.txt

	diff std.txt ft.txt
    exit
    ;;
  -v | --vocabulary_and_test )
	rm -fr std.txt ft.txt && make fclean
	make DEF="-D NS=std" vocabulary_and_time && ./vocabulary_and_time Yudkowsky_Eliezer_Harry_Potter_and_the_Methods_of_Rationality.txt > std.txt

	make clean
	make DEF="-D NS=ft" vocabulary_and_time && ./vocabulary_and_time Yudkowsky_Eliezer_Harry_Potter_and_the_Methods_of_Rationality.txt > ft.txt

	diff std.txt ft.txt
    exit
    ;;
esac; shift; done
if [[ "$1" == '--' ]]; then shift; fi

echo "usage: ./test.sh [-tmv]"
echo "\nt : running vector_test, map_test, stack_test and set_test (std/ft),\n    writing outputs (std.txt/ft.txt),\n    comparing (std.txt/ft.txt using diff)"
echo "\nm : running ft_containers (std/ft) using main — https://projects.intra.42.fr/uploads/document/document/10932/main.cpp,\n    writing outputs (std.txt/ft.txt),\n    comparing (std.txt/ft.txt using diff)"
echo "\nv : running vocabulary (std/ft) using 'Yudkowsky_Eliezer_Harry_Potter_and_the_Methods_of_Rationality.txt',\n    writing outputs (std.txt/ft.txt),\n    comparing (std.txt/ft.txt using diff)"

