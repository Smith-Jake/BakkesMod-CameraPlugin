#pragma once
#include "bakkesmod/plugin/bakkesmodplugin.h";
#pragma comment( lib, "bakkesmod.lib")

class CameraPlugin : public BakkesMod::Plugin::BakkesModPlugin
{
private:
	float FOV, HEIGHT, ANGLE, DISTANCE, STIFFNESS, SWIVELSPEED, TRANSITIONSPEED;

public:
	virtual void onLoad();
	virtual void onUnload();
	virtual ProfileCameraSettings generateRandomSettings();
	virtual void logSettings();
};
