#pragma once
#include "pch.h"
#include "MyNsTest.h"

MyNsTest::MyNsTest(){
	printf("mynstest ctor");
	Noesis::GUI::LoadComponent(this, "MainWindow.xaml");
}

MyNsTest::~MyNsTest(){
}