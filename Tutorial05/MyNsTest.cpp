#pragma once
#include "pch.h"
#include "MyNsTest.h"
#include "Include\NsGui\UIElementCollection.h"
#include "Include\NsGui\Style.h"


using namespace Noesis;

MyNsTest::MyNsTest(){
	this->Initialized() += MakeDelegate(this, &MyNsTest::OnInitialized);
	//Noesis::GUI::LoadComponent(this, "fangxin.xaml");
	//diffusePanel_ = FindName<StackPanel>("diffusePicPanel");
	//initCollectionView();
	Noesis::GUI::LoadComponent(this, "zhaochuangtest.xaml");
	Noesis::Gui::Button * but = FindName<Noesis::Gui::Button>("but3");
	but->Click() += butClick;
	CreateView();
}

MyNsTest::~MyNsTest(){
}
void MyNsTest::OnInitialized(Noesis::BaseComponent* sender, const Noesis::EventArgs& e) {

}

void MyNsTest::butClick(Noesis::BaseComponent*sender, const Noesis::Gui::RoutedEventArgs& e) {
	printf("111111111111111111111111111");
}

/*void MyNsTest::initCollectionView() {

	Noesis::Gui::UIElementCollection* collection = diffusePanel_->GetChildren();
	collection->Clear();
	Noesis::ResourceDictionary* resource = GetResources();
	Noesis::Gui::Style* cellStyle = resource->FindName<Noesis::Gui::Style>("ImageCellStyle");
	for (int i = 0; i < 20; ++i) {
		Ptr<Noesis::Gui::Label> cell = *new Noesis::Gui::Label();
		cell->SetContent("TEST");
		//cell->SetItemData(data.GetPtr());
		cell->SetStyle(cellStyle);
		collection->Add(cell.GetPtr());
	}
}*/

void MyNsTest::CreateView() {
	Noesis::Grid* diffuseGrid = FindName<Noesis::Grid>("mainGrid");
	Noesis::Gui::UIElementCollection* collection = diffuseGrid->GetChildren();
	Noesis::Ptr<Noesis::BitmapImage> image = *new Noesis::BitmapImage("shenjian.png");
	Ptr<Noesis::Gui::Button> singleView = *new Noesis::Gui::Button();
	singleView->SetWidth(80);
	singleView->SetHeight(80);
	Noesis::Ptr<Noesis::ImageBrush> brush = *new Noesis::ImageBrush(image.GetPtr());
	singleView->SetBackground(brush.GetPtr());
	collection->Add(singleView.GetPtr());
}