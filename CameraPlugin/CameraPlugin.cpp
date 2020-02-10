#include "pch.h";
#include "CameraPlugin.h";
#include <filesystem>;

// Instantiate camera variables
float FOV, HEIGHT, ANGLE, DISTANCE, STIFFNESS, SWIVELSPEED, TRANSITIONSPEED;

// Camera Setting min/max values
int FOV_MIN = 60;
int FOV_MAX = 100;
int HEIGHT_MIN = 40;
int HEIGHT_MAX = 200;
int ANGLE_MIN = -15;
int ANGLE_MAX = 0;
int DISTANCE_MIN = 100;
int DISTANCE_MAX = 400;
int STIFFNESS_MIN = 0;
int STIFFNESS_MAX = 1;
int SWIVELSPEED_MIN = 1;
int SWIVELSPEED_MAX = 10;
int TRANSITIONSPEED_MIN = 1;
int TRANSITIONSPEED_MAX = 2;

// Keep track of the current random Camera Settings Profile
ProfileCameraSettings settings;

BAKKESMOD_PLUGIN(CameraPlugin, "Camera plugin", "0.1", PLUGINTYPE_THREADED);

/*
Generates a random ProfileCameraSettings.
*/
void CameraPlugin::generateRandomSettings() {
	// Generate random values for each camera variable
	FOV = rand() % (FOV_MAX - FOV_MIN + 1) + FOV_MIN;
	HEIGHT = rand() % (HEIGHT_MAX - HEIGHT_MIN + 1) + HEIGHT_MIN;
	ANGLE = rand() % (ANGLE_MAX - ANGLE_MIN + 1) + ANGLE_MIN;
	DISTANCE = rand() % (DISTANCE_MAX - DISTANCE_MIN + 1) + DISTANCE_MIN;
	STIFFNESS = rand() % (STIFFNESS_MAX - STIFFNESS_MIN + 1) + STIFFNESS_MIN;
	SWIVELSPEED = rand() % (SWIVELSPEED_MAX - SWIVELSPEED_MIN + 1) + SWIVELSPEED_MIN;
	TRANSITIONSPEED = rand() % (SWIVELSPEED_MAX - SWIVELSPEED_MIN + 1) + SWIVELSPEED_MIN;

	// Return the random ProfileCameraSettings
	settings = { FOV, HEIGHT, ANGLE, DISTANCE, STIFFNESS, SWIVELSPEED, TRANSITIONSPEED };
	logSettings();
}

void CameraPlugin::logSettings() {
	cvarManager->log("FOV:" + std::to_string(FOV));
	cvarManager->log("HEIGHT:" + std::to_string(HEIGHT));
	cvarManager->log("ANGLE:" + std::to_string(ANGLE));
	cvarManager->log("DISTANCE:" + std::to_string(DISTANCE));
	cvarManager->log("STIFFNESS:" + std::to_string(STIFFNESS));
	cvarManager->log("SWIVEL SPEED:" + std::to_string(SWIVELSPEED));
	cvarManager->log("TRANSITION SPEED:" + std::to_string(TRANSITIONSPEED));
}

void CameraPlugin::onLoad() {

	// The body of the code will execute when the player type's "randomize_camera_settings" within the BakkesMod Developer Console
	cvarManager->registerNotifier("randomize_camera_settings", [this](vector<string> commands) {
		
		if (!gameWrapper->IsInFreeplay())
			return;

		// Get the camera of the player
		CameraWrapper camera = gameWrapper->GetCamera();

		// Generate a random Camera Settings Profile
		generateRandomSettings();

		// Set the player's camera to the Camera Settings Profile
		camera.SetCameraSettings(settings);

	}, "Randomizes the player's camera settings", PERMISSION_ALL);

	// Toggling between car/ball cam should not revert to original camera settings
	gameWrapper->HookEvent("Function TAGame.CameraState_BallCam_TA.BeginCameraState", [&](std::string eventName) {gameWrapper->GetCamera().SetCameraSettings(settings);});
	gameWrapper->HookEvent("Function TAGame.CameraState_BallCam_TA.EndCameraState", [&](std::string eventName) {gameWrapper->GetCamera().SetCameraSettings(settings);});
}

void CameraPlugin::onUnload() {

}