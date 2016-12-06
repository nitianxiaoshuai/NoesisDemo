#include <NoesisGUI.h>

#define printf(x) OutputDebugStringA(x)
class MyNsTest : public Noesis::Grid
{
public:
	MyNsTest();
	~MyNsTest();
	
	NS_IMPLEMENT_INLINE_REFLECTION(MyNsTest, Noesis::Grid)
	{
		NsMeta<Noesis::TypeId>("MyNsTest");
	}
};

class Shit1 : public Noesis::BaseComponent
{
public:
	Shit1() {}
	explicit Shit1(NsString name) : _name(name), _imagePath("test.jpg")
	{
		//TODO: byte-array to bitmap
		Noesis::Ptr<Noesis::BitmapImage> image = *new Noesis::BitmapImage("test.jpg");
		auto x = image->GetDpiX();
		auto y = image->GetDpiY();
		auto width = image->GetWidth();
		auto height = image->GetHeight();
		FILE *f;
		fopen_s(&f, "resource\\test.bmp", "rb");
		auto buffer_size = fseek(f, 0, SEEK_END);
		rewind(f);
		NsByte * buffer = static_cast<NsByte *>(malloc(sizeof(unsigned char)*buffer_size));
		fread(buffer, 1, buffer_size, f);
		Noesis::Ptr<Noesis::BitmapSource> source = Noesis::BitmapSource::Create(
			width, height, x,
			// @BUG: buffer is not BGRA32 formatted. to be solved
			y, buffer, buffer_size, width/8);
		_brush = *new Noesis::ImageBrush(source.GetPtr());
		printf("shit1 ctor;");
	}

private:
	NsString _name;
	NsString _imagePath;
	Noesis::Ptr<Noesis::ImageBrush> _brush;

	NS_IMPLEMENT_INLINE_REFLECTION(Shit1, Noesis::BaseComponent)
	{
		NsMeta<Noesis::TypeId>("Shit1");
		NsProp("Name", &Shit1::_name);
		NsProp("ImagePath", &Shit1::_imagePath);
		NsProp("Brush", &Shit1::_brush);
	}
};

class Shit1Collection : public Noesis::BaseComponent
{
public:
	Shit1Collection()
	{
		printf("shit1 collection ctor");
		_shit1 = *new Noesis::ObservableCollection<Shit1>;
		Noesis::Ptr<Shit1> shit11 = *new Shit1("haha");
		_shit1->Add(shit11.GetPtr());
		Noesis::Ptr<Shit1> shit12 = *new Shit1("haha");
		_shit1->Add(shit12.GetPtr());
		Noesis::Ptr<Shit1> shit13 = *new Shit1("haha");
		_shit1->Add(shit13.GetPtr());
		Noesis::Ptr<Shit1> shit14 = *new Shit1("haha");
		_shit1->Add(shit14.GetPtr());
	}

private:
	Noesis::Ptr<Noesis::ObservableCollection<Shit1>> _shit1;

	NS_IMPLEMENT_INLINE_REFLECTION(Shit1Collection, Noesis::BaseComponent)
	{
		NsMeta<Noesis::TypeId>("Shit1Collection");
		NsProp("Shit1s", &Shit1Collection::_shit1);
	}
};
