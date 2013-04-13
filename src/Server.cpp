//- Standard Library -
#include <iostream>
#include <fstream>
#include <string>

//- Centhra Engine -
#include <CE/Base.h>

//- Sandbox -
#include <Sandbox/Server.h>

using namespace ce;
using namespace v8;
using namespace std;

namespace sandbox
{
	Server::Server()
	{
		m_context = Context::New();
	}
	Server::~Server()
	{
		m_context.Dispose();
	}
	bool Server::InitNativeBindings()
	{
		return true;
	}
	bool Server::ExecuteFile(const char *file)
	{
		Context::Scope contextScope(m_context);
		HandleScope handleScope;
		ifstream inFile(file, ios::in | ios::binary | ios::ate);
		if(!inFile.is_open())
			return false;

		int size = (int)inFile.tellg();
		char *fileContents = new char[size + 1];
		for(int a = 0; a <= size; a++)
			fileContents[a] = 0;
		inFile.seekg(0, ios::beg);
		inFile.read(fileContents, size);
		inFile.close();

		Handle<String> source = String::New(fileContents);
		Handle<Script> script = Script::Compile(source);
		Handle<Value> result = script->Run();
		String::AsciiValue ascii(result);
		if(ascii.length())
			print("%s\n", *ascii);

		delete [] fileContents;
		return true;
	}
}
