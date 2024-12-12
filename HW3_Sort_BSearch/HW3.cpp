#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

struct DATA {
	string name;
	unsigned int number;
}data1;

DATA nameandnum(string);
void quicksort(vector <DATA>&, int, int);
void swap(vector <DATA>&, int, int);
vector <DATA> date_v;
int Binarysearch(vector <DATA>&, int, int);
int leftans = 0, rigtans = 0;

int main() {
	/*data1.name = "A1";
	data1.number = 9;
	date_v.push_back(data1);*/
	int length = 0;
	int left = 0, right = 0;
	//string inputtxt;
	//cin >> inputtxt;//inputtxt.c_str()
	//cout<<"enter the filename:";
	ifstream ifs("Input4.txt", ios::in);
	if (!ifs.is_open()) {
		cout << "Failed to open file.\n";
	}
	else {
		string s;
		while (getline(ifs, s)) {
			date_v.push_back(nameandnum(s));
			length++;
		}
		ifs.close();
	}
	cout << "\n\n";
	right = length - 1;
	quicksort(date_v, left, right);//Quicksort
	/*for (int i = 0; i< length; i++) {
		cout << "number=" << date_v[i].number;
		cout << " name=" << date_v[i].name << "\n";
	}*/
	int input, answer;
	string output;
	cout << "find:";
	cin >> input;
	answer = Binarysearch(date_v, length,input);//Binarysearch
	//cout <<"answer=" << answer;
	unsigned int equal = 0;
	if (answer > 0) {
		if (date_v[answer - 1].number == input || date_v[answer + 1].number == input) {  //equal
			equal = 1;
			if (answer - 1 > 0) {
				leftans = answer - 1;
				while ((date_v[leftans].number == input) && leftans >0) { leftans--; }
				leftans++;
			}// if
			if (answer + 1 > 0) {
				rigtans = answer + 1;
				while (date_v[rigtans].number == input) { rigtans++; }
				rigtans--;
			}// if				 
			//cout<<"leftans="<<leftans<<"rigtans="<<rigtans;
		}//if
	}//if  


	//output txt
	ofstream ofs;
	ofs.open("output.txt");
	if (!ofs.is_open()) {
		cout << "Failed to open file.\n";
	}
	else {
		if (answer == -1) {
			ofs << "Cannot Find " << input;
		}//if
		else if (equal == 0) {
			ofs << "Find " << input << "\n" << "     " << date_v[answer].name << " " << date_v[answer].number;
		}//else if
		else {  //equal==1
			ofs << "Find " << input << "\n";
			for (int i = leftans; i <= rigtans; i++) {
				ofs <<"     " << date_v[i].name << " ";
				ofs << date_v[i].number << "\n";
			}//for
		}//else
		ofs << "\n\n";
		for (int i = 0; i < length; i++) {
			ofs <<i<< date_v[i].name << " ";
			ofs << date_v[i].number << "\n";
		}//for
		ofs.close();
	}
	//output txt

	return 0;
}//main

DATA nameandnum(string s) {
	int stop = 0;
	for (int j = 0; stop != 1; j++) { //A
		if (s[j + 1] == ' ') {
			int num = 0;
			for (int k = j + 2; s[k] != '\0'; k++) { //number  
				//number[k] = (a.at(i))[j];		
				num = num * 10 + (s[k] - 48);
				//cout<<"num="<<num<<"\n";					
			}//for
			data1.number = num;
			data1.name = s.erase(j + 1);
			//cout << "number=" << data1.number;
			//cout << " name=" << data1.name<<"\n";
			stop = 1;
		}//if	
	}//for	j
	return data1;
}//nameandnum


void quicksort(vector <DATA> &date_v, int left, int right) {  //quicksort
	if (left >= 0 && right - left > 1) {
		int i, j, k, pivot = 0;
		DATA temp;
		//string tra;
		i = left, j = right;
		temp = date_v[left];//pivot=temp.number
		//tra = a.at(left);
		while (i != j) {
			while (date_v[j].number >= temp.number && i < j) {
				j--;//printf(" %d",j);
			}
			while (date_v[i].number <= temp.number && i < j) {
				i++;//printf("\n%d",i);
			}
			if (i < j) {
				swap(date_v, i, j);
			}
		}
		date_v[left] = date_v[i];
		//a.at(left) = a.at(i);
		date_v[i] = temp;
		//a.at(i) = tra;
		quicksort(date_v, left, i - 1);
		quicksort(date_v, i + 1, right);
	}
	else {
		//return date_v;
	}
	//return date_v;
} //quicksort

void swap(vector <DATA>& date_v, int i, int j) { //swap
	DATA temp1;
	temp1 = date_v[i];
	date_v[i] = date_v[j];
	date_v[j] = temp1;
	//return date_v;
}//swap

int Binarysearch(vector <DATA>& date_v, int length, int searchnum) {  //Binarysearch
	int middle;
	int left = 0, right = length - 1;
	if (searchnum > date_v[right].number)
		return -1;
	for (int i = 0; right > left; i++) {
		middle = left + (right - left) / 2;
		//cout << left << " " << middle << " " << right<<"\n";
		if (right - left != 1) {
			if (searchnum == date_v[middle].number)
				return middle;
			else if (searchnum > date_v[middle].number)
				left = middle + 1;
			else if (searchnum < date_v[middle].number)
				right = middle - 1;
		}//if
		else {       //right-left==1
			if (searchnum == date_v[right].number && searchnum == date_v[left].number)
				return right;
			else if (searchnum == date_v[right].number)
				return right;
			else if (searchnum == date_v[left].number)
				return left;
			else
				return -1;
		}//else	
	}//for
	if (right== left)
		return -1;
	//cout << left << " " << middle << " " << right << "\n";
	leftans = left; rigtans = right;
}//Binarysearch
