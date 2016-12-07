#pragma once
#include "pch.h"
#include "MyNsTest.h"

#include "Include\NsGui\UIElementCollection.h"
#include "Include\NsGui\Style.h"
#include <NoesisGUI.h>
using namespace Noesis;
using namespace Gui;

MyNsTesta::MyNsTesta(){
	Noesis::GUI::LoadComponent(this, "MySeecond.xaml");

}

MyNsTesta::~MyNsTesta() {}

