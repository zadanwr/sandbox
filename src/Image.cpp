//- Centhra Engine -
#include <CE/Base.h>

//- Sandbox -
#include <Sandbox/Image.h>

using namespace v8;

namespace sandbox
{
	Image *Image::CreateFromFile(const char *file)
	{
		ce::Image *baseImage = ce::Image::CreateFromFile(file);

		if(!baseImage)
			return 0;

		Image *image = new Image();
		image->m_image = baseImage;

		Handle<ObjectTemplate> objectTemplate = ObjectTemplate::New();
		objectTemplate->SetInternalFieldCount(1);

		HandleScope handleScope;

		Persistent<Object> instance = Persistent<Object>::New(objectTemplate->NewInstance());
		instance->SetInternalField(0, External::New(image));
		image->m_instance = instance;

		return image;
	}
	Handle<Value> Image::Binding_image(const Arguments& args)
	{
		if(args.Length() < 1)
			return Undefined();
		HandleScope handleScope;

		String::Utf8Value value(args[0]);

		Image *image = Image::CreateFromFile(*value);
		return image->m_instance;
	}

	Image::Image()
	{
		m_image = 0;
	}
	Image::~Image()
	{
		m_instance.Dispose();
		m_instance.Clear();
		delete m_image;
	}
	ce::Image *Image::GetSource() const
	{
		return m_image;
	}
}
