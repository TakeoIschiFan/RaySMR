set -xe

CC="clang"
CFLAGS="-Wall -Wextra"
LIBS=""
SRC="main.c"

$CC $CFLAGS -o raysmr $SRC $LIBS



