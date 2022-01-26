#include <iostream>
#include <stdio.h>
#include <vector>
#include <queue>
using namespace std;

//int** dynamicArray(int n) {
//	int** arr = new int* [n];
//	// Check if the memory has been successfully
//	// allocated by malloc or not
//	if (arr == NULL) {
//		printf("Memory not allocated.\n");
//		exit(0);
//	}
//
//	for (int i = 0; i < n; i++) {
//		arr[i] = new int[3];
//		if (arr[i] == NULL) {
//			printf("Memory not allocated.\n");
//			exit(0);
//		}
//	}
//
//	return arr;
//}

vector<vector<int>> fillArray(vector<vector<int>> vec, int n) {
	printf("Enter burst time, priority and arrival time for each process.\n");
	printf("|Process|B|P|A| \n");

	for (int i = 0; i < n; i++)
	{
		printf("      %2d ", i);
		int a;
		vector<int> v;
		for (int j = 0; j < 3; j++)
		{
			cin >> a;
			v.push_back(a);
		}
		v.push_back(i);
		vec.push_back(v);
	}
	printf("\n");

	return vec;
}

vector<vector<int>> orderArray(vector<vector<int>> vec) {
	vector<vector<int>> sorted;

	for (int time = 0; !vec.empty(); time++) {

		int current;

		for (current = 0; vec[current][2] > time; current++) {
			if (current == vec.size() - 1) {
				time++;
				current = -1;
			}
		}

		for (int i = 0; i < vec.size(); i++) {
			if (vec[i][2] > time)
				continue;

			if (vec[i][1] < vec[current][1]) {
				current = i;
			}
		}

		vec[current][0] = vec[current][0] - 1;

		vector<int> v;
		v.push_back(vec[current][3]);
		v.push_back(time);
		sorted.push_back(v);

		if (vec[current][0] == 0) {
			vec.erase(vec.begin() + current);
		}
	}

	return sorted;
}

void printArray(vector<vector<int>> vec, vector<vector<int>> sorted) {
	printf("Ordered processes based on priority(BT - Burst Time, WT - Waiting Time, RT - Response Time, TT - Turnaround Time): \n");
	printf("| Time | Process | BT | WT | RT | TT | \n");

	int BT, WT, RT, TT;
	for (int i = 0; i < sorted.size(); i++)
	{
		int index = sorted[i][0];
		vec[index][0]--;
		BT = vec[index][0];
		WT = 0;
		/*for (int j = 0; j < i; j++) {
			WT += vec[sorted[j]][0];
		}*/
		RT = WT;
		TT = BT + WT;

		printf("|   %2d |      %2d | %2d | %2d | %2d | %2d | \n", sorted[i][1], sorted[i][0], BT, WT, RT, TT);
	}

	return;
}

//void freeResources(int** arr, int n) {
//	for (int i = 0; i < n; i++)
//		free(arr[i]);
//	free(arr);
//
//	return;
//}

int main()
{
	int n = 0;

	printf("Enter the number of processes: ");
	cin >> n;

	//int** arr = dynamicArray(n);

	vector<vector<int>> vec = fillArray(vec, n);

	vector<vector<int>> sorted = orderArray(vec);

	printArray(vec, sorted);

	//freeResources(arr, n);

	return 0;
}