#include "kernel/param.h"
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char* argv[])
{
    char* command[MAXARG];
    if(argc <= 2 || argv[1][0] == '-')
    {
        printf("incorrect usage of strace, exiting\n");
        exit(1);
    }
    int mask_arg = atoi(argv[1]);
    if(trace(mask_arg) <0)
    {
        printf("error in strace.c, requesting kernel to engage `trace` failed, exiting\n");
        exit(1);
    }

    //if control reaches here that means inputs and args are fine, set up for exec
    for(int i = 2; i< argc; i++)
    {
        command[i-2] = argv[i];
    }
    //real exec-ing
    exec(command[0], command);
    exit(0);
}