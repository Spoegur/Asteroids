#pragma once
#ifndef _TIMER_
#define _TIMER_
#include "raylib.h"
#include "raymath.h"
#include <list>
#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <assert.h>

typedef struct Timer {

public:

	Timer();

	Timer(float timer);

	~Timer() noexcept;

	float Lifetime;

	void StartTimer(Timer* timer, float lifetime);
	void UpdateTimer(Timer* timer);
	bool TimerDone(Timer* timer);
	float getTime(Timer* timer);

}Timer;
#endif // _TIMER_