#include "pch.h";
#include "CameraPlugin.h";
#include <filesystem>

BAKKESMOD_PLUGIN(CameraPlugin, "Camera plugin", "0.1", PLUGINTYPE_FREEPLAY);

void CameraPlugin::onLoad() {
	cvarManager->registerNotifier("randomize_camera_settings", [&gw = this->gameWrapper](vector<string> commands) {
		if (!gw->IsInFreeplay())
			return;

		CameraWrapper camera = gw->GetCamera();
		ProfileCameraSettings settings = {107, 100, -4, 100, 1, 5, 1.20};

		camera.SetCameraSettings(settings);
		
	}, "Randomizes the player's camera settings", PERMISSION_FREEPLAY);
}

void CameraPlugin::onUnload() {

}