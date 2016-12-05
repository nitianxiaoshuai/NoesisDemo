#include <NoesisGUI.h>
#include<wpframework.h>
#include <stdio.h>
#include <vector>
#include<D3D11.h>
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

class ImageN : public Noesis::BaseComponent {
public:
	ImageN() {};
	ImageN( NsString imageName) : _imageName(imageName) {}
	NsString _imageName;

	NS_IMPLEMENT_INLINE_REFLECTION(ImageN, BaseComponent)
	{
		NsMeta<Noesis::TypeId>("ImageN");
		NsProp("ImageName", &ImageN::_imageName);
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




class DataModel4 : public Noesis::BaseComponent
{
public:
	DataModel4()
	{
		_imageN = *new Noesis::ObservableCollection<ImageN>;
		std::vector<NsString> imageNameV{ "hudie.png","shenjian.png","anmie.png","dapao.png" };
		for (NsInt i = 0; i < imageNameV.size(); i++) {
			Noesis::Ptr<ImageN> img = *new ImageN(imageNameV[i]);
			_imageN->Add(img.GetPtr());
		}
	}
private:
	Noesis::Ptr< Noesis::ObservableCollection<ImageN> > _imageN;

	NS_IMPLEMENT_INLINE_REFLECTION(DataModel4, BaseComponent)
	{
		NsMeta<Noesis::TypeId>("DataModel4");
		NsProp("ImageNN", &DataModel4::_imageN);
	}
};
