//- Standard Library -
#include <iostream>
#include <string>

//- Centhra Engine -
#include <CE/AppFrontend.h>
#include <CE/Base.h>
#include <CE/Canvas.h>
#include <CE/Thread.h>

//- Sandbox -
#include <Sandbox/Server.h>

using namespace ce;
using namespace sandbox;
using namespace std;

void *stdinFunc(void *arg);

//- Define your own implementation of the AppFrontend class. -
class AppSandbox : public AppFrontend
{
	Canvas *m_canvas;
	Server *m_server;
	Thread *m_stdinThread;

public:
	string m_workingStr;

	AppSandbox()
	{
		m_canvas = 0;
		m_server = 0;
		m_stdinThread = new Thread(&stdinFunc);
		m_workingStr = "";
	}
	~AppSandbox()
	{
	}

	//- Define the virtual functions for the class. -
	bool OnStart()
	{
		print("o-> OnStart\n");
		m_canvas = Canvas::Create(640, 480, "Sandbox Game");
		m_server = new Server();

		m_server->ExecuteFile("../mod/server.js");
		m_stdinThread->Start(this);
		return true;
	}
	bool OnProcess()
	{
		if(m_workingStr.size())
		{
			m_server->ExecuteString(m_workingStr.c_str());
			m_workingStr = "";
		}

		sleepMS(1);
		return true;
	}
	void OnStopped()
	{
		print("o-> OnStopped\n");
		m_stdinThread->Join();
		delete m_server;
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

void *stdinFunc(void *arg)
{
	AppSandbox *app = (AppSandbox *)arg;
	
	while(app->IsRunning())
	{
		string in;
		getline(cin, in);
		app->m_workingStr = in;
		sleepMS(1);
	}
	
	Thread::Exit(NULL);
	return 0;
}

int main(int argc, char **argv)
{
	AppSandbox myApp;

	myApp.Start();

	//- Run the App's main loop. -
	while(myApp.IsRunning())
		myApp.Process();

	Thread::Exit(NULL);
	return 0;
}
