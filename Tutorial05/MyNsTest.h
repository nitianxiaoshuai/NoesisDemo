#include <NoesisGUI.h>
#pragma once
#ifdef WIN32
#pragma execution_character_set("utf-8")
#endif

#include <NoesisGUI.h>


class MyNsTest : public Noesis::Grid
{
public:
	Noesis::StackPanel* diffusePanel_;
public:
	MyNsTest();
	~MyNsTest();

	void MyNsTest::initCollectionView();
	void MyNsTest::OnInitialized(Noesis::BaseComponent* sender, const Noesis::EventArgs& e);
	
	NS_IMPLEMENT_INLINE_REFLECTION(MyNsTest, Noesis::Grid)
	{
		NsMeta<Noesis::TypeId>("MyNsTest");
	}
};