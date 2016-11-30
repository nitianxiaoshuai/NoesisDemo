#include "pch.h"
#include "NsManager.h"
#include "MyNsTest.h"
#include "Demo.h"

NsManager* NsManager::singleton = 0;
NsManager::NsManager(){
	
}

NsManager::~NsManager(){

}

NsManager* NsManager::getSingleton(){
	if (singleton == NULL){
		singleton = new NsManager();
	}
	return singleton;
}

void NsManager::NsRegisterReflection(bool registerComponents)
{
	NS_REGISTER_COMPONENT(MyNsTest)
	NS_REGISTER_COMPONENT(Shit1Collection)
	NS_REGISTER_COMPONENT(Shit1)
	NS_REGISTER_COMPONENT(DataModel3)
	NS_REGISTER_COMPONENT(Player)
}