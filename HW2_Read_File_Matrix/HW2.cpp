#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;
void Matrix(vector<string>,int& ,int&,int (*matrix)[9][9]);
void Matrix_Transpose(int&,int&,int (*matrix)[9][9]);
void Matrix_Multiplication(vector<string>,int &,int &,int (*matrix)[9][9]);
int main(){
	string Transpose = "Matrix_Transpose";
	string Multiplication = "Matrix_Multiplication";
	int row=0,column=0;
	int matrix[9][9]={0};
	vector<string> a;
    ifstream ifs("input05.txt", std::ios::in);
    if (!ifs.is_open()) {
        cout << "Failed to open file.\n";
    } else {
        string s;
        while (getline(ifs, s)) {
            cout << s << "\n";
            a.push_back(s);
        }
        ifs.close();
    }
    ifs.close();
	cout<< "\n";
	
	if(!a.at(0).compare(Transpose)){
		cout<<"Matrix_Transpose"<< "\n";
		Matrix(a,row,column,&matrix);
		Matrix_Transpose(row,column,&matrix);
		cout<<"row="<<row<<" column="<<column<<"\n";//answer
		for(int i = 0 ; i<column ; i ++){
		for(int j = 0 ; j<row ; j ++){
			cout<<matrix[i][j]<<" ";
		}
		cout<<"\n";
		}//answer 
	}
	else if(!a.at(0).compare(Multiplication)){
		cout<<"Matrix_Multiplication"<< "\n";
		Matrix_Multiplication(a,row,column,&matrix);
	}
    return 0;
}//main

void Matrix(vector<string>a,int &row,int &column,int (*matrix)[9][9]){
	int k=0,l=0;
	for(int i = 2 ; a.at(i).compare("End_Matrix_Transpose")!=0 ; i ++){
		for(int j = 0 ; (a.at(i))[j]!=';' ;j++ ){
			if((a.at(i))[j]!=' '){
				if(((a.at(i))[j+1]==' ')||((a.at(i))[j+1]=='\n')){
					(*matrix)[l][k]=(a.at(i))[j]-48;
					k++;	
				}
				else{
					(*matrix)[l][k]=10*((a.at(i))[j]-48)+(a.at(i))[j+1]-48;
					k++;
					j++;
				}
			}
			row = k ;
		}
		k=0;l++;
		column = l ;
	} 
}//Matrix

void Matrix_Transpose(int &row,int &column,int (*matrix)[9][9]){
	int temp;
	int TransposeMatrix[9][9];
	for(int i = 0 ; i<column ; i++){
		for(int j = 0 ;j<row  ; j++){
			TransposeMatrix[i][j]=(*matrix)[i][j];
		}
	}
	temp=row;
	row=column;
	column=temp;
	for(int i = 0 ; i<column; i++){
		for(int j = 0 ;j<row; j++){
			(*matrix)[i][j]=TransposeMatrix[j][i];
		}
	}
} //Matrix_Transpose

int Name(vector<string>a,int rowname){
	if((a.at(rowname))[0]=='N'&&(a.at(rowname))[1]=='a'&&(a.at(rowname))[2]=='m'&&(a.at(rowname))[3]=='e')
	return 1;
	else
	return 0;
}//Name

void Matrix_Multiplication(vector<string>a,int &row,int &column,int (*matrix)[9][9]){
	int matrix1[9][9];
	int matrix2[9][9];
	int answer[9][9]={0};
	int row1,column1,row2,column2,rowa,columna;
	int k=0,l=0;
	int control=0;
	for(int i = 2 ; control!=1 ; i++){
		 if(Name(a,i)==1){
			i++;control=1;k=0,l=0;
			for(i; a.at(i).compare("End_Matrix_Multiplication")!=0 ; i ++){
				for(int j = 0 ; (a.at(i))[j]!=';' ;j++ ){
					if((a.at(i))[j]!=' '){
						if(((a.at(i))[j+1]==' ')||((a.at(i))[j+1]=='\n')){
							matrix2[l][k]=(a.at(i))[j]-48;
							k++;	
						}
						else{
							matrix2[l][k]=10*((a.at(i))[j]-48)+(a.at(i))[j+1]-48;
							k++;
							j++;
						}
					}
					row2 = k ;
				}
				k=0;l++;
				column2 = l ;
			}
		}//if
		
		else{
			for(int j = 0 ; (a.at(i))[j]!=';' ;j++ ){
				if((a.at(i))[j]!=' '){
					if(((a.at(i))[j+1]==' ')||((a.at(i))[j+1]=='\n')){
						matrix1[l][k]=(a.at(i))[j]-48;
						k++;	
					}
					else{
						matrix1[l][k]=10*((a.at(i))[j]-48)+(a.at(i))[j+1]-48;
						k++;
						j++;
					}
				}
				row1 = k ;
			}
			k=0;l++;
			column1 = l ;
		}//else
	}//for
		rowa=column1;columna=row2;
		for(int i = 0 ; i<columna ; i++){
			for(int j = 0 ;j<rowa  ; j++){
				for(int m = 0 ; m < row1 ; m++){
					answer[i][j]=answer[i][j]+matrix1[i][m]*matrix2[m][j];
				}
			}
		} 
		for(int i = 0 ; i<columna ; i ++){//answer
			for(int j = 0 ; j<rowa ; j ++){
				cout<<answer[i][j]<<" ";
			}
			cout<<"\n";
		}//answer 
}//Matrix_Multiplication

