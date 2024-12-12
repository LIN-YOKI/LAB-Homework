#include <stdio.h>
#include <stdlib.h> 
#include <time.h>
#include <math.h>
void Quicksort(int[] ,int ,int ,int ,int& );
void swap(int[] ,int ,int );
void pivotclassify(int[],int ,int ,int &, int );
int main(){
	int m,n;
	int left,right,reference;
	int random[100000] = {0} ;
	unsigned int seed;
	int pivot;
	seed = time(NULL);
	srand(seed);
	printf("m = ");
	scanf("%d",&m);
	printf("n = ");
	scanf("%d",&n);
	while(1){
		printf("亂數:");
		for(int i = 0 ; i < n ; i++ ){ //印出random(亂數)
			random[i] = rand()%m;
			printf(" %d",random[i]);
		}
		printf("\n");
		left=0;
		right=n-1;
		Quicksort(random,n,left,right,pivot);//排序陣列 
		printf("排序:");
		for(int a = 0; a < n ; a++){ //印出random(排序後) 
			printf(" %d",random[a]);
		}//for
		printf("\n");
		printf("m = ");
		scanf("%d",&m);
		printf("n = ");
		scanf("%d",&n);
	}
	return 0;
}

void Quicksort(int random[],int n,int left,int right,int &pivot){ //快速排序 分堆處理 
    if(left<right){
    	pivotclassify(random,left,right,pivot,n);
    	Quicksort(random,n, left, pivot-1,pivot);
    	Quicksort(random,n, pivot+1, right,pivot);
	}//if
}// Quicksort

void pivotclassify(int random[],int left,int right, int &pivot, int n){ //選一個基準點pivot，以pivot為基準分兩堆 
	int i=left,j=left;
	pivot = right; //假設基準點為random的最後一個數字 (right) 
	for(j ; j < right ; j++ ){ //決定i的初始值 
		if(random[j]>random[right]){
			i = j - 1 ;
			break;
		}//if
		else if( j == (right-1) )//如果基準點比所有數字都大 
			i = right - 1 ;
	}//for
	for(j ; j < right ; j++ ){  
		if(random[j]<random[right]){
			i++ ;	
			swap(random,i,j); //把random[i]跟random[j]的值交換	
		}//if
	}//for	
	swap(random,right,i+1); //把random[right]跟random[i+1]交換
	pivot = i+1;//最後基準值pivot的落點 (相當於random[i+1]) 
}

void swap(int random[],int i,int j){ //把random[i]跟random[j]的值交換
	int temp;
	temp = random[i];
	random[i] = random[j];
	random[j] = temp;
}
