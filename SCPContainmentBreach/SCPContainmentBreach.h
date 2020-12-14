#ifndef HP_SCPCONTAINMENTBREACH
#define HP_SCPCONTAINMENTBREACH

#include "logging/Logger.h"
#include "window/Window.h"

class SCPContainmentBreach
{
public: 
	SCPContainmentBreach();

	int Initialise();

	int Run();
	void Stop();

	bool CanRun;

	void Update();
	void Render();


private:

};

#endif // !HP_SCPCONTAINMENTBREACH