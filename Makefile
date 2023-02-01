NAME				=	ft_containers

VOCABULARY_AND_TIME =	vocabulary_and_time
VECTOR_TEST			=	vector_test
MAP_TEST			=	map_test
STACK_TEST			=	stack_test
SET_TEST			=	set_test

INTRA_MAIN			=	intra_main.cpp
VOCABULARY_MAIN		=	vocabulary_main.cpp
VECTOR_TEST_MAIN	=	vector_test.cpp
MAP_TEST_MAIN		=	map_test.cpp
STACK_TEST_MAIN		=	stack_test.cpp
SET_TEST_MAIN		=	set_test.cpp

TEST_TEXT			=	map.hpp

HEADERS			=	iterator.hpp \
					map.hpp \
					pair.hpp \
					RBTree.hpp \
					utils.hpp \
					vector.hpp \
					stack.hpp \
					set.hpp

INTRA_OBJ			=	${INTRA_MAIN:.cpp=.o}
VOCABULARY_OBJ		=	${VOCABULARY_MAIN:.cpp=.o}
VECTOR_TEST_OBJ		=	${VECTOR_TEST_MAIN:.cpp=.o}
MAP_TEST_OBJ		=	${MAP_TEST_MAIN:.cpp=.o}
STACK_TEST_OBJ		=	${STACK_TEST_MAIN:.cpp=.o}
SET_TEST_OBJ		=	${SET_TEST_MAIN:.cpp=.o}


FLAGS	=	-Wall -Wextra -Werror -std=c++98

DEF		=	-D NS=ft

all:		${NAME} ${VOCABULARY_AND_TIME} ${VECTOR_TEST} ${MAP_TEST} \
${STACK_TEST} ${SET_TEST}


%.o:   		%.cpp ${HEADERS}
			c++ -c ${FLAGS} ${DEF} -I. $< -o ${<:.cpp=.o}

${NAME}:		${INTRA_OBJ} Makefile ${HEADERS}
			c++ ${FLAGS} ${INTRA_OBJ} -o $@

${VOCABULARY_AND_TIME}:	${VOCABULARY_OBJ} Makefile ${HEADERS}
			c++ ${FLAGS} ${VOCABULARY_OBJ} -o $@

${VECTOR_TEST}:	${VECTOR_TEST_OBJ} Makefile ${HEADERS}
			c++ ${FLAGS} ${VECTOR_TEST_OBJ} -o $@

${MAP_TEST}:	${MAP_TEST_OBJ} Makefile ${HEADERS}
			c++ ${FLAGS} ${MAP_TEST_OBJ} -o $@

${STACK_TEST}:	${STACK_TEST_OBJ} Makefile ${HEADERS}
			c++ ${FLAGS} ${STACK_TEST_OBJ} -o $@

${SET_TEST}:	${SET_TEST_OBJ} Makefile ${HEADERS}
			c++ ${FLAGS} ${SET_TEST_OBJ} -o $@

check_leaks:	clean ${NAME} ${VOCABULARY_AND_TIME} ${VECTOR_TEST} \
${MAP_TEST} ${STACK_TEST} ${SET_TEST}
			leaks --atExit -- ./${NAME} 0
			leaks --atExit -- ./${VOCABULARY_AND_TIME} ${TEST_TEXT}
			leaks --atExit -- ./${VECTOR_TEST}
			leaks --atExit -- ./${MAP_TEST}
			leaks --atExit -- ./${STACK_TEST}
			leaks --atExit -- ./${SET_TEST}

run_test:		test.sh ${HEADERS}
				-./test.sh -t
				-./test.sh -v
				-./test.sh -m

clean:
			rm -fr ${INTRA_OBJ} ${VOCABULARY_OBJ} ${VECTOR_TEST_OBJ} \
			${MAP_TEST_OBJ} ${STACK_TEST_OBJ} ${SET_TEST_OBJ}

fclean:		clean
			rm -fr ${NAME} ${INTRA} ${VOCABULARY_AND_TIME} \
			${VECTOR_TEST} ${MAP_TEST} ${STACK_TEST} ${SET_TEST} ft.txt std.txt

re:			clean fclean all

.PHONY: all clean fclean re 
