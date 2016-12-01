#pragma once
#include <NoesisGUI.h>
#include <string>
#include <stdio.h>

class ModelSecond : public Noesis::BaseComponent
{
public:
	ModelSecond() {};
	ModelSecond(NsString  t1, std::string t2, std::string t4, std::string t3, std::string t5, std::string t6) :textTitle1(t1) , textTitle2(t2), textTitle3(t3), textTitle4(t4), textTitle5(t5), textTitle6(t6){};
	~ModelSecond() {};

private:
	NsString  textTitle1;
	std::string textTitle2;
	std::string textTitle3;
	std::string textTitle4;
	std::string textTitle5;
	std::string textTitle6;
	NS_IMPLEMENT_INLINE_REFLECTION(ModelSecond, BaseComponent)
	{
		NsMeta<Noesis::TypeId>("ModelSecond");
		NsProp("textTitle1", &ModelSecond::textTitle1);
	}
};

class ModelThree : public Noesis::BaseComponent {
public:
	ModelThree() {
		Noesis::Ptr<ModelSecond> second = *new ModelSecond("aa","bb","cc","dd","ee","ff");
	};
	~ModelThree() {};
private:
	Noesis::Ptr<ModelSecond> second;

	NS_IMPLEMENT_INLINE_REFLECTION(ModelThree, BaseComponent)
	{
		NsMeta<Noesis::TypeId>("ModelThree");
		NsProp("Model", &ModelThree::second);
	}
};



class MySeecond : public Noesis::Grid
{
public:
	MySeecond();
	~MySeecond();
private:
		NS_IMPLEMENT_INLINE_REFLECTION(MySeecond, Noesis::Grid)
	{
		NsMeta<Noesis::TypeId>("MySeecond");
	}
};