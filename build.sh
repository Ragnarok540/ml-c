set -xe

mkdir -p bin

clang -Wall -Wextra -o bin/twice src/twice.c -lm
clang -Wall -Wextra -o bin/gates src/gates.c -lm
clang -Wall -Wextra -o bin/xor src/xor.c -lm
clang -Wall -Wextra -o bin/nn src/nn.c -lm
