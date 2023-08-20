#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

struct DATA {
    string start;
    string end;
    int weight;
}data1;

struct PATH {
    string point;
    bool visited;
    int cost;
    int previous;
}path1;

vector <DATA> data_vec;
vector <PATH> path_vec;
int** table;

//function
DATA readfile(string s);
int V_max(int Vmax);
void build_path_vec(void);
void Dijkstra(void);
void path_table(int w, int h);
int V_number(string point);

int main(void) {
    string inputtxt;
    cout << "Please enter the file name:";
    cin >> inputtxt;
    ifstream ifs(inputtxt.c_str(), ios::in);
    if (!ifs.is_open()) {
        cout << "Failed to open file.\n";
    }
    else {
        string s;
        while (getline(ifs, s)) {
            //cout << s << "\n";
            data_vec.push_back(readfile(s));
        }
        ifs.close();
    }

    build_path_vec();//target path
    path_table(path_vec.size(), path_vec.size());//build path table
    Dijkstra();
    
    //output txt
    string output = "";
    ofstream ofs;
    ofs.open("output.txt");
    if (!ofs.is_open()) {
        cout << "Failed to open file.\n";
    }
    else {
        for (int i = 0; i < path_vec.size(); i++) {
            output = "";
            if (i == 0) {
                ofs << "destination : S    ";
                ofs << "weight = " << path_vec[i].cost << "   ";
            }
            else if (i == (path_vec.size() - 1)) {
                ofs << "destination : T    ";
                ofs << "weight = " << path_vec[i].cost << "   ";
            }
            else {
                ofs << "destination : V" << i << "    ";
                ofs << "weight = " << path_vec[i].cost << "   ";
            }
            ofs << "path = " ;
            int point,previous;
            previous = path_vec[i].previous;
            point = i;
            output.insert(0, path_vec[point].point);
            while (previous != 0) {
                previous = path_vec[point].previous;               
                output.insert(0, "->");
                output.insert(0, path_vec[previous].point);
                point = previous;
            }              
            ofs << output << "\n\n";
        }


        ofs.close();
    }
    //output txt
}

void Dijkstra(void) { 
    int point_previous = 0;
    int min_weight, point_min = 0;
    path_vec[0].visited = true;
    //initialize path_vec cost[0]
    for (int i = 0; i < path_vec.size(); i++) {
        path_vec[i].cost = table[0][i];
        if (path_vec[i].cost < 99999) {
            path_vec[i].previous = point_previous;
        }
    }
    //Dijkstra
    for (int i = 0; i < path_vec.size(); i++) {
        min_weight = 99999999;
        for (int k = 0; k < path_vec.size(); k++) { //minimum value of the current node
            if (!path_vec[k].visited && path_vec[k].cost < min_weight) {
                min_weight = path_vec[k].cost;
                point_min = k;
            }
        }
        path_vec[point_min].visited = true;
        point_previous = point_min;
        for (int i = 0; i < path_vec.size(); i++) {//Update the previous node and the shortest path         
            if ((path_vec[point_min].cost + table[point_min][i]) < path_vec[i].cost
                && table[point_min][i] < 99999 && i != point_min) {
                path_vec[i].previous = point_previous;
                path_vec[i].cost = path_vec[point_min].cost + table[point_min][i];
            }
        }

    }
}

void path_table(int w, int h) { //build a w*h matrix   
    //build a w*h matrix
    table = new int* [h];
    for (int i = 0; i < h; i++) {
        table[i] = new int[w];
    }
    //initialize
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if(i == j) table[i][j] = 0;
            else table[i][j] = 999999999;//999999999     
        }
    }

    int i = 0, j = 0;
    int Vnumber;

    for (int k = 0; k < data_vec.size(); k++) {
        if (!(data_vec[k].start.compare("S"))) { // start == "S"
            //start i
            i = 0;
            //end j
            if (!(data_vec[k].end.compare("T"))) { // end == "T"
                j = w - 1;
            }
            else { // end != "T"
                Vnumber = V_number(data_vec[k].end);
                j = Vnumber;               
            }
            table[i][j] = data_vec[k].weight;
        }
        else { // start != "S"
            //start i
            Vnumber = V_number(data_vec[k].start);
            i = Vnumber;
            //end j
            if (!(data_vec[k].end.compare("T"))) { // end == "T"
                j = w - 1;
            }
            else {  // end != "T"
                Vnumber = V_number(data_vec[k].end);
                j = Vnumber;
            }
            table[i][j] = data_vec[k].weight;
        }
    }

}

void build_path_vec(void) {
    int Vmax = 0;
    Vmax = V_max(Vmax);
    //initialize
    stringstream temp_number;
    string number;
    for (int i = 0; i < Vmax + 2; i++) {
        if (i == 0)  path1.point = "S";       
        else if (i == Vmax + 1) path1.point = "T";          
        else {
            temp_number.str("");
            temp_number.clear();
            path1.point = "V";
            temp_number << i;
            temp_number >> number;
            path1.point += number;
        }
        path1.visited = false;
        path1.cost = 999999999;
        path1.previous = -1;
        path_vec.push_back(path1);
    }
}

int V_max(int Vmax) { //S,V1,V2......Vmax,T (What is the "max" value)
    int temp = 0;
    string no_V;//The string delete "V"

    for (int i = 0; i < data_vec.size(); i++) {
        if ((data_vec[i].start.compare("T")) && (data_vec[i].start.compare("S")) &&
            (data_vec[i].end.compare("T")) && (data_vec[i].end.compare("S"))) { //"S", "T" are not considered
            temp = V_number(data_vec[i].start);
            if (Vmax < temp) Vmax = temp;
            temp = V_number(data_vec[i].end);
            if (Vmax < temp) Vmax = temp;
        }
    }
    return Vmax;
}

int V_number(string point_name) {//if "V1",return int 1;
    int number = 0;
    string no_V;//The string delete "V"

    no_V = point_name.substr(1, point_name.length()); //delete "V"
    number = stoi(no_V);
    return number;
}

DATA readfile(string s) { //Split the " " and ";"
    int start = 0, end = 0, time = 0;
    string weight_str;

    for (int i = 0; i <= s.size(); i++) {
        if (s[i] == ' ' && time == 0) {
            end = i;
            data1.start = s.substr(start, end - start);
            start = end + 1;
            time++;
        }
        else if (s[i] == ' ' && time == 1) {
            end = i;
            data1.end = s.substr(start, end - start);
            start = end + 1;
            time++;
        }
        else if (s[i] == ';' && time == 2) {
            end = i;
            weight_str = s.substr(start, end - start);
            data1.weight = stoi(weight_str);
        }
    }
    return data1;

}

