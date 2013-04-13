//- Standard Library -
#include <iostream>
#include <fstream>
#include <string>

//- Centhra Engine -
#include <CE/Base.h>

//- Sandbox -
#include <Sandbox/Entity.h>
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

	void Server::SetFocus(game2d::ZoneEntity *c_entity) {
		m_plane->Place(c_entity);
		m_camera->SetFocus(c_entity);

		print("%f\n",m_view->GetCamera()->GetFocus()->GetPosition()[0]);
	}

	void Server::PlaceEntity(game2d::ZoneEntity *c_entity) {
		//m_camera->SetFocus(c_entity);
		m_plane->Place(c_entity);
	}

	void Server::ProccessPhysics(float dt) {
		//print("%f\n",dt);
		m_plane->ProcessPhysics(dt);
		Context::Scope contextScope(m_context);
		HandleScope handleScope;

		Handle<Object> t_server = Handle<Object>::Cast(m_context->Global()->Get(String::New(m_serverName.c_str())));
		Handle<Function> onEvent = Handle<Function>::Cast(t_server->Get(String::New("onEvent")));
		v8::Handle<v8::Value> args[] = {Integer::New(6)};
  		onEvent->Call(onEvent,1,args);
	}

	void Server::Render() {


				m_view->Render();
	}
	Server::Server()
	{
		Handle<ObjectTemplate> global = ObjectTemplate::New();

		//- Global Functions -
		global->Set(String::New("print"), FunctionTemplate::New(Binding_print));
		global->Set(String::New("exec"), FunctionTemplate::New(Binding_exec));
		global->Set(String::New("registerMod"), FunctionTemplate::New(Binding_registerMod));

		//- Global Classes -
		global->Set(String::New("entity"), FunctionTemplate::New(Entity::Binding_entity));

		m_context = Context::New(NULL, global);

		m_plane = new game2d::Plane(16, 16, 64.f);

		m_camera = new game2d::ZoneCamera();
		//m_camera->SetFocus(m_entity);

		m_view = new ui::GameView2D(Vector2<int>(0, 0), Vector2<int>(640, 480));
		m_view->SetCamera(m_camera);

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
		Context::Scope contextScope(m_context);
		HandleScope handleScope;

		Handle<Object> t_server = Handle<Object>::Cast(m_context->Global()->Get(String::New(m_serverName.c_str())));
		Handle<Function> onEvent = Handle<Function>::Cast(t_server->Get(String::New("onEvent")));
		v8::Handle<v8::Value> args[] = {Integer::New(0),Integer::New(key)};
  		onEvent->Call(onEvent,2,args);
  		return true;
	} 
	bool Server::SendKeyup(int key) {
		Context::Scope contextScope(m_context);
		HandleScope handleScope;

		Handle<Object> t_server = Handle<Object>::Cast(m_context->Global()->Get(String::New(m_serverName.c_str())));
		Handle<Function> onEvent = Handle<Function>::Cast(t_server->Get(String::New("onEvent")));
		v8::Handle<v8::Value> args[] = {Integer::New(1),Integer::New(key)};
  		onEvent->Call(onEvent,2,args);
  		return true;
	} 
	void Server::RemoveDead() {
		m_plane->RemoveDead();
	}
	void Server::SendMouseButtonDown(ce::Event event) {
		float x = (float)event.mouseMotion.x - (640.f/2.f - m_camera->GetFocus()->GetPosition()[0]);
		float y = (480.f - (float)event.mouseMotion.y) - (480.f/2.f - m_camera->GetFocus()->GetPosition()[1]);
		
		Context::Scope contextScope(m_context);
		HandleScope handleScope;

		Handle<Object> t_server = Handle<Object>::Cast(m_context->Global()->Get(String::New(m_serverName.c_str())));
		Handle<Function> onEvent = Handle<Function>::Cast(t_server->Get(String::New("onEvent")));

		Vector2<float> mouse = Vector2<float>(x,y);
		mouse = mouse - m_camera->GetFocus()->GetPosition();
		if(mouse.GetLength() != 0) mouse /= mouse.GetLength();

		Handle<Array> events = Array::New();
		events->Set(Integer::New(0), Number::New(x));
		events->Set(Integer::New(1), Number::New(y));
		events->Set(Integer::New(2), Number::New(event.mouseMotion.x));
		events->Set(Integer::New(3), Number::New(event.mouseMotion.y));
		events->Set(Integer::New(4), Number::New(mouse[0]));
		events->Set(Integer::New(5), Number::New(mouse[1]));
		Handle<Value> args[] = {Number::New(2),events};
  		onEvent->Call(onEvent,2,args);
	}


}
