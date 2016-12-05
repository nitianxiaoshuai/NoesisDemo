#pragma once
#include "pch.h"
#include "MyNsTest.h"
#include <string>
#include "Include\NsGui\Style.h"
#include "Include\NsGui\UIElementCollection.h"
#include "Include\NsGui\ColumnDefinition.h"
using namespace Noesis;

MyNsTest::MyNsTest(){
	this->Initialized() += MakeDelegate(this, &MyNsTest::OnInitialized);
	Noesis::GUI::LoadComponent(this, "addChuguiView.xaml");
	std::string str = "БъЬт";
	for (int i = 0; i < 20; i++) {
		gridTopData_.push_back(str + std::to_string(i));
	}
	reloadView();
}
//https://msdn.microsoft.com/zh-cn/library/vs/alm/ms752271(v=vs.110).aspx
void MyNsTest::reloadView(){
	gridTop_ = FindName<Grid>("GridTop");
	gridTop_->GetRowDefinitions()->Clear();
	gridTop_->GetColumnDefinitions()->Clear();
	
	Style *style = GetResources()->FindName<Style>("ButtonStyle");

	gridTop_->GetRowDefinitions()->Add(new RowDefinition());

	for (int i = 0; i < gridTopData_.size(); i++) {
		gridTop_->GetColumnDefinitions()->Add(new ColumnDefinition());

		Ptr<Button> btn = *new Button();
		btn->SetStyle(style);
		btn->SetContent(gridTopData_[i].c_str());

		gridTop_->SetRow(btn.GetPtr(), 0);
		gridTop_->SetColumn(btn.GetPtr(), i);
		//Noesis::Gui::Grid::SetRow(btn.GetPtr(), 1);
		//Noesis::Gui::Grid::SetColumn(btn.GetPtr(), i);
		
		gridTop_->GetChildren()->Add(btn.GetPtr());
	}
}

void MyNsTest::OnInitialized(Noesis::BaseComponent* sender, const Noesis::EventArgs& e) {

}

MyNsTest::~MyNsTest(){
}
