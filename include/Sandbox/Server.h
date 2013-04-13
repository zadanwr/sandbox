#ifndef _SANDBOX_SERVER_H_
#define _SANDBOX_SERVER_H_

//- Javascript V8 -
#include <v8.h>
#include <string>

namespace sandbox
{
	class Server
	{
		static Server *ms_current;

		v8::HandleScope m_handleScope;
		v8::Persistent<v8::Context> m_context;
		std::string m_serverName;

	public:
		static Server *GetCurrent();

		Server();
		~Server();

		bool ExecuteFile(const char *file);
		bool ExecuteString(const char *str);
		v8::Persistent<v8::Context> GetContext() const;
		void RegisterMod(const char *ModObject);
		bool SendKeydown(int key);
	};
}

#endif
