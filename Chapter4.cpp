#include <ctime>
#include <string>
#include<iostream>
#include <math.h>
#include<windows.h>

using namespace std;

struct TimerClass {
	int m_hour;
	int m_minutes;
	int m_seconds;
	string m_name;

	TimerClass() {
		struct tm newtime;
		time_t now = time(0);
		localtime_s(&newtime, &now);

		m_hour = newtime.tm_hour;
		m_minutes = newtime.tm_min;
		m_seconds = newtime.tm_sec;
		m_name = {};

		cout << "Object constructed at " << m_hour << ":" << m_minutes << ":" << m_seconds << "."<< endl;
	}

	TimerClass(const string& name) {
		struct tm newtime;
		time_t now = time(0);
		localtime_s(&newtime, &now);

		m_hour = newtime.tm_hour;
		m_minutes = newtime.tm_min;
		m_seconds = newtime.tm_sec;
		m_name = name;

		cout << m_name <<" constructed at " << m_hour << ":" << m_minutes << ":" << m_seconds << "." << endl;
	}

	~TimerClass() {
		struct tm newtime;
		time_t now = time(0);
		localtime_s(&newtime, &now);

		m_hour = abs(newtime.tm_hour - m_hour);
		m_minutes = abs(newtime.tm_min - m_minutes);
		m_seconds = abs(newtime.tm_sec - m_seconds);

		cout << m_name<<" destructed at " << newtime.tm_hour << ":" << newtime.tm_min << ":" << newtime.tm_sec << "." << endl;
		if (m_name == "") {
			cout << "\"noname\" object lifetime " << m_hour << ":" << m_minutes << ":" << m_seconds << "." << endl;
		}
		else {
			cout << m_name << "lifetime " << m_hour << ":" << m_minutes << ":" << m_seconds << "." << endl;
		}
	}

	TimerClass(const TimerClass& other) {
		m_hour = other.m_hour;
		m_minutes = other.m_minutes;
		m_seconds = other.m_seconds;
	}

	TimerClass& operator=(const TimerClass& other) {
		m_hour = other.m_hour;
		m_minutes = other.m_minutes;
		m_seconds = other.m_seconds;
	}

	TimerClass& operator=(TimerClass&& other) noexcept {
		m_hour = other.m_hour;
		m_minutes = other.m_minutes;
		m_seconds = other.m_seconds;

		other.m_hour = 0;
		other.m_minutes = 0;
		other.m_seconds = 0;
	}
};

struct ControlObj {
	TimerClass* m_timer;
	string m_name;

	ControlObj(const string& name) {
		m_name = name;
		m_timer = new TimerClass(name);
	}

	~ControlObj() {
		delete m_timer;
		m_name = "";
	}

	void work() {
		Sleep(20000);
	}
};

int main() {
	ControlObj* riko = new ControlObj("Riko");
	riko->work();
	delete riko;
}