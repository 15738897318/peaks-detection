/*
* 2016-5-30
* ���� ����-����ҵ��ʹ��-��ֹ���� 3.0 ������� 
*/

#include "find_peak.h"
#include "find_peak.c"

int sig[MAX_SIGNAL_LEN];  //ԭʼ���� 
int filter_sig[MAX_SIGNAL_LEN]; //�˲�������� 
int peaks[MAX_SIGNAL_LEN];   //����λ������ 
int troughs[MAX_SIGNAL_LEN];   // ����λ�� 

int main(){
	char inputfile_name[30] = "test-data/y01.dat";
	char outputfile_name[30] = "test-data/out.dat";
	
	int i,n1,n2,n3,n4;
	
	FILE *input_file = fopen(inputfile_name,"r");
	FILE *output_file = fopen(outputfile_name,"w");
	if(input_file == NULL){
		fprintf(stderr,"�����ļ�������\n");
		exit(1);
	}
	
	n1 = input_signal(sig,input_file);  //���� 
	
	process(sig,n1);  //����Ԥ��������ƫ�� 
	
	n2 = mean_filter(sig,n1,filter_sig,6);  //��ֵ�˲� 
	//n2 = median_filter(filter_sig,n2,filter_sig,9);   //��ֵ�˲� 
	
	printf("%s�Ľ����\n\n",inputfile_name);
	
	output_signal(filter_sig,n2,output_file) ;  //�����˲�������� 
	printf("�˲���������Ѿ��������ļ� %s ��\n",outputfile_name);
	
	n3 = find_peaks(filter_sig,n2,peaks);  //���� 
	n4 = find_troughs(filter_sig,n2,troughs);   //���� 

	printf("\n�˲��󲨷�λ�ã�\n");
	for(i=0;i<n3;i++)
		printf("%d ",peaks[i]+1);  //�±��1��ʼ������Ҫ+1 
	printf("\n");
	printf("\n�˲��󲨹�λ�ã�\n");
	for(i=0;i<n4;i++)
		printf("%d ",troughs[i]+1);
	printf("\n");
}
