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
	virtual void generateRandomSettings();
	virtual void logSettings(ProfileCameraSettings settings);
	virtual bool isEmptySettings(ProfileCameraSettings settings);
};
