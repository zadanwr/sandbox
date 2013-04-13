//- Centhra Engine -
#include <CE/Base.h>
#include <CE/App.h>

//- Sandbox -
#include <Sandbox/Entity.h>

#ifdef _WIN32
	//- Windows -
	#include <Windows.h>
#endif

//- OpenGL -
#include <GL/gl.h>

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
		objectTemplate->Set(String::New("kill"), FunctionTemplate::New(Binding_kill));
		objectTemplate->Set(String::New("setSprite"), FunctionTemplate::New(Binding_setSprite));
		objectTemplate->Set(String::New("setAnimation"), FunctionTemplate::New(Binding_setAnimation));
		
		HandleScope handleScope;

		Entity *entity = new Entity(position, extent);
		Persistent<Object> instance = Persistent<Object>::New(objectTemplate->NewInstance());
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
	Handle<Value> Entity::Binding_kill(const Arguments& args)
	{
		HandleScope handleScope;
		Local<Object> self = args.This();
		Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
		void* ptr = wrap->Value();
		static_cast<Entity *>(ptr)->Kill();

		
		return Undefined();
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
	Handle<Value> Entity::Binding_setID(const Arguments& args)
	{
		if(args.Length() < 1)
			return Undefined();

		HandleScope handleScope;

		Local<Object> self = args.This();
		Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
		void* ptr = wrap->Value();
		//static_cast<Entity *>(ptr)->SetPosition(ce::Vector2<float>((float)args[0]->NumberValue(), (float)args[1]->NumberValue()));

		static_cast<Entity *>(ptr)->id = args[0]->IntegerValue();

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
	Handle<Value> Entity::Binding_setSprite(const Arguments& args)
	{
		if(args.Length() < 1)
			return Undefined();

		HandleScope handleScope;

		Local<Object> self = args.This();
		Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
		void* ptr = wrap->Value();

		Local<Object> sprite = Local<Object>::Cast(args[0]);
		Local<External> wrap2 = Local<External>::Cast(sprite->GetInternalField(0));
		void* ptr2 = wrap2->Value();
		Sprite *spr = static_cast<Sprite *>(ptr2);
		static_cast<Entity *>(ptr)->m_sprite = spr;

		return Undefined();
	}
	Handle<Value> Entity::Binding_setAnimation(const Arguments& args)
	{
		if(args.Length() < 1)
			return Undefined();

		HandleScope handleScope;

		Local<Object> self = args.This();
		Local<External> wrap = Local<External>::Cast(self->GetInternalField(0));
		void* ptr = wrap->Value();

		Entity *entity = static_cast<Entity *>(ptr);
		entity->m_animation = args[0]->IntegerValue();
		entity->m_animationStart = ce::App::GetCurrent()->GetRunTimeMS();

		return Undefined();
	}
	bool Entity::OnCollision(ce::game2d::ZoneEntity *collider) {

		HandleScope handleScope;

		Handle<Function> onEvent = Handle<Function>::Cast(this->m_instance->Get(String::New("onCollide")));
		v8::Handle<v8::Value> args[] = {((Entity *)collider)->m_instance};
		onEvent->Call(onEvent,1,args);
		return true;
	}

	Entity::Entity(ce::Vector2<float> position, ce::Vector2<float> extent) : ce::game2d::ZoneEntity(position, extent)
	{
		m_sprite = 0;
		m_animation = 0;
		m_animationStart = 0;
	}
	Entity::~Entity()
	{
		m_instance.Dispose();
		m_instance.Clear();
	}
	void Entity::DoRender()
	{
		if(m_sprite)
		{
			ce::Vector2<float> extent = GetExtent();
			glPushMatrix();
				glScalef(extent[0], extent[1], 1.f);
				float t = (ce::App::GetCurrent()->GetRunTimeMS() - m_animationStart) / 1000.f;
				m_sprite->GetSource()->Draw(m_animation, t);
			glPopMatrix();
		}
		else
			ce::game2d::ZoneEntity::DoRender();
	}
}
