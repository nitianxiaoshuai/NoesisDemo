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
	std::string str = "标题";
	for (int i = 0; i < 20; i++) {
		gridTopData_.push_back(str + std::to_string(i));
	}
	reloadView();
}
//https://msdn.microsoft.com/zh-cn/library/vs/alm/ms752271(v=vs.110).aspx
void MyNsTest::reloadView(){
	gridTop_ = FindName<Grid>("GridTop");
	
	Noesis::Gui::Style *style = GetResources()->FindName<Noesis::Gui::Style>("ButtonStyle");
	
	for (size_t i = 0; i < gridTopData_.size(); i++) {
		Ptr<Noesis::Gui::Button> btn = *new Noesis::Gui::Button();
		btn->SetContent(gridTopData_[i].c_str());
		btn->SetStyle(style);
		gridTop_->SetRow(btn.GetPtr(), 0);
		gridTop_->SetColumn(btn.GetPtr(), i);
		//Noesis::Gui::Grid::SetRow(btn.GetPtr(), 0);
		//Noesis::Gui::Grid::SetColumn(btn.GetPtr(), i);
		
	}
}

void MyNsTest::OnInitialized(Noesis::BaseComponent* sender, const Noesis::EventArgs& e) {

}

MyNsTest::~MyNsTest(){
}

/*
<Button  Grid.Column="0" Grid.Row="0" Content="标题1" Style="{StaticResource ButtonStyle}"></Button>
<Button  Grid.Column="1" Grid.Row="0" Content="标题2" Style="{StaticResource ButtonStyle}"></Button>
<Button  Grid.Column="2" Grid.Row="0" Content="标题3" Style="{StaticResource ButtonStyle}"></Button>
<Button  Grid.Column="3" Grid.Row="0" Content="标题4" Style="{StaticResource ButtonStyle}"></Button>
<Button  Grid.Column="4" Grid.Row="0" Content="标题5" Style="{StaticResource ButtonStyle}"></Button>
<Button  Grid.Column="5" Grid.Row="0" Content="标题6" Style="{StaticResource ButtonStyle}"></Button>
<Button  Grid.Column="6" Grid.Row="0" Content="标题7" Style="{StaticResource ButtonStyle}"></Button>
<Button  Grid.Column="7" Grid.Row="0" Content="标题8" Style="{StaticResource ButtonStyle}"></Button>
<Button  Grid.Column="8" Grid.Row="0" Content="标题9" Style="{StaticResource ButtonStyle}"></Button>
<Button  Grid.Column="9" Grid.Row="0" Content="标题10" Style="{StaticResource ButtonStyle}"></Button>
*/