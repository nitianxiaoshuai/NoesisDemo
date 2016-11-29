#pragma once

class NsManager{
public:
	NsManager();
	~NsManager();

	static NsManager* getSingleton();
	void NsRegisterReflection(bool registerComponents);

private:
	static NsManager* singleton;

};