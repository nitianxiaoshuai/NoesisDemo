#pragma once
#include "pch.h"

class Player : public Noesis::BaseComponent
{
public:
	Player() {}
	Player(NsString name, Noesis::Color color, NsFloat32 scale, NsString pos) : _name(name), _scale(scale),
		_pos(pos), _color(*new Noesis::SolidColorBrush(color)) {}

private:
	NsString _name;
	NsFloat32 _scale;
	NsString _pos;
	Noesis::Ptr<Noesis::Brush> _color;

	NS_IMPLEMENT_INLINE_REFLECTION(Player, BaseComponent)
	{
		NsMeta<Noesis::TypeId>("Player");
		NsProp("Name", &Player::_name);
		NsProp("Scale", &Player::_scale);
		NsProp("Pos", &Player::_pos);
		NsProp("Color", &Player::_color);
	}

};

class DataModel3 : public Noesis::BaseComponent
{
public:
	DataModel3()
	{
		_players = *new Noesis::ObservableCollection<Player>;

		Noesis::Ptr<Player> player0 = *new Player("Player0", Noesis::Color::Red, 1.0f, "(0,0,0)");
		_players->Add(player0.GetPtr());

		Noesis::Ptr<Player> player1 = *new Player("Player1", Noesis::Color::Gray, 0.75f, "(0,30,0)");
		_players->Add(player1.GetPtr());

		Noesis::Ptr<Player> player2 = *new Player("Player2", Noesis::Color::Orange, 0.50f, "(0,-10,0)");
		_players->Add(player2.GetPtr());

		Noesis::Ptr<Player> player3 = *new Player("Player3", Noesis::Color::Green, 0.85f, "(0,-10,0)");
		_players->Add(player3.GetPtr());
	}

private:
	Noesis::Ptr<Noesis::ObservableCollection<Player> > _players;

	NS_IMPLEMENT_INLINE_REFLECTION(DataModel3, BaseComponent)
	{
		NsMeta<Noesis::TypeId>("DataModel3");
		NsProp("Players", &DataModel3::_players);
	}
};