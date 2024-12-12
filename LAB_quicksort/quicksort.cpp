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
		printf("�ü�:");
		for(int i = 0 ; i < n ; i++ ){ //�L�Xrandom(�ü�)
			random[i] = rand()%m;
			printf(" %d",random[i]);
		}
		printf("\n");
		left=0;
		right=n-1;
		Quicksort(random,n,left,right,pivot);//�Ƨǰ}�C 
		printf("�Ƨ�:");
		for(int a = 0; a < n ; a++){ //�L�Xrandom(�Ƨǫ�) 
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

void Quicksort(int random[],int n,int left,int right,int &pivot){ //�ֳt�Ƨ� ����B�z 
    if(left<right){
    	pivotclassify(random,left,right,pivot,n);
    	Quicksort(random,n, left, pivot-1,pivot);
    	Quicksort(random,n, pivot+1, right,pivot);
	}//if
}// Quicksort

void pivotclassify(int random[],int left,int right, int &pivot, int n){ //��@�Ӱ���Ipivot�A�Hpivot����Ǥ���� 
	int i=left,j=left;
	pivot = right; //���]����I��random���̫�@�ӼƦr (right) 
	for(j ; j < right ; j++ ){ //�M�wi����l�� 
		if(random[j]>random[right]){
			i = j - 1 ;
			break;
		}//if
		else if( j == (right-1) )//�p�G����I��Ҧ��Ʀr���j 
			i = right - 1 ;
	}//for
	for(j ; j < right ; j++ ){  
		if(random[j]<random[right]){
			i++ ;	
			swap(random,i,j); //��random[i]��random[j]���ȥ洫	
		}//if
	}//for	
	swap(random,right,i+1); //��random[right]��random[i+1]�洫
	pivot = i+1;//�̫��ǭ�pivot�����I (�۷��random[i+1]) 
}

void swap(int random[],int i,int j){ //��random[i]��random[j]���ȥ洫
	int temp;
	temp = random[i];
	random[i] = random[j];
	random[j] = temp;
}
