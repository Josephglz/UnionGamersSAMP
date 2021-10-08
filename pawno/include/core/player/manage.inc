#include <gui/hud/main>
#include <core/player/data>
#include <gui/hud/textdraw>
#include <utils/system/factions> 
#include <utils/system/vehicles>
#include <utils/system/business>
#include <utils/system/jobs>

new WeatherCount;
/*==============================	[		STOCKS		]	==============================*/
stock FixPlayerData(playerid)
{
	if(GetPlayerSkin(playerid) != PlayersData[playerid][Skin])
	{
		if(TempInfo[playerid][Work] == 0)
		{	
			SetPlayerSkin(playerid, PlayersData[playerid][Skin]);
		}
	}
	if(GetPlayerMoney(playerid) != PlayersData[playerid][Money])
	{
		ResetPlayerMoney(playerid);
		GivePlayerMoney(playerid, PlayersData[playerid][Money]);
	}
	if(GetPlayerInterior(playerid) != PlayersData[playerid][pInterior])
	{
		SetPlayerInterior(playerid, PlayersData[playerid][pInterior]);
	}
	if(GetPlayerVirtualWorld(playerid) != PlayersData[playerid][pVW])
	{
		SetPlayerVirtualWorld(playerid, PlayersData[playerid][pVW]);
	}
	return 1;
}

stock SetPlayerDeathSegs(playerid)
{
	if(TempInfo[playerid][IsDeath] == true && Logged[playerid] == true)
	{
		TempInfo[playerid][DeathCooldown]--;
		new deathsegs[16];
		format(deathsegs, sizeof(deathsegs), "%02d segundos", TempInfo[playerid][DeathCooldown]);
		PlayerTextDrawSetString(playerid, DeadTD_Time[playerid], deathsegs);
		ApplyAnimation(playerid, "CRACK", "crckdeth2", 4.1, 1, 1, 1, 1, 0, 1);
	}
	return 1;
}

stock PutPlayerToDeath(playerid)
{
	SpawnPlayer(playerid);
	TempInfo[playerid][IsDeath] = false;
	TempInfo[playerid][DeathCooldown] = 0;
	PlayersData[playerid][pFood] = 90.0;
	PlayersData[playerid][pDrink] = 90.0;
	HideDeathTextDraw(playerid);
	TogglePlayerControllable(playerid, 1);

	SendClientMessageEx(playerid, -1, "%s Pagaste $30 dólares de Servicios Hospitalarios.", InfoMsg);
	SetPlayerHealth(playerid, 90);
	ResetPlayerMoney(playerid);
	PlayersData[playerid][Money] -= 30;
	GivePlayerMoney(playerid, PlayersData[playerid][Money]);
	SetPlayerSkin(playerid, PlayersData[playerid][Skin]);
	SetPlayerInterior(playerid, 0);
	SetPlayerVirtualWorld(playerid, 0);
	SetPlayerPos(playerid, 1179.0396, -1323.5474, 14.1498);
	PlayerPlaySound(playerid,1039,0.0,0.0,0.0);
	return 1;
}

stock split(const strsrc[], strdest[][], delimiter)
{
    new i, li;
    new aNum;
    new len;
    while(i <= strlen(strsrc))
    {
        if(strsrc[i] == delimiter || i == strlen(strsrc))
        {
            len = strmid(strdest[aNum], strsrc, li, i, 128);
            strdest[aNum][len] = 0;
            li = i+1;
            aNum++;
        }
        i++;
    }
    return 1;
}

stock GetFirstName(playerid)
{
	new PlayerName[128], Split[3][128];
	GetPlayerName(playerid, PlayerName, sizeof(PlayerName));
	split(PlayerName, Split, '_');
	return Split[0];
}

stock GetLastName(playerid)
{
    new namestring[2][MAX_PLAYER_NAME], name[MAX_PLAYER_NAME];
    GetPlayerName(playerid,name,MAX_PLAYER_NAME);
    split(name, namestring, '_');
    return namestring[1];
}

stock FixSpecialString(string[])
{
	new szFixed[1024], iPos, iLen;
	for (iLen = strlen(string); iPos < iLen; iPos ++)
	{
		switch (string[iPos])
		{
			case 'á':   szFixed[iPos] = 152;
			case 'Á':   szFixed[iPos] = 129;
			case 'é':   szFixed[iPos] = 158;
			case 'É':   szFixed[iPos] = 135;
			case 'í':   szFixed[iPos] = 162;
			case 'Í':   szFixed[iPos] = 139;
			case 'ó':   szFixed[iPos] = 166;
			case 'Ó':   szFixed[iPos] = 143;
			case 'ú':   szFixed[iPos] = 170;
			case 'Ú':   szFixed[iPos] = 147;
			case 'ñ':   szFixed[iPos] = 174;
			case 'Ñ':   szFixed[iPos] = 173;
			default:    szFixed[iPos] = string[iPos];
		}
	}
	return szFixed;
}

stock IsPlayerNearCajero(playerid)
{
	new nc;
	for(new i=0; i < sizeof(Cajeros); i++)
	{
		if(IsPlayerInRangeOfPoint(playerid, 3.0, Cajeros[i][0], Cajeros[i][1], Cajeros[i][2]))
		{
			nc= 1;
		}
	}
	return nc;
}

stock IsPlayerInGasStation(playerid)
{
	new nGs;
	for(new i = 0; i < sizeof(Gasolineras); i++)
	{
		if(IsPlayerInRangeOfPoint(playerid, 10.0, Gasolineras[i][0], Gasolineras[i][1], Gasolineras[i][2]))
		{
			nGs = 1;
		}
	}
	return nGs;
}

stock Float:GetVehicleSpeed(vehicleid)
{
    new Float:x, Float:y, Float:z;
    if(GetVehicleVelocity(vehicleid, x, y, z))
    {
        return floatsqroot((x * x) + (y * y) + (z * z)) * 181.5;
    }
    return 0.0;
}

stock NeedExpForPlayer(playerid)
{
	new exp;
	switch(PlayersData[playerid][Level])
	{
	    case 0 .. 10:	{		exp = 10;	}
	    case 11 .. 20:  {       exp = 20;   }
	    case 21 .. 40:  {       exp = 30;   }
	    case 41 .. 60:  {       exp = 40;   }
	    case 61 .. 200: {       exp = 50;   }
	}
	return exp;
}
/*==============================	[		CALLBACKS		]	==============================*/
forward KickPlayerEx(playerid);
forward OnPlayerDeathEx(playerid);
forward Clock();
forward PayDay();
forward PlayerConsume(playerid);
forward ConsumoVehiculo(vehicleid);

public KickPlayerEx(playerid)
{
	Kick(playerid);
	return 1;
}

public OnPlayerDeathEx(playerid)
{
	SetPlayerPos(playerid, TempInfo[playerid][dPosX], TempInfo[playerid][dPosY], TempInfo[playerid][dPosZ]);
	ApplyAnimation(playerid, "CRACK", "crckdeth2", 4.1, 1, 1, 1, 1, 0, 1);
	TempInfo[playerid][DeathCooldown] = 180;
	TempInfo[playerid][IsDeath] = true;
	ShowDeathTextDraw(playerid);
	return 1;
}

public Clock()
{
	//=============		CLOCK		=============
	new string[100], string2[150], mtext[15];
	new year, month, day;
	getdate(year, month, day);
	switch(month)
	{
		case 1: mtext = "Enero";
		case 2: mtext = "Febrero";
		case 3: mtext = "Marzo";
		case 4: mtext = "Abril";
		case 5: mtext = "Mayo";
		case 6: mtext = "Junio";
		case 7: mtext = "Julio";
		case 8: mtext = "Agosto";
		case 9: mtext = "Septiembre";
		case 10: mtext = "Octubre";
		case 11: mtext = "Noviembre";
		case 12: mtext = "Diciembre";
		default: mtext = "Indefinido";		
	}
	format(string2, sizeof(string2), "%d de %s, %d", day, mtext, year);
	TextDrawSetString(Text:Reloj2, string2);
	new hour, minute, second;
	gettime(hour, minute, second);
	format(string, sizeof(string), "%02d:%02d:%02d", hour, minute, second);
	TextDrawSetString(Text:Reloj1, string);

	/*===============       [ PER SECOND FUNCTIONS ]     =============== */
	for(new i = 0; i <= GetPlayerPoolSize(); i++)
	{
		if(IsPlayerConnected(i) && Logged[i] == true)
		{
			SetPlayerTime(i, hour, minute);
			FixPlayerData(i);
			PlayerConsume(i);
			/*===============       [ DEATH SYSTEM ]     =============== */
			if(TempInfo[i][DeathCooldown] != 0)
			{
				SetPlayerDeathSegs(i);
			}
			else if(TempInfo[i][IsDeath] == true && TempInfo[i][DeathCooldown] <= 1)
			{
				PutPlayerToDeath(i);
			}
		}
	}

	for(new i=0; i <= GetVehiclePoolSize(); i++)
	{
	    if(i != INVALID_VEHICLE_ID)
	    {
	        if(VehData[i][Engine] == 1)
	        {
				ConsumoVehiculo(i);
			}
		}
	}

	if (minute == 00 && second == 00)
	{
		PayDay();
	}
	return 1;
}

public PayDay()
{
    new p, msg[25];
	for(new i=0; i <= GetPlayerPoolSize(); i++)
	{
		if(IsPlayerConnected(i) && Logged[i] == true)
		{
		    SendClientMessageEx(i, -1, "{FBDA8E}|___________________ {008000}Banco{FBDA8E} ___________________|");
			if(FaccData[1][Money] > 500)
			{
				switch(PlayersData[i][Vip])
				{
					case 0:{    p=20;}      case 1:{    p=40;}
				}
				PlayersData[i][BankAccount] += p;
				FaccData[0][Money] -= p;
				SendClientMessageEx(i, -1, "{BDF766}Banco: Nuevo Balance: $%d", PlayersData[i][BankAccount]);
				SendClientMessageEx(i, -1, "{BDF766}Banco: Paga: $%d", p);
				SendClientMessageEx(i, -1, "{BDF766}Banco: Cuenta Bancaria: #%d", PlayersData[i][ID]);
			}
			else
			{
			    SendClientMessageEx(i, -1, "{FF0000}Banco: El Deposito del Banco no tiene suficiente efectivo.");
			    SendClientMessageEx(i, -1, "{FF0000}Banco: Deberás esperar al próximo PayDay.");
			}
			SendClientMessage(i, -1, "{FBDA8E}|_____________________ {008000}Fin{FBDA8E} ____________________|");
			format(msg, sizeof(msg), "~B~Hora de la Paga!");
			GameTextForPlayer(i, msg, 1000, 1);
			PlayersData[i][Exp]++;
			PlayerPlaySound(i, 1133, 0, 0, 10.0);
			SavePlayerData(i, 0);
			if(PlayersData[i][Exp] >= NeedExpForPlayer(i))
			{
			    PlayersData[i][Level]++;
			    SetPlayerScore(i, GetPlayerScore(i)+1);
			    PlayersData[i][Exp] = 0;
				SendClientMessageEx(i, -1, "%s Haz subido de nivel, felicidades!", InfoMsg);
			}
		}
	}
	WeatherCount++;
	/*=====---[ GUARDADOS ]---=====*/
	SaveFactions();
	SaveCars();
	SaveNegocios();
	GuardarObjetos();
	
	if(WeatherCount >= 3)
	{
		new id=random(5);
		switch(id)
		{
			case 0:{	SetWeather(1);}     case 1:{	SetWeather(4);}     case 2:{	SetWeather(12);}
			case 3:{    SetWeather(16);}    case 4:{	SetWeather(20);}
		}
		WeatherCount = 0;
	}
	return 1;
}

public PlayerConsume(playerid)
{
	if(IsPlayerConnected(playerid) && Logged[playerid] == true)
	{
		PlayersData[playerid][pFood] -= 0.005;
		PlayersData[playerid][pDrink] -= 0.003;

		if(PlayersData[playerid][pFood] <= 10.0 && TempInfo[playerid][IsDeath] == false)
		{
			new Float:pHealthX;
			GetPlayerHealth(playerid, pHealthX);
			SetPlayerHealth(playerid, pHealthX - 0.0001);
		}
		if(PlayersData[playerid][pDrink] <= 20.0)
		{
			PlayersData[playerid][pFood] -= 0.003;
		}
		SetPlayerProgressBarValue(playerid, PJ_Food[playerid], PlayersData[playerid][pFood]);
		SetPlayerProgressBarValue(playerid, PJ_Drink[playerid], PlayersData[playerid][pDrink]);
	}
	return 1;
}

public ConsumoVehiculo(vehicleid)
{
	if(vehicleid != INVALID_VEHICLE_ID)
	{
		if(VehData[vehicleid][Engine] == 1)
		{
		    new Float:VeH;
		    GetVehicleHealth(vehicleid, VeH);
		    if(VehData[vehicleid][Fuel] <= 0)
			{
				VehData[vehicleid][Engine] = 0;
				new engine, lights, alarm, doors, bonnet, boot, objective;
				GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
				SetVehicleParamsEx(vehicleid, VEHICLE_PARAMS_OFF, lights, alarm, doors, bonnet, boot, objective);
			}
			if(VehData[vehicleid][Aceite] < 30)
			{
			    SetVehicleHealth(vehicleid, VeH-0.60);
			}
			if(GetVehicleSpeed(vehicleid) > 0 && GetVehicleSpeed(vehicleid) < 5)
			{
				VehData[vehicleid][Fuel] = VehData[vehicleid][Fuel] - 0.005;
				VehData[vehicleid][Aceite] = VehData[vehicleid][Aceite] - 0.009;
			}
			else if(GetVehicleSpeed(vehicleid) > 5 && GetVehicleSpeed(vehicleid) < 20)
			{
				VehData[vehicleid][Fuel] = VehData[vehicleid][Fuel] - 0.012;
				VehData[vehicleid][Aceite] = VehData[vehicleid][Aceite] - 0.015;
			}
			else if(GetVehicleSpeed(vehicleid) > 20 && GetVehicleSpeed(vehicleid) < 50)
			{
				VehData[vehicleid][Fuel] = VehData[vehicleid][Fuel] - 0.015;
				VehData[vehicleid][Aceite] = VehData[vehicleid][Aceite] - 0.015;
			}
			else if(GetVehicleSpeed(vehicleid) > 50 && GetVehicleSpeed(vehicleid) < 80)
			{
				VehData[vehicleid][Fuel] = VehData[vehicleid][Fuel] - 0.018;
				VehData[vehicleid][Aceite] = VehData[vehicleid][Aceite] - 0.015;
			}
			else if(GetVehicleSpeed(vehicleid) > 80 && GetVehicleSpeed(vehicleid) < 120)
			{
				VehData[vehicleid][Fuel] = VehData[vehicleid][Fuel] - 0.022;
				VehData[vehicleid][Aceite] = VehData[vehicleid][Aceite] - 0.015;
			}
			else if(GetVehicleSpeed(vehicleid) > 120)
			{
				VehData[vehicleid][Fuel] = VehData[vehicleid][Fuel] - 0.025;
				VehData[vehicleid][Aceite] = VehData[vehicleid][Aceite] - 0.007;
			}
			for(new i=0; i <= GetPlayerPoolSize(); i++)
			{
			    if(IsPlayerInVehicle(i, vehicleid))
			    {
	                MedidoresVelocimetro(i, vehicleid);
			    }
			}
		}
	}
	return 1;
}