//»»»»»»»»»» RESOURCES ««««««««««
#include <core/player/data>
#include <core/server/database>
#include <gui/hud/textdraw>

//»»»»»»»»»» VARIABLES ««««««««««
new TVehiculos;
new TimerLlenado[MAX_PLAYERS];
new bool:LlenarGas[MAX_PLAYERS]; 

enum vInfo {
	IDDB,
	Owner,
	Model,
	Plate,
	vType, //1 - Personal, 2 - Faccion, 3 - Job, 4 - Público
	Key,
	Alarm,
	Luces,	//Luces vehículo
	Capo,   //Capo vehículo
	Engine,
	Float:Fuel,
	Float:Aceite,
	Float:Status,
	Float:vX,
	Float:vY,
	Float:vZ,
	Float:vAngle,
	Float:vPx,
	Float:vPy,
	Float:vPz,
	Color1,
	Color2,
	Faccion,
	FKey,
	Factura,
	Estereo,
	VehID,
	tEstereo
};
new VehData[MAX_VEHICLES][vInfo];

//»»»»»»»»»» STOCKS ««««««««««
stock MedidoresVelocimetro(playerid, vehicleid)
{
	if(IsPlayerConnected(playerid))
	{
	    if(vehicleid != INVALID_VEHICLE_ID)
	    {
	        if(IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
	        {
				SetPlayerProgressBarValue(playerid, Vel_GasoBar[playerid], VehData[vehicleid][Fuel]);
				SetPlayerProgressBarValue(playerid, Vel_AceiteBar[playerid], VehData[vehicleid][Aceite]);
	        }
	    }
	}
	return 1;
}

stock SetEstereoForPlayer(playerid, stationid)
{
	switch(stationid)
	{
	    case 0:	{StopAudioStreamForPlayer(playerid);} //Apagada
	    case 1: {PlayAudioStreamForPlayer(playerid, "http://us4.internet-radio.com:8258/listen.pls");}//Rock
	    case 2: {PlayAudioStreamForPlayer(playerid, "http://uk6.internet-radio.com:8124/listen.pls");}//Pop
	    case 3: {PlayAudioStreamForPlayer(playerid, "http://192.99.4.210:3844/listen.pls");}//Cumbia
	    case 4: {PlayAudioStreamForPlayer(playerid, "http://192.95.18.39:5892/listen.pls");}//Reggaeton
	    case 5: {PlayAudioStreamForPlayer(playerid, "http://uk1.internet-radio.com:8294/live.m3u");}//Metal
	    case 6: {PlayAudioStreamForPlayer(playerid, "http://192.96.205.59:7610/listen.pls");}//Jazz
	    case 7: {PlayAudioStreamForPlayer(playerid, "http://mp3stream2.apasf.apa.at:8000/listen.pls");}//80's
	    case 8: {PlayAudioStreamForPlayer(playerid, "http://carsija.topstream.net:19406/listen.pls");}//Country
	    case 9: {PlayAudioStreamForPlayer(playerid, "http://162.144.106.6:9111/listen.pls");}//HipHop
	    case 10: {PlayAudioStreamForPlayer(playerid, "http://uk6.internet-radio.com:8124/listen.pls");}//Latin
	    case 11:
	    {
	        new url[180];
	        GetPVarString(playerid, "EstereoURL", url, sizeof(url));
	        PlayAudioStreamForPlayer(playerid, url);
	        DeletePVar(playerid, "EstereoURL");
	    }
	}
	return 1;
}

stock Float:GetDistanceBetweenPoints(Float:dbpX, Float:dbpY, Float:dbpZ, Float:PointX, Float:PointY, Float:PointZ)
{
	new Float:Distance;
	Distance = floatabs(floatsub(dbpX, PointX)) + floatabs(floatsub(dbpY, PointY)) + floatabs(floatsub(dbpZ, PointZ));
	return Distance;
}

stock GetNearestVehicle(playerid, Float:Distance = 1000.0)
{
	Distance = floatabs(Distance);
	if(Distance == 0.0) Distance = 1000.0;
	new Float:nvX[2], Float:nvY[2], Float:nvZ[2];
	new Float:NearestPos = Distance;
	new NearestVehicle = INVALID_VEHICLE_ID;
	GetPlayerPos(playerid, nvX[0], nvY[0], nvZ[0]);
	for(new i; i < MAX_VEHICLES; i++)
	{
		if(!IsVehicleStreamedIn(i, playerid) || i == GetPlayerVehicleID(playerid)) continue;
		GetVehiclePos(i, nvX[1], nvY[1], nvZ[1]);
		if(NearestPos > GetDistanceBetweenPoints(nvX[0], nvY[0], nvZ[0], nvX[1], nvY[1], nvZ[1])) NearestPos = GetDistanceBetweenPoints(nvX[0], nvY[0], nvZ[0], nvX[1], nvY[1], nvZ[1]), NearestVehicle = i;
	}
	if(NearestPos < Distance) return NearestVehicle;
	return INVALID_VEHICLE_ID;
}
//»»»»»»»»»» FUNCIONES ««««««««««

forward LoadVehiculos();
forward SaveCars();
forward EncenderMotor(playerid, vehicleid);
forward ApagarMotor(playerid, vehicleid);
forward LlenarGasolina(vehicleid, playerid);
forward CreateVehicleEx(playerid, modelid, type, ownerid);

public LoadVehiculos()
{
    /*----------------===== [ VARIABLES ] =====-----------------*/
	new query[50], matricula[9];
	/*-----------------===== [ CONSULTA ] =====-----------------*/
	mysql_format(g_MySQL, query, sizeof(query), "SELECT * FROM vehicles");
	new Cache:result=mysql_query(g_MySQL, query);
	if(cache_num_rows() > 0)
	{
	    TVehiculos++;
	    for(new i=0; i < cache_num_rows(); i++)
	    {
			cache_get_value_name_int(i, "IDDB", VehData[TVehiculos][IDDB]);
			cache_get_value_name_int(i, "Owner", VehData[TVehiculos][Owner]);
			cache_get_value_name_int(i, "Model", VehData[TVehiculos][Model]);
			cache_get_value_name_int(i, "Plate", VehData[TVehiculos][Plate]);
			cache_get_value_name_int(i, "Type", VehData[TVehiculos][vType]);
			cache_get_value_name_int(i, "vKey", VehData[TVehiculos][Key]);
			cache_get_value_name_int(i, "Alarm", VehData[TVehiculos][Alarm]);
			cache_get_value_name_int(i, "Engine", VehData[TVehiculos][Engine]);
			cache_get_value_name_float(i, "Fuel", VehData[TVehiculos][Fuel]);
			cache_get_value_name_float(i, "Aceite", VehData[TVehiculos][Aceite]);
			cache_get_value_name_float(i, "Status", VehData[TVehiculos][Status]);
			cache_get_value_name_float(i, "vX", VehData[TVehiculos][vX]);
			cache_get_value_name_float(i, "vY", VehData[TVehiculos][vY]);
			cache_get_value_name_float(i, "vZ", VehData[TVehiculos][vZ]);
			cache_get_value_name_float(i, "vAngle", VehData[TVehiculos][vAngle]);
			cache_get_value_name_int(i, "Color1", VehData[TVehiculos][Color1]);
			cache_get_value_name_int(i, "Color2", VehData[TVehiculos][Color2]);
			cache_get_value_name_int(i, "Faccion", VehData[TVehiculos][Faccion]);
			cache_get_value_name_int(i, "FKey", VehData[TVehiculos][FKey]);
			cache_get_value_name_int(i, "Factura", VehData[TVehiculos][Factura]);
			cache_get_value_name_float(i, "vPx", VehData[TVehiculos][vPx]);
			cache_get_value_name_float(i, "vPy", VehData[TVehiculos][vPy]);
			cache_get_value_name_float(i, "vPz", VehData[TVehiculos][vPz]);
			cache_get_value_name_int(i, "Estereo", VehData[TVehiculos][Estereo]);
            /*-----------------===== [ CREACION ] =====-----------------*/
            VehData[TVehiculos][VehID] = AddStaticVehicleEx(VehData[TVehiculos][Model], VehData[TVehiculos][vX], VehData[TVehiculos][vY], VehData[TVehiculos][vZ], VehData[TVehiculos][vAngle], VehData[TVehiculos][Color1], VehData[TVehiculos][Color2], -1);
            /*--------------===== [ CONFIGURACION ] =====---------------*/
			format(matricula, sizeof(matricula), "%d", VehData[TVehiculos][Plate]);
			SetVehicleNumberPlate(VehData[TVehiculos][VehID], matricula);
            SetVehicleHealth(VehData[TVehiculos][VehID], VehData[TVehiculos][Status]);
            new engine, lights, alarm, doors, bonnet, boot, objective;
            if(VehData[TVehiculos][Key] == 0) //Cerrado
			{
				GetVehicleParamsEx(VehData[TVehiculos][VehID], engine, lights, alarm, doors, bonnet, boot, objective);
				SetVehicleParamsEx(VehData[TVehiculos][VehID], engine, lights, alarm, VEHICLE_PARAMS_ON, bonnet, boot, objective);
			}
			else if(VehData[TVehiculos][Key] == 1) //Abierto
			{
				GetVehicleParamsEx(VehData[TVehiculos][VehID], engine, lights, alarm, doors, bonnet, boot, objective);
				SetVehicleParamsEx(VehData[TVehiculos][VehID], engine, lights, alarm, VEHICLE_PARAMS_OFF, bonnet, boot, objective);
			}
			if(VehData[TVehiculos][Model] != 510)
			{
	            if(VehData[TVehiculos][Engine] == 1) //Encendido
				{
					GetVehicleParamsEx(VehData[TVehiculos][VehID], engine, lights, alarm, doors, bonnet, boot, objective);
					SetVehicleParamsEx(VehData[TVehiculos][VehID], VEHICLE_PARAMS_ON, lights, alarm, doors, bonnet, boot, objective);
				}
				else if(VehData[TVehiculos][Engine] == 0) //Apagado
				{
					GetVehicleParamsEx(VehData[TVehiculos][VehID], engine, lights, alarm, doors, bonnet, boot, objective);
					SetVehicleParamsEx(VehData[TVehiculos][VehID], VEHICLE_PARAMS_OFF, lights, alarm, doors, bonnet, boot, objective);
				}
			}
			else
			{
				GetVehicleParamsEx(VehData[TVehiculos][VehID], engine, lights, alarm, doors, bonnet, boot, objective);
				SetVehicleParamsEx(VehData[TVehiculos][VehID], VEHICLE_PARAMS_ON, lights, alarm, doors, bonnet, boot, objective);
			}
            if(VehData[TVehiculos][Alarm] == 1) //Alarma-Si
			{
				GetVehicleParamsEx(VehData[TVehiculos][VehID], engine, lights, alarm, doors, bonnet, boot, objective);
				SetVehicleParamsEx(VehData[TVehiculos][VehID], engine, lights, VEHICLE_PARAMS_ON, doors, bonnet, boot, objective);
			}
			else if(VehData[TVehiculos][Alarm] == 0) //Alarma-No
			{
				GetVehicleParamsEx(VehData[TVehiculos][VehID], engine, lights, alarm, doors, bonnet, boot, objective);
				SetVehicleParamsEx(VehData[TVehiculos][VehID], engine, lights, VEHICLE_PARAMS_OFF, doors, bonnet, boot, objective);
			}
		}
	}
	cache_delete(result);
	return 1;
}

public SaveCars()
{
    new query[600], Cache:result;
    for(new i=1; i < MAX_VEHICLES;i++)
    {
        if(VehData[i][vType] == 1 || VehData[i][vType] == 2)
        {
			//----------
			GetVehicleHealth(VehData[i][VehID], VehData[i][Status]);
			GetVehicleZAngle(VehData[i][VehID], VehData[i][vAngle]);
			GetVehiclePos(VehData[i][VehID], VehData[i][vX], VehData[i][vY], VehData[i][vZ]);
			//----------
			mysql_format(g_MySQL, query, sizeof(query), "UPDATE vehicles SET `Owner` = '%d', `Model` = '%d', `Plate` = '%d', `Type` = '%d', `vKey` = '%d' WHERE `IDDB` = '%d'",
			VehData[i][Owner], VehData[i][Model], VehData[i][Plate], VehData[i][vType], VehData[i][Key], VehData[i][IDDB]);
			result = mysql_query(g_MySQL, query);
			cache_delete(result);
			//----------
			mysql_format(g_MySQL, query, sizeof(query), "UPDATE vehicles SET `Alarm` = '%d', `Engine` = '%d', `Fuel` = '%f', `Aceite` = '%f' WHERE `IDDB` = '%d'",
			VehData[i][Alarm], VehData[i][Engine], VehData[i][Fuel], VehData[i][Aceite], VehData[i][IDDB]);
			result = mysql_query(g_MySQL, query);
			cache_delete(result);
			//----------
			mysql_format(g_MySQL, query, sizeof(query), "UPDATE vehicles SET `Status` = '%f', `vX` = '%f', `vY` = '%f', `vZ` = '%f', `vAngle` = '%f' WHERE `IDDB` = '%d'",
			VehData[i][Status], VehData[i][vX], VehData[i][vY], VehData[i][vZ], VehData[i][vAngle], VehData[i][IDDB]);
			result = mysql_query(g_MySQL, query);
			cache_delete(result);
			//----------
			mysql_format(g_MySQL, query, sizeof(query), "UPDATE vehicles SET `Color1` = '%d', `Color2` = '%d', `Faccion` = '%d', `FKey` = '%d', `Factura` = '%d' WHERE `IDDB` = '%d'",
			VehData[i][Color1], VehData[i][Color2], VehData[i][Faccion], VehData[i][FKey], VehData[i][Factura], VehData[i][IDDB]);
			result = mysql_query(g_MySQL, query);
			cache_delete(result);
			//-----------
			mysql_format(g_MySQL, query, sizeof(query), "UPDATE vehicles SET `vPx` = '%f', `vPy` = '%f', `vPz` = '%f', `Estereo`='%d' WHERE `IDDB` = '%d'",
			VehData[i][vPx], VehData[i][vPy], VehData[i][vPz], VehData[i][Estereo], VehData[i][IDDB]);
			result = mysql_query(g_MySQL, query);
			cache_delete(result);
		}
	}
	return 1;
}

public EncenderMotor(playerid, vehicleid)
{
	new engine, lights, alarm, doors, bonnet, boot, objective;
	GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
	SetVehicleParamsEx(vehicleid, VEHICLE_PARAMS_ON, lights, alarm, doors, bonnet, boot, objective);
	GameTextForPlayer(playerid, "~w~Motor ~g~Encendido",1000,3);
	VehData[vehicleid][Engine] = 1;
	new string[128 + MAX_PLAYER_NAME];
	format(string, sizeof(string), "**Vehículo encendido [ID:%d]", playerid);
	ProxDetector(30.0, playerid, string, 0xFFFF00FF,0xFFFF00FF,0xFFFF00FF,0xFFFF00FF,0xFFFF00FF);
	SetTimerEx("IntentarTimer", 2000, false, "d", playerid);
}

public ApagarMotor(playerid, vehicleid)
{
	new engine, lights, alarm, doors, bonnet, boot, objective;
	GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
	SetVehicleParamsEx(vehicleid, VEHICLE_PARAMS_OFF, lights, alarm, doors, bonnet, boot, objective);
	GameTextForPlayer(playerid, "~w~Motor ~r~Apagado",1000,3);
	VehData[vehicleid][Engine] = 0;
	new string[128 + MAX_PLAYER_NAME];
	format(string, sizeof(string), "**Vehículo apagado [ID:%d]", playerid);
	ProxDetector(30.0, playerid, string, 0xFFFF00FF,0xFFFF00FF,0xFFFF00FF,0xFFFF00FF,0xFFFF00FF);
	SetTimerEx("IntentarTimer", 2000, false, "d", playerid);
}

public LlenarGasolina(vehicleid, playerid)
{
	if(VehData[vehicleid][Fuel] >= 100.0)
	{
	    KillTimer(TimerLlenado[playerid]);
	    LlenarGas[playerid] = false;
	}
	else
	{
	    VehData[vehicleid][Fuel] += 1.5;
	    MedidoresVelocimetro(playerid, vehicleid);
	}
	return 1;
}

public CreateVehicleEx(playerid, modelid, type, ownerid)
{
	new Float:jugaX, Float:jugaY, Float:jugaZ, matricula[15], query[500];
	GetPlayerPos(playerid, jugaX, jugaY, jugaZ);
	VehData[TVehiculos][Owner] = ownerid;
	VehData[TVehiculos][Model] = modelid;
	VehData[TVehiculos][Plate] = 1000+random(999999);
	VehData[TVehiculos][vType] = type;
	VehData[TVehiculos][Key] = 0;
	VehData[TVehiculos][Alarm] = 0;
	VehData[TVehiculos][Engine] = 0;
	VehData[TVehiculos][Fuel] = 100.0;
	VehData[TVehiculos][Aceite] = 100.0;
	VehData[TVehiculos][Status] = 1000.0;
	VehData[TVehiculos][Color1] = 0;
	VehData[TVehiculos][Color2] = 0;
	VehData[TVehiculos][vX] = jugaX;
	VehData[TVehiculos][vY] = jugaY;
	VehData[TVehiculos][vZ] = jugaZ;
	VehData[TVehiculos][VehID] = AddStaticVehicleEx(VehData[TVehiculos][Model], jugaX, jugaY, jugaZ, 90.0, VehData[TVehiculos][Color1], VehData[TVehiculos][Color2], -1);
	format(matricula, sizeof(matricula), "%d", VehData[TVehiculos][Plate]);
	SetVehicleNumberPlate(VehData[TVehiculos][VehID], matricula);
	new engine, lights, alarm, doors, bonnet, boot, objective;
	GetVehicleParamsEx(TVehiculos, engine, lights, alarm, doors, bonnet, boot, objective);
	SetVehicleParamsEx(TVehiculos, VEHICLE_PARAMS_OFF, lights, alarm, VEHICLE_PARAMS_ON, bonnet, boot, objective);
	//----------
	mysql_format(g_MySQL, query, sizeof(query), "INSERT INTO `vehicles` (`Owner`, `Model`, `Plate`, `Type`) VALUES ('%d', '%d', '%d', '%d')",
	VehData[TVehiculos][Owner], VehData[TVehiculos][Model], VehData[TVehiculos][Plate], VehData[TVehiculos][vType]);
	new Cache:result = mysql_query(g_MySQL, query);
	cache_delete(result);
	//----------
	TVehiculos++;
	return 1;
}