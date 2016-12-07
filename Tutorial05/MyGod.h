#include <NoesisGUI.h>

#define printf(x) OutputDebugStringA(x)
class MyNsTest : public Noesis::Grid
{
public:
	MyNsTest() {
		Noesis::GUI::LoadComponent(this, "fangxin.xaml");
	};
	~MyNsTest() {};

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
		Noesis::Ptr<Noesis::BitmapImage> image = *new Noesis::BitmapImage("dapao.png");
		auto x = image->GetDpiX();
		auto y = image->GetDpiY();
		auto width = image->GetWidth();
		auto height = image->GetHeight();
		_brush = *new Noesis::ImageBrush(image.GetPtr());
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

class Player : public Noesis::BaseComponent
{
public:
	Player() {}
	Player(NsString name) : _name(name) {}

private:
	NsString _name;


	NS_IMPLEMENT_INLINE_REFLECTION(Player, BaseComponent)
	{
		NsMeta<Noesis::TypeId>("Player");
		NsProp("Name", &Player::_name);

	}

};

class DataModel3 : public Noesis::BaseComponent
{
public:
	DataModel3()
	{
		_players = *new Noesis::ObservableCollection<Player>;
		std::vector<NsString> nameVector{ "DDL","ssss2","DFG3","PPDLer4","PLKKJ","Pl" };

		for (NsInt i = 0; i < nameVector.size(); i++) {
			Noesis::Ptr<Player> player = *new Player(nameVector[i]);
			_players->Add(player.GetPtr());
		}
	}
private:
	Noesis::Ptr< Noesis::ObservableCollection<Player> > _players;

	NS_IMPLEMENT_INLINE_REFLECTION(DataModel3, BaseComponent)
	{
		NsMeta<Noesis::TypeId>("DataModel3");
		NsProp("Players", &DataModel3::_players);
	}
};



