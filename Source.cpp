#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>
#include <string>
#include <functional>
#include <iterator>
using namespace std;

struct Activity {
	string name;
	vector<tuple<string, int>> timer;
};
void printActivity(Activity[5][7]);
bool isSafeName(Activity, Activity[5][7]);
int isSafeDay(string);
int isSafeHour(int);
int isSafeStop(Activity [5][7]);

void backtracking_search(vector<Activity>);
vector<Activity> recursive_backtracking(vector<Activity>, vector<Activity>, Activity [5][7]);
Activity select_unassigned_variable(vector<Activity>, vector<Activity>, Activity schedul[5][7]);
Activity mvr(vector<Activity>);
int k = 0;
///declaration of new backtrack mvr + fw
void backtracking_search_mvr_fw(vector<Activity>);
vector<Activity> recursive_backtracking_mvr_fw(vector<Activity>, vector<Activity>, Activity[5][7], vector<Activity>);
Activity select_unassigned_variable_mvr_fw(vector<Activity>, vector<Activity>, Activity schedul[5][7]);
vector<Activity> fw(Activity, vector<Activity>);
///start of new backtrack
void backtracking_search_mvr_fw(vector<Activity> activitys) {
	//itt letrehoz egy scheduleot
	Activity schedul[5][7];
	for (int i = 0; i < 5; ++i) {
		for (int j = 0; j < 7; ++j) {
			//Activity temp;
			schedul[i][j].name = "";

		}
	}
	Activity tempActivity;
	tempActivity.name = "";
	vector<Activity> temp;
	temp.push_back(tempActivity);
	recursive_backtracking_mvr_fw(temp, activitys, schedul,activitys);//meg hozza kene adni a schedule-t 
}
vector<Activity> recursive_backtracking_mvr_fw(vector<Activity> assignment, vector<Activity> activitys,
	Activity schedul[5][7], vector<Activity> mvrActivitys) {
	if (isSafeStop(schedul) == activitys.capacity())
	{
		std::cout << "FINAL\n";
		printActivity(schedul);
		int x = 2;
		std::cout << "FINAL\n Number of value assignments: "<<k;
		return assignment; 
	}
	Activity temp = select_unassigned_variable_mvr_fw(activitys, mvrActivitys, schedul);
	k++;
	mvrActivitys = fw(temp,mvrActivitys);
	for (int i = 0; i < temp.timer.capacity(); ++i)
	{
		int index = isSafeDay(get<0>(temp.timer[i]));
		int index2 = isSafeHour(get<1>(temp.timer[i]));
		if (index != -1 && index2 != -1 && schedul[index][index2].name == "")
		{
			assignment.push_back(temp);
			schedul[index][index2].name = temp.name;
			printActivity(schedul);
			vector<Activity> result = recursive_backtracking_mvr_fw(assignment, activitys, schedul, mvrActivitys);
			if (result.back().name != "fail") {
				return result;
			}
			assignment.pop_back();
			schedul[index][index2].name = "";
			mvrActivitys = activitys;
		}
	}
	Activity dump;
	dump.name = "fail";
	assignment.push_back(dump);
	return assignment;//fail
}
//fw
vector<Activity> fw(Activity temp, vector<Activity> mvrActivitys) {
	vector<Activity> copyActivitys;
	for (int i = 0; i < mvrActivitys.capacity(); ++i) {
		Activity tempActivity;
		for (int j = 0; j < mvrActivitys[i].timer.capacity(); ++j) {
			if (temp.timer.capacity() == 1)
				if (get<0>(temp.timer[0]) != get<0>(mvrActivitys[i].timer[j])
					|| get<1>(temp.timer[0]) != get<1>(mvrActivitys[i].timer[j])) {
					tempActivity.name = mvrActivitys[i].name;
					tempActivity.timer.push_back(mvrActivitys[i].timer[j]);
				}
		}
		copyActivitys.push_back(tempActivity);
	}
	for (auto it = copyActivitys.begin(); it != copyActivitys.end();)
	{
		if ((string)it->name == "")
			it = copyActivitys.erase(it);
		else
			++it;
	}

	return copyActivitys;
}
//mvr
Activity mvr(vector<Activity> activitys) {
	int min = 9999;
	Activity minActivity;
	for (int i = 0; i < activitys.capacity(); ++i) {
		std::cout << activitys[i].name << endl;
		if (activitys[i].timer.capacity() <= min) {
			min = activitys[i].timer.capacity();
			minActivity = activitys[i];
			
		}
	}
	return minActivity;
}
Activity select_unassigned_variable_mvr_fw(vector<Activity> activitys, vector<Activity> mvrActivitys, Activity schedul[5][7]) {
		Activity temp = mvr(mvrActivitys);
			if (isSafeName(temp, schedul))
			{
				return temp;
			}
	Activity tempActivity;
	tempActivity.name = "";
	return tempActivity;
}




///end of new backtrack
///normal backtrack 
void backtracking_search(vector<Activity> activitys) {
	//itt letrehoz egy scheduleot
	Activity schedul[5][7];
	for (int i = 0; i < 5; ++i) {
		for (int j = 0; j < 7; ++j) {
			//Activity temp;
			schedul[i][j].name = "";

		}
	}
	Activity tempActivity;
	tempActivity.name = "";
	vector<Activity> temp;
	temp.push_back(tempActivity);
	recursive_backtracking(temp, activitys, schedul);//meg hozza kene adni a schedule-t 
}
vector<Activity> recursive_backtracking(vector<Activity> assignment, vector<Activity> activitys, Activity schedul[5][7]) {
	
	if (isSafeStop(schedul) == activitys.capacity())
	{
		std::cout << "\nFINAL\n";
		printActivity(schedul);
		std::cout << "\nFINAL\n Number of value assignments: " << k;
		return assignment;
	}
	Activity temp = select_unassigned_variable(activitys, assignment, schedul);
	k++;
	for (int i=0;i < temp.timer.capacity(); ++i)
	{
		int index = isSafeDay(get<0>(temp.timer[i]));
		int index2 = isSafeHour(get<1>(temp.timer[i]));
		if (index != -1 && index2 != -1 && schedul[index][index2].name == "")
		{
			assignment.push_back(temp);
			schedul[index][index2].name = temp.name;
			printActivity(schedul);
			vector<Activity> result = recursive_backtracking(assignment, activitys, schedul);
			if (result.back().name != "fail") {
				return result;
			}
			assignment.pop_back();
			schedul[index][index2].name = "";
		}
	}
	Activity dump;
	dump.name = "fail";
	assignment.push_back(dump);
	return assignment;//fail
}


Activity select_unassigned_variable(vector<Activity> activitys, vector<Activity> assignment,Activity schedul[5][7]) {
	for (int i = 0; i < activitys.capacity(); ++i) {
			if (isSafeName(activitys[i], schedul))
			{
				return activitys[i];
			}
	}
	Activity tempActivity;
	tempActivity.name = "";
	return tempActivity;
}

int isSafeHour(int time) {
	int index;
	if (time == 8) {
		index = 0;
	}
	else if (time == 10) {
		index = 1;
	}
	else if (time == 12) {
		index = 2;
	}
	else if (time == 14) {
		index = 3;
	}
	else if (time == 16) {
		index = 4;
	}
	else if (time == 18) {
		index = 5;
	}
	else if (time == 20) {
		index = 6;
	}
	else {
		index = -1;
	}
	return index;
}

int isSafeDay(string day) {
	int index;
	if (day == "hetfo") {
		index = 0;
	}
	else if (day == "kedd") {
		index = 1;
	}
	else if (day == "szerda") {
		index = 2;
	}
	else if (day == "csutortok") {
		index = 3;
	}
	else if (day == "pentek") {
		index = 4;
	}
	else {
		index = -1;
	}
	return index;
}
bool isSafeName(Activity activity, Activity schedul[5][7]) {
	for (int i = 0; i < 5; ++i) {
		for (int j = 0; j < 7; ++j) {
			if (schedul[i][j].name == activity.name || activity.name == "") {
				return false;
			}
		}
	}
	return true;
}
int isSafeStop(Activity schedul[5][7]) {
	int temp = 0;
	for (int i = 0; i < 5; ++i) {
		for (int j = 0; j < 7; ++j) {
			if (schedul[i][j].name != "") {
				temp = temp + 1;
			}
		}
	}
	return temp;
}

void printActivity(Activity schedul[5][7]) {
	int temp = 0;
	for (int i = 0; i < 5; ++i) {
		for (int j = 0; j < 7; ++j) {
			if (schedul[i][j].name != "") {
				if (i == 0) {
					std::cout << "Hetfo ";
				}
				else if (i == 1) {
					std::cout << "Kedd ";
				}
				else if (i == 2) {
					std::cout << "Szerda ";
				}
				else if (i == 3) {
					std::cout << "Csutortok ";
				}
				else if (i == 4) {
					std::cout << "Pentek ";
				}
				std::cout << schedul[i][j].name << " " << 8 + j * 2 << endl;
			}
		}
	}
	std::cout << endl;
}

int main() {
	Activity a;
	a.name = "Foot";
	a.timer.push_back(make_tuple("hetfo", 12));
	a.timer.push_back(make_tuple("szerda", 12));
	
	Activity b;
	b.name = "Net";
	b.timer.push_back(make_tuple("kedd", 10));
	
	Activity c;
	c.name = "Tennis";
	c.timer.push_back(make_tuple("hetfo", 12));

	Activity d;
	d.name = "App";
	d.timer.push_back(make_tuple("kedd", 10));
	d.timer.push_back(make_tuple("pentek", 10));
	
	Activity e;
	e.name = "Real";
	e.timer.push_back(make_tuple("pentek", 10));
	e.timer.push_back(make_tuple("pentek", 16));
	e.timer.push_back(make_tuple("kedd", 10));
	
	vector<Activity> array;
	array.push_back(a);
	array.push_back(b);
	array.push_back(c);
	array.push_back(d);
	array.push_back(e);

	cout << "RAW BACKTRACK\n";
	backtracking_search(array);
	cout << endl << endl << endl;
	k = 0;
	cout << "\nMVR + FW\n";
	backtracking_search_mvr_fw(array);
	
	return 0;
}