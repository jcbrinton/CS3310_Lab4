/*
Joseph Brinton
Group 9 Lab #5 Backtracking
CS 3310 Section 001
*/

#define _SCL_SECURE_NO_WARNINGS 

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <string.h>
#include <time.h>
#include <stdio.h>
#include <dos.h>
#include <iomanip>
#include <vector>
#include <algorithm>      
#include <random>

using namespace std;
using std::setw;

int basic_operations = 0;
int nodes_visited = 0;
int edges=0;
std::vector<int> vcolor;
std::vector<std::vector<bool>>  W;
int n, m;

//randomly generates weights and values for each item
void graphGen() {
	W.resize(n);
	for (int k = 0; k < n; k++) 
		W[k].resize(n);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if(i==j)
				W[i][j] = false;
			else {
				int b = rand() % 2;
				if (b == 1 && j<i)
					edges++;
				W[i][j] = b;
				W[j][i] = b;
			}
		}
	}

}

bool promising(int i) {
	nodes_visited++;
	int j = 0;
	bool swt = true;

	while (j<i &&swt ) {
		if (W[i][j] == 1 && vcolor[i] == vcolor[j]) {
			swt = false;
		}
		j++;
	}
	return swt;
}

void coloring(int i ){
	int color;
	basic_operations++;

	if (promising(i)) {
		if (i == n-1) {
			for (int j = 0; j < n; j++)
					cout << setw(4) << std::left << vcolor[j] << " ";
				cout << endl;
		}
		else
			for (color = 1; color <= m; color++) {
					vcolor[i + 1] = color;
					coloring(i + 1);
			}
	}
}

int montecarlo(int i) {
	vcolor.clear();
	int t = m;
	int msub = 1;
	int mprod = 1;
	int numnodes = 1;
	vector<int>prom_children;
	
	while (msub != 0 && i!=n) {
		mprod = mprod * msub;
		numnodes = numnodes + mprod*t;

		prom_children.clear();
		vcolor.resize(vcolor.size() + 1);
		for (int j = 0; j < t; j++) {
			vcolor[i] =(j);
			if (promising(i)) {
				prom_children.push_back(j);
			}
			
		}
		msub = prom_children.size();

		if (msub != 0) {
			vcolor[i] = prom_children[rand() % (msub)];
		}
	
		i++;
	
	}

	return numnodes;
}


//main function
int main()
{
	while (true) {

		int count = 0;
		cout << "Enter the number of vertices in the graph n: ";
		cin >> n;
		while (!cin || n<0) {
			cin.clear();
			cin.ignore();
			cout << "Input invalid. Enter the number of vertices in the graph n: ";
			cin >> n;
		}
		cout << "Enter the number of colors m to test for: ";
		cin >> m;
		while (!cin || m<0) {
			cin.clear();
			cin.ignore();
			cout << "Input invalid. Enter the number of colors m to test for: ";
			cin >> m;
		}
		count = n;

		graphGen();
		vcolor.resize(n);
		/*for (int k = 0; k < n; k++) {
			for (int j = 0; j < n; j++)
				cout << setw(4) << std::left << W[k][j] << " ";
			cout << endl;
		}
		cout << endl;*/


		clock_t start;
		clock_t end;
		clock_t elapsed_clock;
		clock_t elapsed_time;
		cout << "Solutions: " << endl;
		start = clock();

		coloring(-1);

		end = clock();
		elapsed_clock = end - start;
		elapsed_time = ((end - start) / (CLK_TCK));
		
		cout << setw(11) << std::left << "" << setw(11) << std::left << "Number" << setw(11) << std::left << "Number of" << setw(11) << std::left << "Time" << setw(11) << std::left << "Basic" << setw(11) << std::left << "Monte" << setw(11) << std::left << "Edges" << endl;
		cout << setw(11) << std::left << "Algorithm" << setw(11) << std::left << "Items (n)" << setw(11) << std::left << "Colors (m) " << setw(11) << std::left << "Elapsed" << setw(11) << std::left << "Operations" << setw(11) << std::left << "Carlo" << setw(11) << std::left << "" << endl;

		cout << setw(11) << "B-tracking" << setw(11) << count << setw(11) << m << setw(11) << elapsed_clock << setw(11) << basic_operations<<setw(11) << montecarlo(0) << setw(11) << edges << endl;


		//reset stats
		basic_operations = 0;
		edges = 0;
		nodes_visited = 0;
		n = 0;
		vcolor.clear();
		for (int k = 0; k < n; k++)
			W[k].clear();
		W.clear();
		
	}

}

