if [[ "$1" != "" ]]; then
    gcc -Wall -Werror -Wextra create_field.c -o create_field.out
    ./create_field.out > $1
    gcc -Wall -Werror -Wextra game_of_life.c -o game_of_life.out
    cat "$1" | ./game_of_life.out
else
    echo "input file name"
fi
