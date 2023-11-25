#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "board.h"
#include "board.c"

#define MAX_CHARNAME  200
#define N_PLAYER      3
#define MAX_DIE       6

#define PLAYERSTATUS_LIVE  0
#define PLAYERSTATUS_DIE   1
#define PLAYERSTATUS_END   2

int player_position[N_PLAYER];//��ġ 
char player_name[N_PLAYER][MAX_CHARNAME]; //�̸� 
int player_coin[N_PLAYER];//�������� �� 
int player_status[N_PLAYER];//���� ���� 0-live,1-die,2-end 
char player_statusString[3][MAX_CHARNAME]={"LIVE", "DIE", "END"}; //���� ���� ���ڿ� 

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

void opening(void)
{
	printf("===================\n");
	printf("====game start!====\n");
	printf("===================\n");
	
}

int rolldie(void)
{
	return rand()%MAX_DIE+1;
}

void printPlayerPosition(int player)
{
	int i;
	
	for(i=0;i<N_BOARD;i++)
	{
		printf("|");
		if(i==player_position[player])
			printf("%c",player_name[player][0]);
		else
		{
			if (board_getBoardStatus(i)==BOARDSTATUS_NOK)
				printf("x");
			else
				printf(" ");
		}
	}
	printf("|\n");
}

void printPlayerStatus(void)
{
	int i;
	printf("player status ---\n");
	for (i=0;i<N_PLAYER;i++)
	{
		printf("%s: pos %i, coin %i, status %s\n", player_name[i], player_position[i], player_coin[i], player_statusString[player_status[i]]);
	}
	printf("-----------------\n");
}

void checkDie(void)
{
	int i;
	for(i=0;i<N_PLAYER;i++)
		if(board_getBoardStatus(player_position[i])==BOARDSTATUS_NOK)
		{
			player_status[i]=PLAYERSTATUS_DIE;
			printf("%s in pos %i has died!! (coin %i)\n", player_name[i], player_position[i], player_coin[i]);
		}
}
			
int game_end(void)
{
	int i;
	int flag_end=1;
	
	//if all the player are died?
	for (i=0;i<N_PLAYER;i++)
	{
		if (player_status[i]==PLAYERSTATUS_LIVE)
		{
			flag_end=0;
			break;
		}
	}
	return flag_end;
}

int getAlivePlayer(void)
{
	int i;
	int cnt=0;
	for(i=0;i<N_PLAYER;i++)
	{
		if(player_status[i]==PLAYERSTATUS_END)
			cnt++;
	}
	pirntf("the number of survivors:%i\n",cnt);
}

int getWinner(void)
{
	int i;
	int winner=0;
	int max_coin=-1;
	
	for (i=0;i<N_PLAYER;i++)
	{
		if(player_coin[i]>max_coin)
		{
			max_coin=player_coin[i];
			winner=i;
		}
	}
	printf("Winner is %s\n",i);
}


int main(int argc, char *argv[]) {
	int i;
	int turn=0;
	int pos=0;
	
	
	srand((unsigned)time(NULL));
	
	//0. opening
	opening();
	//1. �ʱ�ȸ&�÷��̾� �̸� ���� 
	board_initBoard(); 
	//1-2 �÷��̾� �ʱ�ȭ 
	for (i=0;i<N_PLAYER;i++) 
	{
	 	player_position[i]=0;
	 	player_coin[i]=0;
	 	player_status[i]=PLAYERSTATUS_LIVE;
	 	//�÷��̾� �̸� 
	 	printf("player %i's name:",i);
	 	scanf("%s",player_name[i]);
	}
	
	//2. �ݺ��� (�÷��̾� ��)

	do{
	int step;
	int coinResult;
	char c;
	
	if(player_status[turn] !=PLAYERSTATUS_LIVE)
	{
		turn=(turn+1)%N_PLAYER;
		continue;
	}
	
	//2-1. ����, �÷��̾��� ���� ���
	board_printBoardStatus();
	
	for (i=0;i<N_PLAYER;i++)
	 	printPlayerPosition(i);
	printPlayerStatus();
	
	  
	 //2-2. �ֻ��� ������
	printf("%s turn!!", player_name[turn]);
	printf("press any key to roll a die!\n");
	scanf("%d",&c);
	fflush(stdin);
	step=rolldie();
	pos+=step;
	 
	 //2-3. �̵�
	player_position[turn]+=step;
	if(player_position[turn]>=N_BOARD)
		player_position[turn]=N_BOARD-1;
	
	if(player_position[turn]==N_BOARD-1)
		player_status[turn]= PLAYERSTATUS_END;
		
	printf("Die result: %i, a moved to %i\n",step,player_position[turn]);
	
	
 
	 //2-4. ���� �ݱ�
	coinResult=board_getBoardCoin(pos);
	player_coin[turn]+=coinResult;
	if(coinResult!=0)
		{
		printf("-> Lucky! a got %i coins\n", coinResult);
		}
	
	 //2-5. ������
	turn=(turn+1)%N_PLAYER;//wrap around �� ��� ����
	 
	 //2-6. if(����: ��� �÷��̾ �ѹ� �� ���� �� ����) ��� ���� 
	 if(turn==0)
	 {
	 	//����
	 	int shark_pos=SHARK_INITPOS;
	 	shark_pos=board_stepShark();
		printf("shark moved to %i\n", shark_pos);
		checkDie();
		
	 }
	}while(game_end()==0);
	
	//3. ����(���� ���, ���)
	getAlivePlayer();
	for (i=0;i<N_PLAYER;i++)
	{
		if (player_status[i]==PLAYERSTATUS_END)
		printf("GAME END!!!");
		else
		getWinner();
	}
	
	return 0;
}
