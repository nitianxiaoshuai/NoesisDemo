#include <NoesisGUI.h>

class MyNsTest : public Noesis::Grid
{
public:
	MyNsTest();
	~MyNsTest();
	Noesis::StackPanel* diffusePanel_;
	void MyNsTest::initCollectionView();
	void MyNsTest::OnInitialized(Noesis::BaseComponent* sender, const Noesis::EventArgs& e);
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

class DataModel3 : public Noesis::BaseComponent
{
public:
	DataModel3()
	{
		_players = *new Noesis::ObservableCollection<Player>;

		Noesis::Ptr<Player> player0 = *new Player("Player0");
		_players->Add(player0.GetPtr());

		Noesis::Ptr<Player> player1 = *new Player("Player1");
		_players->Add(player1.GetPtr());

		Noesis::Ptr<Player> player2 = *new Player("Player2");
		_players->Add(player2.GetPtr());

		Noesis::Ptr<Player> player3 = *new Player("Player3");
		_players->Add(player3.GetPtr());
	}

private:
	Noesis::Ptr< Noesis::ObservableCollection<Player> > _players;

	NS_IMPLEMENT_INLINE_REFLECTION(DataModel3, BaseComponent)
	{
		NsMeta<Noesis::TypeId>("DataModel3");
		NsProp("Players", &DataModel3::_players);
	}
};
