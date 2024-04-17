/*
 * Debug GL 2.1 No extensions
 *
 * GLAD: $GLAD --out-path=$tmp --api="gl:compatibility=2.1" --extensions="" c --loader --debug
 * COMPILE: $GCC $test -o $tmp/test -I$tmp/include $tmp/src/gl.c -ldl
 * RUN: $tmp/test
 */

#include <glad/gl.h>

int main(void) {
    return 0;
}
