#pragma once
#include "pch.h"
#include "MyNsTest.h"
#include <string>
MyNsTest::MyNsTest(){
	Noesis::GUI::LoadComponent(this, "addChuguiView.xaml");
	std::string str = "БъЬт";
	for (int i = 0; i < 20; i++) {
		gridTopData_.push_back(str + std::to_string(i));
	}
}

void MyNsTest::reloadView(){
	Grid g;
}

MyNsTest::~MyNsTest(){
}