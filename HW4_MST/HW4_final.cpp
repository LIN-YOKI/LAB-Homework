#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;
struct DATA {
	int name;
	int x;
	int y;
}data1;
struct COMPARE {
	int name1;
	int name2;
	double distance;
	int lined1;
	int lined2;
}compare1;
struct LINE {
	int name1;
	int name2;
	double distance;
}line1;
struct DOT {
	int group;
}dot1;
DATA namexy(string, int);
LINE connected(int, int, double);
COMPARE tempconnected(int, int, double, int, int);
DOT notes(int);
void quicksort(int, int);
void swap(int, int);
double distance(int, int, int, int);
vector <DATA> data_v;
vector<LINE> line_v;
vector<COMPARE>compare_v;
vector<DOT>dot_v;
int length = 0, linelength = 0, comparelength = 0;
double sum = 0;
int main() {
	int left = 0, right = 0;
	string inputtxt;
	cout<<"enter the filename:";
	cin >> inputtxt;//"test_29.txt"
	ifstream ifs(inputtxt.c_str(), ios::in);
	if (!ifs.is_open()) {
		cout << "Failed to open file.\n";
	}
	else {
		string s;
		while (getline(ifs, s)) {
			cout << s << "\n";
			data_v.push_back(namexy(s, length));
			length++;
		}
		ifs.close();
	}
	for (int i = 0; i <= length; i++) {
		dot_v.push_back(notes(i));
	}
	double pointdistance;
	for (int i = 0; i < length; i++) {
		for (int j = i + 1; j < length; j++) {
			if (i != j) {
				pointdistance = distance(data_v[i].x, data_v[j].x, data_v[i].y, data_v[j].y);
				compare_v.push_back(tempconnected(data_v[i].name, data_v[j].name, pointdistance, i, j));
				comparelength++;
			}//if
		}//for
	}//for
	right = comparelength - 1;
	/*for (int i = 0; i < comparelength; i++) {
		cout << i << " " << compare_v[i].name1 << " ";
		cout << compare_v[i].name2 << " ";
		cout << compare_v[i].distance << "\n";
	}*/
	quicksort(left, right);
	/*cout << "compare_v quicksort" << "\n";
	for (int i = 0; i < comparelength; i++) {
		cout << i << " " << compare_v[i].name1 << " ";
		cout << compare_v[i].name2 << " ";
		cout << compare_v[i].distance << "\n";
	}*/

	int pointsame = 0, labelone = 0, groupzero = 0;
	int replacename1, replacename2;
	int group = 0, temp1, temp2;
	//mst
	for (int i = 0; i < comparelength; i++) {
		replacename1 = compare_v[i].name1;
		replacename2 = compare_v[i].name2;
		if (dot_v[replacename1].group == dot_v[replacename2].group &&
			dot_v[replacename1].group != 0 && dot_v[replacename2].group != 0)
			continue;
		for (int i = 1; i <= length; i++) {
			if (dot_v[i].group == 0)
				groupzero++;
		}//for
		if (groupzero == 0 && group == 1) { //group為1 沒有group=0
			break;
		}//if
		if (dot_v[replacename1].group == 0 && dot_v[replacename2].group == 0) { //group都是0
			group++;
			dot_v[replacename1].group = group;
			dot_v[replacename2].group = group;
			line_v.push_back(connected(compare_v[i].name1, compare_v[i].name2, compare_v[i].distance));
			sum = sum + compare_v[i].distance;
			linelength++;
		}//if
		else if (dot_v[replacename1].group == 0 && dot_v[replacename2].group != 0) { //group一個0一個不是0
			dot_v[replacename1].group = dot_v[replacename2].group;
			line_v.push_back(connected(compare_v[i].name1, compare_v[i].name2, compare_v[i].distance));
			sum = sum + compare_v[i].distance;
			linelength++;
		}//else if
		else if (dot_v[replacename1].group != 0 && dot_v[replacename2].group == 0) { //group一個0一個不是0
			dot_v[replacename2].group = dot_v[replacename1].group;
			line_v.push_back(connected(compare_v[i].name1, compare_v[i].name2, compare_v[i].distance));
			sum = sum + compare_v[i].distance;
			linelength++;
		}//else if
		else if ((dot_v[replacename1].group != dot_v[replacename2].group) &&
			(dot_v[replacename1].group >= dot_v[replacename2].group)) {
			group--;
			temp1 = dot_v[replacename1].group;
			temp2 = dot_v[replacename2].group;
			for (int j = 0; j <= length; j++) {
				if (dot_v[j].group == temp1) {
					dot_v[j].group = temp2;
				}//if
			}//for	
			for (int j = 0; j <= length; j++) {
				if (dot_v[j].group > temp1)
					dot_v[j].group--;
			}//for

			line_v.push_back(connected(compare_v[i].name1, compare_v[i].name2, compare_v[i].distance));
			sum = sum + compare_v[i].distance;
			linelength++;

		}//else if
		else if ((dot_v[replacename1].group != dot_v[replacename2].group) &&
			(dot_v[replacename1].group < dot_v[replacename2].group)) {
			group--;
			temp1 = dot_v[replacename1].group;
			temp2 = dot_v[replacename2].group;
			for (int j = 0; j <= length; j++) {
				if (dot_v[j].group == temp2) {
					dot_v[j].group = temp1;
				}//if
			}//for
			for (int j = 0; j <= length; j++) {
				if (dot_v[j].group > temp2)
					dot_v[j].group--;
			}//for
			line_v.push_back(connected(compare_v[i].name1, compare_v[i].name2, compare_v[i].distance));
			sum = sum + compare_v[i].distance;
			linelength++;
		}//else if
		groupzero = 0;
	}//for
	
	cout << "line_v" << "\n";
	for (int i = 0; i < linelength; i++) {
		cout << i << " " << line_v[i].name1 << " ";
		cout << line_v[i].name2 << " ";
		cout << line_v[i].distance << "\n";
	}//for
	cout << "sum=" << sum << "\n";

	//output txt
	ofstream ofs;
	ofs.open("output.txt");
	if (!ofs.is_open()) {
		cout << "Failed to open file.\n";
	}
	else {
		for (int i = 0; i < linelength; i++) {
			ofs << "N" << line_v[i].name1 << " " << "N" << line_v[i].name2 << " " << line_v[i].distance << "\n";
		}//for
		ofs << "Total Wire Length = " << sum;
		ofs.close();
	}
	//output txt

	return 0;
}//main



DATA namexy(string s, int length) {
	int stop = 0;
	int number2 = 0;
	int negativex = 1, negativey = 1;
	for (int j = 0; stop != 1; j++) { //N
		if (s[j + 1] == '(') {
			int x = 0, y = 0;
			for (int k = j + 2; s[k] != ')'; k++) { //xy  
				if (s[k] != '-' && number2 == 0) {
					x = x * 10 + (s[k] - 48);
				}
				else if (s[k] == '-' && number2 == 0)
					negativex = -1;
				if (s[k + 1] == ',') {
					number2 = k;
					k = k + 2;
				}
				if (s[k] != '-' && number2 != 0) {
					if (k > number2 && number2 != 0)
						y = y * 10 + (s[k] - 48);
				}
				else if (s[k] == '-' && number2 != 0)
					negativey = -1;
			}//for k
			//cout << "negativex=" << negativex << "\n";
			//cout << "negativey=" << negativey << "\n";
			data1.x = x * negativex;
			data1.y = y * negativey;
			//cout<<"x="<<data1.x<<" ";	
			//cout<<"y="<<data1.y<<" ";
			stop = 1;
		}//if	
	}//for	j
	data1.name = length + 1;
	//cout << " name=" << data1.name<<"\n";
	return data1;
}//namexy


void quicksort(int left, int right) {  //quicksort
	if (left >= 0 && right - left >= 1) {
		int i, j;
		COMPARE temp;
		//string tra;
		i = left, j = right;
		temp = compare_v[left];//pivot=temp.number
		//tra = a.at(left);
		while (i != j) {
			while (compare_v[j].distance >= temp.distance && i < j) {
				j--; //cout << "1compare_v[j].distance="<< compare_v[j].distance<<"\n";
			}
			while (compare_v[i].distance <= temp.distance && i < j) {
				i++; //cout << "2compare_v[i].distance="<< compare_v[i].distance<<"\n";
			}
			if (i < j) {
				swap(i, j);
			}
		}
		compare_v[left] = compare_v[i];
		//a.at(left) = a.at(i);
		compare_v[i] = temp;
		//a.at(i) = tra;
		quicksort(left, i - 1);
		quicksort(i + 1, right);
	}
} //quicksort

void swap(int i, int j) { //swap
	COMPARE temp1;
	temp1 = compare_v[i];
	compare_v[i] = compare_v[j];
	compare_v[j] = temp1;
	//return date_v;
}//swap

LINE connected(int name1, int name2, double distance) {
	line1.name1 = name1;
	line1.name2 = name2;
	line1.distance = distance;
	return line1;
}

COMPARE tempconnected(int name1, int name2, double distance, int i, int j) {
	compare1.name1 = name1;
	compare1.name2 = name2;
	compare1.distance = distance;
	compare1.lined1 = i;
	compare1.lined2 = j;
	return compare1;
}

DOT notes(int i) {
	dot1.group = 0;
	return dot1;
}

double distance(int x1, int x2, int y1, int y2) {
	int valuex, valuey;
	double absvaluex, absvaluey, abstransfer;
	valuex = x1 - x2; absvaluex = abs(valuex);
	valuey = y1 - y2; absvaluey = abs(valuey);
	abstransfer = sqrt(pow(absvaluex, 2) + pow(absvaluey, 2));
	return abstransfer;
}




