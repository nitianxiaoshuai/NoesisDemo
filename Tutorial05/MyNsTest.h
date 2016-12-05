#include <NoesisGUI.h>
#include <stdio.h>
#include <vector>

class MyNsTest : public Noesis::Grid
{
public:
	MyNsTest();
	~MyNsTest();
	//Noesis::StackPanel* diffusePanel_;
	//void MyNsTest::initCollectionView();
	//void MyNsTest::OnInitialized(Noesis::BaseComponent* sender, const Noesis::EventArgs& e);
	NS_IMPLEMENT_INLINE_REFLECTION(MyNsTest, Noesis::Grid)
	{
		NsMeta<Noesis::TypeId>("MyNsTest");
	}
};
class Player : public Noesis::BaseComponent
{
public:
	Player() {}
	Player(NsString name,NsString imageName) : _name(name), _imageName(imageName){}

private:
	NsString _name;
	NsString _imageName;
	//BitmapImage _image;

	NS_IMPLEMENT_INLINE_REFLECTION(Player, BaseComponent)
	{
		NsMeta<Noesis::TypeId>("Player");
		NsProp("Name1", &Player::_name);
		NsProp("Name2", &Player::_name);
		NsProp("ImageName", &Player::_imageName);
		//NsProp("Image"), &Player::_image);
	}

};

class DataModel3 : public Noesis::BaseComponent
{
public:
	DataModel3()
	{
		_players = *new Noesis::ObservableCollection<Player>;
		std::vector<NsString> nameVector{"Player1","Player2","Player3","Player4","Player5","Player6","Player7","Player8","Player9","Player10","Player11","Player12","Player13","Player14", "Player15"};
		std::vector<NsString> imageName{"shenjian.png","dianchui.png"};
		for (NsInt i = 0; i < nameVector.size(); i++) {
			NsString imgName = "";
			if (i % 2 == 0) {
				imgName = imageName[0];
			} 
			else {
				imgName = imageName[1];
			}
			Noesis::Ptr<Player> player = *new Player(nameVector[i], imgName);
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
