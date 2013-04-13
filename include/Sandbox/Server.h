#ifndef _SANDBOX_SERVER_H_
#define _SANDBOX_SERVER_H_

//- Javascript V8 -
#include <v8.h>

namespace sandbox
{
	class Server
	{
		static Server *ms_current;

		v8::HandleScope m_handleScope;
		v8::Persistent<v8::Context> m_context;

	public:
		static Server *GetCurrent();

		Server();
		~Server();

		bool ExecuteFile(const char *file);
		bool ExecuteString(const char *str);
	};
}

#endif
