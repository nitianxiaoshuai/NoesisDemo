#pragma once
#include "pch.h"
#include "MyNsTest.h"
#include "Include\NsGui\UIElementCollection.h"
#include "Include\NsGui\Style.h"


using namespace Noesis;

MyNsTest::MyNsTest(){
	this->Initialized() += MakeDelegate(this, &MyNsTest::OnInitialized);
	Noesis::GUI::LoadComponent(this, "moveButton.xaml");
	diffusePanel_ = FindName<StackPanel>("panel");
	initCollectionView();
	//Noesis::Gui::Button * but = FindName<Noesis::Gui::Button>("btn2");
	//but->MouseUp() += MakeDelegate(this, &MyNsTest::MouseUpEvent);
}

MyNsTest::~MyNsTest(){
}
void MyNsTest::OnInitialized(Noesis::BaseComponent* sender, const Noesis::EventArgs& e) {

}

void MyNsTest::MouseDownEvent(Noesis::Core::BaseComponent* sender, const Noesis::MouseButtonEventArgs& e) {
	if (e.leftButton == MouseButtonState_Pressed) {
		Noesis::Grid* mainGrid = FindName<Noesis::Grid>("mainGrid");
		Noesis::Point p = mainGrid->PointFromScreen(e.position);
		Noesis::Gui::UIElementCollection* collection = mainGrid->GetChildren();
		Noesis::Ptr<Noesis::BitmapImage> image = *new Noesis::BitmapImage("shenjian.png");
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
		button1_->MouseUp() += MakeDelegate(this, &MyNsTest::MouseUpEvent);
	}
}

void MyNsTest::MouseUpEvent(Noesis::BaseComponent*sender, const Noesis::Gui::MouseButtonEventArgs& e) {
	Noesis::Grid* mainGrid = FindName<Noesis::Grid>("mainGrid");
	mainGrid->GetChildren()->Remove(button1_);
}

void MyNsTest::myMouseButtonMove(Noesis::BaseComponent* sender, const  Noesis::Gui::MouseEventArgs& e) {
	Noesis::Grid* mainGrid = FindName<Noesis::Grid>("mainGrid");
	Noesis::Point p = mainGrid->PointFromScreen(e.position);
	Noesis::Drawing::Thickness tmpmargin = this->getMovesMargin(p);
	button1_->SetMargin(tmpmargin);
}

Noesis::Drawing::Thickness MyNsTest::getMovesMargin(Noesis::Point curPoint)
{
	Noesis::Grid* mainGrid = FindName<Noesis::Grid>("mainGrid");
	NsSize width = mainGrid->GetWidth();
	NsSize height = mainGrid->GetHeight();
	Noesis::Drawing::Thickness tmpmargin;
	tmpmargin.left = curPoint.x-40;
	tmpmargin.top = curPoint.y-40;
	tmpmargin.bottom = 0;
	tmpmargin.right = 0;
	return tmpmargin;
}



void MyNsTest::initCollectionView() {

	Noesis::Gui::UIElementCollection* collection = diffusePanel_->GetChildren();
	collection->Clear();
	Noesis::ResourceDictionary* resource = GetResources();
	Noesis::Gui::Style* cellStyle = resource->FindName<Noesis::Gui::Style>("ImageCellStyle");
	for (int i = 0; i < 20; ++i) {
		Ptr<Noesis::Gui::Button> cell = *new Noesis::Gui::Button();
		cell->SetStyle(cellStyle);
		cell->MouseDown() += MakeDelegate(this, &MyNsTest::MouseDownEvent);
		collection->Add(cell.GetPtr());
	}
}