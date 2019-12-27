#include <stdio.h>
#include <signal.h>

void handler(int sig);

void handler(int sig)
{
        signal(sig, handler);
        printf("Receive signal: %d\n", sig);
}

int main(void) {
        signal(SIGHUP, handler);

        while (1)
        {
                sleep(1);
        }
        return 0;
}


/** 
 * signal SIGHUP
 * handle SIGHUP noprint 
 * signal 0
 * ptype $_siginfo
 * ptype $_siginfo._sifields._sigfault
 * p $_siginfo._sifields._sigfault.si_addr
 * https://sourceware.org/gdb/onlinedocs/gdb/Signals.html
 * https://coderwall.com/p/wyb2ug/how-fix-the-no-symbol-table-is-loaded-gdb-issue-on-mountain-lion
 * Follow the following 2 steps:
        Make sure the optimization level is -O0
        Add -ggdb flag when compiling your program
 */