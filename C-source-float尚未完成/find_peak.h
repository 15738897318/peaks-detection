/*
* 2016-5-30
* ���� ����-����ҵ��ʹ��-��ֹ���� 3.0 ������� 
*/

#ifndef	_FIND_PEAK
#define _FIND_PEAK

#include "stdio.h"
#include "stdlib.h" 

#define MAX_SIGNAL_LEN  100000 //�����źŵ���󳤶� 
#define SCALE	0.4  //��ֵ����ϵ�� 
#define NEIGHBOUR 35  //��������뾶 
#define MAX_SUB_LEN 30  //��ֵ�˲����߾�ֵ�˲�ʱ��������󳤶� 

//typedef int DataType;  //���е��������� 

//�������� 
int input_signal(int sig[],FILE *inputfile);

//�������� 
void output_signal(float sig[],int n,FILE *outputfile);

//��ֵ�˲� 
int mean_filter(int in[],int n, float out[],int k);

//��ֵ�˲� 
int median_filter(int in[],int n, float out[],int k);

//Ѱ�Ҳ��� 
int find_peaks(float sig[],int n1,int peaks[] );

//Ѱ�Ҳ��� 
int find_troughs(float sig[],int n1,int troughs[]);

#endif
