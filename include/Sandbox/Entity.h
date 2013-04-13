#ifndef _SANDBOX_ENTITY_H_
#define _SANDBOX_ENTITY_H_

//- Standard Library -
#include <string>

//- Centhra Engine -
#include <CE/Game2D/ZoneEntity.h>

//- Javascript V8 -
#include <v8.h>

#include "Server.h"

namespace sandbox
{
	class Entity : public ce::game2d::ZoneEntity
	{
		v8::Persistent<v8::Object> m_instance;
		Entity(ce::Vector2<float> position, ce::Vector2<float> extent);
		
	public:
		int id;
		static Entity *Create(ce::Vector2<float> position, ce::Vector2<float> extent);
		static v8::Handle<v8::Value> Binding_entity(const v8::Arguments& args);
		static v8::Handle<v8::Value> Binding_getPosition(const v8::Arguments& args);
		static v8::Handle<v8::Value> Binding_getExtent(const v8::Arguments& args);
		static v8::Handle<v8::Value> Binding_getVelocity(const v8::Arguments& args);
		static v8::Handle<v8::Value> Binding_setPosition(const v8::Arguments& args);
		static v8::Handle<v8::Value> Binding_setExtent(const v8::Arguments& args);
		static v8::Handle<v8::Value> Binding_setVelocity(const v8::Arguments& args);
		static v8::Handle<v8::Value> Binding_setAsFocus(const v8::Arguments& args);
		static v8::Handle<v8::Value> Binding_setID(const v8::Arguments& args);
		static v8::Handle<v8::Value> Binding_kill(const v8::Arguments& args);
		bool OnCollision(ce::game2d::ZoneEntity *collider);

		~Entity();
	};
}

#endif
