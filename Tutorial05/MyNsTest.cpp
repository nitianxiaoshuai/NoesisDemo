#pragma once
#include "pch.h"
#include "MyNsTest.h"

MyNsTest::MyNsTest(){
	Noesis::GUI::LoadComponent(this, "MyNsTest.xaml");
}

MyNsTest::~MyNsTest(){
}