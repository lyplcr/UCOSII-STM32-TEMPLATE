#define PRINT_GLOBALS
#include "usart.h"
#include "main.h"


/************************************************************************/
/*  ���ڴ�ӡ����                                                        */
/************************************************************************/ 
void print_init(void)
{
	uart_init(115200);
}
