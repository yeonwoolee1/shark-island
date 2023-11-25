#include <stdio.h>
#include <stdlib.h>
#include "board.h"

#define N_BOARD            15 //���� ĭ ���� 
#define N_COINPOS          12
#define MAX_COIN           4

#define MAX_SHARKSTEP      6
#define SHARK_INITPOS      -2


static int board_status[N_BOARD]; 
static int board_coin[N_BOARD];

static int board_sharkposition; 
 


int board_initBoard(void)  //���� �ʱ�ȭ 
{
	int i; 
	for(i=0;i<N_BOARD;i++)
	{
		board_status[i]=BOARDSTATUS_OK;
		board_coin[i]=0;
	}
	
	board_sharkposition=SHARK_INITPOS;
	
	//���� �Ҵ� 
	for(i=0;i<N_COINPOS;i++)
	{	int flag=0;
		while(flag==0)
		{
			int allocPos=rand()%N_BOARD;
			if(board_coin[allocPos]==0)//i���� ���� �Ҵ� 
			{
				board_coin[allocPos]=rand()%MAX_COIN+1;
				flag=1;
			}
		}
	}

	return 0;
}

int board_printBoardStatus(void)  //��ü ������ ���� ��� 
{
	int i;
	
	printf("==========BOARD STATUS==========\n");
	for (i=0;i<N_BOARD;i++)
	{
		printf("|");
		if(board_status[i]==BOARDSTATUS_NOK)
			printf("x");
		else
			printf("o");
			
	}
	printf ("|\n");
	printf("=================================\n");
	
	return 0; 
}


int board_getBoardStatus(int pos)  //Ư�� ĭ�� �ļ� ���� ���
{
	return board_status[pos];	
}

int board_getBoardCoin(int pos)  //���� ���� ��� 
{
	int coin = board_coin[pos];
	board_coin[pos]=0;
	return coin;
}


//int board_getSharkPosition(void);  //����� ��ġ �ⷰ 
int board_stepShark(void)//��� ���� ���  
{
	int step =rand()%MAX_SHARKSTEP+1;
	int i;
	for(i=0;i<=board_sharkposition+step;i++)
	{ 
		if (i>=0 && i<N_BOARD)
			board_status[i]=BOARDSTATUS_NOK;
	}
	board_sharkposition+=step;
	
	return board_sharkposition;
}






