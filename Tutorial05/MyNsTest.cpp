#pragma once
#include "pch.h"
#include "MyNsTest.h"

#include "Include\NsGui\UIElementCollection.h"
#include "Include\NsGui\Style.h"

using namespace Noesis;

MyNsTest::MyNsTest(){
	this->Initialized() += MakeDelegate(this, &MyNsTest::OnInitialized);
	Noesis::GUI::LoadComponent(this, "fangxin.xaml");
	diffusePanel_ = FindName<StackPanel>("diffusePicPanel");
	initCollectionView();
	//Noesis::GUI::LoadComponent(this, "cslizi.xaml");
}

MyNsTest::~MyNsTest(){
}
void MyNsTest::OnInitialized(Noesis::BaseComponent* sender, const Noesis::EventArgs& e) {

}

void MyNsTest::initCollectionView() {

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
}