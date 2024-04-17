/*
 * GLX 1.0
 *
 * GLAD: $GLAD --out-path=$tmp --api="glx=1.0,gl:core" c --loader
 * COMPILE: $GCC $test -o $tmp/test -I$tmp/include $tmp/src/glx.c -ldl -DGLAD_GLX_NO_X11
 * RUN: $tmp/test
 */

#include <glad/glx.h>

int main(void) {
    Display *display = NULL;
    (void) gladLoaderLoadGLX(display, 0);
    (void) gladLoaderUnloadGLX();
    return 0;
}
