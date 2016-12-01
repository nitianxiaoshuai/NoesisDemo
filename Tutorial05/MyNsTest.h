#include <NoesisGUI.h>
#include <stdio.h>
#include <string>
#include <vector>

class MyNsTest : public Noesis::Grid
{
public:
	MyNsTest();
	~MyNsTest();
	Noesis::StackPanel* diffusePanel_;
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
	Player(NsString name) : _name(name) {}

private:
	NsString _name;
	//NsString _imagename;

	NS_IMPLEMENT_INLINE_REFLECTION(Player, BaseComponent)
	{
		NsMeta<Noesis::TypeId>("Player");
		NsProp("Name", &Player::_name);
		//NsProp("ImageName", &Player::_imagename);
	}

};

class DataModel3 : public Noesis::BaseComponent
{
public:
	DataModel3()
	{
		_players = *new Noesis::ObservableCollection<Player>;
		std::vector<NsString> nameVector{"Player1","Player2","Player3","Player4","Player5","Player6","Player7","Player8","Player9","Player10","Player11","Player12","Player13","Player14", "Player15"};
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
