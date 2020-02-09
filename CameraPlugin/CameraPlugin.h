#pragma once
#include "bakkesmod/plugin/bakkesmodplugin.h";
#pragma comment( lib, "bakkesmod.lib")

class CameraPlugin : public BakkesMod::Plugin::BakkesModPlugin
{
public:
	virtual void onLoad();
	virtual void onUnload();
};
