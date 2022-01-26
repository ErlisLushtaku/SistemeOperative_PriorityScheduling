#include <iostream>
#include <stdio.h>
#include <vector>
#include <map>
#include <utility>
using namespace std;

vector<vector<int>> fillVector(vector<vector<int>> vec, int n) {
	printf("Enter burst time, priority and arrival time for each process.\n");
	printf("|Process|B|P|A| \n");

	for (int i = 0; i < n; i++)
	{
		printf("      %2d ", i);
		vector<int> v;
		for (int j = 0; j < 3; j++)
		{
			int a;
			cin >> a;
			v.push_back(a);
		}
		v.push_back(i);
		vec.push_back(v);
	}
	printf("\n");

	return vec;
}

vector<vector<int>> orderVector(vector<vector<int>> vec) {
	
	vector<vector<int>> sorted;

	for (int time = 0; !vec.empty(); time++) {

		// Gjejme indeksin e procesit te pare qe eshte ne ready queue
		int current;
		for (current = 0; vec[current][2] > time; current++) {
			if (current == vec.size() - 1) {
				time++;
				current = -1;
			}
		}

		// Krahasojme me proceset tjera dhe gjejme procesin me prioritet me te larte
		for (int i = 0; i < vec.size(); i++) {
			if (vec[i][2] > time)
				continue;

			if (vec[i][1] < vec[current][1]) {
				current = i;
			}
		}

		// Vendosim ne vektorin sorted indeksin e procesit te zgjedhur dhe kohen e tanishme
		vector<int> v;
		v.push_back(vec[current][3]);
		v.push_back(time);
		sorted.push_back(v);

		// Dekrementojme BurstTime te procesit te zgjedhur dhe shqyrtojme a behet 0
		vec[current][0]--;
		if (vec[current][0] == 0) {
			vec.erase(vec.begin() + current);
		}
	}

	return sorted;
}

void printVector(vector<vector<int>> vec, vector<vector<int>> sorted) {
	printf("Ordered processes based on priority(BT - Burst Time, WT - Waiting Time, RT - Response Time, TT - Turnaround Time): \n");
	printf("| Time | Process | BT | WT | RT | TT | \n");

	vector<vector<int>> BTs = vec;
	map<int, pair<int, bool>> infos; // index, RT, iPari
	int BT, WT, RT, TT, AT;

	for (int i = 0; i < sorted.size(); i++)
	{
		int index = sorted[i][0];
		int time = sorted[i][1];

		vec[index][0]--;
		BT = vec[index][0];
		AT = vec[index][2];

		if (infos[index].second == false) {
			RT = time - AT;
			infos[index].first = RT;
			infos[index].second = true;
		}

		bool iFundit = true;
		for (int j = i + 1; j < sorted.size(); j++) {
			if (index == sorted[j][0]) {
				iFundit = false;
				break;
			}
		}

		if (iFundit) {
			TT = time + 1 - AT;
			WT = TT - BTs[index][0];
			RT = infos[index].first;
			printf("|   %2d |      %2d | %2d | %2d | %2d | %2d | \n", time, index, BT, WT, RT, TT);
		}
		else {
			printf("|   %2d |      %2d | %2d |    |    |    | \n", time, index, BT);
		}
	}

	return;
}

int main()
{
	int n = 0;

	printf("Enter the number of processes: ");
	cin >> n;

	vector<vector<int>> vec = fillVector(vec, n);

	vector<vector<int>> sorted = orderVector(vec);

	printVector(vec, sorted);

	return 0;
}