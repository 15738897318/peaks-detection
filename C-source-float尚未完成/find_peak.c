/*
* 2016-5-30
* ���� ����-����ҵ��ʹ��-��ֹ���� 3.0 �������
*/

#include "find_peak.h"
#include "math.h"

#define IS_EQUAL(a,b) (fabs((a)-(b))<0.0000001)

static float get_max(float sig[],int n);
static float get_min(float sig[],int n);
static int is_exist(int a[],int n,int key);
static int find_maximums(float sig[],int n,int maximums[]);
static float get_median(float a[],int n);
static int compare(float a,float b);


/*
* ��inputfile�л�ȡ�ź����У�����ֵ�Ƕ�ȡ�źŵ����� 
* sig:��ȡ�����ź����� 
*/
int input_signal(int sig[],FILE *inputfile){
	int i=0;
	while(!feof(inputfile)){
		int tmp;
		fscanf(inputfile,"%d",&tmp);
		sig[i++] =  tmp;
		if(i>= MAX_SIGNAL_LEN)
			break;
	}
	return i;
} 

/*
* ���ź�������ļ���
* sig:��������У�n:���г��ȣ�outputfile:����ļ� 
*/
void output_signal(float sig[],int n,FILE *outputfile){
	int i;
	for(i=0;i<n;i++){
		fprintf(outputfile,"%.4f",sig[i]);
		if(i<n-1)
			fprintf(outputfile," ");
	}		
}

/*
* Ѱ�Ҳ��� 
* sig���������У�n1�����г��� ��peaks[]:���沨���λ�� 
* ����ֵ�ǲ�������� 
*/
int find_peaks(float sig[],int n1,int peaks[] ){
	int maximums[MAX_SIGNAL_LEN];
	int n2 = find_maximums(sig,n1,maximums);
	float max = get_max(sig,n1);
	float min = get_min(sig,n1);
	float threshold = (max - min)*SCALE;
	int i,j,num=0;
	int found = 0;
	printf("%f %f\n",max,min);
	for(i=0;i<n2;i++){
		int index = maximums[i];
		printf("%d\n",index+1);
		if(max - sig[index] <= threshold)
			found = 1;
		else
			continue;
		for(j=index-NEIGHBOUR;j<index+NEIGHBOUR;j++){
			if(j<0 || j>=n1)
				continue;
			if(compare(sig[index] , sig[j]) == -1)
				found = 0;
			if(compare(sig[index] , sig[j]) == 0 && is_exist(peaks,num,j))
				found = 0;
		}
		if(found == 1)
			peaks[num++] = index;
	}
	return num;
}

/*
* Ѱ�Ҳ��� 
* sig���������У�n1�����г���, troughs[]:���沨�ȵ�λ�� 
* ����ֵ�ǲ��ȵ����� 
* �㷨��ԭʼ���е��෴���Ĳ������ԭʼ���еĲ��� 
*/
int find_troughs(float sig[],int n1,int troughs[] ){
	float tmp[MAX_SIGNAL_LEN];
	int i;
	for(i=0;i<n1;i++)
		tmp[i] = sig[i] * -1;
	return find_peaks(tmp,n1,troughs); 
} 

/*
* ��ֵ�˲�
* in:�������У�n:�������г���
* out:�˲������У�k:���ֵ�������г��� 
* ����ֵ���˲������г��� 
*/ 
int mean_filter(int in[],int n,float out[],int k){
	if(k > n || k > MAX_SUB_LEN){
		fprintf(stderr,"��ֵ�˲������������\n");
		exit(1);
	}
	int i,num = 0; 
	for(i=0;i<n-k+1;i++){
		float sum = 0.0;
		int tmp;
		for(tmp=i;tmp<=i+k-1;tmp++)
			sum = sum + in[tmp];
		out[num++] = sum/(k*1.0);
	}
	return num;
}

/*
* ��ֵ�˲�
* in:�������У�n:�������г���
* out:�˲������У�k:����ֵ�������г��� 
* ����ֵ���˲������г��� 
*/ 
int median_filter(int in[],int n,float out[],int k){
	if(k > n || k > MAX_SUB_LEN){
		fprintf(stderr,"��ֵ�˲������������\n");
		exit(1);
	}
	int i,num = 0;
	for(i=0;i<n-k+1;i++){
		int j,index=0;
		float tmp[MAX_SUB_LEN];
		for(j=i;j<=i+k-1;j++){
			tmp[index++] = in[j];
		}
		out[num++] = get_median(tmp,index);
	}
	return num;
}


/*
static int find_maximums(int sig[],int n,int maximums_index[]){
	int i,num=0;
	if(n<=2){
		return num;
	}
	int diff[MAX_SIGNAL_LEN]; //���
	int tmp=0;
	for(i=1;i<n;i++){
		if(sig[i] - sig[i-1] > 0)
			diff[tmp++] = 1;
		else if(sig[i] - sig[i-1] == 0)
			diff[tmp++] = 0;
		else
			diff[tmp++] = -1;		 
	}
	for(i=1;i<tmp;i++){ //�ڶ��β���󼫴�ֵ 
		if(diff[i] - diff[i-1] < 0)
			maximums_index[num++] = i; 
	}
	return num;	
}*/

/*
* Ѱ��sig[]�еļ���ֵ������ 
* ��������� maximums�У����ص��Ǽ�ֵ������ 
*/
static int find_maximums(float sig[],int n,int maximums[]){
	int i,j,num=0;
	for(i=1;i<n-1;i++){
		if(compare(sig[i],sig[i-1]) <= 0)   // sig[i-1] >= sig[i] 
			continue;
		if(compare(sig[i] , sig[i+1]) < 0 )   //  sig[i-1] < sig[i] < sig[i+1]
			continue;
		if(compare(sig[i] , sig[i+1]) > 0){  //  sig[i-1] < sig[i] > sig[i+1]  
			maximums[num++] = i;
			continue;
		}
		j = i+2;               // sig[i-1] < sig[i] == sig[i+1]
		while(j<n && compare(sig[i],sig[j])!=0) 
			j++;
		if(j == n){
			break;
		}
		if(compare(sig[i],sig[j])>0)
			maximums[num++] = i;
		i = j-1;		
	}
	return num;
}

/*
* �����е����ֵ 
*/
static float get_max(float sig[],int n){
	int i;
	float max = -10000000.0;
	for(i=0;i<n;i++){
		if(sig[i] > max)
			max = sig[i];
	}
	return max;
} 

/*
* �����е���Сֵ 
*/
static float get_min(float sig[],int n){
	int i;
	float min = 10000000.0;
	for(i=0;i<n;i++){
		if(sig[i] < min)
			min = sig[i];
	}
	return min;
} 

/*
* �������Ƿ����ĳ���� 
*/
static int is_exist(int a[],int n,int key){
	int i;
	for(i=0;i<n;i++){
		if(a[i] == key)
			return 1;
	}
	return 0;
}

/*
* ��һ�����е���λֵ,��nΪż��ʱȡ�м���������ƽ��ֵ 
*/
static float get_median(float a[],int n){
	int i,j,tmp;
	for(i=0;i<n;i++){  //���� 
		for(j=i+1;j<n;j++){
			if(a[i] < a[j]){
				tmp = a[i];
				a[i] = a[j];
				a[j] = a[i];
			}
		}
	}
	if(n%2==1)
		return a[(n-1)/2];
	return (a[n/2] + a[n/2-1])/(2*1.0);
}

/*
* �����������ıȽ� 
*/
static int compare(float a,float b){
	if(a - b > 0.000001)
		return 1;
	if(a - b < -0.000001)
		return -1;
	return 0;
} 
