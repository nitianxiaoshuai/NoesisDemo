#pragma once
#include "pch.h"
#include "MyNsTest.h"

#include "Include\NsGui\UIElementCollection.h"
#include "Include\NsGui\Style.h"
#include <NoesisGUI.h>
using namespace Noesis;
using namespace Gui;

MyNsTest::MyNsTest(){
	Noesis::GUI::LoadComponent(this, "MySeecond.xaml");

}

MyNsTest::~MyNsTest() {}

Noesis::Image DataModel3::getiamge(NsString str) {
	Noesis::Gui::Image();
}
