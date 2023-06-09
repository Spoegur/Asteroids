#include "Timer.h"
#include "raylib.h"
#include "raymath.h"
#include <list>
#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <assert.h>

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
void Timer::StartTimer(Timer* timer, float lifetime)
{
	if (timer != NULL) {
		timer->Lifetime = lifetime;
		std::cout << "The timer has started at is currently at: " << timer->Lifetime << std::endl;
	}
}

// Update a timer using the Frametime as a reference
void Timer::UpdateTimer(Timer* timer)
{
	// Subtracts the current frametime from the timer for exceptions sake
	if (timer != NULL) {
		timer->Lifetime += GetFrameTime();
		std::cout << "The timer is currently at: " << timer->Lifetime << std::endl;
	}
}

// Checks whether a timer is done
bool Timer::TimerDone(Timer* timer)
{
	if (timer != NULL) {
		return timer->Lifetime <= 0;
	}
}

float Timer::getTime(Timer* timer)
{
	return timer->Lifetime;
}
