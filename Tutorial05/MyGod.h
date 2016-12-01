#pragma once
#include<NoesisGUI.h>
#include<Noesis.h>

class MyGod : public Noesis::Grid
{
public:
	MyGod() {
		Noesis::GUI::LoadComponent(this, "MySeecond.xaml");
		title = "678";
	}
	~MyGod() {};
	NsString title;
	NS_IMPLEMENT_INLINE_REFLECTION(MyGod, Noesis::Grid)
	{
		NsMeta<Noesis::TypeId>("MyGod");
		NsProp("Name", &MyGod::title);
	}
};

class ModelShit: public Noesis::BaseComponent
{
public:
	ModelShit() {
		SetLast("56789");
	};

	~ModelShit() {
	
	};

	const NsChar* GetLast() const
	{
		return _name.c_str();
	}

	void SetLast(const NsString last)
	{
		if (_name != last)
		{
			_name = last;
		}
	}

	NsString _name;

	NS_IMPLEMENT_INLINE_REFLECTION(ModelShit, BaseComponent)
	{
		NsMeta<Noesis::TypeId>("ModelShit");
		NsProp("Names", &ModelShit::_name);
	}

};



