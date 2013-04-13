#ifndef _SANDBOX_SPRITE_H_
#define _SANDBOX_SPRITE_H_

//- Standard Library -
#include <string>

//- Centhra Engine -
#include <CE/Game2D/Sprite.h>
#include <Sandbox/Image.h>

//- Javascript V8 -
#include <v8.h>

namespace sandbox
{
	class Sprite
	{
		ce::game2d::Sprite *m_sprite;
		Image *m_image;
		v8::Persistent<v8::Object> m_instance;

		Sprite();

	public:
		static Sprite *Create(Image *image);
		static v8::Handle<v8::Value> Binding_sprite(const v8::Arguments& args);

		ce::game2d::Sprite *GetSource() const;

		~Sprite();
	};
}

#endif
