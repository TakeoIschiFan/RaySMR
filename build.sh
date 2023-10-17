set -xe

# C compiler
CC="clang"

# Flags for the C compiler.
# pkg-config is a platform-agnostic tool that finds installed packages on your system. In this case, we add raylibs cflags using pkgconfig.
CFLAGS="-Wall -Wextra `pkg-config --cflags raylib`"

# Link with raylib and math
LIBS="-lm `pkg-config --libs raylib`"
SRC="main.c"

$CC $CFLAGS -o raysmr $SRC $LIBS




