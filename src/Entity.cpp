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

	Entity::Entity(ce::Vector2<float> position, ce::Vector2<float> extent) : ce::game2d::ZoneEntity(position, extent)
	{
	}
	Entity::~Entity()
	{
		// TODO: Delete Javascript instance
	}
}
