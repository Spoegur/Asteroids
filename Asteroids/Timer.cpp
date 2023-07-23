#include "raylib.h"
#include "raymath.h"
#include <list>
#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <assert.h>
#include "Timer.h"


Timer::Timer()
{
	
}

Timer::Timer(float timer)
{
}

Timer::~Timer()
{
}

// Start or Restart a timer using Lifetime as its length
void Timer::StartTimer(Timer* timer, float objLifetime)
{
	if (timer != NULL) {
		timer->lifetime = objLifetime;
	}
}

// Update a Stopwatch using the Frametime as a reference
void Timer::UpdateStopWatch(Timer* timer)
{
	// Adds the current frametime from the timer for exceptions sake
	if (timer != NULL) {
		timer->lifetime += GetFrameTime();
	}
}

// Update a timer using the Frametime as a reference
void Timer::UpdateTimer(Timer* timer)
{
	// Subtracts the current frametime from the timer for exceptions sake
	if (timer != NULL) {
		timer->lifetime -= GetFrameTime();
	}
}

// Checks whether a timer is done
bool Timer::TimerDone(Timer* timer)
{
	if (timer != NULL) {
		return timer->lifetime <= 0;
	}
}

float Timer::getTime(Timer* timer)
{
	return timer->lifetime;
}
