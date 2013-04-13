//- Centhra Engine -
#include <CE/Base.h>

//- Sandbox -
#include <Sandbox/Sprite.h>

using namespace v8;

namespace sandbox
{
	Sprite *Sprite::Create(Image *image)
	{
		ce::game2d::Sprite *baseSprite = new ce::game2d::Sprite(image->GetSource());
		Sprite *sprite = new Sprite();
		sprite->m_sprite = baseSprite;

		Handle<ObjectTemplate> objectTemplate = ObjectTemplate::New();
		objectTemplate->SetInternalFieldCount(1);

		HandleScope handleScope;

		Persistent<Object> instance = Persistent<Object>::New(objectTemplate->NewInstance());
		instance->SetInternalField(0, External::New(sprite));
		sprite->m_instance = instance;

		return sprite;
	}
	Handle<Value> Sprite::Binding_sprite(const Arguments& args)
	{
		if(args.Length() < 1)
			return Undefined();
		HandleScope handleScope;

		Local<Object> image = Local<Object>::Cast(args[0]);
		Local<External> wrap = Local<External>::Cast(image->GetInternalField(0));
		void* ptr = wrap->Value();

		Image *img = static_cast<Image *>(ptr);
		Sprite *sprite = Sprite::Create(img);
		return sprite->m_instance;
	}
	Handle<Value> Sprite::Binding_addAnimation(const Arguments& args)
	{
		if(args.Length() < 8)
			return Undefined();
		HandleScope handleScope;

		Local<Object> sprite = Local<Object>::Cast(args.This());
		Local<External> wrap = Local<External>::Cast(sprite->GetInternalField(0));
		void* ptr = wrap->Value();
		Sprite *sp = static_cast<Sprite *>(ptr);

		float minX = (float)args[0]->NumberValue();
		float minY = (float)args[1]->NumberValue();
		float maxX = (float)args[2]->NumberValue();
		float maxY = (float)args[3]->NumberValue();
		float stepX = (float)args[4]->NumberValue();
		float stepY = (float)args[5]->NumberValue();
		int numSteps = args[7]->IntegerValue();
		float *times = new float[numSteps];
		Local<Array> timeArray = Local<Array>::Cast(args[6]);
		for(int a = 0; a < numSteps; a++)
			times[a] = (float)timeArray->Get(a)->NumberValue();
		sp->GetSource()->AddAnimation(ce::Vector2<float>(minX, minY), ce::Vector2<float>(maxX, maxY), ce::Vector2<float>(stepX, stepY), times, numSteps);
		delete [] times;

		return Undefined();
	}

	Sprite::Sprite()
	{
		m_sprite = 0;
		m_image = 0;
	}
	Sprite::~Sprite()
	{
		m_instance.Dispose();
		m_instance.Clear();
		delete m_sprite;
	}
	ce::game2d::Sprite *Sprite::GetSource() const
	{
		return m_sprite;
	}
}
