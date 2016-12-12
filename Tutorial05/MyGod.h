#include <NoesisGUI.h>
#include<wpframework.h>
#include <stdio.h>
#include <vector>
#include<D3D11.h>
#include <string>
#include "pch.h"
#include "Include\NsGui\Style.h"
#include "Include\NsGui\UIElementCollection.h"
#include "Include\NsGui\ColumnDefinition.h"
#include "Include\NsCore\DelegateGenerator.h"
#define printf(x) OutputDebugStringA(x)
using namespace Noesis;
class MyNsTest : public Noesis::Grid
{
public:
	MyNsTest() 
	{
		Noesis::GUI::LoadComponent(this, "fangxin.xaml");
		
		diffusePanel_ = FindName<StackPanel>("panel");
		initCollectionView();
		this->Initialized() += MakeDelegate(this, &MyNsTest::OnInitialized);
	};

	~MyNsTest() {};

	Noesis::Gui::Button *button1_;
	Noesis::Gui::Button *button2_;
	Noesis::StackPanel* diffusePanel_;
	void OnInitialized(Noesis::BaseComponent* sender, const Noesis::EventArgs& e) {

	}
	void myMouseButtonDown(BaseComponent* sender, const Noesis::Gui::MouseButtonEventArgs& e) {
		if (e.leftButton == MouseButtonState_Pressed) {
			Noesis::Grid* mainGrid = FindName<Noesis::Grid>("mainSrceen");
			Noesis::Point p = mainGrid->PointFromScreen(e.position);
			Noesis::Gui::UIElementCollection* collection = mainGrid->GetChildren();
			Noesis::Ptr<Noesis::BitmapImage> image = *new Noesis::BitmapImage("hudie.png");
			Ptr<Noesis::Gui::Button> singleView = *new Noesis::Gui::Button();
			singleView->SetHorizontalAlignment(HorizontalAlignment_Left);
			singleView->SetVerticalAlignment(VerticalAlignment_Top);
			singleView->SetWidth(80);
			singleView->SetHeight(80);
			Noesis::Drawing::Thickness tmpmargin = this->getMovesMargin(p);
			singleView->SetMargin(tmpmargin);
			Noesis::Ptr<Noesis::ImageBrush> brush = *new Noesis::ImageBrush(image.GetPtr());
			singleView->SetBackground(brush.GetPtr());
			collection->Add(singleView.GetPtr());
			button1_ = singleView.GetPtr();
			button1_->MouseMove() += MakeDelegate(this, &MyNsTest::myMouseButtonMove);
			button1_->MouseUp() += MakeDelegate(this, &MyNsTest::myMouseButtonUp);
		}
	
	};
	void myMouseButtonUp(BaseComponent* sender, const Noesis::Gui::MouseButtonEventArgs& e) {
		Noesis::Grid* mianScrren = FindName<Noesis::Grid>("mainSrceen");
		mianScrren->GetChildren()->Remove(button1_);

		Noesis::Point p = mianScrren->PointFromScreen(e.position);
		Noesis::Grid* midgrid = FindName<Noesis::Grid>("midgrid");

		Noesis::Gui::UIElementCollection* collection = midgrid->GetChildren();
		Noesis::Ptr<Noesis::BitmapImage> image = *new Noesis::BitmapImage("hudie.png");
		Ptr<Noesis::Gui::Button> singleView = *new Noesis::Gui::Button();
		singleView->SetHorizontalAlignment(HorizontalAlignment_Left);
		singleView->SetVerticalAlignment(VerticalAlignment_Top);
		singleView->SetWidth(80);
		singleView->SetHeight(80);
		Noesis::Drawing::Thickness tmpmargin = this->getMidMargin(p);
		singleView->SetMargin(tmpmargin);
		Noesis::Ptr<Noesis::ImageBrush> brush = *new Noesis::ImageBrush(image.GetPtr());
		singleView->SetBackground(brush.GetPtr());

		collection->Add(singleView.GetPtr());
		button2_ = singleView.GetPtr();
	};
	void myMouseButtonMove(BaseComponent* sender, const Noesis::Gui::MouseEventArgs& e) {
		Noesis::Gui::Grid* mianScrren = FindName<Noesis::Gui::Grid>("mainSrceen");
		Noesis::Point p = mianScrren->PointFromScreen(e.position);
		Noesis::Drawing::Thickness tem = getMovesMargin(p);
		button1_->SetMargin(tem);
	};

	Noesis::Drawing::Thickness getMovesMargin(Noesis::Point curPoint)
{
	Noesis::Grid* mainGrid = FindName<Noesis::Grid>("mainSrceen");
	NsSize width = mainGrid->GetWidth();
	NsSize height = mainGrid->GetHeight();
	Noesis::Drawing::Thickness tmpmargin;
	tmpmargin.left = curPoint.x-40;
	tmpmargin.top = curPoint.y-40;
	tmpmargin.bottom = 0;
	tmpmargin.right = 0;
	return tmpmargin;
	};

	Noesis::Drawing::Thickness getMidMargin(Noesis::Point curPoint)
	{
		Noesis::Grid* mainGrid = FindName<Noesis::Grid>("midgrid");
		NsSize width = mainGrid->GetWidth();
		NsSize height = mainGrid->GetHeight();
		Noesis::Drawing::Thickness tmpmargin;
		tmpmargin.left = curPoint.x;
		tmpmargin.top = curPoint.y;
		tmpmargin.bottom = 0;
		tmpmargin.right = 0;
		return tmpmargin;
	};

	void initCollectionView() {

		Noesis::Gui::UIElementCollection* collection = diffusePanel_->GetChildren();
		collection->Clear();
		Noesis::ResourceDictionary* resource = GetResources();
		Noesis::Gui::Style* cellStyle = resource->FindName<Noesis::Gui::Style>("ImageCellStyle");
		for (int i = 0; i < 20; ++i) {
			Ptr<Noesis::Gui::Button> cell = *new Noesis::Gui::Button();
			cell->SetStyle(cellStyle);
			cell->MouseDown() += MakeDelegate(this, &MyNsTest::myMouseButtonDown);
			collection->Add(cell.GetPtr());
		}
	}
	

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
		NsProp("TitleName", &Player::_name);

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




