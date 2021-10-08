#include <gui/hud/textdraw>

stock CamaraInicio(playerid)
{
	SetPlayerCameraPos(playerid, 1533.2587, -1763.7717, 73.6204);
	SetPlayerCameraLookAt(playerid, 1532.9288, -1762.8286, 73.0504);
	SetPlayerPos(playerid,1513.4531, -1782.2853, 68.0610);
	TogglePlayerControllable(playerid, 0);
	TextDrawShowForPlayer(playerid, LoginBackground);
	return 1;
}

forward ResetPlayerCamera(playerid);

public ResetPlayerCamera(playerid)
{
    SetCameraBehindPlayer(playerid);
	TogglePlayerControllable(playerid, 1);
	return 1;
}