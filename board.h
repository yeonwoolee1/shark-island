#define N_BOARD            15 //보드 칸 갯수 

#define BOARDSTATUS_OK      1//보드 괜찮 
#define BOARDSTATUS_NOK     0//보드 파손





int board_initBoard(void); //보드 초기화 
int board_printBoardStatus(void);//전체 보드의 상태 출력 

int board_getBoardStatus(int pos);//특정 칸의 파손 여부 출력
int board_getBoardCoin(int pos);//동전 습득 명령 

int board_getSharkPosition(void);//상어의 위치 출럭 
int board_stepShark(void);//상어 전진 명령 

