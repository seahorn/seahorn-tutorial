#include <seahorn/seahorn.h>
#include <stdlib.h>


extern int nd(void);
extern int nd_ch(void);

#define N 8

int main(void) {
    char pwd[N]; // secret.
    short pwd_taint[N] = {0};
    int i;

    char input[N]; // public.

    // initialize pwd.
    for(i = 0; i < N-1; i++) {
        int pwd_ch = nd_ch();
        assume(pwd_ch > 32);
        assume(pwd_ch < 127);
        pwd[i] = pwd_ch;

        pwd_taint[i] = 1;
        if (nd()) { break; }
    }
    pwd[i] = '\0';

    // initialize input
    for(i = 0; i < N-1; i++) {
        int in_ch = nd_ch();
        assume(in_ch > 32);
        assume(in_ch < 127);
        input[i] = in_ch;
        if (nd()) { break; }
    }
    input[i] = '\0';


    // now compare the two.
    int bad = 0;
    int j = 0;

    short bad_taint = 0;
    short j_taint = 0;
    while(j < N)
    {
        if (pwd[j] != input[j])
        {
            bad = 1;
            // bad might be tainted because the assignment is control
            // dependent on a possibly tainted condition
            bad_taint = pwd_taint[j];
            break;
        }

        if (!pwd[j] || !input[j])
            break;

        j++;
        // the value of j is dependent on possibly tainted control
        j_taint = pwd_taint[j];
    }

    printf("pwd: %s, input %s\n", pwd, input);
    // check that the value of variable j is not tainted on exit
    sassert (j_taint == 0);
    return 0;
}
