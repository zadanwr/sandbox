//- Centhra Engine -
#include <CE/Base.h>

//- Sandbox -
#include <Sandbox/Entity.h>

using namespace v8;

namespace sandbox
{
	Entity *Entity::Create(ce::Vector2<float> position, ce::Vector2<float> extent)
	{
		Handle<ObjectTemplate> objectTemplate = ObjectTemplate::New();
		objectTemplate->SetInternalFieldCount(1);
		objectTemplate->Set(String::New("getPosition"), FunctionTemplate::New(Binding_getPosition));
		objectTemplate->Set(String::New("getExtent"), FunctionTemplate::New(Binding_getExtent));
		objectTemplate->Set(String::New("getVelocity"), FunctionTemplate::New(Binding_getVelocity));
		objectTemplate->Set(String::New("setPosition"), FunctionTemplate::New(Binding_setPosition));
		objectTemplate->Set(String::New("setExtent"), FunctionTemplate::New(Binding_setExtent));
		objectTemplate->Set(String::New("setVelocity"), FunctionTemplate::New(Binding_setVelocity));
		objectTemplate->Set(String::New("setAsFocus"), FunctionTemplate::New(Binding_setAsFocus));
		
		HandleScope handleScope;

		Entity *entity = new Entity(position, extent);
		Local<Object> instance = objectTemplate->NewInstance();
		instance->SetInternalField(0, External::New(entity));
		entity->m_instance = instance;

		return entity;
	}
	Handle<Value> Entity::Binding_entity(const Arguments& args)
	{
		if(args.Length() < 4)
			return Undefined();
		HandleScope handleScope;

		float posX = (float)args[0]->NumberValue();
		float posY = (float)args[1]->NumberValue();
		float extX = (float)args[2]->NumberValue();
		float extY = (float)args[3]->NumberValue();

		Entity *entity = Entity::Create(ce::Vector2<float>(posX, posY), ce::Vector2<float>(extX, extY));
		
		Server::GetCurrent()->PlaceEntity(static_cast<Entity *>(entity));
		return entity->m_instance;
	}
	Handle<Value> Entity::Binding_getPosition(const Arguments& args)
	{
		HandleScope handleScope;

		Local<Object> self = args.This();
		Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
		void* ptr = wrap->Value();
		ce::Vector2<float> position = static_cast<Entity *>(ptr)->GetPosition();

		Handle<Array> result = Array::New();
		for(int a = 0; a < 2; a++)
			result->Set(Integer::New(a), Number::New(position[a]));
		return result;
	}
	Handle<Value> Entity::Binding_setAsFocus(const Arguments& args)
	{
		HandleScope handleScope;

		Local<Object> self = args.This();
		Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
		void* ptr = wrap->Value();

		Server::GetCurrent()->SetFocus(static_cast<Entity *>(ptr));


		return Undefined();
	}
	Handle<Value> Entity::Binding_getExtent(const Arguments& args)
	{
		HandleScope handleScope;

		Local<Object> self = args.This();
		Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
		void* ptr = wrap->Value();
		ce::Vector2<float> extent = static_cast<Entity *>(ptr)->GetExtent();

		Handle<Array> result = Array::New();
		for(int a = 0; a < 2; a++)
			result->Set(Integer::New(a), Number::New(extent[a]));
		return result;
	}
	Handle<Value> Entity::Binding_getVelocity(const Arguments& args)
	{
		HandleScope handleScope;

		Local<Object> self = args.This();
		Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
		void* ptr = wrap->Value();
		ce::Vector2<float> velocity = static_cast<Entity *>(ptr)->GetVelocity();

		Handle<Array> result = Array::New();
		for(int a = 0; a < 2; a++)
			result->Set(Integer::New(a), Number::New(velocity[a]));
		return result;
	}
	Handle<Value> Entity::Binding_setPosition(const Arguments& args)
	{
		if(args.Length() < 2)
			return Undefined();

		HandleScope handleScope;

		Local<Object> self = args.This();
		Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
		void* ptr = wrap->Value();
		static_cast<Entity *>(ptr)->SetPosition(ce::Vector2<float>((float)args[0]->NumberValue(), (float)args[1]->NumberValue()));

		return Undefined();
	}
	Handle<Value> Entity::Binding_setExtent(const Arguments& args)
	{
		if(args.Length() < 2)
			return Undefined();

		HandleScope handleScope;

		Local<Object> self = args.This();
		Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
		void* ptr = wrap->Value();
		static_cast<Entity *>(ptr)->SetExtent(ce::Vector2<float>((float)args[0]->NumberValue(), (float)args[1]->NumberValue()));

		return Undefined();
	}
	Handle<Value> Entity::Binding_setVelocity(const Arguments& args)
	{
		if(args.Length() < 2)
			return Undefined();

		HandleScope handleScope;

		Local<Object> self = args.This();
		Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
		void* ptr = wrap->Value();
		static_cast<Entity *>(ptr)->SetVelocity(ce::Vector2<float>((float)args[0]->NumberValue(), (float)args[1]->NumberValue()));

		return Undefined();
	}

	Entity::Entity(ce::Vector2<float> position, ce::Vector2<float> extent) : ce::game2d::ZoneEntity(position, extent)
	{
	}
	Entity::~Entity()
	{
		// TODO: Delete Javascript instance
	}
}
