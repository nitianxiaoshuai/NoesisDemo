#pragma once
#include "pch.h"
#include "MyNsTest.h"
#include <string>
#include "Include\NsGui\Style.h"
#include "Include\NsGui\UIElementCollection.h"
MyNsTest::MyNsTest(){
	this->Initialized() += MakeDelegate(this, &MyNsTest::OnInitialized);
	Noesis::GUI::LoadComponent(this, "addChuguiView.xaml");
	std::string str = "БъЬт";
	for (int i = 0; i < 20; i++) {
		gridTopData_.push_back(str + std::to_string(i));
	}
}

void MyNsTest::reloadView(){
	gridTop_ = FindName<Grid>("GridTop");
	//gridTop_
}

void MyNsTest::OnInitialized(Noesis::BaseComponent* sender, const Noesis::EventArgs& e) {

}

MyNsTest::~MyNsTest(){
}