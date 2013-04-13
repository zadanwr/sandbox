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
	Handle<Value> Binding_print(const Arguments& args)
	{
		if(args.Length() < 1)
			return Undefined();
		HandleScope handleScope;
		for(int a = 0; a < args.Length(); a++)
		{
			Handle<Value> arg = args[a];
			String::Utf8Value value(arg);
			print("%s", *value);
		}
		return Undefined();
	}
	Handle<Value> Binding_registerMod(const Arguments& args)
	{
		if(args.Length() < 1)
			return Undefined();
		HandleScope handleScope;
		Handle<Value> arg = args[0];
		String::Utf8Value value(arg);
		
		Server::GetCurrent()->RegisterMod(*value);
  
		print("%s\n", *value);
		return Undefined();
	}
	Handle<Value> Binding_exec(const Arguments& args)
	{
		if(args.Length() < 1)
			return Undefined();
		HandleScope handleScope;
		Handle<Value> arg = args[0];
		String::Utf8Value value(arg);
		Server::GetCurrent()->ExecuteFile(*value);
		return Undefined();
	}

	Server *Server::ms_current = 0;
	Server *Server::GetCurrent()
	{
		return ms_current;
	}
	Server::Server()
	{
		Handle<ObjectTemplate> global = ObjectTemplate::New();
		global->Set(String::New("print"), FunctionTemplate::New(Binding_print));
		global->Set(String::New("exec"), FunctionTemplate::New(Binding_exec));
		global->Set(String::New("registerMod"), FunctionTemplate::New(Binding_registerMod));

		m_context = Context::New(NULL, global);

		ms_current = this;
	}

	void Server::RegisterMod(const char *ModObject) {

		//m_server = Handle<Object>::Cast(m_context->Global()->Get(String::New(ModObject)));
		m_serverName = string(ModObject);

		//How to call onCreate:
		/*
		Handle<Function> oCTest = Handle<Function>::Cast(m_server->Get(String::New("onEvent")));
		v8::Handle<v8::Value> args[] = {Integer::New(49)};
  		oCTest->Call(oCTest,1,args);
  		*/
  		
	}



	Server::~Server()
	{
		m_context.Dispose();
	}

	Persistent<Context> Server::GetContext() const {

		return m_context;
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
/*		String::AsciiValue ascii(result);
		if(ascii.length())
			print("%s\n", *ascii);
*/
		delete [] fileContents;
		return true;
	}
	bool Server::ExecuteString(const char *str)
	{
		Context::Scope contextScope(m_context);
		HandleScope handleScope;

		Handle<String> source = String::New(str);
		Handle<Script> script = Script::Compile(source);
		Handle<Value> result = script->Run();
/*		String::AsciiValue ascii(result);
		if(ascii.length())
			print("%s\n", *ascii);
*/		return true;
	}

	bool Server::SendKeydown(int key) {
		print("%s\n",m_serverName.c_str());
		Context::Scope contextScope(m_context);
		HandleScope handleScope;

		Handle<Object> t_server = Handle<Object>::Cast(m_context->Global()->Get(String::New(m_serverName.c_str())));
		Handle<Function> onEvent = Handle<Function>::Cast(t_server->Get(String::New("onEvent")));
		v8::Handle<v8::Value> args[] = {Integer::New(0),Integer::New(key)};
  		onEvent->Call(onEvent,2,args);
  		return true;
	} 

}
