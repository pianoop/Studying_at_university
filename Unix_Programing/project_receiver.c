#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define DEFINED_KEY 0x17101213

int main (int argc, char **argv)
{
	int msg_qid;
	struct 
	{
		long mtype;
		char content[256];
	} msg;

	system("clear");
	fprintf(stdout, "======RECEIVER=======\n");
	
	if((msg_qid = msgget(DEFINED_KEY, IPC_CREAT | 0666)) < 0)
	{
		perror("msgget: ");
		exit(-1);
	}

	while(1)
	{
		memset(msg.content, 0x0, 256);
		if(msgrcv(msg_qid, &msg, 256, 0, 0) < 0)
		{
			perror("msgsnd: ");
			exit(-1);
		}
		puts(msg.content);
	}

	return 0;
}
