/*
	* Created on Tue Oct 16 2021
	*
	* Copyright © 2021 - UnionGamers
	*
*/
//========== [ LIBRERIAS ] ==========
#include		<a_samp>
#include        <a_mysql>
#include        <zcmd>
#include        <discord-connector>
#include        <progress2>
#include        <sscanf2>
#include		<mselection>
#include        <streamer>
//========== [ MODULES ] ==========
#include        <utils/fixes/anims>
#include        <utils/fixes/vehdirects>

#include        <utils/system/factions>
#include        <utils/system/doors>
#include        <utils/system/discord>
#include        <utils/system/vehicles>
#include        <utils/system/business>
#include        <utils/system/jobs>

#include        <utils/commands/general/role>
#include        <utils/commands/general/anims>
#include        <utils/commands/admin/admins>
#include        <utils/commands/general/main>

#include        <core/player/login>
#include        <core/player/manage>
#include        <core/player/data>

#include        <core/server/database>
#include        <core/server/anticheat>
#include        <core/server/dataloader>
#include        <core/server/main>

#include        <gui/hud/camera>
#include        <gui/hud/textdraw>
#include        <gui/hud/main>
#include        <gui/hud/chat>

main()
{
	print("_______________________________");
	print("|-                           -|");
	print("|-        UnionGamers        -|");
	print("|-    Script: UnionGamers    -|");
	print("|-     Copyright © 2021      -|");
	printf("|-      Version: %s       -|", Server_Version);
	print("|_____________________________|");
	print(" ");
	print(" ");
	print(" ");
	printf("[Servidor]: Se han cargado: %d Facciones.", TFacciones);
	printf("[Servidor]: Se han cargado: %d Rangos.", TRangos);
	printf("[Servidor]: Se han cargado: %d Coches.", TVehiculos);
	printf("[Servidor]: Se han cargado: %d Negocios.", TNegocios);
}
//=========== [ DIALOGOS ] ==========
#define			DIALOG_REGMAIL			0
#define         DIALOG_REGPASS          1
#define         DIALOG_REGAGE           2
#define         DIALOG_REGGENDER        3
#define         DIALOG_REGCITY          4
#define         DIALOG_LOGIN            5
#define         DIALOG_GLOBAL_INPUT     10

#define     	MENU_NEGOCIO            11
#define         MENU_NEGOCIO_CREAR		12
#define         MENU_NEGOCIO_TIPO		13
#define         MENU_NEGOCIO_TIPO2		14
#define         MENU_NEGOCIO_PRECIO		15
#define         MENU_NEGOCIO_PRECIO2    16
#define			MENU_NEGOCIO_TP         17

#define         DIALOG_COMPRAR247       18
#define         DIALOG_COMIDA           19
#define         DIALOG_ELECTRONICA      20

#define			DIALOG_MAPEAR           21
//============ [ VARIABLES ] ===============
new bool:BetaPhase = false;
//============ [ STOCKS ] ===========
stock SendClientMessageEx(playerid, color, const text[], {Float, _}:...)
{
	static args, str[144];

	if ((args = numargs()) == 3)
	{
	    SendClientMessage(playerid, color, text);
	}
	else
	{
		while (--args >= 3)
		{
			#emit LCTRL 5
			#emit LOAD.alt args
			#emit SHL.C.alt 2
			#emit ADD.C 12
			#emit ADD
			#emit LOAD.I
			#emit PUSH.pri
		}
		#emit PUSH.S text
		#emit PUSH.C 144
		#emit PUSH.C str
		#emit PUSH.S 8
		#emit SYSREQ.C format
		#emit LCTRL 5
		#emit SCTRL 4
		SendClientMessage(playerid, color, str);
		#emit RETN
	}
	return 1;
}

stock IsValidRPName(name[])
{
    if(('A' <= name[0] <= 'Z') && ('a' <= name[1] <= 'z'))
    {
        if(IsValidRPInput(name))
        {
            if(strfind(name, "_") != -1)
            {
                new underline = strfind(name, "_"), pos = underline +1;
                if(('A' <= name[pos] <= 'Z') && ('a' <= name[pos +1] <= 'z'))
                {
                    for(new i; i < strlen(name); ++i)
                    {
                        if(('A' <= name[i] <= 'Z') && (i != 0) && (i != pos)) return 0;
                        else if((name[i] == '_') && (i != underline)) return 0;
                        else continue;
                    }
                    return 1;
                }
            }
        }
    }
    return 0;
}

stock IsValidRPInput(const ipstr[])
{
    for(new i = 0; ipstr[i] != EOS; ++i)
    {
        switch(ipstr[i])
        {
            case 'A'..'Z', 'a'..'z','_': continue;
            default: return 0;
        }
    }
    return 1;
}

stock GetPlayerNameEx(playerid)
{
	new nombre[MAX_PLAYER_NAME];
	GetPlayerName(playerid, nombre, sizeof(nombre));
	return nombre;
}

//============= [ FORWARDS ] ===========
forward VerifyUser(playerid);
//============ [ CALLBACKS ] ===========
public VerifyUser(playerid)
{
	if(cache_num_rows() > 0)
	{
	    cache_get_value(0, "rName", TempInfo[playerid][rName], 128);
	    CamaraInicio(playerid);
	    ShowPlayerDialog(playerid, DIALOG_LOGIN, DIALOG_STYLE_PASSWORD, "{FF0984}Login {FFFFFF}» {FF8000}Union {0080FF}Gamers", "Bienvenido nuevamente!\n\nIngrese su contraseña porfavor.", "{00D200}»", "{FF0000}X");
	}
	else
	{
	    CamaraInicio(playerid);
	    new str[86+1];
		format(str, sizeof(str), "Bienvenido!\n\n{ffffff}Ingrese un {EFFF40}correo electrónico {ffffff}para registrarse.");
		ShowPlayerDialog(playerid, DIALOG_REGMAIL, DIALOG_STYLE_INPUT, "{FF0984}Registro {FFFFFF}» {FF8000}Union {0080FF}Gamers", str, "{00D200}»", "{FF0000}X");
	}
	return 1;
}

//============ [ FUNCIONES ] ===========
public OnGameModeInit()
{
    //»»»»»»»»»»»»»»»»»»»»		CONFIGURACION SERVER		««««««««««««««««««««
    SetGameModeText(Server_GameText);
    new rcon[80];
    format(rcon, sizeof(rcon), "hostname %s", Server_Name);
    SendRconCommand(rcon);
    format(rcon, sizeof(rcon), "weburl %s", Server_Web);
    SendRconCommand(rcon);
    format(rcon, sizeof(rcon), "mapname %s", Server_Map);
    SendRconCommand(rcon);
	format(rcon, sizeof(rcon), "language %s", Server_Language);
    SendRconCommand(rcon);
	format(rcon, sizeof(rcon), "password %s", Server_Password);
    SendRconCommand(rcon);
	format(rcon, sizeof(rcon), "rconpassword %s", Server_Rcon);
    //»»»»»»»»»»»»»»»»»»»»		CONFIGURACION 		««««««««««««««««««««
    DisableInteriorEnterExits();
    ManualVehicleEngineAndLights();
	EnableStuntBonusForAll(0);
	UsePlayerPedAnims();
	ShowPlayerMarkers(0);
	SetNameTagDrawDistance(20.0);
    SendRconCommand("loadfs map");
    SetRichPresenceBot();
    //»»»»»»»»»»»»»»»»»»»»		TIMERS 		««««««««««««««««««««
    SetTimer("Clock", 1000, true); //Timer Global Hora
	//»»»»»»»»»»»»»»»»»»»»»»»»		OTROS		««««««««««««««««««««««««
	for(new i = 0; i < MAX_VEHICLES; i++)
    {
        Blink[i][0] = -1;
        Blink[i][1] = -1;
        Blink[i][2] = -1;
        Blink[i][3] = -1;
    }
    SetTimer("B_TrailerCheck", 1000, 1);
	//»»»»»»»»»»»»»»»»»»»»»»»»		MENUS		««««««««««««««««««««««««
	SkinList = LoadModelSelectionMenu("skins.txt");
	//»»»»»»»»»»»»»»»»		FUNCIONES PRINCIPALES 		««««««««««««««««
	CreateTextDraws();
	Create3DTextLabelEx();
	ConnectDataBase();
	LoadDoors();
	LoadFactions();
	LoadVehiculos();
	LoadNegocios();
	CargarObjetos();
	//»»»»»»»»»»»»»»»»		FIX MODELS 		««««««««««««««««
	AddSimpleModel(-1, 19379, -2001, "login.dff", "login.txd");
	AddSimpleModel(-1, 19379, -2002, "logo.dff", "logo.txd");
	AddSimpleModel(-1, 19379, -2003, "dni.dff", "dni.txd");
	AddSimpleModel(-1, 19379, -2004, "bank.dff", "bank.txd");
	AddSimpleModel(-1, 19379, -2005, "velo_base.dff", "velo_base.txd");
	AddSimpleModel(-1, 19379, -2006, "vel_icon_aceite.dff", "vel_icon_aceite.txd");
	AddSimpleModel(-1, 19379, -2007, "vel_icon_luces.dff", "vel_icon_luces.txd");
	AddSimpleModel(-1, 19379, -2008, "vel_icon_motor.dff", "vel_icon_motor.txd");
	AddSimpleModel(-1, 19379, -2009, "vel_icon_seat.dff", "vel_icon_seat.txd");
	AddSimpleModel(-1, 19379, -2010, "vel_icon_seguro.dff", "vel_icon_seguro.txd");
	return 1;
}

public OnGameModeExit()
{
	SaveDoorsMain();
	SaveFactions();
	SaveCars();
	SaveNegocios();
	GuardarObjetos();
	for(new i = 0; i <= GetPlayerPoolSize(); i++)
	{
	    if(IsPlayerConnected(i) && Logged[i] == true)
	    {
	    	SavePlayerData(i, 0);
		}
	}
    for(new i=0;i<MAX_VEHICLES;i++) DisableCarBlinking(i);
    DisconnectDataBase();
	return 1;
}

public OnPlayerRequestClass(playerid, classid)
{
    ResetPlayerVariables(playerid);
    SetPlayerColor(playerid, 0xFF8040FF);
	if(Logged[playerid] == false)
	{
		new query[520];
		mysql_format(g_MySQL, query, sizeof(query), "SELECT `rName` FROM `users` WHERE `Name` = '%s'", GetPlayerNameEx(playerid));
		mysql_tquery(g_MySQL, query, "VerifyUser", "d", playerid);
	}
	//=== Debug ===
	for (new i; i < sizeof(AnimationLibraries); i++) ApplyAnimation(playerid, AnimationLibraries[i], "null", 0.0, 0, 0, 0, 0, 0);
	return 1;
}

public OnPlayerConnect(playerid)
{
	/*========== [ CONFIG PLAYER CONNECT ] ==========*/
	CreatePlayerTextDrawEx(playerid);
	CreatePlayerProgressBarEx(playerid);
	SetPlayerColor(playerid, 0x808080FF);
	//================================================
	if(IsValidRPName(GetPlayerNameEx(playerid)) || BetaPhase == true)
	{
	    ResetPlayerVariables(playerid);
	    PlayAudioStreamForPlayer(playerid, "http://union-gamers.com/res/samp/login.mp3");
	    for(new i=0; i < 30; i++)
	    {
	        SendClientMessageEx(playerid, -1, "");
	    }
	}
	else
	{
		ShowPlayerDialog(playerid, 404, DIALOG_STYLE_MSGBOX, "{FF0984}Error {FFFFFF}» {FF8000}Union {0080FF}Gamer", "Debes utilizar un nombre con formato permitido\nFormato: {80FF80}Nombre_Apellido", "Aceptar", "");
		SetTimerEx("KickPlayerEx", 400, false, "d", playerid);
	}
	return 1;
}

public OnPlayerDisconnect(playerid, reason)
{
    SavePlayerData(playerid, 0);
	return 1;
}

public OnPlayerSpawn(playerid)
{
	if(GetPVarInt(playerid, "CanJoin") == 0)
	{
	    Kick(playerid);
	}
	if(PlayersData[playerid][Banned] == 0 && Logged[playerid] == true)
	{
		TextDrawHideForPlayer(playerid, LoginBackground);
		TextDrawShowForPlayer(playerid, logoUG);
		TextDrawShowForPlayer(playerid, Reloj1);
		TextDrawShowForPlayer(playerid, Reloj2);
		ShowPlayerProgressBar(playerid, PJ_Food[playerid]);
		ShowPlayerProgressBar(playerid, PJ_Drink[playerid]);
		StopAudioStreamForPlayer(playerid);
		SetPlayerSkillLevel(playerid, 0, 1);
		SetPlayerColor(playerid, 0xFFFFFFFF);

        if(GetPVarInt(playerid, "CamaraRegistro") == 1)
		{
			SetTimerEx("ResetPlayerCamera", 3800, false, "d", playerid);
			DeletePVar(playerid, "CamaraRegistro");
		}
	}
	else
	{
	    SendClientMessageEx(playerid, -1, "%s Tu cuenta se encuentra Baneada. Si es un error, contacta un Administrador.", InfoMsg);
	    SetTimerEx("KickPlayerEx", 400, false, "d", playerid);
	}
	return 1;
}

public OnPlayerDeath(playerid, killerid, reason)
{
	GetPlayerPos(playerid, TempInfo[playerid][dPosX], TempInfo[playerid][dPosY], TempInfo[playerid][dPosZ]);
	return OnPlayerDeathEx(playerid);
}

public OnPlayerCommandPerformed(playerid, cmdtext[], success)
{
	if(Logged[playerid] == true)
	{
		if(!success)
		{
			SendClientMessageEx(playerid, -1, "{40FF00}» {007BFF}El comando ({FFFFFF}%s{007BFF}) es inválido. Por favor, use '{9C33FF}/Ayuda{007BFF}'", cmdtext);
            PlayerPlaySound(playerid, 1138, 0.0, 0.0, 0.0);
		}
	}
	else
	{
	    SendClientMessageEx(playerid, -1, "%s Haz sido silenciado o no haz ingresado aun al servidor.", HelpMsg);
	}
	return 1;
}

public OnVehicleSpawn(vehicleid)
{
	if(vehicleid != INVALID_VEHICLE_ID)
	{
	    if(GetVehicleModel(vehicleid) == 510)
	    {
	        new engine, lights, alarm, doors, bonnet, boot, objective;
			GetVehicleParamsEx(VehData[vehicleid][VehID], engine, lights, alarm, doors, bonnet, boot, objective);
			SetVehicleParamsEx(VehData[vehicleid][VehID], VEHICLE_PARAMS_ON, lights, alarm, doors, bonnet, boot, objective);
	    }
	    else
	    {
			new matricula[16];
			format(matricula, sizeof(matricula), "%d", VehData[TVehiculos][Plate]);
			SetVehicleNumberPlate(VehData[TVehiculos][VehID], matricula);
			new engine, lights, alarm, doors, bonnet, boot, objective;
			if(VehData[vehicleid][Key] == 0) //Cerrado
			{
				GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
				SetVehicleParamsEx(vehicleid, engine, lights, alarm, VEHICLE_PARAMS_ON, bonnet, boot, objective);
			}
			else if(VehData[vehicleid][Key] == 1) //Abierto
			{
				GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
				SetVehicleParamsEx(vehicleid, engine, lights, alarm, VEHICLE_PARAMS_OFF, bonnet, boot, objective);
			}

			VehData[vehicleid][Engine] = 0;
			VehData[vehicleid][Luces] = 0;
			VehData[vehicleid][Capo] = 0;
			ChangeVehicleColor(vehicleid, VehData[vehicleid][Color1], VehData[vehicleid][Color2]);
			if(VehData[vehicleid][vType] < 3)
			{
				SetVehiclePos(vehicleid, VehData[vehicleid][vPx], VehData[vehicleid][vPy], VehData[vehicleid][vPz]);
			}
		}
		if(B_IsTrailer(vehicleid))
	    {
	        new veh;
	        if((veh = TrailerVehicle[vehicleid]) != 0)
	        {
	            if(IsCarBlinking(veh))
	            {
	                DestroyDynamicObject(Blink[veh][1]);
	                DestroyDynamicObject(Blink[veh][3]);
	                Blink[veh][1] = -1;
	                Blink[veh][3] = -1;
	            }
	        }
	    }
	    else DisableCarBlinking(vehicleid);
	}
    return 1;
}

public OnVehicleDeath(vehicleid, killerid)
{
	return 1;
}

public OnPlayerText(playerid, text[])
{
	ServerChat(playerid, text);
	return 0;
}

public OnPlayerCommandText(playerid, cmdtext[])
{
	return 1;
}

public OnPlayerEnterVehicle(playerid, vehicleid, ispassenger)
{
	return 1;
}

public OnPlayerExitVehicle(playerid, vehicleid)
{
	new seat;
    seat=GetPlayerVehicleSeat(playerid);
    if(Cinturon[playerid] == true)
    {
		ClearAnimations(playerid);
		PutPlayerInVehicle(playerid, vehicleid, seat);
		GameTextForPlayer(playerid, "~w~Cinturon: ~r~Abrochado", 3000, 5);
    }
	return 1;
}

public OnPlayerStateChange(playerid, newstate, oldstate)
{
    new vID;
	vID = GetPlayerVehicleID(playerid);
    if(newstate == PLAYER_STATE_DRIVER)
    {
		if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 574 && GetPlayerSkin(playerid) != 27 ||
		GetVehicleModel(GetPlayerVehicleID(playerid)) == 478 && GetPlayerSkin(playerid) != 261)
		{
			RemovePlayerFromVehicle(playerid);
			SendClientMessageEx(playerid, -1, "%s No estás trabajando actualmente.", InfoMsg);
		}
		if(GetVehicleModel(vID) != 510)
		{
			new engine, lights, alarm, doors, bonnet, boot, objective;
			GetVehicleParamsEx(vID, engine, lights, alarm, doors, bonnet, boot, objective);

			PlayerTextDrawShow(playerid, Vel_Base[playerid]);
			PlayerTextDrawShow(playerid, Vel_Speed[playerid]);
			ShowPlayerProgressBar(playerid, Vel_GasoBar[playerid]);
			ShowPlayerProgressBar(playerid, Vel_AceiteBar[playerid]);
			MedidoresVelocimetro(playerid, vID);

			if(VehData[vID][Key] == 0) //Rojo - Cerrado
			{
			    PlayerTextDrawShow(playerid, Vel_Lock[playerid]);
			}

			if(lights == 1)	{	PlayerTextDrawShow(playerid, Vel_Luces[playerid]);}
			if(Cinturon[playerid] == false) {   PlayerTextDrawShow(playerid, Vel_Seat[playerid]);}
			if(VehData[vID][Status] <= 600.0)   {   PlayerTextDrawShow(playerid, Vel_Motor[playerid]);}
			if(VehData[vID][Aceite] <= 30.0)  {   PlayerTextDrawShow(playerid, Vel_iAceite[playerid]);}
		}
	}
    else if(oldstate == PLAYER_STATE_DRIVER || oldstate == PLAYER_STATE_PASSENGER)
    {
        SetEstereoForPlayer(playerid, 0);
        PlayerTextDrawHide(playerid, Vel_Base[playerid]);
        PlayerTextDrawHide(playerid, Vel_Speed[playerid]);
        PlayerTextDrawHide(playerid, Vel_iAceite[playerid]);
        PlayerTextDrawHide(playerid, Vel_Luces[playerid]);
        PlayerTextDrawHide(playerid, Vel_Motor[playerid]);
        PlayerTextDrawHide(playerid, Vel_Seat[playerid]);
        PlayerTextDrawHide(playerid, Vel_Lock[playerid]);
		HidePlayerProgressBar(playerid, Vel_GasoBar[playerid]);
		HidePlayerProgressBar(playerid, Vel_AceiteBar[playerid]);
		
		#if BLINK_DISABLE_ON_EXIT_VEHICLE == 0
        return 1;
        #else
        if(BlinkSide[GetPVarInt(playerid, "blink-car")] != 2) DisableCarBlinking(GetPVarInt(playerid, "blink-car"));
        #endif
    }
	return 1;
}

public OnPlayerEnterCheckpoint(playerid)
{
	if(Trabajando[playerid] == true && IsPlayerInAnyVehicle(playerid))
	{
		DisablePlayerCheckpoint(playerid);
		if(TempInfo[playerid][Work] == 1)
		{
			JobCount[playerid]++;
			if(JobCount[playerid] < 20)
			{
				SendClientMessageEx(playerid, -1, "%s Llevas un total de %d lugares limpiados. Continua al siguiente punto.", InfoMsg, JobCount[playerid]);
				new rand = random(sizeof(jobChecks));
				SetPlayerCheckpoint(playerid, jobChecks[rand][0], jobChecks[rand][1], jobChecks[rand][2], 3.0 );
			}
			else if(JobCount[playerid] == 20)
			{
				SendClientMessageEx(playerid, -1, "%s Lleva el vehiculo de regreso para recibir tu paga.", InfoMsg);
				SetPlayerCheckpoint(playerid, 1751.56, -2057.02, 13.7534, 3.0 );
			}
			else if(JobCount[playerid] == 21)
			{
				SendClientMessageEx(playerid, -1, "%s Haz completado tu trabajo con ?xito, recibiste $150 de pago.", InfoMsg);
				PlayersData[playerid][Money] += 150;
				GivePlayerMoney(playerid, 150);
				FaccData[1][Money] -= 150;
				Trabajando[playerid] = false;
				JobCount[playerid] = 0;
				VehData[GetPlayerVehicleID(playerid)][Fuel] = 100.0;
				VehData[GetPlayerVehicleID(playerid)][Aceite] = 100.0;
				SetVehicleToRespawn(GetPlayerVehicleID(playerid));
			}
			else if(JobCount[playerid] >= 22)
			{
				new paga;
				paga = JobCount[playerid] - 23;
				JobCount[playerid] -= 23;
				SendClientMessageEx(playerid, -1, "%s Finalizaste la ruta, con %d zonas limpiadas, ganaste: $%d", InfoMsg, JobCount[playerid], paga);
				PlayersData[playerid][Money] += paga;
				FaccData[1][Money] -= paga;
				GivePlayerMoney(playerid, paga);
				VehData[GetPlayerVehicleID(playerid)][Fuel] = 100.0;
				VehData[GetPlayerVehicleID(playerid)][Aceite] = 100.0;
				SetVehicleToRespawn(GetPlayerVehicleID(playerid));
				Trabajando[playerid] = false;
			}
		}
		else if(TempInfo[playerid][Work] == 2)
		{
			JobCount[playerid]++;
			if(JobCount[playerid] == 1)
			{
				SendClientMessageEx(playerid, -1, "%s Lleva el coche de regreso para terminar.", InfoMsg);
				SetPlayerCheckpoint(playerid, -397.723, -1442.86, 25.7209, 3.0);
			}
			else if(JobCount[playerid] == 3)
			{
				SendClientMessageEx(playerid, -1, "%s Haz terminado tú recorrido.", InfoMsg);
				Trabajando[playerid] = false;
				JobCount[playerid] = 0;
				VehData[GetPlayerVehicleID(playerid)][Fuel] = 100.0;
				VehData[GetPlayerVehicleID(playerid)][Aceite] = 100.0;
				SetVehicleToRespawn(GetPlayerVehicleID(playerid));
			}
			else
			{
				SendClientMessageEx(playerid, -1, "%s Haz completado tu trabajo con ?xito, recibiste $80 de pago.", InfoMsg);
				SendClientMessageEx(playerid, -1, "%s Sube a un nuevo vehículo y usa: /Ruta.", InfoMsg);
				PlayersData[playerid][Money] += 80;
				GivePlayerMoney(playerid, 80);
				FaccData[1][Money] -= 80;
				Trabajando[playerid] = false;
				JobCount[playerid] = 0;
				VehData[GetPlayerVehicleID(playerid)][Fuel] = 100.0;
				VehData[GetPlayerVehicleID(playerid)][Aceite] = 100.0;
				SetVehicleToRespawn(GetPlayerVehicleID(playerid));
			}
		}
		else
		{
			//Nada aún
		}
	}
	return 1;
}

public OnPlayerLeaveCheckpoint(playerid)
{
	return 1;
}

public OnPlayerEnterRaceCheckpoint(playerid)
{
	return 1;
}

public OnPlayerLeaveRaceCheckpoint(playerid)
{
	return 1;
}

public OnRconCommand(cmd[])
{
	return 1;
}

public OnPlayerRequestSpawn(playerid)
{
	return 1;
}

public OnObjectMoved(objectid)
{
	return 1;
}

public OnPlayerObjectMoved(playerid, objectid)
{
	return 1;
}

public OnPlayerPickUpPickup(playerid, pickupid)
{
	return 1;
}

public OnVehicleMod(playerid, vehicleid, componentid)
{
	return 1;
}

public OnVehiclePaintjob(playerid, vehicleid, paintjobid)
{
	return 1;
}

public OnVehicleRespray(playerid, vehicleid, color1, color2)
{
	return 1;
}

public OnPlayerSelectedMenuRow(playerid, row)
{
	return 1;
}

public OnPlayerExitedMenu(playerid)
{
	return 1;
}

public OnPlayerInteriorChange(playerid, newinteriorid, oldinteriorid)
{
	return 1;
}

public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	//----------------------- Tecla "H"
	if(newkeys == KEY_CTRL_BACK)
	{
	    for(new i = 0; i <= TObjetos; i++)
		{
			if(IsPlayerInRangeOfPoint(playerid, 7.0, Objetos[i][xobjeto], Objetos[i][yobjeto], Objetos[i][zobjeto]))
			{
			    if(Objetos[i][Move] == 1)
			    {
			        switch(Objetos[i][Tipo])
			        {
			            case 0 .. 1:
			            {
							if(Objetos[i][Estado] == 1)
					        {
								MoveDynamicObject(Objetos[i][ID], Objetos[i][oPosX], Objetos[i][oPosY], Objetos[i][oPosZ], 3.0, Objetos[i][oRotX], Objetos[i][oRotY], Objetos[i][oRotZ]);
								Objetos[i][Estado] = 2;
							}
							else if(Objetos[i][Estado] == 2)
							{
								MoveDynamicObject(Objetos[i][ID], Objetos[i][xobjeto], Objetos[i][yobjeto], Objetos[i][zobjeto], 3.0, Objetos[i][rotx], Objetos[i][roty], Objetos[i][rotz]);
								Objetos[i][Estado] = 1;
							}
			            }
			            case 2:
			            {
			                if(Objetos[i][oOwner] == PlayersData[playerid][Faction])
			        		{
			        		    if(Objetos[i][Estado] == 1)
						        {
									MoveDynamicObject(Objetos[i][ID], Objetos[i][oPosX], Objetos[i][oPosY], Objetos[i][oPosZ], 3.0, Objetos[i][oRotX], Objetos[i][oRotY], Objetos[i][oRotZ]);
									Objetos[i][Estado] = 2;
								}
								else if(Objetos[i][Estado] == 2)
								{
									MoveDynamicObject(Objetos[i][ID], Objetos[i][xobjeto], Objetos[i][yobjeto], Objetos[i][zobjeto], 3.0, Objetos[i][rotx], Objetos[i][roty], Objetos[i][rotz]);
									Objetos[i][Estado] = 1;
								}
							}
			            }
			        }
				}
			}
		}

	}
 	//----------------------- Tecla "F"
	if(newkeys == KEY_SECONDARY_ATTACK)
	{
	    if(Animation[playerid] == true)
	    {
	        ClearAnimations(playerid);
	        Animation[playerid] = false;
	    }
	    for(new i = 0; i < sizeof(VendingMachinePos); i++)
		{
			if(IsPlayerInRangeOfPoint(playerid, 2.0, VendingMachinePos[i][0], VendingMachinePos[i][1], VendingMachinePos[i][2]))
		    {
				GetPlayerHealth(playerid, TempInfo[playerid][dHealth]);
				SetPlayerHealth(playerid, TempInfo[playerid][dHealth] - 50);
				ClearAnimations(playerid);
		    }
		}
	}
	//----------------------- Tecla "Y"
	if(newkeys == KEY_YES)
	{
		for(new i = 0; i < sizeof(PuertaInfor); i++)
		{
			if(IsPlayerInRangeOfPoint(playerid, 1, PuertaInfor[i][bExteriorX][0], PuertaInfor[i][bExteriorX][1], PuertaInfor[i][bExteriorX][2]))
			{
				if(GetPlayerInterior(playerid) == PuertaInfor[i][bExteriorID] && GetPlayerVirtualWorld(playerid) == PuertaInfor[i][bVirWorldEXT])
				{
					if(PuertaInfor[i][bLocked] == 0)
					{
						Informacion[playerid][InBuilding] = i;
						SetPlayerInterior( playerid, PuertaInfor[i][bInteriorID]);
						SetPlayerVirtualWorld( playerid, PuertaInfor[i][bVirWorldINT]);
						PlayersData[playerid][pInterior] = PuertaInfor[i][bInteriorID];
						PlayersData[playerid][pVW] = PuertaInfor[i][bVirWorldINT];
						Informacion[playerid][pVirtualWorld] = PuertaInfor[i][bVirWorldINT];
						LoadObjects(playerid);
						SetPlayerPos(playerid, PuertaInfor[i][bInteriorX][0], PuertaInfor[i][bInteriorX][1], PuertaInfor[i][bInteriorX][2]);
					}
					else
					{
						GameTextForPlayer(playerid, "~w~Puerta: ~r~Cerrada", 1000, 5);
					}
				}
			}
			else if(IsPlayerInRangeOfPoint(playerid, 1, PuertaInfor[i][bInteriorX][0], PuertaInfor[i][bInteriorX][1], PuertaInfor[i][bInteriorX][2]))
			{
				if(PuertaInfor[i][bLocked] == 0)
				{
					Informacion[playerid][InBuilding] = i;
					SetPlayerInterior(playerid, PuertaInfor[i][bExteriorID]);
					SetPlayerVirtualWorld(playerid, PuertaInfor[i][bVirWorldEXT]);
					PlayersData[playerid][pInterior] = PuertaInfor[i][bExteriorID];
					PlayersData[playerid][pVW] = PuertaInfor[i][bVirWorldEXT];
					Informacion[playerid][pVirtualWorld] = 0;
					LoadObjects(playerid);
					SetPlayerPos(playerid, PuertaInfor[i][bExteriorX][0], PuertaInfor[i][bExteriorX][1], PuertaInfor[i][bExteriorX][2]);
				}
				else
				{
					GameTextForPlayer(playerid, "~w~Puerta: ~r~Cerrada", 1000, 5);
				}
			}
			else if(IsPlayerInRangeOfPoint(playerid, 1, Negocios[i][nPEx], Negocios[i][nPEy], Negocios[i][nPEz]) && GetPlayerInterior(playerid) == Negocios[i][nIntE] && GetPlayerVirtualWorld(playerid) == Negocios[i][nVwE])
            {
                if(PlayersData[playerid][Money] >= Negocios[i][nEntrada])
                {
					SetPlayerPos(playerid, Negocios[i][nPIx], Negocios[i][nPIy], Negocios[i][nPIz]);
					PlayersData[playerid][pInterior] = Negocios[i][nIntI];
					PlayersData[playerid][pVW] = Negocios[i][nVwI];
					SetPlayerInterior(playerid, Negocios[i][nIntI]);
					SetPlayerVirtualWorld(playerid, Negocios[i][nVwI]);
					LoadObjects(playerid);
					PlayersData[playerid][Money] -= Negocios[i][nEntrada];
					GivePlayerMoney(playerid, -Negocios[i][nEntrada]);
					Negocios[i][nMoney] += Negocios[i][nEntrada];
					EnNegocio[playerid] = i;
				}
				else
				{
				    SendClientMessageEx(playerid, -1, "%s No tienes suficiente dinero para ingresar a este negocio.", InfoMsg);
				}
            }
            else if(IsPlayerInRangeOfPoint(playerid, 1, Negocios[i][nPIx], Negocios[i][nPIy], Negocios[i][nPIz]) && GetPlayerInterior(playerid) == Negocios[i][nIntI] && GetPlayerVirtualWorld(playerid) == Negocios[i][nVwI])
            {
				SetPlayerPos(playerid, Negocios[i][nPEx], Negocios[i][nPEy], Negocios[i][nPEz]);
				PlayersData[playerid][pInterior] = Negocios[i][nIntE];
				PlayersData[playerid][pVW] = Negocios[i][nVwE];
				SetPlayerInterior(playerid, Negocios[i][nIntE]);
				SetPlayerVirtualWorld(playerid, Negocios[i][nVwE]);
				EnNegocio[playerid] = 0;
            }
		}
	}
	//----------------------- Tecla "N"
	if (GetPlayerVehicleSeat(playerid) == 0)
	{
		if(newkeys == KEY_NO && IsPlayerInAnyVehicle(playerid))
		{
		    new vID = GetPlayerVehicleID(playerid);
			if(GetVehicleModel(vID) != 510)
			{
			    new string[128 + MAX_PLAYER_NAME];

				if(VehData[vID][Engine] == 0)
				{
				    new Float:lavive;
				    GetVehicleHealth(vID, lavive);
				    if(VehData[vID][Fuel] != 0)
				    {
						if(lavive > 350)
						{
					        if(LlenarGas[playerid] == false)
					        {
						    	if(TryRole[playerid] == false)
						    	{
									SetTimerEx("EncenderMotor", 200, false, "dd", playerid, vID);
									GameTextForPlayer(playerid, "~w~Encendiendo...",2000,3);
									format(string, sizeof(string), "*%s inserta la llave en el switch y la gira levemente!", RemoveUnderScore(playerid));
									ProxDetector(30.0, playerid, string, 0xC2A2DAAA,0xC2A2DAAA,0xC2A2DAAA,0xC2A2DAAA,0xC2A2DAAA);
									TryRole[playerid] = true;
									SetTimerEx("TryTimer", 2000, false, "d", playerid);
								}
								else
								{
								    SendClientMessageEx(playerid, -1, "%s Debes esperar 2 segundos para volver a intentarlo!", InfoMsg);
								}
							}
							else
							{
							    SendClientMessageEx(playerid, -1, "%s No puedes encender el coche hasta terminar de llenar el deposito.", InfoMsg);
							}
						}
						else
						{
							SendClientMessageEx(playerid, -1, "%s Tú vehículo tiene una falla, busca un mecánico!", InfoMsg);
						}
					}
					else
					{
					    SendClientMessageEx(playerid, -1, "%s Este vehículo no tiene gasolina.", InfoMsg);
					}
				}
				else
				{
				    if(TryRole[playerid] == false)
				    {
						SetTimerEx("ApagarMotor", 500, false, "dd", playerid, vID);
						GameTextForPlayer(playerid, "~w~Apagando...",1000,3);
						format(string, sizeof(string), "*%s gira la llave del switch!", RemoveUnderScore(playerid));
						ProxDetector(30.0, playerid, string, 0xC2A2DAAA,0xC2A2DAAA,0xC2A2DAAA,0xC2A2DAAA,0xC2A2DAAA);
						TryRole[playerid] = true;
						SetTimerEx("TryTimer", 2000, false, "d", playerid);
					}
					else
					{
					    SendClientMessageEx(playerid, -1, "%s Debes esperar 2 segundos para volver a intentarlo!", InfoMsg);
					}
				}
			}
			return 1;
		}
	}
	//---------------------------------------- Direccionales Coche
	new veh = GetPlayerVehicleID(playerid);
    if(veh != 0)
    {
        if(GetPlayerVehicleSeat(playerid) == 0)
        {
            #if BLINK_ALLOW_EMERGENCY == 1
            if(newkeys & KEY_LOOK_BEHIND)
            {
                if(!IsCarBlinking(veh)) SetCarBlinking(veh, 2), SetPVarInt(playerid, "blink-car", veh);
                    else DisableCarBlinking(veh);
            }
            #endif
                if(newkeys & KEY_LOOK_LEFT)
            	{
					if(!IsCarBlinking(veh)) SetCarBlinking(veh, 0), SetPVarInt(playerid, "blink-car", veh);
                    else DisableCarBlinking(veh);
                }
                else if(newkeys & KEY_LOOK_RIGHT)
            	{
                    if(!IsCarBlinking(veh)) SetCarBlinking(veh, 1), SetPVarInt(playerid, "blink-car", veh);
                    else DisableCarBlinking(veh);
                }

	            if(IsCarBlinking(veh))
	            {
	                new Float:a, Float:b = BlinkR[veh];
	                GetVehicleZAngle(veh, a);

	                if(BlinkSide[veh] == 0)
	                {
	                    b+=BLINK_TURN_ANGLE;
	                    if(b > 360.0) b -=360.0;
	                    if(a < b-180) a = a+360;
	                    if(b < a-180) b = b+360;

	                    if(a > b) DisableCarBlinking(veh);
	                }
	                else if(BlinkSide[veh] == 1)
	                {
	                    b-=BLINK_TURN_ANGLE;
	                    if(b < 0.0) b = 360.0 + b;
	                    if(a < b-180) a = a+360;
	                    if(b < a-180) b = b+360;

	                    if(a < b) DisableCarBlinking(veh);
	                }
	            }
        }
	}
	return 1;
}

public OnRconLoginAttempt(ip[], password[], success)
{
	return 1;
}

public OnPlayerUpdate(playerid)
{
	//---------------------------------------
	if(IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
	{
		new string[32], Float:H, vehicle = GetPlayerVehicleID(playerid);
		format(string, sizeof(string), "~b~%.0f", GetVehicleSpeed(vehicle));
		PlayerTextDrawSetString(playerid, Vel_Speed[playerid], string);
		GetVehicleHealth(vehicle, H);
		VehData[vehicle][Status] = H;
		//---------------
		if(H < 600)
		{
			PlayerTextDrawShow(playerid, Vel_Motor[playerid]);
		}
		else if(H > 600)
		{
		    PlayerTextDrawHide(playerid, Vel_Motor[playerid]);
		}
		if(VehData[vehicle][Aceite] < 30.0)
		{
			PlayerTextDrawShow(playerid, Vel_iAceite[playerid]);
		}
		else if(VehData[vehicle][Aceite] > 30.0)
		{
			PlayerTextDrawHide(playerid, Vel_iAceite[playerid]);
		}
	}
	return 1;
}

public OnPlayerStreamIn(playerid, forplayerid)
{
	return 1;
}

public OnPlayerStreamOut(playerid, forplayerid)
{
	return 1;
}

public OnVehicleStreamIn(vehicleid, forplayerid)
{
	return 1;
}

public OnVehicleStreamOut(vehicleid, forplayerid)
{
	return 1;
}

public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	switch(dialogid)
	{
	    //----------
	    case DIALOG_REGMAIL:
	    {
	        if(response)
	        {
				if(strfind(inputtext, "@", true) != -1)
				{
					new mail[150], str[77+1];
					format(mail, sizeof(mail), "%s", inputtext);
					PlayersData[playerid][Mail] = mail;
					SendClientMessageEx(playerid, -1, "%s Tu Correo Electrónico es: %s ", InfoMsg, PlayersData[playerid][Mail]);
					format(str, sizeof(str), "{FFFFFF}Contraseña:\n\nIngresa una {EFFF40}contraseña {ffffff}para tu cuenta.");
					ShowPlayerDialog(playerid, DIALOG_REGPASS, DIALOG_STYLE_PASSWORD, "{FF0984}Registro {FFFFFF}» {FF8000}Union {0080FF}Gamer", str, "{00D200}»", "{FF0000}X");

				}
				else
				{
					new str[120+1];
					format(str, sizeof(str), "{EFFF40}Correo Electrónico {DE2A2A}inválido{ffffff} introduce un correo válido.\n\nEjemplo: {83DE38}correo@dominio.com");
					ShowPlayerDialog(playerid, DIALOG_REGMAIL, DIALOG_STYLE_INPUT, "{FF0984}Registro {FFFFFF}» {FF8000}Union {0080FF}Gamer", str, "{00D200}»", "{FF0000}X");
				}
	        }
	        else
	        {
	            SendClientMessageEx(playerid, -1, "%s Cancelaste el Registro.", InfoMsg);
                KickPlayerEx(playerid);
	        }
	    }
	    //----------
		case DIALOG_REGPASS:
		{
			if(response)
			{
				if(strlen(inputtext) > 6 && strlen(inputtext) < 40)
				{
					new hash[65];
					SHA256_PassHash(inputtext, NameForHash(GetPlayerNameEx(playerid)), hash, 64);
					SendClientMessageEx(playerid, -1, "%s Contraseña Guardada.", InfoMsg);
					PlayersData[playerid][Password] = hash;

					new str[73+1];
					format(str, sizeof(str), "{FFFFFF}Edad:\n\nIngresa la {EFFF40}edad {ffffff}que tendrá tu personaje.");
					ShowPlayerDialog(playerid, DIALOG_REGAGE, DIALOG_STYLE_INPUT, "{FF0984}Registro {FFFFFF}» {FF8000}Union {0080FF}Gamer", str, "{00D200}»", "{FF0000}X");
				}
				else
				{
					new str[137+1];
					format(str, sizeof(str), "{EFFF40}Contraseña {DE2A2A}inválida{ffffff} introduce una contraseña válida.\n\nNota: {83DE38}Debe ser mayor a 8 carácteres y menor a 40.");
					ShowPlayerDialog(playerid, DIALOG_REGPASS, DIALOG_STYLE_PASSWORD, "{FF0984}Registro {FFFFFF}» {FF8000}Union {0080FF}Gamer", str, "{00D200}»", "{FF0000}X");
				}
			}
			else
			{
				SendClientMessageEx(playerid, -1, "%s Cancelaste el Registro.", InfoMsg);
                KickPlayerEx(playerid);
			}
		}
		//----------
		case DIALOG_REGAGE:
		{
			if(response)
			{
				if(strval(inputtext) > 17 && strval(inputtext) < 99)
				{
					SendClientMessageEx(playerid, -1, "%s Tu personaje tendrá: {EFFF40}%d {AEAEAE}Años.", InfoMsg, strval(inputtext));
					PlayersData[playerid][Age] = strval(inputtext);

					new str[80+1];
					format(str, sizeof(str), "%s{FFFFFF}Genero:\n\nSelecciona el {EFFF40}genero {ffffff}que tendrá tu personaje.");
					ShowPlayerDialog(playerid, DIALOG_REGGENDER, DIALOG_STYLE_MSGBOX, "{FF0984}Registro {FFFFFF}» {FF8000}Union {0080FF}Gamer", str, "{3fe8e2}Masculino", "{f175ff}Femenino");
				}
				else
				{
					new str[140+1];
					format(str, sizeof(str), "{ffffff}La {EFFF40}edad {ffffff} es {DE2A2A}inválida{ffffff} introduce una edad válida.\n\nNota: {83DE38}Debe ser mayor a 17 y menor a 99.");
					ShowPlayerDialog(playerid, DIALOG_REGAGE, DIALOG_STYLE_INPUT, "{FF0984}Registro {FFFFFF}» {FF8000}Union {0080FF}Gamer", str, "{00D200}»", "{FF0000}X");
				}
			}
			else
			{
				SendClientMessageEx(playerid, -1, "%s Cancelaste el Registro.", InfoMsg);
                KickPlayerEx(playerid);
			}
		}
		//----------
		case DIALOG_REGGENDER:
		{
			if(response)
			{
				SendClientMessageEx(playerid, -1, "%s Seleccionaste el Genero: {3fe8e2}Masculino{AEAEAE}.", InfoMsg);
				PlayersData[playerid][Gender] = 1;

				new str[128+1];
				format(str, sizeof(str), "{45FF3B}» {FFB700}Los Santos\n{45FF3B}» {00A6FF}San Fierro{FF2B2B} {Disabled}\n{45FF3B}» {FF4D4D}Las Venturas{FF2B2B} {Disabled}");
				ShowPlayerDialog(playerid, DIALOG_REGCITY, DIALOG_STYLE_LIST, "{FF0984}Registro {FFFFFF}» {FF8000}Union {0080FF}Gamer", str, "{00D200}»", "{FF0000}X");
			}
			else
			{
				SendClientMessageEx(playerid, -1, "%s Seleccionaste el Genero: {f175ff}Femenino{AEAEAE}.", InfoMsg);
				PlayersData[playerid][Gender] = 2;

				new str[128+1];
				format(str, sizeof(str), "{45FF3B}» {FFB700}Los Santos\n{45FF3B}» {00A6FF}San Fierro{FF2B2B} {Disabled}\n{45FF3B}» {FF4D4D}Las Venturas{FF2B2B} {Disabled}");
				ShowPlayerDialog(playerid, DIALOG_REGCITY, DIALOG_STYLE_LIST, "{FF0984}Registro {FFFFFF}» {FF8000}Union {0080FF}Gamer", str, "{00D200}»", "{FF0000}X");
			}
		}
		//----------
		case DIALOG_REGCITY:
		{
			if(response)
			{
				switch(listitem)
				{
					case 0: //LS
					{
					    SetSpawnInfo(playerid, NO_TEAM, PlayersData[playerid][Skin], 1649.1991, -2286.3701, -1.2096, 270.1755, 0,0,0,0,0,0);
	                    SpawnPlayer(playerid);
						SendClientMessageEx(playerid, -1, "%s Seleccionaste Ciudad: {FFB700}Los Santos{AEAEAE}.", InfoMsg);
						PlayersData[playerid][City] = 1;
						PlayersData[playerid][Money] = 120;
						GivePlayerMoney(playerid, 120);
						SetPVarInt(playerid, "CanJoin", 1);
						CreatePlayerAccount(playerid);

						new str[138+1];
						format(str, sizeof(str), "\n\t \t {0AFF37}Cuenta Creada!\n\n{FFFFFF}Obtuviste un Bono de {038C13}$120 {FFFFFF}de bienvenida.\n\nDisfruta de nuestra Comunidad\n\n");
						ShowPlayerDialog(playerid, 404, DIALOG_STYLE_MSGBOX, "{FF0984}Registro {FFFFFF}» {FF8000}Union {0080FF}Gamer", str, "{3DFF47}Jugar!", "");
					}
					case 1: //SF
					{
						SendClientMessageEx(playerid, -1, "%s Ciudad: {00A6FF}San Fierro {ff3030}Deshabilitada Temporalmente{AEAEAE}.", InfoMsg);

						new str[128+1];
						format(str, sizeof(str), "{45FF3B}» {FFB700}Los Santos\n{45FF3B}» {00A6FF}San Fierro{FF2B2B} {Disabled}\n{45FF3B}» {FF4D4D}Las Venturas{FF2B2B} {Disabled}");
						ShowPlayerDialog(playerid, DIALOG_REGCITY, DIALOG_STYLE_LIST, "{FF0984}Registro {FFFFFF}» {FF8000}Union {0080FF}Gamer", str, "{00D200}»", "{FF0000}X");
					}
					case 2: //LV
					{
						SendClientMessageEx(playerid, -1, "%s Ciudad: {FF4D4D}Las Venturas {ff3030}Deshabilitada Temporalmente{AEAEAE}.", InfoMsg);

						new str[128+1];
						format(str, sizeof(str), "{45FF3B}» {FFB700}Los Santos\n{45FF3B}» {00A6FF}San Fierro{FF2B2B} {Disabled}\n{45FF3B}» {FF4D4D}Las Venturas{FF2B2B} {Disabled}");
						ShowPlayerDialog(playerid, DIALOG_REGCITY, DIALOG_STYLE_LIST, "{FF0984}Registro {FFFFFF}» {FF8000}Union {0080FF}Gamer", str, "{00D200}»", "{FF0000}X");
					}
				}
			}
			else
			{
				SendClientMessageEx(playerid, -1, "%s Cancelaste el Registro.", InfoMsg);
				KickPlayerEx(playerid);
			}
		}
		//----------
		case DIALOG_LOGIN:
		{
		    if(response)
		    {
				new hash[65];
				SHA256_PassHash(inputtext, NameForHash(TempInfo[playerid][rName]), hash, 65);
				new query[250];
				mysql_format(g_MySQL, query, sizeof(query), "SELECT * FROM `users` WHERE `Name`='%e' AND `Password`='%e'", GetPlayerNameEx(playerid), hash);
				mysql_tquery(g_MySQL, query, "LoadPlayerData", "i", playerid);
		    }
		    else
		    {
				SendClientMessageEx(playerid, -1, "%s Cancelaste el Login.", InfoMsg);
                KickPlayerEx(playerid);
		    }
		}
		//----------
		case DIALOG_CONFIG:
		{
			if(response)
			{
				switch(listitem)
				{
					case 0: //Password
					{
					    new str[55+1];
						format(str, sizeof(str), "{FFFFFF}Ingrese su contraseña {FF1919}ACTUAL{FFFFFF}.");
						ShowPlayerDialog(playerid, DIALOG_GLOBAL_INPUT, DIALOG_STYLE_PASSWORD, "{0080FF}Configuración {FFFFFF}» {FF8000}Contraseña", str, "{00D200}»", "{FF0000}X");
						SetPVarString(playerid, "InputType", "Config");
						SetPVarString(playerid, "ConfigType", "Password1");
					}
					case 1: //mail
					{
					    new str[60+1];
						format(str, sizeof(str), "{FFFFFF}Ingrese un nuevo{00FF1E} Correo Electrónico{FFFFFF}.");
						ShowPlayerDialog(playerid, DIALOG_GLOBAL_INPUT, DIALOG_STYLE_INPUT, "{0080FF}Configuración {FFFFFF}» {FF8000}Correo Electronico", str, "{00D200}»", "{FF0000}X");
						SetPVarString(playerid, "InputType", "Config");
						SetPVarString(playerid, "ConfigType", "Mail");
					}
					case 2: //Age
					{
					    new str[117+1];
						format(str, sizeof(str), "{FFFFFF}Ingrese su nueva{00FF1E} Edad{FFFFFF} deseada.\n\n{FF2B2B}Nota: {FFFFFF}La edad se incrementa cada 5 niveles.");
						ShowPlayerDialog(playerid, DIALOG_GLOBAL_INPUT, DIALOG_STYLE_INPUT, "{0080FF}Configuración {FFFFFF}» {FF8000}Edad", str, "{00D200}»", "{FF0000}X");
						SetPVarString(playerid, "InputType", "Config");
						SetPVarString(playerid, "ConfigType", "Age");
					}
					case 3: //Acento
					{
					    new str[600];
						strcat(str, "{B7FF00}1. {FFFFFF}Ninguno\n{B7FF00}2. {FFFFFF}Inglés\n{B7FF00}3. {FFFFFF}Ruso\n{B7FF00}4. {FFFFFF}Italiano\n{B7FF00}5. {FFFFFF}Alemán\n");
						strcat(str, "{B7FF00}6. {FFFFFF}Japonés\n{B7FF00}7. {FFFFFF}Latino\n{B7FF00}8. {FFFFFF}Francés\n{B7FF00}9. {FFFFFF}Chino\n{B7FF00}10. {FFFFFF}Portugués\n{B7FF00}11. {FFFFFF}Mexicano\n");
						strcat(str, "{B7FF00}12. {FFFFFF}Colombiano\n{B7FF00}13. {FFFFFF}Venezolano\n{B7FF00}14. {FFFFFF}Peruano\n{B7FF00}15. {FFFFFF}Ecuatoriano\n{B7FF00}16. {FFFFFF}Argentino\n");
						strcat(str, "{B7FF00}17. {FFFFFF}Chileno\n{B7FF00}18. {FFFFFF}Uruguayo\n{B7FF00}19. {FFFFFF}Dominicano\n{B7FF00}20. {FFFFFF}Puerto Rico");
						ShowPlayerDialog(playerid, DIALOG_GLOBAL_INPUT, DIALOG_STYLE_LIST, "{0080FF}Configuración {FFFFFF}» {FF8000}Acento", str, "{00D200}»", "{FF0000}X");
						SetPVarString(playerid, "InputType", "Config");
						SetPVarString(playerid, "ConfigType", "Acento");
					}
					case 4: //Reiniciar Cuenta
					{
					}
				}
			}
		}
		//----------
		case DIALOG_GLOBAL_INPUT:
		{
		    if(response)
		    {
				new Type[20], Config[50];
				GetPVarString(playerid, "ConfigType", Config, sizeof(Config));
                GetPVarString(playerid, "InputType", Type, sizeof(Type));
				if(!strcmp(Type, "Config", true))
				{
					if(!strcmp(Config, "Password1", true))
					{
					    new hash[65];
						SHA256_PassHash(inputtext, NameForHash(TempInfo[playerid][rName]), hash, 65);
						
					    if(!strcmp(hash, PlayersData[playerid][Password], true))
					    {
					        SetPVarString(playerid, "ConfigType", "Password2");
					    	new str[55+1];
							format(str, sizeof(str), "{FFFFFF}Ingrese una contraseña {00FF1E}NUEVA{FFFFFF}.");
							ShowPlayerDialog(playerid, DIALOG_GLOBAL_INPUT, DIALOG_STYLE_INPUT, "{0080FF}Configuración {FFFFFF}» {FF8000}Contraseña", str, "{00D200}»", "{FF0000}X");
					    }
					    else
					    {
					        new str[65+1];
							format(str, sizeof(str), "{FFFFFF}Contraseña {FF1919}Incorrecta{FFFFFF} Intenta nuevamente.");
							ShowPlayerDialog(playerid, DIALOG_GLOBAL_INPUT, DIALOG_STYLE_INPUT, "{0080FF}Configuración {FFFFFF}» {FF8000}Contraseña", str, "{00D200}»", "{FF0000}X");
					    }
					}
					else if(!strcmp(Config, "Password2", true))
					{
					    if(strlen(inputtext) > 6 && strlen(inputtext) < 40)
						{
							new hash[65], query[256];
							SHA256_PassHash(inputtext, NameForHash(TempInfo[playerid][rName]), hash, 64);
							SendClientMessageEx(playerid, -1, "%s Tú contraseña se ha cambiado.", InfoMsg);
							mysql_format(g_MySQL, query, sizeof(query), "UPDATE `users` SET `Password`='%e' WHERE `Password`='%e' AND `Name`='%e'", hash, PlayersData[playerid][Password], GetPlayerNameEx(playerid));
							new Cache:result = mysql_query(g_MySQL, query);
							cache_delete(result);
							PlayersData[playerid][Password] = hash;
							DeletePVar(playerid, "ConfigType");
							DeletePVar(playerid, "InputType");
						}
						else
						{
							new str[137+1];
							format(str, sizeof(str), "{EFFF40}Contraseña {DE2A2A}inválida{ffffff} introduce una contraseña válida.\n\nNota: {83DE38}Debe ser mayor a 8 carácteres y menor a 40.");
							ShowPlayerDialog(playerid, DIALOG_GLOBAL_INPUT, DIALOG_STYLE_PASSWORD, "{0080FF}Configuración {FFFFFF}» {FF8000}Contraseña", str, "{00D200}»", "{FF0000}X");
						}
					}
					else if(!strcmp(Config, "Mail", true))
					{
						if(strfind(inputtext, "@", true) != -1)
						{
							new mail[150], query[256];
							SendClientMessageEx(playerid, -1, "%s Tu Nuevo Correo Electrónico es: %s ", InfoMsg, inputtext);
                            mysql_format(g_MySQL, query, sizeof(query), "UPDATE `users` SET `Mail`='%e' WHERE `Mail`='%e' AND `Name`='%e'", inputtext, PlayersData[playerid][Mail], GetPlayerNameEx(playerid));
							new Cache:result = mysql_query(g_MySQL, query);
							cache_delete(result);
							format(mail, sizeof(mail), "%s", inputtext);
							PlayersData[playerid][Mail] = mail;
							DeletePVar(playerid, "ConfigType");
							DeletePVar(playerid, "InputType");
						}
						else
						{
							new str[120+1];
							format(str, sizeof(str), "{EFFF40}Correo Electrónico {DE2A2A}inválido{ffffff} introduce un correo válido.\n\nEjemplo: {83DE38}correo@dominio.com");
							ShowPlayerDialog(playerid, DIALOG_GLOBAL_INPUT, DIALOG_STYLE_INPUT, "{0080FF}Configuración {FFFFFF}» {FF8000}Correo Electronico", str, "{00D200}»", "{FF0000}X");
						}
					}
					else if(!strcmp(Config, "Age", true))
					{
					    if(strval(inputtext) > PlayersData[playerid][Age])
					    {
					        new query[256];
							SendClientMessageEx(playerid, -1, "%s Tu Nueva Edad es: %d ", InfoMsg, strval(inputtext));
                            mysql_format(g_MySQL, query, sizeof(query), "UPDATE `users` SET `Age`='%i' WHERE `Name`='%e' AND `Password`='%e'", strval(inputtext), GetPlayerNameEx(playerid), PlayersData[playerid][Password]);
							new Cache:result = mysql_query(g_MySQL, query);
							cache_delete(result);
							PlayersData[playerid][Age] = strval(inputtext);
							DeletePVar(playerid, "ConfigType");
							DeletePVar(playerid, "InputType");
					    }
					    else
					    {
							new str[155+1];
							format(str, sizeof(str), "{ffffff}La {EFFF40}Edad {ffffff}que introduciste es {DE2A2A}inválida{ffffff}.\n\nIntroduce una edad {FF0000}Mayor {FFFFFF}a tu edad actual: {EFFF40}%d", PlayersData[playerid][Age]);
							ShowPlayerDialog(playerid, DIALOG_GLOBAL_INPUT, DIALOG_STYLE_INPUT, "{0080FF}Configuración {FFFFFF}» {FF8000}Edad", str, "{00D200}»", "{FF0000}X");
						}
					}
					else if(!strcmp(Config, "Acento", true))
					{
					    new query[250];
					    PlayersData[playerid][Origin] = listitem;
						SendClientMessageEx(playerid, -1, "%s Seleccionaste acento: %s", InfoMsg, Acentos(playerid));
						mysql_format(g_MySQL, query, sizeof(query), "UPDATE `users` SET `Origin`='%i' WHERE `Name`='%e' AND `Password`='%e'", listitem, GetPlayerNameEx(playerid), PlayersData[playerid][Password]);
						new Cache:result = mysql_query(g_MySQL, query);
						cache_delete(result);
						DeletePVar(playerid, "ConfigType");
						DeletePVar(playerid, "InputType");
					}
					else
					{
				    	SendClientMessageEx(playerid, -1, "%s Ocurrió un error inesperado.", InfoMsg);
					}
				}
				else if(!strcmp(Type, "Depositar", true))
				{
				    if(strval(inputtext) > 0)
				    {
				        if(strval(inputtext) <= PlayersData[playerid][Money])
				        {
				            PlayersData[playerid][BankAccount] += strval(inputtext);
							PlayersData[playerid][Money] -= strval(inputtext);
							GivePlayerMoney(playerid, -strval(inputtext));
				        }
				        else
				        {
				            SendClientMessageEx(playerid, -1, "%s No tienes suficiente dinero en mano.", InfoMsg);
				        }
				    }
				    else
				    {
				        SendClientMessageEx(playerid, -1, "%s La cantidad debe ser mayor a 0.", InfoMsg);
				    }
				}
				else if(!strcmp(Type, "Retirar", true))
				{
					if(strval(inputtext) > 0)
					{
					    if(strval(inputtext) <= PlayersData[playerid][BankAccount])
					    {
					        PlayersData[playerid][BankAccount] -= strval(inputtext);
					        PlayersData[playerid][Money] += strval(inputtext);
							GivePlayerMoney(playerid, strval(inputtext));
					    }
					    else
					    {
					        SendClientMessageEx(playerid, -1, "%s No tienes suficiente dinero en tu Cuenta.", InfoMsg);
					    }
					}
					else
					{
					    SendClientMessageEx(playerid, -1, "%s La cantidad debe ser mayor a 0.", InfoMsg);
					}
				}
				else if(!strcmp(Type, "FaccionMenu", true))
				{
				    switch(listitem)
				    {
				        case 0: //Crear Faccion.
				        {
							new str[56+1];
							format(str, sizeof(str), "{FFFFFF}Ingrese el nombre de la{00FF1E} Facción{FFFFFF}.");
							ShowPlayerDialog(playerid, DIALOG_GLOBAL_INPUT, DIALOG_STYLE_INPUT, "{0080FF}Configuración {FFFFFF}» {FF8000}Crear Facción", str, "{00D200}»", "{FF0000}X");
							SetPVarString(playerid, "InputType", "FaccionEdit");
							SetPVarString(playerid, "ConfigType", "CreateFaccion1");
							TempInfo[playerid][cacheID] = TFacciones+1;
							TFacciones++;
				        }
				        case 1: //Editar Faccion.
				        {
							new str[61+1];
							format(str, sizeof(str), "{FFFFFF}Ingrese la{00FF1E} ID de la Facción{FFFFFF} a editar.");
							ShowPlayerDialog(playerid, DIALOG_GLOBAL_INPUT, DIALOG_STYLE_INPUT, "{0080FF}Configuración {FFFFFF}» {FF8000}Editar Faccion", str, "{00D200}»", "{FF0000}X");
							SetPVarString(playerid, "InputType", "FaccionEdit");
							SetPVarString(playerid, "ConfigType", "EditFaccion1");
				        }
				        case 2: //Eliminar Faccion.
				        {
							SetPVarString(playerid, "InputType", "FaccionEdit");
							SetPVarString(playerid, "ConfigType", "DeleteFaccion1");
				        }
				        case 3: //Añadir Rango.
				        {
							SetPVarString(playerid, "InputType", "FaccionEdit");
							SetPVarString(playerid, "ConfigType", "CreateRank1");
				        }
				        case 4: //Editar Rango.
				        {
							SetPVarString(playerid, "InputType", "FaccionEdit");
							SetPVarString(playerid, "ConfigType", "EditRank1");
				        }
				        case 5: //Info Faccion.
				        {
							//---- Print Faction info.
				        }
				    }
				}
				else if(!strcmp(Type, "FaccionEdit", true))
				{
					if(response)
					{
					    new string[40];
						if(!strcmp(Config, "CreateFaccion1", true))
						{
						    format(string, sizeof(string), "%s", inputtext);
						    FaccData[TempInfo[playerid][cacheID]][Name] = string;
						    new str[179+1];
							format(str, sizeof(str), "{FFFFFF}Ingrese el tipo de {00FF1E} Facción{FFFFFF} que desea.\n\n{3BE610}1 - {FFFFFF}Pública\n{3BE610}2 - {FFFFFF}Privada\n{3BE610}3 - {FFFFFF}Pandilla\n");
							format(str, sizeof(str), "%s{3BE610}4 - {FFFFFF}Mafia", str);
							ShowPlayerDialog(playerid, DIALOG_GLOBAL_INPUT, DIALOG_STYLE_INPUT, "{0080FF}Configuración {FFFFFF}» {FF8000}Crear Facción", str, "{00D200}»", "{FF0000}X");
							SetPVarString(playerid, "InputType", "FaccionEdit");
							SetPVarString(playerid, "ConfigType", "CreateFaccion2");
						}
						else if(!strcmp(Config, "CreateFaccion2", true))
						{
						    new val = strval(inputtext);
						    if(val > 0 && val < 5)
						    {
						        FaccData[TempInfo[playerid][cacheID]][fType] = val;
						        new str[110+1];
								format(str, sizeof(str), "{FFFFFF}¿Deseas Habilitar la Radio para la facción {00FF1E} %s{FFFFFF}?", FaccData[TempInfo[playerid][cacheID]][Name]);
								ShowPlayerDialog(playerid, DIALOG_GLOBAL_INPUT, DIALOG_STYLE_MSGBOX, "{0080FF}Configuración {FFFFFF}» {FF8000}Crear Facción", str, "{3EF705}Sí", "{F73B3B}No");
                                SetPVarString(playerid, "InputType", "FaccionEdit");
								SetPVarString(playerid, "ConfigType", "CreateFaccion3");
							}
						    else
						    {
								new str[179+1];
								format(str, sizeof(str), "{FFFFFF}El tipo debe ser del 1 al 4.\n\n{3BE610}1 - {FFFFFF}Pública\n{3BE610}2 - {FFFFFF}Privada\n{3BE610}3 - {FFFFFF}Pandilla\n");
								format(str, sizeof(str), "%s{3BE610}4 - {FFFFFF}Mafia", str);
								ShowPlayerDialog(playerid, DIALOG_GLOBAL_INPUT, DIALOG_STYLE_INPUT, "{0080FF}Configuración {FFFFFF}» {FF8000}Crear Facción", str, "{00D200}»", "{FF0000}X");
								SetPVarString(playerid, "InputType", "FaccionEdit");
								SetPVarString(playerid, "ConfigType", "CreateFaccion1");
						    }
						}
						else if(!strcmp(Config, "CreateFaccion3", true))
						{
						    if(response)
						    {
						        FaccData[TempInfo[playerid][cacheID]][Radio] = 1;
						    }
						    else
						    {
								FaccData[TempInfo[playerid][cacheID]][Radio] = 0;
						    }
					        new str[110+1];
							format(str, sizeof(str), "{FFFFFF}¿Deseas Habilitar el Family para la facción {00FF1E} %s{FFFFFF}?", FaccData[TempInfo[playerid][cacheID]][Name]);
							ShowPlayerDialog(playerid, DIALOG_GLOBAL_INPUT, DIALOG_STYLE_MSGBOX, "{0080FF}Configuración {FFFFFF}» {FF8000}Crear Facción", str, "{3EF705}Sí", "{F73B3B}No");
							SetPVarString(playerid, "InputType", "FaccionEdit");
							SetPVarString(playerid, "ConfigType", "CreateFaccion4");
						}
						else if(!strcmp(Config, "CreateFaccion4", true))
						{
						    if(response)
						    {
						        FaccData[TempInfo[playerid][cacheID]][Family] = 1;
						    }
						    else
						    {
								FaccData[TempInfo[playerid][cacheID]][Family] = 0;
						    }
						    new str[317+1], tipo[50], radio[20], family[20];
						    if(FaccData[TempInfo[playerid][cacheID]][fType] == 1){  tipo = "{FFFFFF}1 (Pública)";}
						    else if(FaccData[TempInfo[playerid][cacheID]][fType] == 2){  tipo = "{FFFFFF}2 (Privada)";}
						    else if(FaccData[TempInfo[playerid][cacheID]][fType] == 3){  tipo = "{FFFFFF}3 (Pandilla)";}
						    else if(FaccData[TempInfo[playerid][cacheID]][fType] == 4){  tipo = "{FFFFFF}4 (Mafia)";}
						    if(FaccData[TempInfo[playerid][cacheID]][Radio] == 0){  radio = "{F73B3B}0 (No)";}
						    if(FaccData[TempInfo[playerid][cacheID]][Radio] == 1){  radio = "{3DF736}1 (Sí)";}
						    if(FaccData[TempInfo[playerid][cacheID]][Family] == 0){  family = "{F73B3B}0 (No)";}
						    if(FaccData[TempInfo[playerid][cacheID]][Family] == 1){  family = "{3DF736}1 (Sí)";}
						    
							format(str, sizeof(str), "Se ha creado una nueva Facción.\n\n{F7E540}ID: {FFFFFF}%d\n{F7E540}Nombre: {FFFFFF}%s\n{F7E540}Tipo: %s", TempInfo[playerid][cacheID], FaccData[TempInfo[playerid][cacheID]][Name], tipo);
							format(str, sizeof(str), "%s\n{F7E540}Radio: %s\n{F7E540}Family: %s\n{F7E540}Dinero: {FFFFFF}$%d\n{F7E540}Materiales: {FFFFFF}%d\n{F7E540}Drogas: {FFFFFF}%d", str, radio, family, FaccData[TempInfo[playerid][cacheID]][Money], FaccData[TempInfo[playerid][cacheID]][Mats], FaccData[TempInfo[playerid][cacheID]][Drugs]);
							ShowPlayerDialog(playerid, 404, DIALOG_STYLE_MSGBOX, "{0080FF}Configuración {FFFFFF}» {FF8000}Crear Facción", str, "Aceptar", "");
							//------------------
							new query[300];
							mysql_format(g_MySQL, query, sizeof(query), "INSERT INTO `factions`(`ID`, `Name`, `Type`, `Money`, `Radio`, `Family`, `Mats`, `Drugs`) VALUES (null, '%e', '%d', '%d', '%d', '%d', '%d', '%d')",
                            FaccData[TempInfo[playerid][cacheID]][Name], FaccData[TempInfo[playerid][cacheID]][fType], FaccData[TempInfo[playerid][cacheID]][Money],
                            FaccData[TempInfo[playerid][cacheID]][Radio], FaccData[TempInfo[playerid][cacheID]][Family], FaccData[TempInfo[playerid][cacheID]][Mats],
                            FaccData[TempInfo[playerid][cacheID]][Drugs]);
                            mysql_tquery(g_MySQL, query);
							//------------------
							SendAdminLog(playerid, 0, 4, FaccData[TempInfo[playerid][cacheID]][Name]);
							DeletePVar(playerid, "ConfigType");
							DeletePVar(playerid, "InputType");
						}
						else if(!strcmp(Config, "EditFaccion1", true))
						{
						    TempInfo[playerid][cacheID] = strval(inputtext);
						    SendClientMessageEx(playerid, -1, "EditFaccion1 %d", TempInfo[playerid][cacheID]);
				    		new menu[500];
							strcat(menu, "{BFE44E}» {FFFFFF}Cambiar Nombre.\n{BFE44E}» {FFFFFF}Activar/Desactivar Radio.\n");
							strcat(menu, "{BFE44E}» {FFFFFF}Activar/Desactivar Family.\n{BFE44E}» {FFFFFF}Eliminar Facción.\n");
							ShowPlayerDialog(playerid, DIALOG_GLOBAL_INPUT, DIALOG_STYLE_LIST, "{0080FF}Configuración {FFFFFF}» {FF4646}Facciones", menu, "{00D200}»", "{FF0000}X");
							SetPVarString(playerid, "InputType", "FaccionEdit");
							SetPVarString(playerid, "ConfigType", "EditFaccion2");
						}
						else if(!strcmp(Config, "EditFaccion2", true))
						{
						    switch(listitem)
						    {
						        case 0: //Cambiar Nombre
						        {
						            new str[100+1];
									format(str, sizeof(str), "{FFFFFF}Ingrese el nuevo nombre para {00FF1E} %s{FFFFFF}.\t", FaccData[TempInfo[playerid][cacheID]][Name]);
									ShowPlayerDialog(playerid, DIALOG_GLOBAL_INPUT, DIALOG_STYLE_INPUT, "{0080FF}Configuración {FFFFFF}» {FF4646}Cambiar Nombre", str, "{00D200}»", "{FF0000}X");
									SetPVarString(playerid, "InputType", "FaccionEdit");
									SetPVarString(playerid, "ConfigType", "EditFaccion3");
						        }
						        case 1: //Radio
						        {
						            new str[172+1], status[20];
						            if(FaccData[TempInfo[playerid][cacheID]][Radio] == 0){  status = "Desactivado";}
						            else if(FaccData[TempInfo[playerid][cacheID]][Radio] == 1){ status = "Activado";}
									format(str, sizeof(str), "{FFFFFF}¿Desea modificar el acceso a la {00FF1E} Radio{FFFFFF} de la facción\n{00FF1E} %s{FFFFFF}?\n\nActualmente:", FaccData[TempInfo[playerid][cacheID]][Name]);
									format(str, sizeof(str), "%s{FFB50A} %s", str, status);
									ShowPlayerDialog(playerid, DIALOG_GLOBAL_INPUT, DIALOG_STYLE_MSGBOX, "{0080FF}Configuración {FFFFFF}» {FF8000}Radio", str, "{3EF705}Activar", "{F73B3B}Desactivar");
									SetPVarString(playerid, "InputType", "FaccionEdit");
									SetPVarString(playerid, "ConfigType", "RadioFaccion1");
						        }
						        case 2: //Family
						        {
						            new str[172+1], status[20];
						            if(FaccData[TempInfo[playerid][cacheID]][Family] == 0){  status = "Desactivado";}
						            else if(FaccData[TempInfo[playerid][cacheID]][Family] == 1){ status = "Activado";}
									format(str, sizeof(str), "{FFFFFF}¿Desea modificar el acceso al {00FF1E} Family{FFFFFF} de la facción\n{00FF1E} %s{FFFFFF}?\n\nActualmente:", FaccData[TempInfo[playerid][cacheID]][Name]);
									format(str, sizeof(str), "%s{FFB50A} %s", str, status);
									ShowPlayerDialog(playerid, DIALOG_GLOBAL_INPUT, DIALOG_STYLE_MSGBOX, "{0080FF}Configuración {FFFFFF}» {FF8000}Family", str, "{3EF705}Activar", "{F73B3B}Desactivar");
									SetPVarString(playerid, "InputType", "FaccionEdit");
									SetPVarString(playerid, "ConfigType", "FamilyFaccion1");
						        }
						        case 3: //Eliminar Facción
						        {
						            new query[350];
						            mysql_format(g_MySQL, query, sizeof(query), "DELETE FROM `factions` WHERE `ID` = '%d'", TempInfo[playerid][cacheID]);
						            mysql_tquery(g_MySQL, query);
						            mysql_format(g_MySQL, query, sizeof(query), "ALTER TABLE factions AUTO_INCREMENT = 1");
						            mysql_tquery(g_MySQL, query);

									SendAdminLog(playerid, 0, 6, FaccData[TempInfo[playerid][cacheID]][Name]);
						        }
						    }
						}
						else if(!strcmp(Config, "EditFaccion3", true))
						{
						    if(response)
						    {
						        new name[40], str[500];
						        format(name, sizeof(name), "%s", inputtext);
						        FaccData[TempInfo[playerid][cacheID]][Name] = name;
						        
						        new tipo[50], radio[20], family[20];
							    if(FaccData[TempInfo[playerid][cacheID]][fType] == 1){  tipo = "{FFFFFF}1 (Pública)";}
							    else if(FaccData[TempInfo[playerid][cacheID]][fType] == 2){  tipo = "{FFFFFF}2 (Privada)";}
							    else if(FaccData[TempInfo[playerid][cacheID]][fType] == 3){  tipo = "{FFFFFF}3 (Pandilla)";}
							    else if(FaccData[TempInfo[playerid][cacheID]][fType] == 4){  tipo = "{FFFFFF}4 (Mafia)";}
							    if(FaccData[TempInfo[playerid][cacheID]][Radio] == 0){  radio = "{F73B3B}0 (No)";}
							    if(FaccData[TempInfo[playerid][cacheID]][Radio] == 1){  radio = "{3DF736}1 (Sí)";}
							    if(FaccData[TempInfo[playerid][cacheID]][Family] == 0){  family = "{F73B3B}0 (No)";}
							    if(FaccData[TempInfo[playerid][cacheID]][Family] == 1){  family = "{3DF736}1 (Sí)";}
						        format(str, sizeof(str), "Se ha editado la Facción.\n\n{F7E540}ID: {FFFFFF}%d\n{F7E540}Nombre: {FFFFFF}%s\n{F7E540}Tipo: %s", TempInfo[playerid][cacheID], FaccData[TempInfo[playerid][cacheID]][Name], tipo);
								format(str, sizeof(str), "%s\n{F7E540}Radio: %s\n{F7E540}Family: %s\n{F7E540}Dinero: {FFFFFF}$%d\n{F7E540}Materiales: {FFFFFF}%d\n{F7E540}Drogas: {FFFFFF}%d", str, radio, family, FaccData[TempInfo[playerid][cacheID]][Money], FaccData[TempInfo[playerid][cacheID]][Mats], FaccData[TempInfo[playerid][cacheID]][Drugs]);
								ShowPlayerDialog(playerid, 404, DIALOG_STYLE_MSGBOX, "{0080FF}Configuración {FFFFFF}» {FF8000}Crear Facción", str, "Aceptar", "");
								DeletePVar(playerid, "ConfigType");
								DeletePVar(playerid, "InputType");
								mysql_format(g_MySQL, str, sizeof(str), "UPDATE `factions` SET `Name`='%e' WHERE `ID`='%d'",
								FaccData[TempInfo[playerid][cacheID]][Name], TempInfo[playerid][cacheID]);
	                            mysql_tquery(g_MySQL, str);
	                            
								SendAdminLog(playerid, 0, 5, FaccData[TempInfo[playerid][cacheID]][Name]);
							}
						}
						else if(!strcmp(Config, "RadioFaccion1", true))
						{
						    SendClientMessageEx(playerid, -1, "%s Point RadioFaccion1. | ConfigType: %s | InputType: %s", InfoMsg, Type, Config);
						    if(response)
						    {
						        FaccData[TempInfo[playerid][cacheID]][Radio] = 1;
						    }
						    else
						    {
						        FaccData[TempInfo[playerid][cacheID]][Radio] = 0;
						    }
							new tipo[50], radio[20], family[20], str[500];
			    			if(FaccData[TempInfo[playerid][cacheID]][fType] == 1){  tipo = "{FFFFFF}1 (Pública)";}
						    else if(FaccData[TempInfo[playerid][cacheID]][fType] == 2){  tipo = "{FFFFFF}2 (Privada)";}
						    else if(FaccData[TempInfo[playerid][cacheID]][fType] == 3){  tipo = "{FFFFFF}3 (Pandilla)";}
						    else if(FaccData[TempInfo[playerid][cacheID]][fType] == 4){  tipo = "{FFFFFF}4 (Mafia)";}
						    if(FaccData[TempInfo[playerid][cacheID]][Radio] == 0){  radio = "{F73B3B}0 (No)";}
						    if(FaccData[TempInfo[playerid][cacheID]][Radio] == 1){  radio = "{3DF736}1 (Sí)";}
							if(FaccData[TempInfo[playerid][cacheID]][Family] == 0){  family = "{F73B3B}0 (No)";}
			    			if(FaccData[TempInfo[playerid][cacheID]][Family] == 1){  family = "{3DF736}1 (Sí)";}
							format(str, sizeof(str), "Se ha editado la Facción.\n\n{F7E540}ID: {FFFFFF}%d\n{F7E540}Nombre: {FFFFFF}%s\n{F7E540}Tipo: %s", TempInfo[playerid][cacheID], FaccData[TempInfo[playerid][cacheID]][Name], tipo);
							format(str, sizeof(str), "%s\n{F7E540}Radio: %s\n{F7E540}Family: %s\n{F7E540}Dinero: {FFFFFF}$%d\n{F7E540}Materiales: {FFFFFF}%d\n{F7E540}Drogas: {FFFFFF}%d", str, radio, family, FaccData[TempInfo[playerid][cacheID]][Money], FaccData[TempInfo[playerid][cacheID]][Mats], FaccData[TempInfo[playerid][cacheID]][Drugs]);
							ShowPlayerDialog(playerid, 404, DIALOG_STYLE_MSGBOX, "{0080FF}Configuración {FFFFFF}» {FF8000}Crear Facción", str, "Aceptar", "");
							DeletePVar(playerid, "ConfigType");
							DeletePVar(playerid, "InputType");

							mysql_format(g_MySQL, str, sizeof(str), "UPDATE `factions` SET `Radio`='%d' WHERE `ID`='%d'",
							FaccData[TempInfo[playerid][cacheID]][Radio], TempInfo[playerid][cacheID]);
							mysql_tquery(g_MySQL, str);
							
							SendAdminLog(playerid, 0, 5, FaccData[TempInfo[playerid][cacheID]][Name]);
						}
						else if(!strcmp(Config, "FamilyFaccion1", true))
						{
						    if(response)
						    {
						        FaccData[TempInfo[playerid][cacheID]][Family] = 1;
						    }
						    else
						    {
						        FaccData[TempInfo[playerid][cacheID]][Family] = 0;
						    }
							new tipo[50], radio[20], family[20], str[500];
			    			if(FaccData[TempInfo[playerid][cacheID]][fType] == 1){  tipo = "{FFFFFF}1 (Pública)";}
						    else if(FaccData[TempInfo[playerid][cacheID]][fType] == 2){  tipo = "{FFFFFF}2 (Privada)";}
						    else if(FaccData[TempInfo[playerid][cacheID]][fType] == 3){  tipo = "{FFFFFF}3 (Pandilla)";}
						    else if(FaccData[TempInfo[playerid][cacheID]][fType] == 4){  tipo = "{FFFFFF}4 (Mafia)";}
						    if(FaccData[TempInfo[playerid][cacheID]][Radio] == 0){  radio = "{F73B3B}0 (No)";}
						    if(FaccData[TempInfo[playerid][cacheID]][Radio] == 1){  radio = "{3DF736}1 (Sí)";}
							if(FaccData[TempInfo[playerid][cacheID]][Family] == 0){  family = "{F73B3B}0 (No)";}
			    			if(FaccData[TempInfo[playerid][cacheID]][Family] == 1){  family = "{3DF736}1 (Sí)";}
							format(str, sizeof(str), "Se ha editado la Facción.\n\n{F7E540}ID: {FFFFFF}%d\n{F7E540}Nombre: {FFFFFF}%s\n{F7E540}Tipo: %s", TempInfo[playerid][cacheID], FaccData[TempInfo[playerid][cacheID]][Name], tipo);
							format(str, sizeof(str), "%s\n{F7E540}Radio: %s\n{F7E540}Family: %s\n{F7E540}Dinero: {FFFFFF}$%d\n{F7E540}Materiales: {FFFFFF}%d\n{F7E540}Drogas: {FFFFFF}%d", str, radio, family, FaccData[TempInfo[playerid][cacheID]][Money], FaccData[TempInfo[playerid][cacheID]][Mats], FaccData[TempInfo[playerid][cacheID]][Drugs]);
							ShowPlayerDialog(playerid, 404, DIALOG_STYLE_MSGBOX, "{0080FF}Configuración {FFFFFF}» {FF8000}Crear Facción", str, "Aceptar", "");
							DeletePVar(playerid, "ConfigType");
							DeletePVar(playerid, "InputType");
							
							mysql_format(g_MySQL, str, sizeof(str), "UPDATE `factions` SET `Family`='%d' WHERE `ID`='%d'",
							FaccData[TempInfo[playerid][cacheID]][Family], TempInfo[playerid][cacheID]);
							mysql_tquery(g_MySQL, str);

							SendAdminLog(playerid, 0, 5, FaccData[TempInfo[playerid][cacheID]][Name]);
						}
					}
				}
				else if(!strcmp(Type, "etc3", true))
				{
				}
				else
				{
				    SendClientMessageEx(playerid, -1, "%s Ocurrió un error inesperado.", InfoMsg);
				}
		    }
		}
		//------------------ PUERTAS
		case MENU_PUERT6:
	    {
			if(response == 1)
	        {
	            switch(listitem)
	            {
	                case 0:
	                {
	                	ShowPlayerDialog(playerid, MENU_PUER2, DIALOG_STYLE_INPUT, "{0080FF}Configuración {FFFFFF}» {FF4646}Puertas.", "{FFFFFF}Escribe la {BFE44E}ID {FFFFFF}de la puerta que moveras", "Aceptar", "Cancelar");
	                }
	                case 1:
	                {
	                	ShowPlayerDialog(playerid, MENU_PUER7, DIALOG_STYLE_INPUT, "{0080FF}Configuración {FFFFFF}» {FF4646}Puertas", "{FFFFFF}Escribe la {BFE44E}ID {FFFFFF}de la puerta que moveras", "Aceptar", "Cancelar");
	                }
	            }
	        }
	        return 1;
	    }
	    //--------------------
	    case MENU_PUER7:
		{
	        new string[158];
	        if(response == 1)
	        {
	            if(strval(inputtext) <= 0 || strval(inputtext) > MAX_BUILDINGS)
	            {
	                SendClientMessageEx(playerid, -1, "%s ID de puerta inválida.", InfoMsg);
	            }
	            else
	            {
	                format(string, sizeof(string), "PuertasD/PUERTA_%d.ini", strval(inputtext));
					if(!dini_Exists(string))
	                {
                  		SendClientMessageEx(playerid, -1, "%s Esa puerta no existe.", InfoMsg);
	                    return 1;
	                }
	                else
	                {
		                DestroyDynamic3DTextLabel(LabelDI[strval(inputtext)]);
		                DestroyDynamicPickup(PuertaInfor[strval(inputtext)][bPickupID1]);

		                GetPlayerPos(playerid, PuertaInfor[strval(inputtext)][bInteriorX][0], PuertaInfor[strval(inputtext)][bInteriorX][1], PuertaInfor[strval(inputtext)][bInteriorX][2]);
		                PuertaInfor[strval(inputtext)][bInteriorID] = GetPlayerInterior(playerid);
		                PuertaInfor[strval(inputtext)][bVirWorldINT] = GetPlayerVirtualWorld(playerid);
		                switch(PuertaInfor[strval(inputtext)][bType])
			            {
			                case 1: //Publico
			                {
								PuertaInfor[strval(inputtext)][bPickupID1] = CreateDynamicPickup(1239, 23, PuertaInfor[strval(inputtext)][bInteriorX][0], PuertaInfor[strval(inputtext)][bInteriorX][1], PuertaInfor[strval(inputtext)][bInteriorX][2], PuertaInfor[strval(inputtext)][bVirWorldINT], PuertaInfor[strval(inputtext)][bInteriorID], -1, 150.0 );
							}
			                case 2: //Faccion
			                {
								PuertaInfor[strval(inputtext)][bPickupID1] = CreateDynamicPickup(1314, 23, PuertaInfor[strval(inputtext)][bInteriorX][0], PuertaInfor[strval(inputtext)][bInteriorX][1], PuertaInfor[strval(inputtext)][bInteriorX][2], PuertaInfor[strval(inputtext)][bVirWorldINT], PuertaInfor[strval(inputtext)][bInteriorID], -1, 150.0 );
			                }
			                case 3: //SuperMercados
			                {
								PuertaInfor[strval(inputtext)][bPickupID1] = CreateDynamicPickup(19134, 23, PuertaInfor[strval(inputtext)][bInteriorX][0], PuertaInfor[strval(inputtext)][bInteriorX][1], PuertaInfor[strval(inputtext)][bInteriorX][2], PuertaInfor[strval(inputtext)][bVirWorldINT], PuertaInfor[strval(inputtext)][bInteriorID], -1, 150.0 );
			                }
			                case 4: //PuertaInterior
			                {
								PuertaInfor[strval(inputtext)][bPickupID1] = CreateDynamicPickup(19198, 23, PuertaInfor[strval(inputtext)][bInteriorX][0], PuertaInfor[strval(inputtext)][bInteriorX][1], PuertaInfor[strval(inputtext)][bInteriorX][2], PuertaInfor[strval(inputtext)][bVirWorldINT], PuertaInfor[strval(inputtext)][bInteriorID], -1, 150.0 );
			                }
						}
		                format(string, sizeof(string), "\t{BFE44E}%s{FFFFFF}\n\n{0000FF}Dirección: {BFE44E}%s%d", PuertaInfor[strval(inputtext)][bName], GetGPSFromDoor(strval(inputtext)), strval(inputtext));
		                LabelDI[strval(inputtext)] = CreateDynamic3DTextLabel(string, 0xF0CC00FF, PuertaInfor[strval(inputtext)][bInteriorX][0], PuertaInfor[strval(inputtext)][bInteriorX][1], PuertaInfor[strval(inputtext)][bInteriorX][2]+0.75,10.0,INVALID_PLAYER_ID,INVALID_VEHICLE_ID,PuertaInfor[strval(inputtext)][bVirWorldINT],PuertaInfor[strval(inputtext)][bInteriorID],-1,-1, 100.0);

		                SendClientMessageEx( playerid, -1, "%s Interior de la puerta cambiado!", InfoMsg);
		                SaveDoor(strval(inputtext));
		                for(new i=0; i <= GetPlayerPoolSize(); i++)
				        {
							if(PlayersData[i][Admin] >= 2)
							{
							    SendClientMessageEx(i, -1, "%s PUERTA: %d ACCION: Mover By: %s", AlertMsg, strval(inputtext), RemoveUnderScore(playerid));
							}
				        }
	                }

	            }
	        }
			return 1;
		}
	    //--------------------
	    case MENU_PUER2:
		{
	        new string[158];
	        if(response == 1)
	        {
	            if(strval(inputtext) <= 0 || strval(inputtext) > MAX_BUILDINGS)
	            {
	                SendClientMessageEx(playerid, -1, "%s Esta ID es inválida.", InfoMsg);
	            }
	            else
	            {
					format(string, sizeof(string), "PuertasD/PUERTA_%d.ini", strval(inputtext));
				}
				if(!dini_Exists(string))
	            {
					SendClientMessageEx(playerid, -1, "%s Esa puerta no existe!", InfoMsg);
					return 1;
	            }
	            else
	            {
					DestroyDynamicPickup(PuertaInfor[strval(inputtext)][bPickupID]);
					DestroyDynamic3DTextLabel(LabelDE[strval(inputtext)]);
					PuertaInfor[strval(inputtext)][bExteriorID] = GetPlayerInterior(playerid);
					PuertaInfor[strval(inputtext)][bVirWorldINT] = GetPlayerVirtualWorld(playerid);
					GetPlayerPos(playerid, PuertaInfor[strval(inputtext)][bExteriorX][0], PuertaInfor[strval(inputtext)][bExteriorX][1], PuertaInfor[strval(inputtext)][bExteriorX][2]);
                    switch(PuertaInfor[strval(inputtext)][bType])
					{
						case 1: //Publico
						{
							PuertaInfor[strval(inputtext)][bPickupID1] = CreateDynamicPickup(1239, 23, PuertaInfor[strval(inputtext)][bInteriorX][0], PuertaInfor[strval(inputtext)][bInteriorX][1], PuertaInfor[strval(inputtext)][bInteriorX][2], PuertaInfor[strval(inputtext)][bVirWorldINT], PuertaInfor[strval(inputtext)][bInteriorID], -1, 150.0 );
						}
						case 2: //Faccion
						{
							PuertaInfor[strval(inputtext)][bPickupID1] = CreateDynamicPickup(1314, 23, PuertaInfor[strval(inputtext)][bInteriorX][0], PuertaInfor[strval(inputtext)][bInteriorX][1], PuertaInfor[strval(inputtext)][bInteriorX][2], PuertaInfor[strval(inputtext)][bVirWorldINT], PuertaInfor[strval(inputtext)][bInteriorID], -1, 150.0 );
						}
						case 3: //SuperMercados
						{
							PuertaInfor[strval(inputtext)][bPickupID1] = CreateDynamicPickup(19134, 23, PuertaInfor[strval(inputtext)][bInteriorX][0], PuertaInfor[strval(inputtext)][bInteriorX][1], PuertaInfor[strval(inputtext)][bInteriorX][2], PuertaInfor[strval(inputtext)][bVirWorldINT], PuertaInfor[strval(inputtext)][bInteriorID], -1, 150.0 );
						}
						case 4: //PuertaInterior
						{
							PuertaInfor[strval(inputtext)][bPickupID1] = CreateDynamicPickup(19198, 23, PuertaInfor[strval(inputtext)][bInteriorX][0], PuertaInfor[strval(inputtext)][bInteriorX][1], PuertaInfor[strval(inputtext)][bInteriorX][2], PuertaInfor[strval(inputtext)][bVirWorldINT], PuertaInfor[strval(inputtext)][bInteriorID], -1, 150.0 );
						}
					}
					format(string, sizeof(string), "\t{BFE44E}%s{FFFFFF}\n\n{0000FF}Dirección: {BFE44E}%s%d", PuertaInfor[strval(inputtext)][bName], GetGPSFromDoor(strval(inputtext)), strval(inputtext));
					LabelDE[strval(inputtext)] = CreateDynamic3DTextLabel(string, 0xF0CC00FF, PuertaInfor[strval(inputtext)][bExteriorX][0], PuertaInfor[strval(inputtext)][bExteriorX][1], PuertaInfor[strval(inputtext)][bExteriorX][2]+0.75,10.0,INVALID_PLAYER_ID,INVALID_VEHICLE_ID,0,0,-1,-1, 100.0);
					SendClientMessageEx( playerid, -1, "%s Exterior de la puerta cambiado!", InfoMsg);
					SaveDoor(strval(inputtext));
					for(new i=0; i <= GetPlayerPoolSize(); i++)
     				{
						if(PlayersData[i][Admin] >= 2)
						{
			    			SendClientMessageEx(i, -1, "%s PUERTA: %d ACCION: Mover By: %s", AlertMsg, strval(inputtext), RemoveUnderScore(playerid));
						}
       				}
	            }
			}
			return 1;
		}
	    //--------------------
	    case MENU_PUERT2:
		{
	        new string[158];
	        if(response == 1)
	        {
	            switch(listitem)
	            {
	                case 0:
	                {
	                    Informacion[playerid][buildingExterior]++;
	                    Informacion[playerid][cExtID] = GetPlayerInterior( playerid );
	                    GetPlayerPos(playerid, Informacion[playerid][cExtX], Informacion[playerid][cExtY], Informacion[playerid][cExtZ]);

	                    SendClientMessageEx(playerid, -1, "%s Exterior Situado, ahora utiliza /MePuerta y selecciona 'Interior'.", InfoMsg);
	                }
	                case 1:
	                {
	                    Informacion[playerid][buildingInterior]++;
	                    Informacion[playerid][cIntID] = GetPlayerInterior( playerid );
	                    GetPlayerPos( playerid, Informacion[playerid][cIntX], Informacion[playerid][cIntY], Informacion[playerid][cIntZ]);
	                    SendClientMessageEx(playerid, -1, "%s Interior Situado, ahora utiliza /MePuerta y selecciona 'Completar'.", InfoMsg);
	                }
	                case 2:
	                {
	                    if(Informacion[playerid][buildingInterior] > 0 || Informacion[playerid][buildingExterior] > 0)
	                    {
	                        new NuevaPuertaID = Spawnedbuildings+1;
	                        if(NuevaPuertaID >= MAX_BUILDINGS)
	                        {
	                            SendClientMessageEx( playerid, -1, "%s Máximo de Puertas alcanzado! Contacta un Administrador.", InfoMsg);
	                        }
	                        else
	                        {
								format( string, sizeof( string ), "PuertasD/PUERTA_%d.ini", NuevaPuertaID);
								if(dini_Exists(string))
								{
									Spawnedbuildings++;
									format(string, sizeof(string), "%s Puerta (ID: %d) ya existe!", InfoMsg, NuevaPuertaID);
									SendClientMessage(playerid, -1, string);
									SendClientMessageEx(playerid, -1, "%s Coloca nuevamente el botón 'Completar' hasta que se ponga.", InfoMsg);
									ShowPlayerDialog(playerid, MENU_PUERT2, DIALOG_STYLE_LIST, "{0080FF}Configuración {FFFFFF}» {FF4646}Puertas.", "Exterior\nInterior\nCompletar", "Aceptar", "Cancelar");
								}
								else
								{
									PuertaInfor[NuevaPuertaID][bInteriorID] = Informacion[playerid][cIntID];
									PuertaInfor[NuevaPuertaID][bExteriorID] = Informacion[playerid][cExtID];
									PuertaInfor[NuevaPuertaID][bInteriorX][0] = Informacion[playerid][cIntX];
									PuertaInfor[NuevaPuertaID][bInteriorX][1] = Informacion[playerid][cIntY];
									PuertaInfor[NuevaPuertaID][bInteriorX][2] = Informacion[playerid][cIntZ];
									PuertaInfor[NuevaPuertaID][bExteriorX][0] = Informacion[playerid][cExtX];
									PuertaInfor[NuevaPuertaID][bExteriorX][1] = Informacion[playerid][cExtY];
									PuertaInfor[NuevaPuertaID][bExteriorX][2] = Informacion[playerid][cExtZ];
									format(PuertaInfor[NuevaPuertaID][bName], 255, "SinNombre" );
									PuertaInfor[NuevaPuertaID][bLocked] = 0;
									PuertaInfor[NuevaPuertaID][bType] = 0;
									PuertaInfor[NuevaPuertaID][bFacc] = 0;
									PuertaInfor[NuevaPuertaID][bVirWorldINT] = GetPlayerVirtualWorld(playerid);
									PuertaInfor[NuevaPuertaID][bPickupID] = CreateDynamicPickup(18631, 23, PuertaInfor[NuevaPuertaID][bExteriorX][0], PuertaInfor[NuevaPuertaID][bExteriorX][1], PuertaInfor[NuevaPuertaID][bExteriorX][2], PuertaInfor[NuevaPuertaID][bVirWorldEXT], PuertaInfor[NuevaPuertaID][bExteriorID], -1, 150.0 );
									PuertaInfor[NuevaPuertaID][bPickupID1] = CreateDynamicPickup(18631, 23, PuertaInfor[NuevaPuertaID][bInteriorX][0], PuertaInfor[NuevaPuertaID][bInteriorX][1], PuertaInfor[NuevaPuertaID][bInteriorX][2], PuertaInfor[NuevaPuertaID][bVirWorldINT], PuertaInfor[NuevaPuertaID][bInteriorID], -1, 150.0 );

									dini_Create(string);
									dini_Set(string, "Name", "SinNombre");
									dini_IntSet(string, "PickupID", PuertaInfor[NuevaPuertaID][bPickupID]);
									dini_IntSet(string, "PickupID1", PuertaInfor[NuevaPuertaID][bPickupID1]);
									dini_IntSet(string, "Locked", PuertaInfor[NuevaPuertaID][bLocked]);
									dini_IntSet( string, "Tipo", PuertaInfor[NuevaPuertaID][bType]);
									dini_IntSet( string, "ExteriorID", Informacion[playerid][cExtID]);
									dini_IntSet( string, "InteriorID", PuertaInfor[NuevaPuertaID][bInteriorID]);
									dini_IntSet( string, "VirtualWorld", PuertaInfor[NuevaPuertaID][bVirWorldINT]);
									dini_FloatSet( string, "InteriorX", PuertaInfor[NuevaPuertaID][bInteriorX][0]);
									dini_FloatSet( string, "InteriorY", PuertaInfor[NuevaPuertaID][bInteriorX][1]);
									dini_FloatSet( string, "InteriorZ", PuertaInfor[NuevaPuertaID][bInteriorX][2]);
									dini_FloatSet( string, "ExteriorX", PuertaInfor[NuevaPuertaID][bExteriorX][0]);
									dini_FloatSet( string, "ExteriorY", PuertaInfor[NuevaPuertaID][bExteriorX][1]);
									dini_FloatSet( string, "ExteriorZ", PuertaInfor[NuevaPuertaID][bExteriorX][2]);
									dini_IntSet( string, "Faccion", PuertaInfor[NuevaPuertaID][bFacc]);

									Informacion[playerid][buildingExterior]--;
									Informacion[playerid][buildingInterior]--;

									Spawnedbuildings++;

									format(string, sizeof(string), "\t{BFE44E}%s{FFFFFF}\n\n{0000FF}Dirección: {BFE44E}%s%d",PuertaInfor[NuevaPuertaID][bName], GetGPSFromDoor(NuevaPuertaID), NuevaPuertaID);
									LabelDE[NuevaPuertaID] = CreateDynamic3DTextLabel(string, 0xF0CC00FF, PuertaInfor[NuevaPuertaID][bExteriorX][0], PuertaInfor[NuevaPuertaID][bExteriorX][1], PuertaInfor[NuevaPuertaID][bExteriorX][2]+0.75,10.0,INVALID_PLAYER_ID,INVALID_VEHICLE_ID,0,PuertaInfor[NuevaPuertaID][bVirWorldEXT], PuertaInfor[NuevaPuertaID][bExteriorID],-1, 100.0);
									format(string, sizeof(string), "\t{BFE44E}%s{FFFFFF}\n\n{0000FF}Dirección: {BFE44E}%s%d",PuertaInfor[NuevaPuertaID][bName], GetGPSFromDoor(NuevaPuertaID), NuevaPuertaID);
									LabelDI[NuevaPuertaID] = CreateDynamic3DTextLabel(string, 0xF0CC00FF, PuertaInfor[NuevaPuertaID][bInteriorX][0], PuertaInfor[NuevaPuertaID][bInteriorX][1], PuertaInfor[NuevaPuertaID][bInteriorX][2]+0.75,10.0,INVALID_PLAYER_ID,INVALID_VEHICLE_ID,PuertaInfor[NuevaPuertaID][bVirWorldINT],PuertaInfor[NuevaPuertaID][bInteriorID],-1,-1, 100.0);

									format(string, sizeof(string), "%s Utiliza: /MePuerta para cambiar el nombre (ID: %d)", InfoMsg, NuevaPuertaID);
									SendClientMessage(playerid, -1, string);
									SendClientMessageEx(playerid, -1, "%s Puerta creada correctamente!", InfoMsg);
									SetPlayerInterior(playerid, PuertaInfor[NuevaPuertaID][bExteriorID]);
									SetPlayerPos(playerid, PuertaInfor[NuevaPuertaID][bExteriorX][0], PuertaInfor[NuevaPuertaID][bExteriorX][1], PuertaInfor[NuevaPuertaID][bExteriorX][2]);
                                    for(new i=0; i <= GetPlayerPoolSize(); i++)
				     				{
										if(PlayersData[i][Admin] >= 2)
										{
							    			SendClientMessageEx(i, -1, "%s PUERTA: %d ACCION: Creada By: %s", AlertMsg, strval(inputtext), RemoveUnderScore(playerid));
										}
				       				}
								}
							}
	                    }
	                }
	            }
	        }
	        return 1;
	    }
	    //--------------------
	    case MENU_PUERT1:
		{
				if(response == 1)
				{
					if(strval(inputtext) <= 0 || strval(inputtext) > MAX_BUILDINGS)
					{
						SendClientMessageEx(playerid, -1, "%s ID de puerta inválida.", InfoMsg);
					}
					else
					{
	                   SetPlayerPos(playerid, PuertaInfor[strval(inputtext)][bExteriorX][0], PuertaInfor[strval(inputtext)][bExteriorX][1], PuertaInfor[strval(inputtext)][bExteriorX][2]);
					}
				}
				return 1;
	    }
	    //--------------------
        case MENU_PUERT7:
		{
	        if(response == 1)
			{
	            if(strval(inputtext) <= 0 || strval(inputtext) > MAX_BUILDINGS)
				{
	                SendClientMessageEx(playerid, -1, "%s ID de puerta inválida.", InfoMsg);
	            }
	            else
				{
	                   PuertaMoverID[playerid] = strval(inputtext);
	                   ShowPlayerDialog(playerid, MENU_PUER3, DIALOG_STYLE_INPUT, "{0080FF}Configuración {FFFFFF}» {FF4646}Puertas.", "Escribe el VirtualWorld que le pondrás.", "Aceptar", "Cancelar");
	            }
	        }
	        return 1;
	    }
		//--------------------
		case MENU_PUER3:
		{
			new string[158];
	        if(response == 1)
			{
	            if(strval(inputtext) <= 0 || strval(inputtext) > MAX_BUILDINGS)
				{
	                SendClientMessageEx(playerid, -1, "%s ID de puerta inválida.", InfoMsg);
	            }
	            else
				{
	                format(string, sizeof(string), "PuertasD/PUERTA_%d.ini", PuertaMoverID[playerid]);
	                if(!dini_Exists(string))
					{
	                    SendClientMessageEx(playerid, -1, "%s ID de puerta inválida.", InfoMsg);
	                    return 1;
	                }
	                else
	                {
	                    PuertaInfor[PuertaMoverID[playerid]][bVirWorldINT] = strval(inputtext);
	                    format(string, sizeof(string), "%s Has situado la puerta (ID: %d) al VirtualWorld %d.", InfoMsg, PuertaMoverID[playerid], strval(inputtext));
	                    SendClientMessage(playerid, -1, string);
	                    SaveDoor(PuertaMoverID[playerid]);
	                    for(new i=0; i <= GetPlayerPoolSize(); i++)
	     				{
							if(PlayersData[i][Admin] >= 2)
							{
				    			SendClientMessageEx(i, -1, "%s PUERTA: %d ACCION: VW-Config By: %s", AlertMsg, strval(inputtext), RemoveUnderScore(playerid));
							}
	       				}
	                }

	            }
	        }
	        return 1;
	    }
	    //--------------------
	    case MENU_PUERT4:
		{
	        if(response == 1)
			{
	            if(strval(inputtext) <= 0 || strval(inputtext) > MAX_BUILDINGS)
				{
	                SendClientMessageEx(playerid, -1, "%s ID de puerta inválida.", InfoMsg);
	            }
	            else
				{
	                PuertaEliminarID[playerid] = strval(inputtext);
	                ShowPlayerDialog(playerid, MENU_PUER1, DIALOG_STYLE_INPUT, "{0080FF}Configuración {FFFFFF}» {FF4646}Puertas", "Ingresa el nombre que le pondrás a la puerta.", "Aceptar", "Cancelar");
	            }
	        }
	        return 1;
	    }
	    //--------------------
	    case MENU_PUERT5:
		{
	        new string[158];
	        if(response == 1)
			{
	            if(strval(inputtext) <= 0 || strval(inputtext) > MAX_BUILDINGS)
				{
	                SendClientMessageEx(playerid, -1, "%s ID de puerta inválida.", InfoMsg);
	            }
	            else
				{
	                format(string, sizeof(string), "PuertasD/PUERTA_%d.ini", strval(inputtext));
	                if(!dini_Exists(string))
					{
	                    SendClientMessageEx(playerid, -1, "%s ID de puerta inválida.", InfoMsg);
	                    return 1;
	                }
	                if(PuertaInfor[strval(inputtext)][bLocked] == 1)
					{
	                    PuertaInfor[strval(inputtext)][bLocked] = 0;
	                    GameTextForPlayer(playerid, "~g~Puerta Abierta", 1000, 5);
	                    SaveDoor(strval(inputtext));
	                }
	                else
					{
	                    PuertaInfor[strval(inputtext)][bLocked] = 1;
	                    GameTextForPlayer(playerid, "~r~Puerta Cerrada", 1000, 5);
	                    SaveDoor(strval(inputtext));
	                }
				}
	        }
	        return 1;
	    }
	    //--------------------
	    case MENU_PUER1:
		{
	        new string[158];
	        if(response == 1)
			{
	            new LALA1 = PuertaEliminarID[playerid];
	            format(string, sizeof(string), "PuertasD/PUERTA_%d.ini", LALA1);
	            if(!dini_Exists(string))
				{
	                SendClientMessageEx(playerid, -1, "%s ID de puerta inválida.", InfoMsg);
	                return 1;
	            }
	            else
				{
	                format(PuertaInfor[LALA1][bName], 255, "%s", inputtext);
	                dini_Set(string, "Name", PuertaInfor[LALA1][bName]);
	                format(string, sizeof(string), "\t{BFE44E}%s{FFFFFF}\n\n{0000FF}Dirección: {BFE44E}%s%d", PuertaInfor[LALA1][bName], GetGPSFromDoor(LALA1), LALA1);
	                UpdateDynamic3DTextLabelText(LabelDE[LALA1], 0xF0CC00FF, string);

	                format(string, sizeof(string), "\t{BFE44E}%s{FFFFFF}\n\n{0000FF}Dirección: {BFE44E}%s%d", PuertaInfor[LALA1][bName], GetGPSFromDoor(LALA1), LALA1);
	                UpdateDynamic3DTextLabelText(LabelDI[LALA1], 0xF0CC00FF, string);

	                format(string, sizeof(string), "%s Has cambiado el nombre de la puerta (ID: %d) a %s.", InfoMsg, LALA1, inputtext);
	                SendClientMessage(playerid, -1, string);
	                SaveDoor(LALA1);
	                for(new i=0; i <= GetPlayerPoolSize(); i++)
     				{
						if(PlayersData[i][Admin] >= 2)
						{
			    			SendClientMessageEx(i, -1, "%s PUERTA: %d ACCION: Renombrar By: %s", AlertMsg, LALA1, RemoveUnderScore(playerid));
						}
       				}
	            }
	        }
	        return 1;
	    }
	    //--------------------
	    case MENU_PUERT3:
		{
	        new string[158];
	        new FileName[158];
	        if(response == 1)
			{
	            if(strval(inputtext) <= 0 || strval(inputtext) > MAX_BUILDINGS)
				{
	                SendClientMessageEx(playerid, -1, "%s ID de puerta inválida.", InfoMsg);
	            }
	            else
				{
	                format(string, sizeof(string), "PuertasD/PUERTA_%d.ini", strval(inputtext));
	                if(!fexist(string))
					{
	                    SendClientMessageEx(playerid, -1, "%s Esa puerta no existe!", InfoMsg);
	                    return 1;
	                }
	                else
					{
						PuertaInfor[strval(inputtext)][bExteriorX][0] = 0;
						PuertaInfor[strval(inputtext)][bExteriorX][1] = 0;
						PuertaInfor[strval(inputtext)][bExteriorX][2] = 0;
						DestroyDynamicPickup(PuertaInfor[strval(inputtext)][bPickupID]);
						DestroyDynamicPickup(PuertaInfor[strval(inputtext)][bPickupID1]);
						DestroyDynamic3DTextLabel(LabelDE[strval(inputtext)]);
						DestroyDynamic3DTextLabel(LabelDI[strval(inputtext)]);
						format(string, sizeof(string), "%s Has eliminado la puerta (ID: %d).", InfoMsg, strval(inputtext));
						SendClientMessage(playerid, -1, string);
						format(FileName, sizeof(FileName), "PuertasD/PUERTA_%d.ini", strval(inputtext));
						dini_Remove(FileName);
						Spawnedbuildings--;
						for(new i=0; i <= GetPlayerPoolSize(); i++)
	     				{
							if(PlayersData[i][Admin] >= 2)
							{
				    			SendClientMessageEx(i, -1, "%s PUERTA: %d ACCION: Eliminar By: %s", AlertMsg, strval(inputtext), RemoveUnderScore(playerid));
							}
	       				}
	                }
	            }
	        }
	        return 1;
	    }
	    //--------------------
	    case MENU_PUERT8:
		{
	        if(response == 1)
			{
	            if(strval(inputtext) <= 0 || strval(inputtext) > MAX_BUILDINGS)
				{
	                SendClientMessageEx(playerid, -1, "%s ID de puerta inválida.", InfoMsg);
	            }
	            else
				{
	                   PuertaMoverID[playerid] = strval(inputtext);
	                   ShowPlayerDialog(playerid, MENU_PUER4, DIALOG_STYLE_INPUT, "{0080FF}Configuración {FFFFFF}» {FF4646}Puertas.", "Escribe la ID de Faccion de esta puerta.", "Aceptar", "Cancelar");
	            }
	        }
	        return 1;
	    }
	    //--------------------
	    case MENU_PUER4:
		{
			new string[158];
	        if(response == 1)
			{
	            if(strval(inputtext) <= 0 || strval(inputtext) > MAX_BUILDINGS)
				{
	                SendClientMessageEx(playerid, -1, "%s ID de puerta inválida.", InfoMsg);
	            }
	            else
				{
	                format(string, sizeof(string), "PuertasD/PUERTA_%d.ini", PuertaMoverID[playerid]);
	                if(!dini_Exists(string))
					{
	                    SendClientMessageEx(playerid, -1, "%s ID de puerta inválida.", InfoMsg);
	                    return 1;
	                }
	                else
	                {
	                    PuertaInfor[PuertaMoverID[playerid]][bFacc] = strval(inputtext);
	                    format(string, sizeof(string), "%s Has asignado la puerta (ID: %d) a la faccion %d.", InfoMsg, PuertaMoverID[playerid], strval(inputtext));
	                    SendClientMessage(playerid, -1, string);
	                    SaveDoor(PuertaMoverID[playerid]);
	                    for(new i=0; i <= GetPlayerPoolSize(); i++)
	     				{
							if(PlayersData[i][Admin] >= 2)
							{
				    			SendClientMessageEx(i, -1, "%s PUERTA: %d ACCION: Faccion By: %s", AlertMsg, strval(inputtext), RemoveUnderScore(playerid));
							}
	       				}
	                }

	            }
	        }
	        return 1;
	    }
	    //--------------------
	    case MENU_PUERT9:
		{
	        if(response == 1)
			{
	            if(strval(inputtext) <= 0 || strval(inputtext) > MAX_BUILDINGS)
				{
	                SendClientMessageEx(playerid, -1, "%s ID de puerta inválida.", InfoMsg);
	            }
	            else
				{
	                   PuertaMoverID[playerid] = strval(inputtext);
	                   ShowPlayerDialog(playerid, MENU_PUER5, DIALOG_STYLE_INPUT, "{0080FF}Configuración {FFFFFF}» {FF4646}Puertas.", "Escribe el Tipo Puerta.\n1 - Publica\n2 - Faccion\n3 - Supermercados\n4 - Puertas Interiores", "Aceptar", "Cancelar");
	            }
	        }
	        return 1;
	    }
	    case MENU_PUER5:
		{
			new string[158];
	        if(response == 1)
			{
	            if(strval(inputtext) <= 0 || strval(inputtext) > MAX_BUILDINGS)
				{
	                SendClientMessageEx(playerid, -1, "%s ID de puerta inválida.", InfoMsg);
	            }
	            else
				{
	                format(string, sizeof(string), "PuertasD/PUERTA_%d.ini", PuertaMoverID[playerid]);
	                if(!dini_Exists(string))
					{
	                    SendClientMessageEx(playerid, -1, "%s ID de puerta inválida.", InfoMsg);
	                    return 1;
	                }
	                else
	                {
	                    PuertaInfor[PuertaMoverID[playerid]][bType] = strval(inputtext);
	                    DestroyDynamicPickup(PuertaInfor[PuertaMoverID[playerid]][bPickupID]);
						DestroyDynamicPickup(PuertaInfor[PuertaMoverID[playerid]][bPickupID1]);
						switch(PuertaInfor[PuertaMoverID[playerid]][bType])
						{
							case 1: //Publico
							{
								PuertaInfor[PuertaMoverID[playerid]][bPickupID1] = CreateDynamicPickup(1239, 23, PuertaInfor[strval(inputtext)][bInteriorX][0], PuertaInfor[strval(inputtext)][bInteriorX][1], PuertaInfor[strval(inputtext)][bInteriorX][2], PuertaInfor[strval(inputtext)][bVirWorldINT], PuertaInfor[strval(inputtext)][bInteriorID], -1, 150.0 );
								PuertaInfor[PuertaMoverID[playerid]][bPickupID1] = CreateDynamicPickup(1239, 23, PuertaInfor[strval(inputtext)][bExteriorX][0], PuertaInfor[strval(inputtext)][bExteriorX][1], PuertaInfor[strval(inputtext)][bExteriorX][2], PuertaInfor[strval(inputtext)][bVirWorldEXT], PuertaInfor[strval(inputtext)][bExteriorID], -1, 150.0 );
							}
							case 2: //Faccion
							{
								PuertaInfor[PuertaMoverID[playerid]][bPickupID1] = CreateDynamicPickup(1314, 23, PuertaInfor[strval(inputtext)][bInteriorX][0], PuertaInfor[strval(inputtext)][bInteriorX][1], PuertaInfor[strval(inputtext)][bInteriorX][2], PuertaInfor[strval(inputtext)][bVirWorldINT], PuertaInfor[strval(inputtext)][bInteriorID], -1, 150.0 );
								PuertaInfor[PuertaMoverID[playerid]][bPickupID1] = CreateDynamicPickup(1314, 23, PuertaInfor[strval(inputtext)][bExteriorX][0], PuertaInfor[strval(inputtext)][bExteriorX][1], PuertaInfor[strval(inputtext)][bExteriorX][2], PuertaInfor[strval(inputtext)][bVirWorldEXT], PuertaInfor[strval(inputtext)][bExteriorID], -1, 150.0 );
							}
							case 3: //SuperMercados
							{
								PuertaInfor[PuertaMoverID[playerid]][bPickupID1] = CreateDynamicPickup(19134, 23, PuertaInfor[strval(inputtext)][bInteriorX][0], PuertaInfor[strval(inputtext)][bInteriorX][1], PuertaInfor[strval(inputtext)][bInteriorX][2], PuertaInfor[strval(inputtext)][bVirWorldINT], PuertaInfor[strval(inputtext)][bInteriorID], -1, 150.0 );
								PuertaInfor[PuertaMoverID[playerid]][bPickupID1] = CreateDynamicPickup(19134, 23, PuertaInfor[strval(inputtext)][bExteriorX][0], PuertaInfor[strval(inputtext)][bExteriorX][1], PuertaInfor[strval(inputtext)][bExteriorX][2], PuertaInfor[strval(inputtext)][bVirWorldEXT], PuertaInfor[strval(inputtext)][bExteriorID], -1, 150.0 );
							}
							case 4: //PuertaInterior
							{
								PuertaInfor[PuertaMoverID[playerid]][bPickupID1] = CreateDynamicPickup(19198, 23, PuertaInfor[strval(inputtext)][bInteriorX][0], PuertaInfor[strval(inputtext)][bInteriorX][1], PuertaInfor[strval(inputtext)][bInteriorX][2], PuertaInfor[strval(inputtext)][bVirWorldINT], PuertaInfor[strval(inputtext)][bInteriorID], -1, 150.0 );
								PuertaInfor[PuertaMoverID[playerid]][bPickupID1] = CreateDynamicPickup(19198, 23, PuertaInfor[strval(inputtext)][bExteriorX][0], PuertaInfor[strval(inputtext)][bExteriorX][1], PuertaInfor[strval(inputtext)][bExteriorX][2], PuertaInfor[strval(inputtext)][bVirWorldEXT], PuertaInfor[strval(inputtext)][bExteriorID], -1, 150.0 );
							}
						}
	                    format(string, sizeof(string), "%s Has asignado la puerta (ID: %d) Tipo: %d.", InfoMsg, PuertaMoverID[playerid], strval(inputtext));
	                    SendClientMessage(playerid, -1, string);
	                    SaveDoor(PuertaMoverID[playerid]);
	                    for(new i=0; i <= GetPlayerPoolSize(); i++)
	     				{
							if(PlayersData[i][Admin] >= 2)
							{
				    			SendClientMessageEx(i, -1, "%s PUERTA: %d ACCION: Tipo By: %s", AlertMsg, strval(inputtext), RemoveUnderScore(playerid));
							}
	       				}
	                }

	            }
	        }
	        return 1;
	    }
		//--------------------
	    case MENU_PUERT:
		{
	        new string[158];
	        if(response == 1)
			{
	            switch(listitem)
				{
	                case 0:
					{
						ShowPlayerDialog(playerid, MENU_PUERT1, DIALOG_STYLE_INPUT, "{0080FF}Configuración {FFFFFF}» {FF4646}Puertas", "Escribe el ID de la puerta a la que quieres ir", "Aceptar", "Cancelar");
	                }
	                case 1:
	                {
						ShowPlayerDialog(playerid, MENU_PUERT2, DIALOG_STYLE_LIST, "{0080FF}Configuración {FFFFFF}» {FF4646}Puertas", "Exterior\nInterior\nCompletar", "Aceptar", "Cancelar");
	                }
	                case 2:
	                {
						ShowPlayerDialog(playerid, MENU_PUERT3, DIALOG_STYLE_INPUT, "{0080FF}Configuración {FFFFFF}» {FF4646}Puertas", "Escribe el ID de la puerta que borrarás.", "Aceptar", "Cancelar");
	                }
	                case 3:
	                {
	                    for(new i = 0; i < sizeof(PuertaInfor); i++)
						{
							if(IsPlayerInRangeOfPoint(playerid, 3, PuertaInfor[i][bExteriorX][0], PuertaInfor[i][bExteriorX][1], PuertaInfor[i][bExteriorX][2]))
							{
	                            format(string, sizeof(string), "ID PUERTA: %d", i);
	                            SendClientMessage(playerid, -1, string);
	                        }
	                    }
	                }
	                case 4:
	                {
						ShowPlayerDialog(playerid, MENU_PUERT4, DIALOG_STYLE_INPUT, "{0080FF}Configuración {FFFFFF}» {FF4646}Puertas", "Escribe el ID de la puerta que le cambiarás el nombre.", "Aceptar", "Cancelar");
	                }
	                case 5:
	                {
						ShowPlayerDialog(playerid, MENU_PUERT5, DIALOG_STYLE_INPUT, "{0080FF}Configuración {FFFFFF}» {FF4646}Puertas", "Escribe el ID de la puerta que cerrarás", "Aceptar", "Cancelar");
	                }
	                case 6:
	                {
						ShowPlayerDialog(playerid, MENU_PUERT6, DIALOG_STYLE_LIST, "{0080FF}Configuración {FFFFFF}» {FF4646}Puertas", "Exterior\nInterior", "Aceptar", "Cancelar");
	                }
	                case 7:
	                {
						ShowPlayerDialog(playerid, MENU_PUERT7, DIALOG_STYLE_INPUT, "{0080FF}Configuración {FFFFFF}» {FF4646}Puertas", "Escribe el ID de la puerta que vas a editar VW", "Aceptar", "Cancelar");
	                }
	                case 8:
	                {
						ShowPlayerDialog(playerid, MENU_PUERT8, DIALOG_STYLE_INPUT, "{0080FF}Configuración {FFFFFF}» {FF4646}Puertas", "Escribe el ID de la puerta que vas a editar Faccion", "Aceptar", "Cancelar");
	                }
	                case 9:
	                {
						ShowPlayerDialog(playerid, MENU_PUERT9, DIALOG_STYLE_INPUT, "{0080FF}Configuración {FFFFFF}» {FF4646}Puertas", "Escribe el ID de la puerta que vas a editar Tipo", "Aceptar", "Cancelar");
	                }
	            }
	        }
	    }
	    //----------
	    case MENU_NEGOCIO:
	    {
	        if(response)
	        {
	            switch(listitem)
	            {
	                case 0:
					{
						ShowPlayerDialog(playerid, MENU_NEGOCIO_CREAR, DIALOG_STYLE_LIST, "{0080FF}Configuración {FFFFFF}» {FF4646}Negocio", "Exterior\nInterior\nCompletar", "Aceptar", "Cancelar");
	                }
	                case 1:
	                {
						ShowPlayerDialog(playerid, MENU_NEGOCIO_TIPO, DIALOG_STYLE_INPUT, "{0080FF}Configuración {FFFFFF}» {FF4646}Negocio", "Escribe la ID del Negocio", "Aceptar", "Cancelar");
	                }
	                case 2:
	                {
						ShowPlayerDialog(playerid, MENU_NEGOCIO_PRECIO, DIALOG_STYLE_INPUT, "{0080FF}Configuración {FFFFFF}» {FF4646}Negocio", "Escribe la ID del Negocio.", "Aceptar", "Cancelar");
	                }
	                case 3:
	                {
	                    for(new i = 1; i < sizeof(Negocios); i++)
						{
							if(IsPlayerInRangeOfPoint(playerid, 3, Negocios[i][nPEx], Negocios[i][nPEy], Negocios[i][nPEz]))
							{
	                            SendClientMessageEx(playerid, -1, "%s ID Negocio: %d", InfoMsg, i);
	                        }
	                    }
	                }
	                case 4:
	                {
                        ShowPlayerDialog(playerid, MENU_NEGOCIO_TP, DIALOG_STYLE_INPUT, "{0080FF}Configuración {FFFFFF}» {FF4646}Negocio", "Escribe la ID del Negocio que quieres ir", "Ir", "Cancelar");
	                }
				}
	        }
	        return 1;
	    }
	    //----------------------
	    case MENU_NEGOCIO_CREAR:
	    {
	        if(response)
	        {
	            switch(listitem)
	            {
	                case 0:
	                {
	                    GetPlayerPos(playerid, TempInfo[playerid][dPosX], TempInfo[playerid][dPosY], TempInfo[playerid][dPosZ]);
	                    TempInfo[playerid][dInt] = GetPlayerInterior(playerid);
	                    TempInfo[playerid][dVW] = GetPlayerVirtualWorld(playerid);
	                    SetPVarInt(playerid, "cneg", 1);
	                    SendClientMessageEx(playerid, -1, "%s Has posicionado el Exterior, ahora ve al interior. Utiliza: /MeNegocio", InfoMsg);
	                }
	                case 1:
	                {
	                    if(GetPVarInt(playerid, "cneg") == 1)
	                    {
		                    GetPlayerPos(playerid, TempInfo[playerid][dPosX2], TempInfo[playerid][dPosY2], TempInfo[playerid][dPosZ2]);
							TempInfo[playerid][dInt2] = GetPlayerInterior(playerid);
		                    SetPVarInt(playerid, "cneg", 2);
	                    	SendClientMessageEx(playerid, -1, "%s Has posicionado el Interior, ahora selecciona 'Completar'. Utiliza: /MeNegocio", InfoMsg);
						}
						else
						{
							SendClientMessageEx(playerid, -1, "%s Por seguridad, primero posiciona el Exterior.", InfoMsg);
						}
	                }
	                case 2:
	                {
						new NuevoNegocio = TNegocios+1;
						if(NuevoNegocio <= MAX_NEGOCIOS)
						{
							new string[300], cadena[128];
							TNegocios++;
							Negocios[NuevoNegocio][nID] = NuevoNegocio;
							format(cadena, sizeof(cadena), "{00E100}¡En Venta!");
							Negocios[NuevoNegocio][nName] = cadena;
							format(cadena, sizeof(cadena), "Gobierno");
							Negocios[NuevoNegocio][nOwnerN] = cadena;
							Negocios[NuevoNegocio][nOwnerID] = 0;
							Negocios[NuevoNegocio][nType] = 0;
							Negocios[NuevoNegocio][nPEx] = TempInfo[playerid][dPosX];
							Negocios[NuevoNegocio][nPEy] = TempInfo[playerid][dPosY];
							Negocios[NuevoNegocio][nPEz] = TempInfo[playerid][dPosZ];
							Negocios[NuevoNegocio][nPIx] = TempInfo[playerid][dPosX2];
							Negocios[NuevoNegocio][nPIy] = TempInfo[playerid][dPosY2];
							Negocios[NuevoNegocio][nPIz] = TempInfo[playerid][dPosZ2];
							Negocios[NuevoNegocio][nIntE] = TempInfo[playerid][dInt];
							Negocios[NuevoNegocio][nIntI] = TempInfo[playerid][dInt2];
							Negocios[NuevoNegocio][nVwE] = TempInfo[playerid][dVW];
							Negocios[NuevoNegocio][nVwI] = 100+NuevoNegocio;
							Negocios[NuevoNegocio][nPrice] = 0;
							Negocios[NuevoNegocio][nMats] = 10;
							Negocios[NuevoNegocio][nMoney] = 0;
							Negocios[NuevoNegocio][nEntrada] = 0;
							//-------------------------------------
							new query[600];
							format(query, sizeof(query), "INSERT INTO `business` (`nID`, `nName`, `nOwnerN`, `nOwnerID`, `nType`, `nPEx`, `nPEy`, `nPEz`, `nPIx`, `nPIy`, `nPIz`, `nIntE`, `nIntI`, `nVwE`, `nVwI`, `nPrice`, `nMats`, `nMoney`, `nEntrada`) VALUES ('%d', '%s', '%s', '%d', '%d', '%f', '%f', '%f', '%f', '%f', '%f', '%d', '%d', '%d', '%d', '%d', '%d', '%d', '%d')", NuevoNegocio, Negocios[NuevoNegocio][nName],
							Negocios[NuevoNegocio][nOwnerN], Negocios[NuevoNegocio][nOwnerID], Negocios[NuevoNegocio][nType], Negocios[NuevoNegocio][nPEx],
							Negocios[NuevoNegocio][nPEy], Negocios[NuevoNegocio][nPEz], Negocios[NuevoNegocio][nPIx], Negocios[NuevoNegocio][nPIy], Negocios[NuevoNegocio][nPIz],
							Negocios[NuevoNegocio][nIntE], Negocios[NuevoNegocio][nIntI], Negocios[NuevoNegocio][nVwE], Negocios[NuevoNegocio][nVwI], Negocios[NuevoNegocio][nPrice],
							Negocios[NuevoNegocio][nMats], Negocios[NuevoNegocio][nMoney], Negocios[NuevoNegocio][nEntrada]);
							new Cache:result = mysql_query(g_MySQL, query);
							cache_delete(result);
							//--------------------------------------
							format(string, sizeof(string), "{FFFFFF}%s\n{B8D900}Dueño: {FFFFFF}%s\n{B8D900}Tipo: {FFFFFF}Nuevo\n{B8D900}Acceso: {FFFFFF}%d\n{B8D900}Dirección: {FFFFFF}GN-%d", Negocios[NuevoNegocio][nName], Negocios[NuevoNegocio][nOwnerN], Negocios[NuevoNegocio][nEntrada], Negocios[NuevoNegocio][nID]);
							LabelNE[NuevoNegocio] = CreateDynamic3DTextLabel(string, 0xF0CC00FF, Negocios[NuevoNegocio][nPEx], Negocios[NuevoNegocio][nPEy], Negocios[NuevoNegocio][nPEz]+0.75, 20.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, Negocios[NuevoNegocio][nVwE], Negocios[NuevoNegocio][nIntE], -1, 100.0);
							format(string, sizeof(string), "{FFFFFF}%s\n{B8D900}Dueño: {FFFFFF}%s\n{B8D900}Tipo: {FFFFFF}Nuevo\n{B8D900}Acceso: {FFFFFF}%s\n{B8D900}Dirección: {FFFFFF}GN-%d", Negocios[NuevoNegocio][nName], Negocios[NuevoNegocio][nOwnerN], Negocios[NuevoNegocio][nEntrada], Negocios[NuevoNegocio][nID]);
							LabelNI[NuevoNegocio] = CreateDynamic3DTextLabel(string, 0xF0CC00FF, Negocios[NuevoNegocio][nPIx], Negocios[NuevoNegocio][nPIy], Negocios[NuevoNegocio][nPIz]+0.75,20.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, Negocios[NuevoNegocio][nVwI], Negocios[NuevoNegocio][nIntI], -1, 100.0);

							Negocios[NuevoNegocio][nPickE] = CreateDynamicPickup(19135, 23, Negocios[NuevoNegocio][nPEx], Negocios[NuevoNegocio][nPEy], Negocios[NuevoNegocio][nPEz], Negocios[NuevoNegocio][nVwE], Negocios[NuevoNegocio][nIntE], -1, 150.0 );
							Negocios[NuevoNegocio][nPickI] = CreateDynamicPickup(19135, 23, Negocios[NuevoNegocio][nPIx], Negocios[NuevoNegocio][nPIy], Negocios[NuevoNegocio][nPIz], Negocios[NuevoNegocio][nVwI], Negocios[NuevoNegocio][nIntI], -1, 150.0 );
							//--------------------------------------
							SendClientMessageEx(playerid, -1, "%s Negocio: %d Creado.", InfoMsg, NuevoNegocio);
							SetPlayerPos(playerid, Negocios[NuevoNegocio][nPEx], Negocios[NuevoNegocio][nPEy], Negocios[NuevoNegocio][nPEz]);
							SetPlayerInterior(playerid, Negocios[NuevoNegocio][nIntE]);
							SetPlayerVirtualWorld(playerid, Negocios[NuevoNegocio][nVwE]);
							PlayersData[playerid][pInterior] = Negocios[NuevoNegocio][nIntE];
							PlayersData[playerid][pVW] = Negocios[NuevoNegocio][nVwE];

						}
						else
						{
							SendClientMessageEx(playerid, -1, "%s Limite de Negocios alzanzados. Contácta un Administrador.", InfoMsg);
						}
	                }
	            }
	        }
	        return 1;
	    }
	    //----------------------
	    case MENU_NEGOCIO_TIPO:
	    {
	        if(response)
	        {
				if(strval(inputtext) < 0 || strval(inputtext) > MAX_NEGOCIOS)
				{
				    SendClientMessageEx(playerid, -1, "%s Introduciste una ID inválida de Negocio.", InfoMsg);
				}
				else
				{
				    EditandoNegocio[playerid] = strval(inputtext);
				    ShowPlayerDialog(playerid, MENU_NEGOCIO_TIPO2, DIALOG_STYLE_INPUT, "{0080FF}Configuración {FFFFFF}» {FF4646}Negocio.", "Escribe el Tipo Negocio.\n1 - 24/7\n2 - Ropa\n3 - Comida\n4 - Electrónica\n5 - Armeria", "Aceptar", "Cancelar");
				}
	        }
	        return 1;
		}
	    //----------------------
	    case MENU_NEGOCIO_TIPO2:
	    {
	        if(response)
	        {
	            if(strval(inputtext) < 0 || strval(inputtext) > 5)
	            {
	                SendClientMessageEx(playerid, -1, "%s Introducite una ID inválida.", InfoMsg);
	            }
	            else
	            {
	                new nexist;
					for(new i = 0; i <= TNegocios; i++)
					{
					    if(EditandoNegocio[playerid] == i)
					    {
							nexist = 1;
						}
					}
					if(nexist == 1)
					{
					    new tipo[20], string[300];
						Negocios[EditandoNegocio[playerid]][nType] = strval(inputtext);
						switch(Negocios[EditandoNegocio[playerid]][nType])
						{
							case 1:{    tipo="24/7";}   case 2:{    tipo="Ropa";}   case 3:{    tipo="Comida";}   case 4:{    tipo="Electrónica";}   case 5:{    tipo="Armeria";}
						}
						if(Negocios[EditandoNegocio[playerid]][nOwnerID] == 0)
						{
						    format(string, sizeof(string), "{00E100}¡En Venta!\n{B8D900}Precio: {FFFFFF}$%d\n{B8D900}Tipo: {FFFFFF}%s\n{B8D900}Acceso: {FFFFFF}%d\n{B8D900}Dirección: {FFFFFF}GN-%d", Negocios[EditandoNegocio[playerid]][nPrice], tipo, Negocios[EditandoNegocio[playerid]][nEntrada], Negocios[EditandoNegocio[playerid]][nID]);
							UpdateDynamic3DTextLabelText(LabelNE[EditandoNegocio[playerid]], 0xF0CC00FF, string);
							UpdateDynamic3DTextLabelText(LabelNI[EditandoNegocio[playerid]], 0xF0CC00FF, string);
						}
						else
						{
						    format(string, sizeof(string), "{FFFFFF}%s\n{B8D900}Dueño: {FFFFFF}%s\n{B8D900}Tipo: {FFFFFF}%s\n{B8D900}Acceso: {FFFFFF}%d\n{B8D900}Dirección: {FFFFFF}GN-%d", Negocios[EditandoNegocio[playerid]][nName], Negocios[EditandoNegocio[playerid]][nOwnerN], tipo, Negocios[EditandoNegocio[playerid]][nEntrada], Negocios[EditandoNegocio[playerid]][nID]);
							UpdateDynamic3DTextLabelText(LabelNE[EditandoNegocio[playerid]], 0xF0CC00FF, string);
							UpdateDynamic3DTextLabelText(LabelNI[EditandoNegocio[playerid]], 0xF0CC00FF, string);
						}
					}
					else
					{
					    SendClientMessageEx(playerid, -1, "%s ID de Negocio no existente.", InfoMsg);
					}
				}
	        }
	        return 1;
	    }
	    //----------------------
	    case MENU_NEGOCIO_PRECIO:
	    {
	        if(response)
	        {
				if(strval(inputtext) < 0 || strval(inputtext) > MAX_NEGOCIOS)
				{
				    SendClientMessageEx(playerid, -1, "%s Introduciste una ID inválida de Negocio.", InfoMsg);
				}
				else
				{
				    EditandoNegocio[playerid] = strval(inputtext);
				    ShowPlayerDialog(playerid, MENU_NEGOCIO_PRECIO2, DIALOG_STYLE_INPUT, "{0080FF}Configuración {FFFFFF}» {FF4646}Negocio.", "Escribe el precio que tendrá este Negocio.\nNo utilices puntos ni comas.", "Aceptar", "Cancelar");
				}
	        }
	        return 1;
		}
	    //----------------------
	    case MENU_NEGOCIO_PRECIO2:
	    {
	        if(response)
	        {
	            if(strval(inputtext) < 0)
	            {
	                SendClientMessageEx(playerid, -1, "%s El precio debe ser mayor o igual a 0.", InfoMsg);
	            }
	            else
	            {
	                new nexist;
					for(new i = 0; i <= TNegocios; i++)
					{
					    if(EditandoNegocio[playerid] == i)
					    {
							nexist = 1;
						}
					}
					if(nexist == 1)
					{
					    new tipo[20], string[300];
						Negocios[EditandoNegocio[playerid]][nPrice] = strval(inputtext);
						switch(Negocios[EditandoNegocio[playerid]][nType])
						{
							case 1:{    tipo="24/7";}   case 2:{    tipo="Ropa";}   case 3:{    tipo="Comida";}   case 4:{    tipo="Electrónica";}   case 5:{    tipo="Armeria";}
						}
						if(Negocios[EditandoNegocio[playerid]][nOwnerID] == 0)
						{
						    format(string, sizeof(string), "{00E100}¡En Venta!\n{B8D900}Precio: {FFFFFF}$%d\n{B8D900}Tipo: {FFFFFF}%s\n{B8D900}Acceso: {FFFFFF}%d\n{B8D900}Dirección: {FFFFFF}GN-%d", Negocios[EditandoNegocio[playerid]][nPrice], tipo, Negocios[EditandoNegocio[playerid]][nEntrada], Negocios[EditandoNegocio[playerid]][nID]);
							UpdateDynamic3DTextLabelText(LabelNE[EditandoNegocio[playerid]], 0xF0CC00FF, string);
							UpdateDynamic3DTextLabelText(LabelNI[EditandoNegocio[playerid]], 0xF0CC00FF, string);
						}
						else
						{
						    format(string, sizeof(string), "{FFFFFF}%s\n{B8D900}Dueño: {FFFFFF}%s\n{B8D900}Tipo: {FFFFFF}%s\n{B8D900}Acceso: {FFFFFF}%d\n{B8D900}Dirección: {FFFFFF}GN-%d", Negocios[EditandoNegocio[playerid]][nName], Negocios[EditandoNegocio[playerid]][nOwnerN], tipo, Negocios[EditandoNegocio[playerid]][nEntrada], Negocios[EditandoNegocio[playerid]][nID]);
							UpdateDynamic3DTextLabelText(LabelNE[EditandoNegocio[playerid]], 0xF0CC00FF, string);
							UpdateDynamic3DTextLabelText(LabelNI[EditandoNegocio[playerid]], 0xF0CC00FF, string);
						}
					}
					else
					{
					    SendClientMessageEx(playerid, -1, "%s ID de Negocio no existente.", InfoMsg);
					}
				}
	        }
	        return 1;
	    }
	    //-----------------------
	    case MENU_NEGOCIO_TP:
	    {
	        if(response)
	        {
	            if(strval(inputtext) < 0)
	            {
	                SendClientMessageEx(playerid, -1, "%s El ID debe ser mayor o igual a 0.", InfoMsg);
	            }
	            else
	            {
					new nexist;
					for(new i = 1; i <= TNegocios; i++)
					{
					    if(strval(inputtext) == i)
					    {
							nexist = 1;
						}
					}
					if(nexist == 1)
					{
					    SetPlayerPos(playerid, Negocios[strval(inputtext)][nPEx], Negocios[strval(inputtext)][nPEy], Negocios[strval(inputtext)][nPEz]);
					}
					else
					{
					    SendClientMessageEx(playerid, -1, "%s Ese negocio no existe.", InfoMsg);
					}
	            }
	        }
		}
	    //----------
		case DIALOG_COMIDA:
        {
            if(response)
            {
                new Float:h;
				GetPlayerHealth(playerid, h);
				switch(listitem)
	            {
					case 0: //Soda
	                {
						if(PlayersData[playerid][Money] >= 5)
						{
							if(Negocios[EnNegocio[playerid]][nMats] >= 1)
							{
                                Negocios[EnNegocio[playerid]][nMats] -= 1;
                                PlayersData[playerid][Money] -= 5;
                                GivePlayerMoney(playerid, -5);
                                Negocios[EnNegocio[playerid]][nMoney] += 5;
								Notificacion(playerid, "Compraste Soda por $5 dolares");
								SetPlayerSpecialAction(playerid, SPECIAL_ACTION_DRINK_SPRUNK);
								PlayerPlaySound(playerid, 1054, 0.0, 0.0, 10.0);
								PlayersData[playerid][pDrink] += 40.0;
								RoleAction(playerid, "compra una soda.");
							}
							else
							{
							    SendClientMessageEx(playerid, -1, "%s Este negocio no tiene suficientes suministros.", InfoMsg);
							}
						}
						else
						{
						    SendClientMessageEx(playerid, -1, "%s No tienes suficiente dinero para comprar esto.", InfoMsg);
							PlayerPlaySound(playerid, 1055, 0.0, 0.0, 10.0);
						}
					}
					case 1: //Hamburguesa
	                {
						if(PlayersData[playerid][Money] >= 10)
						{
							if(Negocios[EnNegocio[playerid]][nMats] >= 2)
							{
                                Negocios[EnNegocio[playerid]][nMats] -=2;
                                PlayersData[playerid][Money] -= 10;
                                GivePlayerMoney(playerid, -10);
                                Negocios[EnNegocio[playerid]][nMoney] += 10;
								Notificacion(playerid, "Compraste Hamburguesa por $10 dolares");
								ApplyAnimation(playerid, "FOOD", "EAT_Burger",4.1,0,1,1,0,0);
								PlayerPlaySound(playerid, 1054, 0.0, 0.0, 10.0);
								PlayersData[playerid][pFood] += 40.0;
								RoleAction(playerid, "compra una Hamburguesa.");
							}
							else
							{
							    SendClientMessageEx(playerid, -1, "%s Este negocio no tiene suficientes suministros.", InfoMsg);
							}
						}
						else
						{
						    SendClientMessageEx(playerid, -1, "%s No tienes suficiente dinero para comprar esto.", InfoMsg);
							PlayerPlaySound(playerid, 1055, 0.0, 0.0, 10.0);
						}
					}
					case 2: //Pizza
	                {
						if(PlayersData[playerid][Money] >= 12)
						{
							if(Negocios[EnNegocio[playerid]][nMats] >= 3)
							{
                                Negocios[EnNegocio[playerid]][nMats] -= 3;
                                PlayersData[playerid][Money] -= 12;
                                GivePlayerMoney(playerid, -12);
                                Negocios[EnNegocio[playerid]][nMoney] += 12;
								Notificacion(playerid, "Compraste Pizza por $12 dolares");
								ApplyAnimation(playerid, "FOOD", "EAT_Pizza",4.1,0,1,1,0,0);
								PlayerPlaySound(playerid, 1054, 0.0, 0.0, 10.0);
								PlayersData[playerid][pFood] += 34.0;
								RoleAction(playerid, "compra una Pizza.");
							}
							else
							{
							    SendClientMessageEx(playerid, -1, "%s Este negocio no tiene suficientes suministros.", InfoMsg);
							}
						}
						else
						{
						    SendClientMessageEx(playerid, -1, "%s No tienes suficiente dinero para comprar esto.", InfoMsg);
							PlayerPlaySound(playerid, 1055, 0.0, 0.0, 10.0);
						}
					}
					case 3: //HotDog
	                {
						if(PlayersData[playerid][Money] >= 7)
						{
							if(Negocios[EnNegocio[playerid]][nMats] >= 2)
							{
                                Negocios[EnNegocio[playerid]][nMats] -= 2;
                                PlayersData[playerid][Money] -= 7;
                                GivePlayerMoney(playerid, -7);
                                Negocios[EnNegocio[playerid]][nMoney] += 7;
								Notificacion(playerid, "Compraste HotDog por $7 dolares");
								ApplyAnimation(playerid, "FOOD", "EAT_Burger",4.1,0,1,1,0,0);
								PlayerPlaySound(playerid, 1054, 0.0, 0.0, 10.0);
								PlayersData[playerid][pFood] += 24.0;
								RoleAction(playerid, "compra un Hotdog.");
							}
							else
							{
							    SendClientMessageEx(playerid, -1, "%s Este negocio no tiene suficientes suministros.", InfoMsg);
							}
						}
						else
						{
						    SendClientMessageEx(playerid, -1, "%s No tienes suficiente dinero para comprar esto.", InfoMsg);
							PlayerPlaySound(playerid, 1055, 0.0, 0.0, 10.0);
						}
					}
					case 4: //Ensalada
	                {
						if(PlayersData[playerid][Money] >= 15)
						{
							if(Negocios[EnNegocio[playerid]][nMats] >= 4)
							{
                                Negocios[EnNegocio[playerid]][nMats] -= 4;
                                PlayersData[playerid][Money] -= 15;
                                GivePlayerMoney(playerid, -15);
                                Negocios[EnNegocio[playerid]][nMoney] += 15;
								Notificacion(playerid, "Compraste Ensalada por $15 dolares");
								ApplyAnimation(playerid, "FOOD", "EAT_Chicken",4.1,0,1,1,0,0);
								PlayerPlaySound(playerid, 1054, 0.0, 0.0, 10.0);
								PlayersData[playerid][pFood] += 50.0;
								RoleAction(playerid, "compra una Ensalada.");
							}
							else
							{
							    SendClientMessageEx(playerid, -1, "%s Este negocio no tiene suficientes suministros.", InfoMsg);
							}
						}
						else
						{
						    SendClientMessageEx(playerid, -1, "%s No tienes suficiente dinero para comprar esto.", InfoMsg);
							PlayerPlaySound(playerid, 1055, 0.0, 0.0, 10.0);
						}
					}
					case 5: //Pollo Frito
	                {
						if(PlayersData[playerid][Money] >= 20)
						{
							if(Negocios[EnNegocio[playerid]][nMats] >= 5)
							{
                                Negocios[EnNegocio[playerid]][nMats] -= 5;
                                PlayersData[playerid][Money] -= 20;
                                GivePlayerMoney(playerid, -20);
                                Negocios[EnNegocio[playerid]][nMoney] += 20;
								Notificacion(playerid, "Compraste Pollo por $20 dolares");
								ApplyAnimation(playerid, "FOOD", "EAT_Chicken",4.1,0,1,1,0,0);
								PlayerPlaySound(playerid, 1054, 0.0, 0.0, 10.0);
								PlayersData[playerid][pFood] += 60.0;
								RoleAction(playerid, "compra un Pollo Frito.");
							}
							else
							{
							    SendClientMessageEx(playerid, -1, "%s Este negocio no tiene suficientes suministros.", InfoMsg);
							}
						}
						else
						{
						    SendClientMessageEx(playerid, -1, "%s No tienes suficiente dinero para comprar esto.", InfoMsg);
							PlayerPlaySound(playerid, 1055, 0.0, 0.0, 10.0);
						}
					}
					case 6: //Donas
	                {
						if(PlayersData[playerid][Money] >= 5)
						{
							if(Negocios[EnNegocio[playerid]][nMats] >= 1)
							{
                                Negocios[EnNegocio[playerid]][nMats] -= 1;
                                PlayersData[playerid][Money] -= 5;
                                GivePlayerMoney(playerid, -5);
                                Negocios[EnNegocio[playerid]][nMoney] += 5;
								Notificacion(playerid, "Compraste Donut por $5 dolares");
								ApplyAnimation(playerid, "FOOD", "EAT_Chicken",4.1,0,1,1,0,0);
								PlayerPlaySound(playerid, 1054, 0.0, 0.0, 10.0);
								PlayersData[playerid][pFood] += 10.0;
								RoleAction(playerid, "compra un Donut.");
							}
							else
							{
							    SendClientMessageEx(playerid, -1, "%s Este negocio no tiene suficientes suministros.", InfoMsg);
							}
						}
						else
						{
						    SendClientMessageEx(playerid, -1, "%s No tienes suficiente dinero para comprar esto.", InfoMsg);
							PlayerPlaySound(playerid, 1055, 0.0, 0.0, 10.0);
						}
					}
				}
			}
		}
		//-------------------------
		case DIALOG_ELECTRONICA:
		{
			if(response)
			{
			    switch(listitem)
			    {
			        case 0: //Movil
			        {
						SendClientMessageEx(playerid, -1, "{NO_SIGNAL}");
			        }
			        case 1: //Cámara
			        {
						if(Negocios[EnNegocio[playerid]][nMats] >= 30)
						{
							if(PlayersData[playerid][Money] >= 150)
							{
							    GivePlayerWeapon(playerid, 43, 50);
							    PlayersData[playerid][Money] -= 150;
							    GivePlayerMoney(playerid, -150);
							    Negocios[EnNegocio[playerid]][nMoney] += 150;
							    Negocios[EnNegocio[playerid]][nMats] -= 30;
								Notificacion(playerid, "Compraste una Camara por $150 dolares.");
							}
							else
							{
							    SendClientMessageEx(playerid, -1, "%s No tienes suficiente dinero.", InfoMsg);
							}
						}
						else
						{
						    SendClientMessageEx(playerid, -1, "%s Este Negocio no tiene suficientes Cámaras en Stock.", InfoMsg);
						}
			        }
			        case 2: //Saldo
			        {
						SendClientMessageEx(playerid, -1, "{NO_SIGNAL}");
			        }
			    }
			}
		}
	    //----------
	    case DIALOG_MAPEAR:
		{
			if(response)
			{
				if(strfind(inputtext, "1", true) == -1 && strfind(inputtext, "2", true) == -1 && strfind(inputtext, "3", true) == -1 && strfind(inputtext, "4", true) == -1 && strfind(inputtext, "5", true) == -1
				&& strfind(inputtext, "6", true) == -1 && strfind(inputtext, "7", true) == -1 && strfind(inputtext, "8", true) == -1 && strfind(inputtext, "9", true) == -1 && strfind(inputtext, "0", true) == -1)
				{
					SendClientMessageEx(playerid, -1, "%s Ingresaste una ID inválida.", InfoMsg);
				}
				else
				{
					CrearObjeto(playerid, strval(inputtext));
				}
			}
		}
	    //----------
	    //----------
	    //----------
	}
	return 1;
}

public OnPlayerEditDynamicObject(playerid, objectid, response, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz)
{
	switch(Editando[playerid])
	{
		case 1:	//OBJETOS
		{
			new query[400];
			if(response == EDIT_RESPONSE_FINAL)
			{
				MoveDynamicObject(objectid, x, y, z, 1.0, rx, ry, rz);
				Objetos[EditObj[playerid]][xobjeto] = x;
				Objetos[EditObj[playerid]][yobjeto] = y;
				Objetos[EditObj[playerid]][zobjeto] = z;
				Objetos[EditObj[playerid]][rotx] = rx;
				Objetos[EditObj[playerid]][roty] = ry;
				Objetos[EditObj[playerid]][rotz] = rz;
				//-------------------------
				mysql_format(g_MySQL, query, sizeof(query), "UPDATE `objects` SET `xobjeto`='%f', `yobjeto`='%f', `zobjeto`='%f', `rotx`='%f', `roty`='%f', `rotz`='%f' WHERE `ID_DATABASE`='%d'",
				x, y, z, rx, ry, rz, Objetos[EditObj[playerid]][IDDB]);
				new Cache:result=mysql_query(g_MySQL, query);
				cache_delete(result);
				SendClientMessageEx(playerid, -1, "%s Actualizaste la posición del Objeto ID: %d Modelo: %d.", MapMsg, EditObj[playerid], Objetos[EditObj[playerid]][idobjeto]);
                EditObj[playerid] = 0;
			}
			if(response == EDIT_RESPONSE_CANCEL)
			{
				SetDynamicObjectPos(objectid, Objetos[EditObj[playerid]][xobjeto], Objetos[EditObj[playerid]][yobjeto], Objetos[EditObj[playerid]][zobjeto]);
				SetDynamicObjectRot(objectid, Objetos[EditObj[playerid]][rotx], Objetos[EditObj[playerid]][roty], Objetos[EditObj[playerid]][rotz]);
				SendClientMessageEx(playerid, -1, "%s Cancelaste la edición del Objeto ID: %d Modelo: %d.", MapMsg, EditObj[playerid], Objetos[EditObj[playerid]][idobjeto]);
                EditObj[playerid] = 0;
			}
			if(response == EDIT_RESPONSE_UPDATE)
			{
				MoveDynamicObject(objectid, x, y, z, 10.0, rx, ry, rz);
			}
		}
		case 2: //CARTELES
		{
			SendClientMessageEx(playerid, -1, "%s Ocurrió un error inesperado. Contacta un Administrador", ERROR_ADMIN);
		}
		case 3:
		{
            new query[400];
			if(response == EDIT_RESPONSE_FINAL)
			{
				MoveDynamicObject(objectid, Objetos[EditObj[playerid]][xobjeto], Objetos[EditObj[playerid]][yobjeto], Objetos[EditObj[playerid]][zobjeto], 1.0, Objetos[EditObj[playerid]][rotx], Objetos[EditObj[playerid]][roty], Objetos[EditObj[playerid]][rotz]);
				Objetos[EditObj[playerid]][oPosX] = x;
				Objetos[EditObj[playerid]][oPosY] = y;
				Objetos[EditObj[playerid]][oPosZ] = z;
				Objetos[EditObj[playerid]][oRotX] = rx;
				Objetos[EditObj[playerid]][oRotY] = ry;
				Objetos[EditObj[playerid]][oRotZ] = rz;
				Objetos[EditObj[playerid]][Move] = 1;
				Objetos[EditObj[playerid]][Estado] = 1;
				//-------------------------
				mysql_format(g_MySQL, query, sizeof(query), "UPDATE objects SET `oPosX`= '%f', `oPosY`= '%f', `oPosZ`= '%f', `oRotX`= '%f', `oRotY`= '%f', `oRotZ`= '%f' WHERE `ID_DATABASE`='%d'",
				x, y, z, rx, ry, rz, Objetos[EditObj[playerid]][IDDB]);
				new Cache:result=mysql_query(g_MySQL, query);
				cache_delete(result);
				SendClientMessageEx(playerid, -1, "%s Actualizaste el Recorrido del Objeto ID: %d Modelo: %d.", MapMsg, EditObj[playerid], Objetos[EditObj[playerid]][idobjeto]);
                EditObj[playerid] = 0;
			}
			if(response == EDIT_RESPONSE_CANCEL)
			{
				SetDynamicObjectPos(objectid, Objetos[EditObj[playerid]][xobjeto], Objetos[EditObj[playerid]][yobjeto], Objetos[EditObj[playerid]][zobjeto]);
				SetDynamicObjectRot(objectid, Objetos[EditObj[playerid]][rotx], Objetos[EditObj[playerid]][roty], Objetos[EditObj[playerid]][rotz]);
				SendClientMessageEx(playerid, -1, "%s Cancelaste la edición del recorrido del Objeto ID: %d Modelo: %d.", MapMsg, EditObj[playerid], Objetos[EditObj[playerid]][idobjeto]);
                EditObj[playerid] = 0;
			}
		}
	}
	return 1;
}

public OnPlayerModelSelection(playerid, response, listid, modelid)
{
	if(listid == SkinList)
	{
		if(response)
		{
		    if(PlayersData[playerid][Money] >= 80)
		    {
		        if(Negocios[EnNegocio[playerid]][nMats] >= 12)
		        {
		    		PlayersData[playerid][Money] -= 80;
		    		GivePlayerMoney(playerid, -80);
		    		Negocios[EnNegocio[playerid]][nMoney] += 80;
		    		Negocios[EnNegocio[playerid]][nMats] -= 12;
		    		SetPlayerSkin(playerid, modelid);
		    		PlayersData[playerid][Skin] = modelid;
				}
				else
				{
				    SendClientMessageEx(playerid, -1, "%s Este negocio no tiene suficientes prendas para vender.", InfoMsg);
				}
			}
			else
			{
			    SendClientMessageEx(playerid, -1, "%s No tienes $80 para comprarte Ropa!", InfoMsg);
			}
		}
	}
	return 1;
}

public OnPlayerClickPlayer(playerid, clickedplayerid, source)
{
	if(PlayersData[playerid][Admin] >= 3)
	{
		if(Logged[clickedplayerid] == true)
		{
			new Float:pX, Float:pY, Float:pZ;
			GetPlayerPos(clickedplayerid, pX, pY, pZ);
			SetPlayerPos(playerid, pX+2, pY, pZ);
			SetPlayerInterior(playerid, GetPlayerInterior(clickedplayerid));
			SetPlayerVirtualWorld(playerid, GetPlayerVirtualWorld(clickedplayerid));
			PlayersData[playerid][pInterior] = GetPlayerInterior(clickedplayerid);
			PlayersData[playerid][pVW] = GetPlayerVirtualWorld(clickedplayerid);
			SendClientMessageEx(playerid, -1, "%s Te teletransportaste a %s [ID: %d]", InfoMsg, RemoveUnderScore(clickedplayerid), clickedplayerid);
		}
		else
		{
			SendClientMessageEx(playerid, -1, "%s El usuario no se encuentra conectado o no ha iniciado sesión.", ERROR_ADMIN);
		}
	}
	else
	{
        SendClientMessageEx(playerid, -1, NO_ADMIN_PERMISSION);
    }
	return 1;
}

public OnPlayerClickMap(playerid, Float:fX, Float:fY, Float:fZ)
{
    if(PlayersData[playerid][Admin] >= 5)
    {
		SetPlayerPos(playerid, fX, fY, fZ);
		SendClientMessageEx(playerid, -1, "%s Te has teletransportado a una posición del Mapa.", InfoMsg);
    }
    else
    {
        SendClientMessageEx(playerid, -1, NO_ADMIN_PERMISSION);
	}
    return 1;
}

public OnPlayerClickTextDraw(playerid, Text:clickedid)
{
	//===============       [   ESC Button  ]       ===============
	if(clickedid == Text:INVALID_TEXT_DRAW && TempInfo[playerid][IsDeath] == true) //Esc on Death
	{
		ShowDeathTextDraw(playerid);
	}
	if(clickedid == Text:INVALID_TEXT_DRAW && TempInfo[playerid][InATM] == true) //Esc on ATM
	{
	    HideBankUI(playerid);
	}
	
	//===============       [   Others	]       ===============
	if(clickedid == DeadTD_Button)
    {
        PutPlayerToDeath(playerid);
    }
	if(clickedid == bank_close)
	{
	    HideBankUI(playerid);
	}

	//===============       [   Bank SySTEM	]       ===============

	if(TempInfo[playerid][InATM] == true)
	{
	    if(clickedid == bank_retirar)
		{
			SetPVarString(playerid, "InputType", "Retirar");
		    new str[91+1];
			format(str, sizeof(str), "{FFF829}Ingrese la cantidad a desea {FF4F4F}retirar{FFF829}:\n\nBalance: {40FF19}$%d", PlayersData[playerid][BankAccount]);
			ShowPlayerDialog(playerid, DIALOG_GLOBAL_INPUT, DIALOG_STYLE_INPUT, "{FF1919}M{FFFFFF}aze {FF1919}B{FFFFFF}ank {87FF87}» {005EFF}Retirar", str, "{00D200}»", "{FF3333}X");
	        CancelSelectTextDraw(playerid);
	        HideBankUI(playerid);
		}
		else if(clickedid == bank_depositar)
		{
			SetPVarString(playerid, "InputType", "Depositar");
			new str[62+1];
			format(str, sizeof(str), "{FFF829}Ingrese la cantidad a desea {67FF26}depositar{FFF829}:");
			ShowPlayerDialog(playerid, DIALOG_GLOBAL_INPUT, DIALOG_STYLE_INPUT, "{FF1919}M{FFFFFF}aze {FF1919}B{FFFFFF}ank {87FF87}» {005EFF}Depositar", str, "{00D200}»", "{FF3333}X");
	        CancelSelectTextDraw(playerid);
		}
		else if(clickedid == bank_transferir)
		{
		    SendClientMessageEx(playerid, -1, "{C0C0C0}NO SIGNAL");
		}
		else if(clickedid == bank_consultar)
		{
			new str[137+1];
			format(str, sizeof(str), "\n\t{C0C0C0}...: {F8FF2E}Consulta de Saldo {C0C0C0}:...\t\n\n\
			{FF3D3D}Cuenta:\n{FFFFFF}#%d\n\n\
			{FF3D3D}Saldo:\n{FFFFFF}$%d\n\n", PlayersData[playerid][ID], PlayersData[playerid][BankAccount]);
			ShowPlayerDialog(playerid, 404, DIALOG_STYLE_MSGBOX, "{FF1919}M{FFFFFF}aze {FF1919}B{FFFFFF}ank {87FF87}» {005EFF}Consultar", str, "{00D200}Aceptar", "");
	        CancelSelectTextDraw(playerid);
	        HideBankUI(playerid);
		}
	}
	return 1;
}
