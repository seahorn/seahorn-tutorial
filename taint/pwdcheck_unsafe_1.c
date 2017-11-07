#include <seahorn/seahorn.h>
#include <stdlib.h>

extern int nd(void);
extern char nd_ch(void);

// -- marks memory as secret
extern void ifc_set_secret(int *ch);

#define N 8

int main(void) {
    // secret password
    char pwd[N];
    // public input
    char input[N];

    int i;

    // initialize password with non-deterministic input of size N
    for(i = 0; i < N-1; i++) {
        char pwd_ch = nd_ch();
        ifc_set_secret(&pwd_ch);
        // require password to be a printable ASCII character
        assume(pwd_ch > 32 && pwd_ch < 127);
        pwd[i] = pwd_ch;
        // leave part of password uninitialized
        if (nd()) { break; }
    }
    // zero-terminate password
    pwd[i] = '\0';

    // initialize input
    for(i = 0; i < N-1; i++) {
        input[i] = nd_ch();
        // require input to be a printable ASCII character
        assume((int)input[i] > 32 && (int)input[i] < 127);
        if (nd()) { break; }
    }
    // zero terminate input
    input[i] = '\0';


    // Compare input to the password
    int bad = 0;
    int j = 0;
    while (j < N) {
        if (pwd[j] != input[j]) {bad = 1; break;}
        if (!pwd[j] || !input[j]) break;
        j++;
    }

    // does the value of j leaks anything about password?
    printf("pwd=%s", pwd);

    return 0;
}
