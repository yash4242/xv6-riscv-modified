#include "kernel/param.h"
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char* argv[])
{
	if(argc != 3)
	{
		printf("incorrect usage\n");
		exit(0);
	}
	int prio = atoi(argv[1]);
	int whichpid = atoi(argv[2]);

	set_priority(prio, whichpid);
	exit(0);

}