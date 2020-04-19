#include "matrix.h"

int mx_strlen(const char *s) {
    if (s == NULL)
        return 0;
    char *tmp = (char *) s;
    while (*tmp) tmp++;
    return (int) (tmp - s);
}

void mx_printchar(char c) {
    write(1, &c, 1);
}

void mx_printerr(const char *s) {
    write(2, s, mx_strlen(s));
}

void mx_printint(int n) {
    if (n == 0) {
        mx_printchar('0');
        return;
    }
    int buf = n;
    int len = 0;
    while (n != 0) {
        n /= 10;
        len++;
    }
    n = buf;
    if (buf < 0) {
        len++;
        n *= -1;
    }
    char res[len];
    int bufl = len;
    while (n != 0) {
        res[len - 1] = (char) (n % 10 + '0');
        len--;
        n /= 10;
    }
    if (buf < 0)
        res[0] = '-';
    for (int i = 0; i < bufl; ++i) {
        mx_printchar(res[i]);
    }
}


void mx_printstr(const char *s) {
    write(1, s, mx_strlen(s));
}

bool mx_isdigit(int c) {
    return (c>=48&&c<=57);
}

bool mx_isspace(int c) {
    return (9 <= c && c <= 13) || (c==32);
}

char *mx_atoi(const char *str) {
    int len = 0;
    char *buf = (char *) str;
    char *strbuf = (char*) str;
    while (*buf != '\0' && mx_isspace(*buf)) {
        buf++;
    }
    if (*buf == '\0') {
        mx_printerr("Invalid operand: ");
        mx_printerr(strbuf);
        mx_printerr("\n");
        exit(0);
    }
    char *buf1 = buf;
    int minus = 0;
    int sign = 0;
    while (*buf != '\0' &&
           (mx_isdigit(*buf) ||
            ((*buf == 45 || *buf == '+') && sign == 0))) {
        if (*buf == 45 && sign == 0) {
            minus = 1;
            len--;
            buf1++;
        }
        if (*buf == '+' && sign == 0) {
            len--;
            buf1++;
        }
        if (sign == 0)
            sign++;
        len++;
        buf++;
    }
    while (*buf!='\0') {
        if(mx_isspace(*buf)) {
            mx_printerr("Invalid operand: ");
            mx_printerr(strbuf);
            mx_printerr("\n");
            exit(0);
        }
    }
    int res = 0;
    for (int i = 0; i < len; ++i) {
        int dig = 1;
        for (int j = 0; j < len - 1 - i; ++j) {
            dig *= 10;
        }
        res += ((*buf1 - '0') * dig);
        buf1++;
    }
    if (minus)
        res *= -1;
    int n=res;
    int buf3 = n;
    int len3 = 0;
    while (n != 0) {
        n /= 10;
        len3++;
    }
    n = buf3;
    if (buf3 < 0) {
        len3++;
        n *= -1;
    }
    char *res3=(char*)malloc((len3+1)*sizeof(char));
    while (n != 0) {
        res3[len3 - 1] = (char) (n % 10 + '0');
        len--;
        n /= 10;
    }
    if (buf3 < 0)
        res3[0] = '-';
    res3[len3]='\0';
    return res3;
}

int dig_giver(const char *str, const int *arr, int iter) {
    int res = 0;
    int len = mx_strlen(str);
    for (int i = 0; str[i] != '\0'; ++i) {
        int buf = 0;
        if (str[i] == '?') {
            if (iter >= arr[i]) {
                buf = iter / arr[i];
                iter %= arr[i];
                if (i == 0 && len > 1)
                    buf++;
            } else if (i == 0 && len > 1)
                buf = 1;
        } else
            buf = str[i] - '0';
        res = res * 10 + buf;
    }
    int ten = 1;
    for (int i = 0; i < len; ++i) {
        ten *= 10;
    }
    if (res >= ten && len==1) {
        res %= ten;
    }
    if (res > ten && len > 1) {
        res %= ten;
        res = res + ten / 10;
    }
    return res;
}

char operation_giver(const char *str, const int *arr, int i) {
    if (str[0] == '?') {
        int buf1 = i / arr[0];
        switch (buf1 % 4) {
            case 0:
                return '+';
            case 1:
                return '-';
            case 2:
                return '*';
            case 3:
                return '/';
        }
    }
    return (char) str[0];
}

int **arr_giver(const char **op) {
    int lenop[4] = {mx_strlen(op[0]), mx_strlen(op[1]), mx_strlen(op[2]),
                    mx_strlen(op[3])};
    int minus[4] = {0,0,0,0};
    if(op[0][0]=='-') minus[0]++;
    if(op[2][0]=='-') minus[2]++;
    if(op[3][0]=='-') minus[3]++;
    int **arrbuf = (int **) malloc(4 * sizeof(int *));
    arrbuf[0] = (int *) malloc((lenop[0]-minus[0]) * sizeof(int));
    arrbuf[1] = (int *) malloc(lenop[1] * sizeof(int));
    arrbuf[2] = (int *) malloc((lenop[2]-minus[2]) * sizeof(int));
    arrbuf[3] = (int *) malloc((lenop[3]-minus[3]) * sizeof(int));
    int x = 1;
    for (int i = 3; i >= 0; --i) {
        for (int j = minus[i]; j < lenop[i] && i != 1; ++j) {
            if (op[i][lenop[i] - 1 - j] == '?') {
                arrbuf[i][lenop[i] - 1 - j] = x;
                x *= 10;
            } else
                arrbuf[i][lenop[i] - 1 - j] = 0;
        }
    }
    if (op[1][0] == '?')
        arrbuf[1][0] = x;
    else
        arrbuf[1][0] = 0;
    return arrbuf;
}


bool add_check(int a, int b, int res) {
    return (a + b) == res;
}

bool sub_check(int a, int b, int res) {
    return (a - b) == res;
}

bool mul_check(int a, int b, int res) {
    return (a * b) == res;
}

bool div_check(int a, int b, int res) {
    return (b == 0) ? false : (a / b) == res;
}

int iter_max_giver(const char **op) {
    int lenop[4] = {mx_strlen(op[0]), mx_strlen(op[1]), mx_strlen(op[2]),
                    mx_strlen(op[3])};
    int minus[4] = {0,0,0,0};
    if(op[0][0]=='-') minus[0]++;
    if(op[2][0]=='-') minus[2]++;
    if(op[3][0]=='-') minus[3]++;
    int x = 1;
    for (int i = 0; i < 4; ++i) {
        for (int j = minus[i]; j < lenop[i]; ++j) {
            if (op[i][j] == '?') {
                if (i != 1) {
                    if (j == 0 && lenop[i] > 1) x *= 9;
                    else
                        x *= 10;
                } else {
                    x *= 4;
                }
            }
        }
    }
    return x;
}

void matrix_body(const char **op) {
    int **arr = arr_giver((const char **) op);
    int mop0 = 0;
    if(op[0][0]=='-') mop0++;
    int mop1 = 0;
    if(op[2][0]=='-') mop1++;
    int mres = 0;
    if(op[3][0]=='-') mres++;
    int max = iter_max_giver((const char **) op);
    for (int i = 0; i < max; ++i) {
        int op0 = dig_giver(op[0]+mop0, arr[0], i);
        char operation = operation_giver(op[1], arr[1], i);
        int op1 = dig_giver(op[2]+mop1, arr[2], i);
        int res = dig_giver(op[3]+mres, arr[3], i);
        bool to_out = false;
        if (mop0==1)
            op0*=-1;
        if (mop1==1)
            op1*=-1;
        if (mres==1)
            res*=-1;
        switch (operation) {
            case '+':
                to_out = add_check(op0, op1, res);
                break;
            case '-':
                to_out = sub_check(op0, op1, res);
                break;
            case '*':
                to_out = mul_check(op0, op1, res);
                break;
            case '/':
                to_out = div_check(op0, op1, res);
                break;
        }
        if (to_out) {
            mx_printint(op0);
            mx_printchar(' ');
            mx_printchar(operation);
            mx_printchar(' ');
            mx_printint(op1);
            mx_printstr(" = ");
            mx_printint(res);
            mx_printchar('\n');
        }
    }
}

