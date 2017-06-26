#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"	
#include "includes.h"

#include "main.h"

/////////////////////////UCOSII�����ջ����///////////////////////////////////
//START ����
//�����������ȼ�
#define START_TASK_PRIO      			10 //��ʼ��������ȼ�����Ϊ���
//���������ջ��С
#define START_STK_SIZE  				64
//���������ջ�ռ�	
OS_STK START_TASK_STK[START_STK_SIZE];
//�������ӿ�
void start_task(void *pdata);	
 			   
//LED1����
//�����������ȼ�
#define LED1_TASK_PRIO       			7 
//���������ջ��С
#define LED1_STK_SIZE  		    		64
//���������ջ�ռ�	
OS_STK LED1_TASK_STK[LED1_STK_SIZE];
//�������ӿ�
void led1_task(void *pdata);

//LED2����
//�����������ȼ�
#define LED2_TASK_PRIO       			6 
//���������ջ��С
#define LED2_STK_SIZE  					64
//���������ջ�ռ�	
OS_STK LED2_TASK_STK[LED2_STK_SIZE];
//�������ӿ�
void led2_task(void *pdata);

void print_init(void);


 int main(void)
 {
	delay_init();	     //��ʱ��ʼ��	  
	NVIC_Configuration(); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	print_init();
	LED_Init();		  	 //��ʼ����LED���ӵ�Ӳ���ӿ�
	
	OSInit();   
	OSTaskCreate(   //������ʼ����
		(void(*)(void *))&start_task,
		(void *)0,
		(OS_STK *)&START_TASK_STK[START_STK_SIZE - 1],
		(INT8U)START_TASK_PRIO
		);
	
	OSStart();
 }


void start_task(void *pdata)
{
    OS_CPU_SR cpu_sr=0;
	pdata = pdata; 
	OSStatInit();					//��ʼ��ͳ������.�������ʱ1��������	
 	OS_ENTER_CRITICAL();			//�����ٽ���(�޷����жϴ��)    
 	OSTaskCreate(
 	    (void(*)(void *))&led1_task,
		(void *)0,
		(OS_STK*)&LED1_TASK_STK[LED1_STK_SIZE-1],
		(INT8U)LED1_TASK_PRIO
	);
 	OSTaskCreate(
 	    (void(*)(void *))&led2_task,
		(void *)0,
		(OS_STK*)&LED2_TASK_STK[LED2_STK_SIZE-1],
		(INT8U)LED2_TASK_PRIO
	);

#if DEBUG
	printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
	printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
	printf("This system is UCOSII example.\n");
	printf("The version is V%d.%d.%d\n", VERSION_H, VERSION_M, VERSION_L);
	printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
	printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
#endif

	OSTaskSuspend(START_TASK_PRIO);	//������ʼ����.
	OS_EXIT_CRITICAL();				//�˳��ٽ���(���Ա��жϴ��)
}


void led1_task(void *pdata)
{	 
	INT8U time = 0;
	while(1)
	{
		time++;

#if DEBUG
		printf("%d:hello world\n", time);
#endif

		LED0=0;
		OSTimeDlyHMSM(0,0,0,80);
		LED0=1;
		OSTimeDlyHMSM(0,0,0,920);
	}
}


void led2_task(void *pdata)
{	  
	while(1)
	{
// 		LED1=0;
// 		OSTimeDlyHMSM(0,0,0,300);
		LED1=1;
		OSTimeDlyHMSM(0,0,0,300);
	}
}



