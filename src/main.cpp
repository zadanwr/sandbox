//- Centhra Engine -
#include <CE/AppFrontend.h>
#include <CE/Base.h>
#include <CE/Canvas.h>

using namespace ce;

//- Define your own implementation of the AppFrontend class. -
class AppSandbox : public AppFrontend
{
	Canvas *m_canvas;

public:
	AppSandbox()
	{
		m_canvas = 0;
	}
	~AppSandbox()
	{
	}

	//- Define the virtual functions for the class. -
	bool OnStart()
	{
		print("o-> OnStart\n");
		m_canvas = Canvas::Create(640, 480, "Sandbox Game");

		return true;
	}
	bool OnProcess()
	{
		sleepMS(1);
		return true;
	}
	void OnStopped()
	{
		print("o-> OnStopped\n");
		delete m_canvas;
	}
	bool OnEvent(Event &event)
	{
		switch(event.type)
		{
		case event::KeyDown:
			print("%d\n", event.key.keyCode);
			break;
		}
		return true;
	}
};

int main(int argc, char **argv)
{
	AppSandbox myApp;

	myApp.Start();

	//- Run the App's main loop. -
	while(myApp.IsRunning())
		myApp.Process();

	return 0;
}
