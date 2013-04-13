#ifndef _SANDBOX_IMAGE_H_
#define _SANDBOX_IMAGE_H_

//- Standard Library -
#include <string>

//- Centhra Engine -
#include <CE/Image.h>

//- Javascript V8 -
#include <v8.h>

namespace sandbox
{
	class Image
	{
		ce::Image *m_image;
		v8::Persistent<v8::Object> m_instance;
		Image();

	public:
		static Image *CreateFromFile(const char *file);
		static v8::Handle<v8::Value> Binding_image(const v8::Arguments& args);

		ce::Image *GetSource() const;

		~Image();
	};
}

#endif
