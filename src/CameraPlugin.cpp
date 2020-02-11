#include "CameraPlugin.h";
#include <filesystem>;

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

// Keep track of original camera and random settings
ProfileCameraSettings originalSettings;
ProfileCameraSettings randomSettings;

BAKKESMOD_PLUGIN(CameraPlugin, "Camera plugin", "0.2", PLUGINTYPE_THREADED);

/*
Generates a random ProfileCameraSettings.
*/
void CameraPlugin::generateRandomSettings() {
	// Generate random values for each camera variable
	float FOV = rand() % (FOV_MAX - FOV_MIN + 1) + FOV_MIN;
	float HEIGHT = rand() % (HEIGHT_MAX - HEIGHT_MIN + 1) + HEIGHT_MIN;
	float ANGLE = rand() % (ANGLE_MAX - ANGLE_MIN + 1) + ANGLE_MIN;
	float DISTANCE = rand() % (DISTANCE_MAX - DISTANCE_MIN + 1) + DISTANCE_MIN;
	float STIFFNESS = STIFFNESS_MIN + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/(STIFFNESS_MAX-STIFFNESS_MIN)));
	float SWIVELSPEED = SWIVELSPEED_MIN + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/(SWIVELSPEED_MAX-SWIVELSPEED_MIN)));
	float TRANSITIONSPEED = TRANSITIONSPEED_MIN + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/(TRANSITIONSPEED_MAX-TRANSITIONSPEED_MIN)));

	// Return the random ProfileCameraSettings
	randomSettings = { FOV, HEIGHT, ANGLE, DISTANCE, STIFFNESS, SWIVELSPEED, TRANSITIONSPEED };
}

void CameraPlugin::logSettings(ProfileCameraSettings settings) {
	cvarManager->log("FOV:" + std::to_string(settings.FOV));
	cvarManager->log("HEIGHT:" + std::to_string(settings.Height));
	cvarManager->log("ANGLE:" + std::to_string(settings.Pitch));
	cvarManager->log("DISTANCE:" + std::to_string(settings.Distance));
	cvarManager->log("STIFFNESS:" + std::to_string(settings.Stiffness));
	cvarManager->log("SWIVEL SPEED:" + std::to_string(settings.SwivelSpeed));
	cvarManager->log("TRANSITION SPEED:" + std::to_string(settings.TransitionSpeed));
}

void CameraPlugin::onLoad() {

	// The body of the code will execute when the player type's "randomize_camera_settings" within the BakkesMod Developer Console
	cvarManager->registerNotifier("randomize_camera_settings", [this](vector<string> commands) {

		if (!gameWrapper->IsInGame() &&
			!gameWrapper->IsInOnlineGame())
			return;

		// Get the camera of the player
		CameraWrapper camera = gameWrapper->GetCamera();

		// Keep track of the player's original camera settings
		if (isEmptySettings(originalSettings))
			originalSettings = camera.GetCameraSettings();

		// Generate a random Camera Settings Profile
		generateRandomSettings();
		cvarManager->log("Randmozing Camera Settings to:");
		logSettings(randomSettings);

		// Set the player's camera to the Camera Settings Profile
		camera.SetCameraSettings(randomSettings);

		// Toggling between car/ball cam should not revert to original camera settings
		gameWrapper->HookEvent("Function TAGame.CameraState_BallCam_TA.BeginCameraState", [&](std::string eventName) {gameWrapper->GetCamera().SetCameraSettings(randomSettings);});
		gameWrapper->HookEvent("Function TAGame.CameraState_BallCam_TA.EndCameraState", [&](std::string eventName) {gameWrapper->GetCamera().SetCameraSettings(randomSettings);});

	}, "Randomizes the player's camera settings", PERMISSION_ALL);

	// Allow the player to set their camera setting back to original
	cvarManager->registerNotifier("revert_camera_settings", [this](vector<string> commands) {

		if (!gameWrapper->IsInGame() &&
			!gameWrapper->IsInOnlineGame())
			return;

		CameraWrapper camera = gameWrapper->GetCamera();

		// Keep track of the player's original camera settings
		if (isEmptySettings(originalSettings))
			originalSettings = camera.GetCameraSettings();

		camera.SetCameraSettings(originalSettings);

		cvarManager->log("Setting Camera Settings to Original:");
		logSettings(originalSettings);

	}, "Reverts the player's camera settings to the original settings,", PERMISSION_ALL);

}

// Returns TRUE if the settings have not been initialized,
// returns FALSE otherwise.
bool CameraPlugin::isEmptySettings(ProfileCameraSettings settings) {
	if (settings.FOV == 0 && settings.Height == 0 && settings.Pitch == 0 &&
		settings.Distance == 0 && settings.Stiffness == 0 && settings.SwivelSpeed == 0 &&
		settings.TransitionSpeed == 0)
		return true;
	else
		return false;
}

void CameraPlugin::onUnload() {
	free(&originalSettings);
	free(&randomSettings);
}