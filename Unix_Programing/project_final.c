#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <time.h>

struct msg
{
	long mtype;
	char content[256];
};

#define KEY			0x17101213

#define BUFSIZE 	256
#define CHILDSIZE	5		// 10 미만으로 설정
#define MENUSIZE	10

// transfrom Menu to Signal
#define Order_neogul	SIGINT
#define Order_jjapa		SIGQUIT
#define Order_spam		SIGILL
#define Order_kimchi	SIGFPE
#define Order_jeyuc		SIGUSR1
#define Order_cheese	SIGUSR2
#define Order_gogi		SIGPIPE
#define Order_pepsi		SIGTERM
#define Order_sprite	SIGTSTP
#define Order_AA		SIGCONT

#define Order_fail		SIGALRM
#define Order_deadline	SIGCHLD

// menu state (1: waiting, 0: not)
int 	g_menu[MENUSIZE] 		= {0, };
int		g_menu_to_sig[MENUSIZE]	= {Order_neogul, Order_jjapa, Order_spam, Order_kimchi, Order_jeyuc, Order_cheese, Order_gogi, Order_pepsi, Order_sprite, Order_AA};
int 	g_pipe_fd[2];

int 	g_score		= 0,
		g_on		= 0,
		g_fail_cnt	= 0,
		g_child,
		g_msg_qid;

char	*g_fail2_msg	=	"이 자리가 아닌가 보네...";
char	*g_fail3_msg	=	"이 메뉴가 아닌데..., 그냥 먹을게요";
char	*g_success1_msg	=	"잘 먹겠습니다~";
char	g_sys_msg[2][80]	=	{"SYS1) i번 자리에 손님이 앉았습니다.", "SYS2) i번 자리 손님이 나갔습니다, 정산: 00000원"};
char	g_order_msg[MENUSIZE][80];
char	g_menu_name[MENUSIZE][10] =	{"neogul", "jjapa", "spam", "kimchi", "jeyuc",
								"cheese", "gogi", "pepsi", "sprite", "AA"};
char    g_fail_msg[60];

time_t 	g_on_time;				// 해당 자원이 켜진 시간(이용료 계산에 사용)

void update_msg()			// child process별 주문 메시지 업데이트
{
	int 	i;
	char    fail_msg[60]	=  "그냥 취소해주세요 (time over)";
	char	prefix[20] 	=  "MsgX) i번 자리: ";
	char	msg[MENUSIZE][60]	= {"여기 너구리 하나요", "짜파게티 주문할게요",
			"참치스팸마요 주세요", "김치볶음밥 시킬게요",
			"제육덮밥 하나 주문할게요", "치즈떡볶이 하나요",
			"여기 삼겹살 시킬게요", "펩시 제로 주세요",
			"스프라이트 한 개 부탁드려요", "아이스 아메리카노 한 잔 주문이요"};
	prefix[3] = '1';
	prefix[6] = (48 + g_child);
	g_sys_msg[0][6] = 48 + g_child;
	g_sys_msg[1][6] = 48 + g_child;
	for(i = 0; i < MENUSIZE; i++)
	{
		strcat(g_order_msg[i], prefix);
		strcat(g_order_msg[i], msg[i]);
	}

	prefix[3] = '2';
	strcat(g_fail_msg, prefix);
	strcat(g_fail_msg, fail_msg);


	return;
}

void send_msg(char* str)
{
	struct msg sd;
	memset(sd.content, 0x0, BUFSIZE);
	strcat(sd.content, str);
	sd.mtype = 1;
	if(msgsnd(g_msg_qid, &sd, sizeof(sd.content), 0) < 0)
	{
		perror("msgsnd: ");
		exit(-1);
	}
}

void set_receiver()
{
	if((g_msg_qid = msgget(KEY, IPC_CREAT | 0666)) < 0)
	{
		perror("msgget: ");
		exit(-1);
	}
}

void money_to_str(int money)	// SYS2 정산금액 변경
{
	int i = 57;
	while(i > 52) 
	{
		g_sys_msg[1][i] = 48 + (money % 10);
		money /= 10;
		i--;
	}
}

int	str_to_money(char* str)
{
	int ret = (str[53]- 48)*10000 + (str[54]- 48)*1000 + (str[55]- 48)*100 + (str[56]- 48)*10 + (str[57]- 48)*1;
	
	return ret;
}

int menu_idx(int orderno)	// signal to menu_idx
{
	switch(orderno)
	{
	case Order_neogul	:
		return 0;
	case Order_jjapa	:
		return 1;
	case Order_spam		:
		return 2;
	case Order_kimchi	:
		return 3;
	case Order_jeyuc	:
		return 4;
	case Order_cheese	:
		return 5;
	case Order_gogi		:
		return 6;
	case Order_pepsi	:
		return 7;
	case Order_sprite	:
		return 8;
	case Order_AA		:
		return 9;
	default				:
		return -1;
	}
}

void menu_reset()
{
	int menu;
	for(menu = 0; menu < MENUSIZE; menu++)
		g_menu[menu] = 0;
	return;
}

void myhandler(int orderno)
{
	char c;
	int order_idx = menu_idx(orderno), money;
	signal(orderno, myhandler);

	switch(orderno)
	{
	case Order_neogul	:
	case Order_jjapa	:
	case Order_spam		:
	case Order_kimchi	:
	case Order_jeyuc	:
	case Order_cheese	:
	case Order_gogi		:
	case Order_pepsi	:
	case Order_sprite	:
	case Order_AA		:
		if(g_on == 0)
		{
			send_msg(g_fail2_msg);
			return;
		}

		c = 48 + g_child;
		write(g_pipe_fd[1], &c, 1);
		if(g_menu[order_idx] == 1)	
		{
			g_menu[order_idx] = 0;
			g_score += 1000;
			send_msg(g_success1_msg);
			alarm(0);		// count reset
		}
		else				// 메뉴를 잘못 줌
		{
			menu_reset();
			send_msg(g_fail3_msg);
			g_score += 350;
			g_on = 2;		// 다음 rand 신호 때 손님 나감
			alarm(0);
			g_fail_cnt++;
		}
		break;
	case Order_fail		:	// 메뉴를 시간 내에 주지 못함
		menu_reset();
		write(g_pipe_fd[1], g_fail_msg, 80);			// 실패 메시지를 pipe에 전달
		g_on =	2;
		g_fail_cnt++;
		break;
	case Order_deadline	:
		money = g_score + 300 * ((time(NULL) - g_on_time));
		money_to_str(money);
		write(g_pipe_fd[1], g_sys_msg[1], 80);
		exit(g_fail_cnt);
	default:
		return;
	}

	return;
}

void finish(int signo)		// parent process 게임 종료시 뒤처리
{
	if(signo == SIGALRM)
	{
		if(kill(-1, Order_deadline) < 0)	// broadcasting
		{
			printf("deadline error\n");
			exit(1);
		}
	}

	return;
}

void inputFin(int signo)
{
	exit(0);
}


int main()
{
	char	start_str[BUFSIZE];
	int		random, game_time = 60, tmp;
	pid_t	child_pid[CHILDSIZE];
	set_receiver();

	if(pipe(g_pipe_fd) < 0)
	{
		printf("pipe() error\n");
		exit(1);
	}
	system("clear");
	printf("----------- PC방 타이쿤 -----------\n");
	printf("Game 설명: 각 자리에 있는 손님들의 주문을 받아야합니다. ( %d초 동안 진행)\n", game_time);
	printf("잘못된 음식을 주거나 일정 시간이 경과된 경우 손님은 금방 자리를 떠납니다.\n");
	printf("음식을 주는 방법은 \"[자리 번호] [음식이름]\"입니다. 중간에 띄어쓰기에 주의해주세요.\n");
	printf("예시: 1번 자리에서 짜파게티를 주문한 경우)\n $ 1 jjapa\n");
	printf("입력해야하는 음식의 이름은 다음과 같습니다\n------------------------------\n");
	for(tmp = 0; tmp < MENUSIZE; tmp++)
	{
		if(tmp % 4 == 3)
			printf("\n");
		printf("%s  ",g_menu_name[tmp]);
	}
	printf("\n------------------------------\n");
	printf("각각 너구리, 짜파게티, 참치 스팸마요,\n김치볶음밥, 제육 덮밥, 치즈 떡볶이, 삽겹살,\n펩시 제로, 스프라이트, 아이스 아메리카노 입니다.\n");
	printf("메뉴 이름은 플레이 중에 다시 나오지 않으니 꼭 기억해주시길 바랍니다.\n\n\n\n\n\n");
	do
	{
		printf("1을 입력하면 게임이 시작됩니다. \n");
		fgets(start_str, BUFSIZE, stdin);
	}while(!(strlen(start_str) == 2 && start_str[0] == '1'));

	printf("----------- PC방 오픈 -----------\n");

	for(g_child = 0; g_child < CHILDSIZE; g_child++)
	{
		if((child_pid[g_child] = fork()) == 0)	// child process
		{
			int m, money;
			close(g_pipe_fd[0]);	// only use write(g_pipe_fd[1])
			srand(time(NULL) + g_child);	
			update_msg();
			signal(SIGINT, 	myhandler);
			signal(SIGQUIT, myhandler);
			signal(SIGILL, 	myhandler);
			signal(SIGFPE, 	myhandler);
			signal(SIGUSR1, myhandler);
			signal(SIGUSR2, myhandler);
			signal(SIGPIPE, myhandler);
			signal(SIGTERM, myhandler);
			signal(SIGTSTP, myhandler);
			signal(SIGCONT, myhandler);
			signal(SIGALRM, myhandler);
			signal(SIGCHLD,	myhandler);
			
			sleep((rand() & 15) + 3);	// 기다렸다가 자리에 손님 착석
			g_on = 1;
			for(;;)
			{
				if(g_on == 0)	// 꺼진 상태
				{
					sleep((rand() & 15) + 10);
					g_on = 1;
				}	
				else			// 켜진 상태(손님 입장)
				{
					write(g_pipe_fd[1], g_sys_msg[0], 60);
					g_on_time = time(NULL);	// 시작 시간 갱신
					for(;;)
					{
						if(g_on == 2)	// 손님 퇴장
						{
							sleep(rand() & 7);
							g_on = 0;
							money = g_score + 300 * ((time(NULL) - g_on_time));
							money_to_str(money);
							write(g_pipe_fd[1], g_sys_msg[1], 80);
							break;
						}
						else			// 음식 주문
						{
							sleep((rand()& 7) + 3);
							m = rand() % 10;
							g_menu[m] = 1;
							write(g_pipe_fd[1], g_order_msg[m], 80);
							alarm(10);		// 10초 경과시 주문 취소
							while(g_menu[m] == 1)
								pause();
						}
					}
				}
			}

			exit(0);
		}
	}

	char 	buf[BUFSIZE];
	if(fork() == 0)		// 입력 담당 process
	{
		close(g_pipe_fd[0]);
		close(g_pipe_fd[1]);
		signal(SIGCHLD, inputFin);
		int i;
		for(;;)
		{
			fgets(buf, BUFSIZE, stdin);
			buf[strlen(buf) - 1] = '\0';
			if(buf[0] > 47 && buf[0] < 58 && buf[1] == ' ')
			{
				for(i = 0; i < MENUSIZE; i++)
				{
					if(strcmp(&buf[2], g_menu_name[i]) == 0)
					{
						
						if(kill(child_pid[buf[0] - 48], g_menu_to_sig[i]) < 0)
						{
							printf("kill error");
							exit(1);
						}
						i = -1;
						break;
					}
				}
				if(i > 0)
					printf("입력이 잘못 되었습니다.\n");
			}
			else
			{	
				printf("입력이 잘못 되었습니다.\n");
			}
		}
	}

	int child_on_off[CHILDSIZE]= {0, };	// 해당 자리의 on / off 상태 (1, 0)
	int	child_order[CHILDSIZE] = {0, };	// 해당 자리의 주문 상태 
	int order_cnt = 0;
	srand(time(NULL) + 17);
	close(g_pipe_fd[1]);	// only use read(g_pipe_fd[0])
	signal(SIGALRM, finish);
	alarm(game_time);				// gameover after game_time


	for(;;)		// pipe 담당
	{
		if(read(g_pipe_fd[0], buf, BUFSIZE) == 0)
			break;
		if(buf[0] == 'S')
		{
			if(buf[3] == '1')
			{
				child_on_off[(buf[6] - 48)] = 1;
			}
			else
			{
				child_on_off[(buf[6] - 48)] = 0;
				g_score += str_to_money(buf);
			}
			send_msg(buf);
		}
		else if(buf[0] == 'M')
		{
			if(buf[3] == '1')
			{
				order_cnt++;
				child_order[(buf[6] - 48)] = 1;
			}
			else
			{
				child_order[buf[6] - 48] = 0;
			}
			send_msg(buf);
		}
		else
		{
			child_order[buf[0] - 48] = 0;
		}

		// 자리, 주문 갱신 시점
	}
	
	int status;
	for (g_child = 0; g_child <= CHILDSIZE; g_child++)	// 종료 전 정산 상태
	{
		if(wait(&status) < 0)
		{
			printf("wait() error\n");
			exit(1);
		}
		g_fail_cnt += WEXITSTATUS(status);
	}

	printf("----------게임 종료!----------\n");
	printf("  매출: %d 원, 주문 성공 %d 회, 주문 실패 %d 회\n", g_score, order_cnt - g_fail_cnt, g_fail_cnt);

	printf("  1 입력시 ScoreBoard 파일에 기록이 저장됩니다. (그 외 입력시 종료)\n");
	scanf("%d", &status);
	if(status == 1)
	{
		// TODO 파일 열어서(없을 시 생성) lseek로 end에 맞추고 새 기록 작성
		FILE *scores;
		time_t t;
		char *ct;
		time(&t);
		ct = ctime(&t);
		if( (scores = fopen("GameScore", "a")) == NULL)
		{
			printf("fopen error\n");
			exit(1);
		}
		
		fprintf(scores, "매출: %d 원, 주문 성공 %d 회, 주문 실패 %d 회		%s\n", g_score, order_cnt - g_fail_cnt, g_fail_cnt, ct);
		if(fclose(scores) == EOF)
		{
			printf("fclose error\n");
			exit(1);
		}
	}

	printf("플레이 해주셔서 감사합니다.\n");

	return 0;
}
