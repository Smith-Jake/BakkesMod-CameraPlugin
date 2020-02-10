#pragma once
#include "bakkesmod/plugin/bakkesmodplugin.h";
#pragma comment( lib, "bakkesmod.lib")

class CameraPlugin : public BakkesMod::Plugin::BakkesModPlugin
{
private:
	bool enabled = false;
	float DISTANCE, FOV;

public:
	virtual void onLoad();
	virtual void onUnload();
};
