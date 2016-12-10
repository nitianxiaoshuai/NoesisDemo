#include <NoesisGUI.h>
#include<wpframework.h>
#include <stdio.h>
#include <vector>
#include<D3D11.h>
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
		NsString str = "title";
		for (int i = 0; i < 20; i++) {
			gridTopData_.push_back(str + Noesis::ToString(i));
		}
		reloadView();
	}

	~MyNsTest() {};
	Noesis::Grid *gridTop_;
	std::vector<NsString> gridTopData_;
	void reloadView() {
		gridTop_ = FindName<Grid>("GridTop");
		gridTop_->GetRowDefinitions()->Clear();
		gridTop_->GetColumnDefinitions()->Clear();

		Noesis::Style *style = GetResources()->FindName<Noesis::Style>("ButtonStyle");
		Noesis::Ptr<Noesis::RowDefinition> row = *new Noesis::RowDefinition();
		row->SetHeight(45);
		gridTop_->GetRowDefinitions()->Add(row.GetPtr());

		for (int i = 0; i < gridTopData_.size(); i++) {
			Noesis::Ptr<Noesis::ColumnDefinition> column = *new Noesis::ColumnDefinition();
			column->SetWidth(80);
			gridTop_->GetColumnDefinitions()->Add(column.GetPtr());

			Noesis::Ptr<Noesis::Button> btn = *new Noesis::Button();
			btn->SetStyle(style);
			btn->SetContent(gridTopData_[i].c_str());

			gridTop_->SetRow(btn.GetPtr(), 0);
			gridTop_->SetColumn(btn.GetPtr(), i);

			gridTop_->GetChildren()->Add(btn.GetPtr());
		}
		Noesis::Button *btn = FindName<Noesis::Button>("Button1");
		btn->MouseDown += Noesis::Core::MakeDelegate(this,&myMouseButtonDown);
		btn->MouseUp += Noesis::Core::MakeDelegate(this, &myMouseButtonUp);
		btn->MouseMove += Noesis::Core::MakeDelegate(this,&myMouseButtonMove);
		btn->Click() += Noesis::Core::MakeDelegate(this,&myMouseButtonDown);
	};

	void myMouseButtonDown(BaseComponent* sender, const Noesis::Gui::RoutedEventArgs& e) {};
	void myMouseButtonUp(BaseComponent* sender, const Noesis::Gui::RoutedEventArgs& e) {};
	void myMouseButtonMove(BaseComponent* sender, const Noesis::Gui::RoutedEventArgs& e) {};

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

class MyTouch : public Noesis::Grid
{
public:
	MyTouch() {};
	~MyTouch() {};

	void OnManipulationStarting(const Noesis::ManipulationStartingEventArgs& e)
	{
		e.mode = Noesis::ManipulationModes_All;
		e.manipulationContainer = (Noesis::Visual*) FindName("root");
		e.handled = true;
	}

	void OnManipulationInertiaStarting(const Noesis::ManipulationInertiaStartingEventArgs& e)
	{
		e.translationBehavior.desiredDeceleration = 100.0f / (1000.0f * 1000.0f);
		e.rotationBehavior.desiredDeceleration = 360.0f / (1000.0f * 1000.0f);
		e.expansionBehavior.desiredDeceleration = 300.0f / (1000.0f * 1000.0f);
		e.handled = true;
	}

	void OnManipulationDelta(const Noesis::ManipulationDeltaEventArgs& e)
	{
		Noesis::UIElement* rectangle = (Noesis::UIElement*)e.source;
		Noesis::MatrixTransform* tr = (Noesis::MatrixTransform*)rectangle->GetRenderTransform();
		Noesis::Transform2f mtx = tr->GetMatrix();

		mtx.RotateAt(e.deltaManipulation.rotation * Noesis::DegToRad_f, e.manipulationOrigin.x,
			e.manipulationOrigin.y);
		mtx.ScaleAt(e.deltaManipulation.scale, e.deltaManipulation.scale,
			e.manipulationOrigin.x, e.manipulationOrigin.y);
		mtx.Translate(e.deltaManipulation.translation.x, e.deltaManipulation.translation.y);

		tr->SetMatrix(mtx);
		e.handled = true;
	}

private:
	NS_IMPLEMENT_INLINE_REFLECTION(MyTouch, Noesis::Grid)
	{
		NsMeta<Noesis::TypeId>("MyTouch");
	}
};




