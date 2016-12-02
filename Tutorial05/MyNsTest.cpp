#pragma once
#include "pch.h"
#include "MyNsTest.h"

#include "Include\NsGui\UIElementCollection.h"
#include "Include\NsGui\Style.h"

using namespace Noesis;

MyNsTest::MyNsTest(){
	Noesis::GUI::LoadComponent(this, "MySeecond.xaml");
	//Noesis::GUI::LoadComponent(this, "cslizi.xaml");
}

MyNsTest::~MyNsTest(){
}

