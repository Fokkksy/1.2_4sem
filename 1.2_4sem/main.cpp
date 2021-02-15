#include <iostream>
#include <chrono>
#include <algorithm>
#include <vector>

using namespace std;

class Timer {
public:
	Timer() :
		moment_begin(chrono::steady_clock::now()), moment_rest(0) {}
	void pause() {
		auto end = chrono::steady_clock::now();
		moment_rest = chrono::duration_cast <chrono::microseconds> (end - moment_begin);
	}

	void restart() {
		moment_begin = chrono::steady_clock::now();
	}
	~Timer() {
		auto end = chrono::steady_clock::now();
		no_pause_before_end = true;
		if (no_pause_before_end) {
			moment_rest = moment_rest + chrono::duration_cast <chrono::microseconds> (end - moment_begin);

		}
		cout << "microseconds: " << moment_rest.count() << endl;
	}


private:
	chrono::steady_clock::time_point moment_begin;
	chrono::microseconds moment_rest;
	bool no_pause_before_end = false;
};


int main() {
	vector<int> v1(10000, 0);
	vector<int> v2(5000, 0);

	for (auto i = 0; i < size(v1); ++i) {
		v1[i] = i;
	}
	for (auto i = 0; i < size(v2); ++i) {
		v2[i] = i;
	}
	{
		Timer time;
		sort(begin(v1), end(v1), greater<int>());
		time.pause();
		sort(begin(v2), end(v2), greater<int>());
		time.restart();
		sort(begin(v2), end(v2), greater<int>());
	}

	return 0;

}