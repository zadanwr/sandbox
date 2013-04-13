#ifndef _SANDBOX_SERVER_H_
#define _SANDBOX_SERVER_H_

//- Standard Library -
#include <string>

//- Javascript V8 -
#include <v8.h>

#include <CE/Base.h>
#include <CE/Canvas.h>
#include <CE/Thread.h>
#include <CE/Game2D/Plane.h>
#include <CE/Game2D/ZoneEntity.h>
#include <CE/Game2D/ZoneCamera.h>
#include <CE/UI/GameView2D.h>

namespace sandbox
{
	class Server
	{
		static Server *ms_current;

		v8::HandleScope m_handleScope;
		v8::Persistent<v8::Context> m_context;
		std::string m_serverName;
		ce::game2d::ZoneCamera *m_camera;
		ce::ui::GameView2D *m_view;

	public:
		static Server *GetCurrent();
		ce::game2d::Plane *m_plane;

		Server();
		~Server();

		bool ExecuteFile(const char *file);
		bool ExecuteString(const char *str);
		v8::Persistent<v8::Context> GetContext() const;
		void RegisterMod(const char *ModObject);
		bool SendKeydown(int key);
		bool SendKeyup(int key);
		void SetFocus(ce::game2d::ZoneEntity *c_entity);
		void PlaceEntity(ce::game2d::ZoneEntity *c_entity);
		void ProccessPhysics(float dt);
		void Render();
		void SendMouseButtonDown(ce::Event event);
		void RemoveDead();
	};
}

#endif
