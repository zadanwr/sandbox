#ifndef _SANDBOX_MOD_H_
#define _SANDBOX_MOD_H_

namespace sandbox
{
	class Mod
	{
		Mod();

	public:
		static Mod *CreateFromFile(const char *);
	};
}

#endif
