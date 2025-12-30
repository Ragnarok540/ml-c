set -xe

mkdir -p bin

clang -Wall -Wextra -o bin/twice twice.c -lm
clang -Wall -Wextra -o bin/gates gates.c -lm
clang -Wall -Wextra -o bin/xor xor.c -lm
