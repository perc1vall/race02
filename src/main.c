#include <stdio.h>
#include "matrix.h"

int main(int argc, char **argv) {
    if(argc<4) {
        mx_printerr(
                "usage: ./race02 [operand1] [operation] [operand2] [result]\n");
        return 0;
    }
    int len = mx_strlen(argv[2]);
    if (len!=1) {
        mx_printerr("Invalid operation: ");
        mx_printerr(argv[2]);
        mx_printerr("\n");
        exit(0);
    }
    if (argv[2][0]!='+'&&argv[2][0]!='-'&&argv[2][0]!='*'&&argv[2][0]!='/') {
        mx_printerr("Invalid operation: ");
        mx_printerr(argv[2]);
        mx_printerr("\n");
        exit(0);
    }
    char **op = (char **)malloc(sizeof(char*)*4);
    op[0]=argv[1];
    op[1]=argv[2];
    op[2]=argv[3];
    op[3]=argv[4];
    matrix_body((const char **) op);
    return 0;
}

