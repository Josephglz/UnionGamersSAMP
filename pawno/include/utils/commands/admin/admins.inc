#include <zcmd>
#include <sscanf2>
#include <core/player/data>
#include <utils/system/vehicles>
#include <utils/system/mapping>

#define     NO_ADMIN_PERMISSION     "{4B4B4B}[Info]: No eres miembro del Staff."
#define		ERROR_ADMIN				"{C0C0C0}[Info]: "
#define		MapMsg					"{FF8040}[Map]: "
#define		DIALOG_GLOBAL_INPUT		10
#define     MENU_NEGOCIO            11
#define		DIALOG_MAPEAR           21

stock SendAdminLog(sender, emit, type, reason[])
{
	new source[10];
	switch(type)
	{
		case 1:{	source = "KICK";}	case 2:{	source = "BAN";}	case 3:{	source = "RESPAWN";}
		case 4:{	source = "FACCION";}	case 5:{	source = "FACCION";}	case 6:{	source="FACCION";}
		case 7:{	source = "STAFF";}	case 8:{	source = "PAYDAY";} case 9:{	source="COCHE";}
	}

	for(new i=0; i <= GetPlayerPoolSize(); i++)
	{
		if(PlayersData[i][Admin] >= 3)
		{
			switch(type)
			{
				case 1:
				{
					SendClientMessageEx(i, -1, "%s %s: %s Razón: %s. Por: %s", AlertMsg, source, RemoveUnderScore(emit), reason, RemoveUnderScore(sender));
				}
				case 2:
				{
					SendClientMessageEx(i, -1, "%s %s: %s Razón: %s. Por: %s", AlertMsg, source, RemoveUnderScore(emit), reason, RemoveUnderScore(sender));
				}
				case 3:
				{
					SendClientMessageEx(i, -1, "%s %s: Vehículo %d. Por: %s", AlertMsg, source, emit, RemoveUnderScore(sender));
				}
				case 4:
				{
					SendClientMessageEx(i, -1, "%s %s: Creada %s. Por: %s", AlertMsg, source, reason, RemoveUnderScore(sender));
				}
				case 5:
				{
					SendClientMessageEx(i, -1, "%s %s: Editar %s. Por: %s", AlertMsg, source, reason, RemoveUnderScore(sender));
				}
				case 6:
				{
					SendClientMessageEx(i, -1, "%s %s: Eliminar %s. Por: %s", AlertMsg, source, reason, RemoveUnderScore(sender));
				}
				case 7:
				{
					SendClientMessageEx(i, -1, "%s %s: Staff %s | Nivel: %s. Por: %s", AlertMsg, source, RemoveUnderScore(emit), reason, RemoveUnderScore(sender));
				}
				case 8:
				{
					SendClientMessageEx(i, -1, "%s %s Por: %s", AlertMsg, source, RemoveUnderScore(sender));
				}
				case 9:
				{
					SendClientMessageEx(i, -1, "%s %s: MODELO %d. Por: %s", AlertMsg, source, emit, RemoveUnderScore(sender));
				}
			}
		}
	}

	return 1;
}

CMD:cmdstaff(playerid, params[])
{
    if(PlayersData[playerid][Admin] >= 1)
    {
        if(PlayersData[playerid][Admin] >= 1)
        {
		    SendClientMessageEx(playerid, 0, "{D9E35B}|__________________________________[ Auxiliar ]__________________________________|");
		    SendClientMessageEx(playerid, 0, "{AEAEAE}/J [Chat] - /Res [ID] [Texto] - /CmdStaff");
		    SendClientMessageEx(playerid, 0, "{BE7E7E}[+] Recibir Dudas de Usuarios de la Comunidad.");
        }
		if(PlayersData[playerid][Admin] >= 2)
		{
		    SendClientMessageEx(playerid, 0, "{D9E35B}|________________________________[ Staff ]________________________________|");
		    SendClientMessageEx(playerid, 0, "{AEAEAE}/AdminDuty - /A [Chat] - /Ir [ID] - /Traer [ID] - /Spawn [ID] - /Test [ID]");
			SendClientMessageEx(playerid, 0, "{AEAEAE}/(W)hisper [ID] [Chat]");
        }
		if(PlayersData[playerid][Admin] >= 3)
		{
            SendClientMessageEx(playerid, 0, "{D9E35B}|________________________________[ Moderador 1 ]________________________________|");
		    SendClientMessageEx(playerid, 0, "{AEAEAE}/Kick [ID] [Razon] - /TraerVeh [ID_Veh] - /IrVeh [ID_Veh] - /Congelar [ID] - /Descongelar [ID]");
		    SendClientMessageEx(playerid, 0, "{BE7E7E}[+] Click en Jugador del Tabulador para Teletransportarte.");
		}
		if(PlayersData[playerid][Admin] >= 4)
		{
		    SendClientMessageEx(playerid, 0, "{D9E35B}|________________________________[ Moderador 2 ]________________________________|");
		    SendClientMessageEx(playerid, 0, "{AEAEAE} /Respawn [ID_Veh] - /Matar [ID] - /O [Texto] - /MDar [Opción] [ID] [Cant]");
		}
		if(PlayersData[playerid][Admin] >= 5)
		{
		    SendClientMessageEx(playerid, 0, "{D9E35B}|________________________________[ Moderador 3 ]_________________________________|");
		    SendClientMessageEx(playerid, 0, "{AEAEAE} /Ban [ID] [Razon] - /ClearChat - /IrCoord [X] [Y] [Z]");
		    SendClientMessageEx(playerid, 0, "{BE7E7E}[+] Click Derecho en el Mapa para Teletransportarte.");
		}
		if(PlayersData[playerid][Admin] >= 6)
		{
		    SendClientMessageEx(playerid, 0, "{D9E35B}|________________________________[ Moderador Global ]________________________________|");
		    SendClientMessageEx(playerid, 0, "{AEAEAE} /StatsEx [ID] - /SetSkin [ID] [Skin] - /GoInt [Int] - /GoVW [VW]");
		}
		if(PlayersData[playerid][Admin] >= 7)
		{
		    SendClientMessageEx(playerid, 0, "{D9E35B}|________________________________[ Co-Admin ]________________________________|");
		    SendClientMessageEx(playerid, 0, "{AEAEAE} /Staff [ID] [Rango] - /DsMsg [Texto] - /CCambiar [ID] [Modelo] - /ECoche - /Mapeos");
		    SendClientMessageEx(playerid, 0, "{BE7E7E}[+] Administración del staff");
		}
		if(PlayersData[playerid][Admin] >= 8)
		{
		    SendClientMessageEx(playerid, 0, "{D9E35B}|________________________________[ Administrador ]________________________________|");
		    SendClientMessageEx(playerid, 0, "{AEAEAE} /MePuerta - /MeFaccion - /MeNegocio - /PayDayNow - /Faccion [ID] [ID_Faccion] - /CCoche");
		    SendClientMessageEx(playerid, 0, "{BE7E7E}[+] Administración de Facciones");
		}
		if(PlayersData[playerid][Admin] >= 9)
		{
		    SendClientMessageEx(playerid, 0, "{D9E35B}|________________________________[ Scripter ]________________________________|");
		    SendClientMessageEx(playerid, 0, "{AEAEAE} /GMX - /AForce");
		    SendClientMessageEx(playerid, 0, "{BE7E7E}[+] Administración de Servidor");
		}
    }
    else
    {
        SendClientMessageEx(playerid, -1, NO_ADMIN_PERMISSION);
    }

    return 1;
}

CMD:a(playerid, params[])
{
	if(PlayersData[playerid][Admin] >= 2)
	{
		new msg[256], rango[25];
		if (!sscanf(params, "s[256]", msg))
		{
		    switch(PlayersData[playerid][Admin])
		    {
		        case 1:{    rango="Auxiliar";}				case 2:{    rango="Staff";}				case 3:{    rango="Moderador 1";}
		        case 4:{    rango="Moderador 2";}      		case 5:{    rango="Moderador 3";}      	case 6:{    rango="Moderador Global";}
		        case 7:{    rango="Co-Admin";}				case 8:{	rango="Administrador";}		case 9:{	rango="Scripter";}
		    }
			for(new i=0; i <= GetPlayerPoolSize(); i++)
			{
			    if(PlayersData[i][Admin]>=2 && IsPlayerConnected(i))
			    {
			        new string[256];
					if(strlen(msg) > 80)
					{
					    new string2[128];
					    format(string2, sizeof(string2), "{7777FF}— %s", msg[80]);
				    	strdel(msg, 80, strlen(msg));
						format(string, sizeof(string), "{7777FF}[Administración]: %s %s: {7777FF}%s", rango, RemoveUnderScore(playerid), msg);
						SendClientMessageEx(i, -1, string);
						SendClientMessageEx(i, -1, string2);
					}
					else if(strlen(msg) < 80)
					{
	     	     		SendClientMessageEx(i, -1, "{7777FF}[Administración]: %s %s: {7777FF}%s", rango, RemoveUnderScore(playerid), msg);
					}
				}
			}
		}
		else
		{
		    SendClientMessageEx(playerid, -1, "%s Utiliza: /A [Texto]", ERROR_ADMIN);
  		}
	}
	else
    {
        SendClientMessageEx(playerid, -1, NO_ADMIN_PERMISSION);
    }
	return 1;
}

CMD:j(playerid, params[])
{
	if(PlayersData[playerid][Admin]>=1)
	{
		new string[256], rango[120];
		if (!sscanf(params, "s[256]", string))
		{
		    if(PlayersData[playerid][Admin] == 1){  rango="Auxiliar";}
		    if(PlayersData[playerid][Admin] == 2){  rango="Staff";}
		    if(PlayersData[playerid][Admin] == 3){  rango="Moderador 1";}
		    if(PlayersData[playerid][Admin] == 4){  rango="Moderador 2";}
			if(PlayersData[playerid][Admin] == 5){	rango="Moderador 3";}
		    if(PlayersData[playerid][Admin] == 6){  rango="Moderador Global";}
		    if(PlayersData[playerid][Admin] == 7){  rango="Co-Admin";}
		    if(PlayersData[playerid][Admin] == 8){  rango="Administrador";}
			if(PlayersData[playerid][Admin] == 9){	rango="Scripter";}

			for(new i=0; i <= GetPlayerPoolSize(); i++)
			{
			    if(PlayersData[i][Admin]>=1 && IsPlayerConnected(i))
			    {
					new msg[256];
					if(strlen(msg) > 80)
					{
					    new string2[128];
					    format(string2, sizeof(string2), "{FF0880}— %s", msg[80]);
				    	strdel(msg, 80, strlen(msg));
						format(string, sizeof(string), "{FF0880}[Auxiliares]: %s %s{FF0880}: %s", rango, RemoveUnderScore(playerid), msg);
						SendClientMessageEx(i, -1, string);
						SendClientMessageEx(i, -1, string2);
					}
					else if(strlen(msg) < 80)
					{
	     	     		SendClientMessageEx(i,-1, "{FF0880}[Auxiliares]: %s %s{FF0880}: %s", rango, RemoveUnderScore(playerid), string);
					}
			    	
				}
			}
		}
		else
		{
		    SendClientMessageEx(playerid, -1, "%s Utiliza: /J [Texto]", ERROR_ADMIN);
  		}
	}
	else
    {
        SendClientMessageEx(playerid, -1, NO_ADMIN_PERMISSION);
    }
	return 1;
}

CMD:res(playerid, params[])
{
	if(PlayersData[playerid][Admin] >= 1)
	{
	    new id, string[128];
	    if(!sscanf(params, "us[128]", id, string))
	    {
	        if(IsPlayerConnected(id) && id != playerid)
	        {
		        for(new i=0; i <= GetPlayerPoolSize(); i++)
		        {
					if(PlayersData[i][Admin] >= 1 )
					{
					    SendClientMessageEx(i, -1, "%s %s le respondió a %s: %s", DudaMsg, RemoveUnderScore(playerid), RemoveUnderScore(id), string);
					}
				}
				SendClientMessageEx(id, -1, "%s %s respuesta: %s", DudaMsg, RemoveUnderScore(playerid), string);
			}
			else
			{
			    SendClientMessageEx(playerid, -1, "%s Introduciste una ID inválida.", InfoMsg);
			}
		}
		else
		{
		    SendClientMessageEx(playerid, -1, "%s Utiliza: /Res [ID] [Texto]", ERROR_ADMIN);
		}
	}
	else
    {
        SendClientMessageEx(playerid, -1, NO_ADMIN_PERMISSION);
    }
	return 1;
}

CMD:ir(playerid, params[])
{
	if(PlayersData[playerid][Admin] >= 2)
	{
		new pID;
		if(!sscanf(params, "u", pID))
		{
			if(IsPlayerConnected(pID) && pID != playerid)
			{
				if(Logged[pID] == true)
				{
					new Float:pX, Float:pY, Float:pZ;
					GetPlayerPos(pID, pX, pY, pZ);
					SetPlayerPos(playerid, pX+2, pY, pZ);
					SetPlayerInterior(playerid, GetPlayerInterior(pID));
					SetPlayerVirtualWorld(playerid, GetPlayerVirtualWorld(pID));
					SendClientMessageEx(playerid, -1, "%s Haz ido a la Posición de %s [ID: %d]", InfoMsg, RemoveUnderScore(pID), pID);
				}
				else
				{
					SendClientMessageEx(playerid, -1, "%s El usuario no se encuentra conectado o no ha iniciado sesión.", ERROR_ADMIN);
				}
			}
			else
			{
				SendClientMessageEx(playerid, -1, "%s Introduciste una ID inválida.", ERROR_ADMIN);
			}
		}
		else
		{
			SendClientMessageEx(playerid, -1, "%s Utiliza: /Ir [ID]", ERROR_ADMIN);
		}
	}
	else
    {
        SendClientMessageEx(playerid, -1, NO_ADMIN_PERMISSION);
    }
	return 1;
}

CMD:traer(playerid, params[])
{
	if(PlayersData[playerid][Admin] >= 2)
	{
		new pID;
		if(!sscanf(params, "u", pID))
		{
			if(IsPlayerConnected(pID) && pID != playerid)
			{
				if(Logged[pID] == true)
				{
					new Float:pX, Float:pY, Float:pZ;
					GetPlayerPos(playerid, pX, pY, pZ);
					SetPlayerPos(pID, pX+2, pY, pZ);
					SetPlayerInterior(pID, GetPlayerInterior(playerid));
					SetPlayerVirtualWorld(pID, GetPlayerVirtualWorld(playerid));
					SendClientMessageEx(playerid, -1, "%s Haz traido a tú Posición a %s [ID: %d]", InfoMsg, RemoveUnderScore(pID), pID);
					SendClientMessageEx(pID, -1, "%s El Administrador %s [ID: %d] te ha llevado a su posición.", InfoMsg, RemoveUnderScore(playerid), playerid);
				}
				else
				{
					SendClientMessageEx(playerid, -1, "%s El usuario no se encuentra conectado o no ha iniciado sesión.", ERROR_ADMIN);
				}
			}
			else
			{
				SendClientMessageEx(playerid, -1, "%s Introduciste una ID inválida.", ERROR_ADMIN);
			}
		}
		else
		{
			SendClientMessageEx(playerid, -1, "%s Utiliza: /Traer [ID]", ERROR_ADMIN);
		}
	}
	else
    {
        SendClientMessageEx(playerid, -1, NO_ADMIN_PERMISSION);
    }

	return 1;
}

CMD:spawn(playerid, params[])
{
	if(PlayersData[playerid][Admin] >= 2)
	{
		new pID;
		if(!sscanf(params, "u", pID))
		{
			if(IsPlayerConnected(pID) && playerid != pID)
			{
				if(Logged[pID] == true)
				{
					SpawnPlayer(pID);
					SendClientMessageEx(playerid, -1, "%s Mandaste al Spawn a %s [ID: %d].", InfoMsg, RemoveUnderScore(pID), pID);
					SendClientMessageEx(pID, -1, "%s El Administrador %s [ID: %d] te ha mandado al Spawn.", InfoMsg, RemoveUnderScore(playerid), playerid);
				}
				else
				{
					SendClientMessageEx(playerid, -1, "%s El usuario no se encuentra conectado o no ha iniciado sesión.", ERROR_ADMIN);
				}
			}
			else
			{
				SendClientMessageEx(playerid, -1, "%s Introduciste una ID inválida.", ERROR_ADMIN);
			}
		}
		else
		{
			SendClientMessageEx(playerid, -1, "%s Utiliza: /Spawn [ID]", ERROR_ADMIN);
		}
	}
	else
    {
        SendClientMessageEx(playerid, -1, NO_ADMIN_PERMISSION);
    }
	return 1;
}

CMD:test(playerid, params[])
{
	if(PlayersData[playerid][Admin] >= 2)
	{
		new pID;
		if(!sscanf(params, "u", pID))
		{
			if(IsPlayerConnected(pID) && playerid != pID)
			{
				if(Logged[pID] == true)
				{
					new Float:pX, Float:pY, Float:pZ;
					GetPlayerPos(pID, pX, pY, pZ);
					SetPlayerPos(pID, pX, pY, pZ+10);
					SendClientMessageEx(playerid, -1, "%s Posición de %s [ID: %d] Sincronizada.", InfoMsg, RemoveUnderScore(pID), pID);
					SendClientMessageEx(pID, -1, "%s El Administrador %s [ID: %d] te desbugeó.", InfoMsg, RemoveUnderScore(playerid), playerid);
				}
				else
				{
					SendClientMessageEx(playerid, -1, "%s El usuario no se encuentra conectado o no ha iniciado sesión.", ERROR_ADMIN);
				}
			}
			else
			{
				SendClientMessageEx(playerid, -1, "%s Introduciste una ID inválida.", ERROR_ADMIN);
			}
		}
		else
		{
			SendClientMessageEx(playerid, -1, "%s Utiliza: /Test [ID]", ERROR_ADMIN);
		}
	}
	else
    {
        SendClientMessageEx(playerid, -1, NO_ADMIN_PERMISSION);
    }
	return 1;
}

CMD:adminduty(playerid, params[])
{
	if(PlayersData[playerid][Admin] >= 2)
	{
		if(TempInfo[playerid][OnDuty] == false)
		{
			GetPlayerHealth(playerid, TempInfo[playerid][dHealth]);
			SendClientMessageEx(playerid, -1, "%s Ahora estás OnDuty.", InfoMsg);
		    SetPlayerHealth(playerid, 999);
	        SetPlayerColor(playerid, AdminsRangosColorsHEX[PlayersData[playerid][Admin] - 1]);
			TempInfo[playerid][OnDuty] = true;
		}
		else
		{
			if(PlayersData[playerid][Vip] == 1)
			{
				SetPlayerColor(playerid, 0xFFFF11FF);
			}
			else
			{
				SetPlayerColor(playerid, 0xFFFFFFFF);
			}
			TempInfo[playerid][OnDuty] = false;
			SetPlayerHealth(playerid, TempInfo[playerid][dHealth]);
			SendClientMessageEx(playerid, -1, "%s Ya no te encuentras OnDuty.", InfoMsg);
		}
	}
	else
    {
        SendClientMessageEx(playerid, -1, NO_ADMIN_PERMISSION);
    }
	return 1;
}

CMD:whisper(playerid, params[])
{
	new pID, msg[256];
	if(!sscanf(params, "us[256]", pID, msg))
	{
	    if(IsPlayerConnected(pID) && pID != playerid)
	    {
	    	if(PlayersData[playerid][Admin] < 2)
	    	{
	    	    if(PlayersData[pID][Admin] >= 2)
       		 	{
                    new string[256];
					if(strlen(msg) > 80)
					{
					    new string2[128];
					    format(string2, sizeof(string2), "{FF9DFF}— %s", msg[80]);
				    	strdel(msg, 80, strlen(msg));
				    	format(string, sizeof(string), "%s %s[ID:%d] te whispea: %s", WhisperMsg, RemoveUnderScore(playerid), playerid, msg);
				    	SendClientMessageEx(pID, -1, string);
				    	SendClientMessageEx(pID, -1, string2);
				    	format(string, sizeof(string), "%s whispeaste a %s[ID:%d]: %s", WhisperMsg, RemoveUnderScore(pID), pID, msg);
				    	SendClientMessageEx(playerid, -1, string);
				    	SendClientMessageEx(playerid, -1, string2);
					}
					else if(strlen(msg) < 80)
					{
	     	     		SendClientMessageEx(pID, -1, "%s %s[ID:%d] te whispea: %s", WhisperMsg, RemoveUnderScore(playerid), playerid, msg);
		        		SendClientMessageEx(playerid, -1, "%s whispeaste a %s[ID:%d]: %s", WhisperMsg, RemoveUnderScore(pID), pID, msg);
					}
	        	}
	        	else
	        	{
	        	    SendClientMessageEx(playerid, -1, "%s Solo puedes whispear a Administradores.", InfoMsg);
	        	}
	    	}
	    	else
	    	{
	    	    SendClientMessageEx(pID, -1, "%s %s[ID:%d] te whispea: %s", WhisperMsg, RemoveUnderScore(playerid), playerid, msg);
	    	    SendClientMessageEx(playerid, -1, "%s Whispeaste a %s[ID:%d]: %s", WhisperMsg, RemoveUnderScore(pID), pID, msg);
			}
		}
		else
		{
		    SendClientMessageEx(playerid, -1, "%s Introduciste una ID inválida.", ERROR_ADMIN);
		}
	}
	else
	{
	    SendClientMessageEx(playerid, -1, "%s Utiliza: /W [ID] [Texto]", ERROR_ADMIN);
	}
	return 1;
}
CMD:w(playerid, params[]) return cmd_whisper(playerid, params);

CMD:kick(playerid, params[])
{
	if(PlayersData[playerid][Admin] >= 3)
	{
		new pID, msg[124];
		if(!sscanf(params, "us[124]", pID, msg))
		{
			if(IsPlayerConnected(pID) && pID != playerid)
			{
				if(Logged[pID] == true)
				{
					if(PlayersData[playerid][Admin] > PlayersData[pID][Admin])
					{
						SendClientMessageEx(pID, -1, "%s Haz sido kickeado del servidor por %s razón: {FF7575}%s", InfoMsg, RemoveUnderScore(playerid), msg);
		            	SendClientMessageEx(playerid, -1, "%s Haz kickeado al usuario %s [ID:%d] razón: {FF7575}%s", InfoMsg, RemoveUnderScore(pID), pID, msg);
						SetTimerEx("KickPlayerEx", 400, false, "i", pID);
						SendAdminLog(playerid, pID, 1, msg);
					}
					else
					{
						SendClientMessageEx(playerid, -1, "%s No puedes kickear a un administrador superior.", ERROR_ADMIN);
					}
				}
				else
				{
					SendClientMessageEx(playerid, -1, "%s El usuario no se encuentra conectado o no ha iniciado sesión.", ERROR_ADMIN);
				}
			}
			else
			{
				SendClientMessageEx(playerid, -1, "%s Introduciste una ID inválida.", ERROR_ADMIN);
			}
		}
		else
		{
			SendClientMessageEx(playerid, -1, "%s Utiliza: /Kick [ID] [Razón]", ERROR_ADMIN);
		}
	}
	else
    {
        SendClientMessageEx(playerid, -1, NO_ADMIN_PERMISSION);
    }
	return 1;
}

CMD:traerveh(playerid, params[])
{
	if(PlayersData[playerid][Admin] >= 3)
	{
		new vID;
		if(!sscanf(params, "i", vID))
		{
			if(vID != INVALID_VEHICLE_ID)
			{
				new Float:veX, Float:veY, Float:veZ;
				GetPlayerPos(playerid, veX, veY, veZ);
				LinkVehicleToInterior(vID, GetPlayerInterior(playerid));
				SetVehicleVirtualWorld(vID, GetPlayerVirtualWorld(playerid));
				SetVehiclePos(vID, veX, veY, veZ+0.5);
				SendClientMessageEx(playerid, -1, "%s Has traido el Vehículo ID: %d.", InfoMsg, vID);
			}
			else
			{
				SendClientMessageEx(playerid, -1, "%s Introduciste una ID inválida.", ERROR_ADMIN);
			}
		}
		else
		{
			SendClientMessageEx(playerid, -1, "%s Utiliza: /TraerVeh [ID_Veh]", ERROR_ADMIN);
		}
	}
	else
    {
        SendClientMessageEx(playerid, -1, NO_ADMIN_PERMISSION);
    }
	return 1;
}

CMD:irveh(playerid, params[])
{
	if(PlayersData[playerid][Admin] >= 3)
	{
		new vID;
		if(!sscanf(params, "i", vID))
		{
			if(vID != INVALID_VEHICLE_ID)
			{
				new Float:veX, Float:veY, Float:veZ;
				GetVehiclePos(vID, veX, veY, veZ);
				SetPlayerPos(playerid, veX, veY, veZ+2);
				SetPlayerVirtualWorld(playerid, GetVehicleVirtualWorld(vID));
				SendClientMessageEx(playerid, -1, "%s Has ido al Vehículo ID: %d.", InfoMsg, vID);
			}
			else
			{
				SendClientMessageEx(playerid, -1, "%s Introduciste una ID inválida.", ERROR_ADMIN);
			}
		}
		else
		{
			SendClientMessageEx(playerid, -1, "%s Utiliza: /IrVeh [ID_Veh]", ERROR_ADMIN);
		}
	}
	else
    {
        SendClientMessageEx(playerid, -1, NO_ADMIN_PERMISSION);
    }
	return 1;
}

CMD:congelar(playerid, params[])
{
	if(PlayersData[playerid][Admin] >= 3)
	{
		new pID;
		if(!sscanf(params, "u", pID))
		{
			if(IsPlayerConnected(pID) && playerid != pID)
			{
				if(Logged[pID] == true)
				{
					SendClientMessageEx(playerid, -1, "%s Haz congelado a %s [ID: %d]", InfoMsg, RemoveUnderScore(pID), pID);
					SendClientMessageEx(pID, -1, "%s El administrador %s te ha congelado", InfoMsg, RemoveUnderScore(playerid));
					TogglePlayerControllable(pID, 0);
				}
				else
				{
					SendClientMessageEx(playerid, -1, "%s El usuario no se encuentra conectado o no ha iniciado sesión.", ERROR_ADMIN);
				}
			}
			else
			{
				SendClientMessageEx(playerid, -1, "%s Introduciste una ID inválida.", ERROR_ADMIN);
			}
		}
		else
		{
			SendClientMessageEx(playerid, -1, "%s Utiliza: /Congelar [ID]", ERROR_ADMIN);
		}
	}
	else
    {
        SendClientMessageEx(playerid, -1, NO_ADMIN_PERMISSION);
    }
	return 1;
}

CMD:descongelar(playerid, params[])
{
	if(PlayersData[playerid][Admin] >= 3)
	{
		new pID;
		if(!sscanf(params, "u", pID))
		{
			if(IsPlayerConnected(pID) && playerid != pID)
			{
				if(Logged[pID] == true)
				{
					SendClientMessageEx(playerid, -1, "%s Haz congelado a %s [ID: %d]", InfoMsg, RemoveUnderScore(pID), pID);
					SendClientMessageEx(pID, -1, "%s El administrador %s te ha congelado", InfoMsg, RemoveUnderScore(playerid));
					TogglePlayerControllable(pID, 1);
				}
				else
				{
					SendClientMessageEx(playerid, -1, "%s El usuario no se encuentra conectado o no ha iniciado sesión.", ERROR_ADMIN);
				}
			}
			else
			{
				SendClientMessageEx(playerid, -1, "%s Introduciste una ID inválida.", ERROR_ADMIN);
			}
		}
		else
		{
			SendClientMessageEx(playerid, -1, "%s Utiliza: /Descongelar [ID]", ERROR_ADMIN);
		}
	}
	else
    {
        SendClientMessageEx(playerid, -1, NO_ADMIN_PERMISSION);
    }
	return 1;
}

CMD:respawn(playerid, params[])
{
	if(PlayersData[playerid][Admin] >= 4)
	{
		new vID;
		if(!sscanf(params, "i", vID))
		{
			if(vID != INVALID_VEHICLE_ID)
			{
				SetVehicleToRespawn(vID);
				SendClientMessageEx(playerid, -1, "%s Has respawneado el Vehículo ID: %d", InfoMsg, vID);
				SendAdminLog(playerid, vID, 3, "");
			}
			else
			{
				SendClientMessageEx(playerid, -1, "%s Introduciste una ID inválida.", ERROR_ADMIN);
			}
		}
		else
		{
			SendClientMessageEx(playerid, -1, "%s Utiliza: /Respawn [ID_Veh]", ERROR_ADMIN);
		}
	}
	else
	{
        SendClientMessageEx(playerid, -1, NO_ADMIN_PERMISSION);
    }
	return 1;
}

CMD:matar(playerid, params[])
{
	if(PlayersData[playerid][Admin] >= 4)
	{
		new pID;
		if(!sscanf(params, "u", pID))
		{
			if(IsPlayerConnected(pID) && pID != playerid)
			{
				if(Logged[pID] == true)
				{
					SetPlayerHealth(pID, 0.00);
					SendClientMessageEx(playerid, -1, "%s Has matado a %s [ID: %d].", InfoMsg, RemoveUnderScore(pID), pID);
					SendClientMessageEx(pID, -1, "%s El Administrador %s [ID: %d] te ha matado.", InfoMsg, RemoveUnderScore(playerid), playerid);
				}
				else
				{
					SendClientMessageEx(playerid, -1, "%s El usuario no se encuentra conectado o no ha iniciado sesión.", ERROR_ADMIN);
				}
			}
			else
			{
				SendClientMessageEx(playerid, -1, "%s Introduciste una ID inválida.", ERROR_ADMIN);
			}
		}
		else
		{
			SendClientMessageEx(playerid, -1, "%s Utiliza: /Matar [ID]", ERROR_ADMIN);
		}
	}
	else
    {
        SendClientMessageEx(playerid, -1, NO_ADMIN_PERMISSION);
    }
	return 1;
}

CMD:o(playerid, params[])
{
	if(PlayersData[playerid][Admin] >= 4)
	{
		new msg[256];
		if(!sscanf(params, "s[256]", msg))
		{
			new string[256];
			for(new i=0; i <= GetPlayerPoolSize(); i++)
	        {
				if(strlen(msg) > 80)
				{
					new string2[128];
					format(string2, sizeof(string2), "{FF4040}— %s", msg[80]);
					strdel(msg, 80, strlen(msg));
					format(string, sizeof(string), "%s %s: %s", AlertMsg, RemoveUnderScore(playerid), msg);
					SendClientMessageEx(i, -1, string);
					SendClientMessageEx(i, -1, string2);
				}
				else if(strlen(msg) < 80)
				{
					SendClientMessageEx(i, -1, "%s %s: %s", AlertMsg, RemoveUnderScore(playerid), msg);
				}
			}
		}
		else
		{
			SendClientMessageEx(playerid, -1, "%s Utiliza: /O [Texto]", ERROR_ADMIN);
		}
	}
	else
    {
        SendClientMessageEx(playerid, -1, NO_ADMIN_PERMISSION);
    }
	return 1;
}

CMD:mdar(playerid, params[])
{
	if(PlayersData[playerid][Admin] >= 4)
	{
		new pID, option[10], cant;
		if(!sscanf(params, "s[15]ui", option, pID, cant))
		{
			if(IsPlayerConnected(pID) && pID != playerid)
			{
				if(Logged[pID] == true)
				{
					if(!strcmp(option, "vida", true))
					{
						SendClientMessageEx(playerid, -1, "%s Le has dado %d vida al usuario %s [ID: %d].", InfoMsg, cant, RemoveUnderScore(pID), pID);
						SendClientMessageEx(playerid, -1, "%s El Administrador %s [ID: %d] te ha dado %d de vida.", InfoMsg, RemoveUnderScore(playerid), playerid, cant);
						SetPlayerHealth(pID, cant);
					}
					else if(!strcmp(option, "chaleco", true))
					{
						SendClientMessageEx(playerid, -1, "%s Le has dado %d Chaleco al usuario %s [ID: %d].", InfoMsg, cant, RemoveUnderScore(pID), pID);
						SendClientMessageEx(playerid, -1, "%s El Administrador %s [ID: %d] te ha dado %d de Chaleco.", InfoMsg, RemoveUnderScore(playerid), playerid, cant);
						SetPlayerArmour(pID, cant);
					}
					else if(!strcmp(option, "comida", true))
					{
						SendClientMessageEx(playerid, -1, "%s Le has dado %d Comida al usuario %s [ID: %d].", InfoMsg, cant, RemoveUnderScore(pID), pID);
						SendClientMessageEx(playerid, -1, "%s El Administrador %s [ID: %d] te ha dado %d de Comida.", InfoMsg, RemoveUnderScore(playerid), playerid, cant);
						PlayersData[playerid][pFood] = cant;
					}
					else if(!strcmp(option, "agua", true))
					{
						SendClientMessageEx(playerid, -1, "%s Le has dado %d Agua al usuario %s [ID: %d].", InfoMsg, cant, RemoveUnderScore(pID), pID);
						SendClientMessageEx(playerid, -1, "%s El Administrador %s [ID: %d] te ha dado %d de Agua.", InfoMsg, RemoveUnderScore(playerid), playerid, cant);
						PlayersData[playerid][pDrink] = cant;
					}
					else
					{
						SendClientMessageEx(playerid, -1, "%s Opciones disponibles: Vida | Chaleco | Comida | Agua", ERROR_ADMIN);
					}
				}
				else
				{
					SendClientMessageEx(playerid, -1, "%s El usuario no se encuentra conectado o no ha iniciado sesión.", ERROR_ADMIN);
				}
			}
			else
			{
				SendClientMessageEx(playerid, -1, "%s Introduciste una ID inválida.", ERROR_ADMIN);
			}
		}
		else
		{
			SendClientMessageEx(playerid, -1, "%s Utiliza: /MDar [Vida/Chaleco] [ID] [Cant]", ERROR_ADMIN);
		}
	}
	else
    {
        SendClientMessageEx(playerid, -1, NO_ADMIN_PERMISSION);
    }
	return 1;
}

CMD:ban(playerid, params[])
{
	if(PlayersData[playerid][Admin] >= 5)
	{
		new pID, reason[128];
		if(!sscanf(params, "us[128]", pID, reason))
		{
			if(IsPlayerConnected(pID) && pID != playerid)
			{
				if(Logged[pID] == true)
				{
					if(PlayersData[playerid][Admin] > PlayersData[pID][Admin])
					{
						PlayersData[pID][Banned] = 1;
						SendClientMessageEx(playerid, -1, "%s Has Baneado al usuario %s [ID: %d] Razón: %s", InfoMsg, RemoveUnderScore(pID), pID, reason);
						SendClientMessageEx(playerid, -1, "%s El Administrador %s [ID: %d] te ha baneado, razón: %s", AlertMsg, RemoveUnderScore(playerid), playerid, reason);
						SendClientMessageEx(playerid, -1, "%s No olvides tomar Screenshot(SS) de este mensaje en caso de apelar tú sanción.", InfoMsg);
						SetTimerEx("KickPlayerEx", 400, false, "i", pID);
						SendAdminLog(playerid, pID, 2, reason);
					}
					else
					{
						SendClientMessageEx(playerid, -1, "%s No puedes banear administradores mayores.", ERROR_ADMIN);
					}
				}
				else
				{
					SendClientMessageEx(playerid, -1, "%s El usuario no se encuentra conectado o no ha iniciado sesión.", ERROR_ADMIN);
				}
			}
			else
			{
				SendClientMessageEx(playerid, -1, "%s Introduciste una ID inválida.", ERROR_ADMIN);
			}
		}
		else
		{
			SendClientMessageEx(playerid, -1, "%s Utiliza: /Ban [ID] [Razón]", ERROR_ADMIN);
		}
	}
	else
    {
        SendClientMessageEx(playerid, -1, NO_ADMIN_PERMISSION);
    }
	return 1;
}

CMD:clearchat(playerid, params[])
{
	if(PlayersData[playerid][Admin] >= 5)
	{
		new string[150];
		format(string, sizeof(string), "%s El chat ha sido limpiado!", InfoMsg);
		for(new i = 0; i <= 30; i++)
		{
			SendClientMessageToAll(-1, "");
		}
		SendClientMessageToAll(-1, string);
	}
	else
    {
        SendClientMessageEx(playerid, -1, NO_ADMIN_PERMISSION);
    }
	return 1;
}

CMD:ircoord(playerid, params[])
{
	if(PlayersData[playerid][Admin] >= 5)
	{
		new Float:poX, Float:poY, Float:poZ;
		if(!sscanf(params, "fff", poX, poY, poZ))
		{
			SetPlayerPos(playerid, poX, poY, poZ);
			SendClientMessageEx(playerid, -1, "%s Teletransporte a: X = %0.2f | Y = %0.2f | Z = %0.2f", InfoMsg, poX, poY, poZ);
		}
		else
		{
			SendClientMessageEx(playerid, -1, "%s Utiliza: /IrCoord [X] [Y] [Z]", ERROR_ADMIN);
		}
	}
	else
	{
		SendClientMessageEx(playerid, -1, NO_ADMIN_PERMISSION);
	}
	return 1;
}

CMD:goint(playerid, params[])
{
	if(PlayersData[playerid][Admin] >= 6)
	{
		new value;
		if(!sscanf(params, "i", value))
		{
			PlayersData[playerid][pInterior] = value;
			SetPlayerInterior(playerid, value);
			SendClientMessageEx(playerid, -1, "%s Teletransporte a Interior: %d", InfoMsg, value);
		}
		else
		{
			SendClientMessageEx(playerid, -1, "%s Utiliza: /GoInt [Int]", ERROR_ADMIN);
		}
	}
	else
	{
		SendClientMessageEx(playerid, -1, NO_ADMIN_PERMISSION);
	}
	return 1;
}

CMD:govw(playerid, params[])
{
	if(PlayersData[playerid][Admin] >= 6)
	{
		new value;
		if(!sscanf(params, "i", value))
		{
			PlayersData[playerid][pVW] = value;
			SetPlayerVirtualWorld(playerid, value);
			SendClientMessageEx(playerid, -1, "%s Teletransporte a VirtualWorld: %d", InfoMsg, value);
		}
		else
		{
			SendClientMessageEx(playerid, -1, "%s Utiliza: /GoVW [VW]", ERROR_ADMIN);
		}
	}
	else
	{
		SendClientMessageEx(playerid, -1, NO_ADMIN_PERMISSION);
	}
	return 1;
}

CMD:statsex(playerid, params[])
{
	if(PlayersData[playerid][Admin] >= 6)
	{
		new pID, string1[150], string[600], ip[16];
		if(!sscanf(params, "u", pID))
		{
			if(IsPlayerConnected(pID))
	        {
		        GetPlayerIp(playerid, ip, sizeof(ip));
		        format(string, sizeof(string), "ID: %d\nNombre: %s\nCorreo: %s\nIP: %s\nAdmin: %d\nVip: %d\nVida: %f\nChaleco: %f\nSkin: %d\nEdad: %d\nFaccion: %d\nRango: %d\nDinero: %d\nBanco:", PlayersData[pID][UUID],
	 		 	GetPlayerNameEx(pID), PlayersData[pID][Mail], ip,
				PlayersData[pID][Admin], PlayersData[pID][Vip], PlayersData[pID][pHealth],
				PlayersData[pID][pArmour], PlayersData[pID][Skin], PlayersData[pID][Age],
				PlayersData[pID][Faction], PlayersData[pID][fRank], PlayersData[pID][Money],
				PlayersData[pID][BankAccount]);
				format(string1, sizeof(string1), "{FF0984}Estadisticas {FFFFFF}» {FF8000}%s", GetPlayerNameEx(pID));
				ShowPlayerDialog(playerid, 300, DIALOG_STYLE_MSGBOX, string1, string, "Aceptar", "");
			}
		}
		else
		{
			SendClientMessageEx(playerid, -1, "%s Utiliza: /StatsEx [ID]", ERROR_ADMIN);
		}
	}
	else
	{
		SendClientMessageEx(playerid, -1, NO_ADMIN_PERMISSION);
	}
	return 1;
}

CMD:setskin(playerid, params[])
{
	if(PlayersData[playerid][Admin] >= 6)
	{
		new pID, Sk;
		if(!sscanf(params, "ui", pID, Sk))
		{
			if(IsPlayerConnected(pID) && Logged[pID] == true)
			{
				PlayersData[pID][Skin] = Sk;
				SetPlayerSkin(pID, Sk);
				SendClientMessageEx(playerid, -1, "%s Colocaste el Skin %d a %s [ID: %d]", InfoMsg, Sk, RemoveUnderScore(pID), pID);
				SendClientMessageEx(pID, -1, "%s El Administrador %s [ID: %d] te colocó el Skin %d", InfoMsg, RemoveUnderScore(playerid), playerid, Sk);
			}
			else
			{
				SendClientMessageEx(playerid, -1, "%s Introduciste una ID inválida.", ERROR_ADMIN);
			}
		}
		else
		{
			SendClientMessageEx(playerid, -1, "%s Utiliza: /SetSkin [ID] [Skin]", ERROR_ADMIN);
		}
	}
	else
	{
		SendClientMessageEx(playerid, -1, NO_ADMIN_PERMISSION);
	}
	return 1;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CMD:dsmsg(playerid, params[])
{
	if(PlayersData[playerid][Admin] >= 7)
	{
		new string[120];
		if(!sscanf(params, "s[120]", string))
		{
			new DCC_Channel:canal = DCC_FindChannelById("864885416715616304");
			format(string, sizeof(string), "**[SA-MP]:** %s", string);
			DCC_SendChannelMessage(canal, FixSpecialString(string));
		}
		else
		{
			SendClientMessageEx(playerid, -1, "%s Utiliza: /DsMsg [Texto]", ERROR_ADMIN);
		}
	}
	else
	{
		SendClientMessageEx(playerid, -1, NO_ADMIN_PERMISSION);
	}
	return 1;
}

CMD:staff(playerid, params[])
{
	if(PlayersData[playerid][Admin] >= 7)
	{
		new pID, rank;
		if(!sscanf(params, "ui", pID, rank))
		{
			if(IsPlayerConnected(pID) && pID != playerid)
			{
				if(Logged[pID] == true)
				{
					if(PlayersData[playerid][Admin] >= PlayersData[pID][Admin])
					{
						if(rank > 0 && rank < 10)
						{
							PlayersData[pID][Admin] = rank;
							new string[3];
							format(string, sizeof(string), "%d", rank);
							SendAdminLog(playerid, pID, 7, string);
						}
						else
						{
							SendClientMessageEx(playerid, -1, "%s El Rango debe estar entre 1 y 9.", ERROR_ADMIN);
						}
					}
					else
					{
						SendClientMessageEx(playerid, -1, "%s No puedes modificar el rango Staff de un superior..", ERROR_ADMIN);
					}
				}
				else
				{
					SendClientMessageEx(playerid, -1, "%s El usuario no se encuentra conectado o no ha iniciado sesión.", ERROR_ADMIN);
				}
			}
			else
			{
				SendClientMessageEx(playerid, -1, "%s Introduciste una ID inválida.", ERROR_ADMIN);
			}
		}
		else
		{
			SendClientMessageEx(playerid, -1, "%s Utiliza: /Staff [ID] [Rango].", ERROR_ADMIN);
		}
	}
	else
	{
		SendClientMessageEx(playerid, -1, NO_ADMIN_PERMISSION);
	}
	return 1;
}

CMD:ccambiar(playerid, params[])
{
	if(PlayersData[playerid][Admin] >= 7)
	{
	    new vID, mID;
	    if(!sscanf(params, "ii", vID, mID))
	    {
			new query[70], Float:vehcX, Float:vehcY, Float:vehcZ, Float:vA;
			format(query, sizeof(query), "UPDATE vehicles SET `Model` = '%d' WHERE `IDDB` ='%d'", mID, vID);
			mysql_query(g_MySQL, query);
			GetVehicleZAngle(vID, vA);
			GetVehiclePos(vID, vehcX, vehcY, vehcZ);
			DestroyVehicle(vID);
			VehData[vID][VehID] = CreateVehicle(mID, vehcX, vehcY, vehcZ, vA, 0, 0, -1);
			VehData[vID][Model] = mID;
			SendClientMessageEx(playerid, -1, "%s Cambiaste a modelo: %d el coche ID: %d", InfoMsg, mID, vID);
	    	SendAdminLog(playerid, vID, 9, "");
		}
	}
	else
	{
		SendClientMessageEx(playerid, -1, "%s No tienes autorización.", InfoMsg);
	}
	return 1;
}

CMD:ecoche(playerid, params[])
{
	if(PlayersData[playerid][Admin] >= 7)
	{
		new option[15];
		if(!sscanf(params, "s[15]", option))
		{
			if(!strcmp(option, "respawn", true))
			{
				for(new i=0; i <= GetVehiclePoolSize(); i++)
				{
				    if(i != INVALID_VEHICLE_ID)
				    {
				        SetVehiclePos(i, VehData[i][vPx], VehData[i][vPy], VehData[i][vPz]);
				    }
				}
				SendClientMessageToAll(-1, "{008080}[Servidor]: Se Realizó un Respawn General de todos los coches.");
			}
			else if(!strcmp(option, "gasolina", true))
			{
			    for(new i=0; i <= GetVehiclePoolSize(); i++)
				{
				    if(i != INVALID_VEHICLE_ID)
				    {
				        VehData[i][Fuel] = 100.0;
				    }
				}
			    SendClientMessageToAll(-1, "{008080}[Servidor]: Se Realizó un Llenado de Gasolina de todos los coches.");
			}
			else if(!strcmp(option, "aceite", true))
			{
			    for(new i=0; i <= GetVehiclePoolSize(); i++)
				{
				    if(i != INVALID_VEHICLE_ID)
				    {
				        VehData[i][Aceite] = 100.0;
				    }
				}
				SendClientMessageToAll(-1, "{008080}[Servidor]: Se Realizó un Llenado de Aceite de todos los coches.");
			}
			else if(!strcmp(option, "reparar", true))
			{
			    for(new i=0; i <= GetVehiclePoolSize(); i++)
				{
				    if(i != INVALID_VEHICLE_ID)
				    {
				        RepairVehicle(i);
				        VehData[i][Status] = 1000.0;
				    }
				}
				SendClientMessageToAll(-1, "{008080}[Servidor]: Se Realizó un Reparado de todos los coches.");
			}
			else
			{
			    SendClientMessageEx(playerid, -1, "%s Opciones: Respawn - Gasolina - Aceite - Reparar", ERROR_ADMIN);
			}
		}
		else
		{
		    SendClientMessageEx(playerid, -1, "%s Utiliza: /ECoche [Respawn/Gasolina/Aceite/Reparar]", ERROR_ADMIN);
		}
	}
	else
	{
	    SendClientMessageEx(playerid, -1, NO_ADMIN_PERMISSION);
	}
	return 1;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CMD:mepuerta(playerid, params[])
{
	if(PlayersData[playerid][Admin] >= 8)
	{
		new string[500];
		strcat(string, "{BFE44E}» {FFFFFF}Ir a una puerta específica.\n{BFE44E}» {FFFFFF}Crear una puerta nueva.\n");
		strcat(string, "{BFE44E}» {FFFFFF}Eliminar una puerta existente.\n{BFE44E}» {FFFFFF}Obtener el ID de una puerta.\n");
		strcat(string, "{BFE44E}» {FFFFFF}Cambiar nombre de puerta.\n{BFE44E}» {FFFFFF}Cerrar una puerta.\n");
		strcat(string, "{BFE44E}» {FFFFFF}Mover una puerta (INTERIOR/EXTERIOR).\n{BFE44E}» {FFFFFF}Cambiar VirtualWorld de una puerta.\n");
		strcat(string, "{BFE44E}» {FFFFFF}Asignar Faccion.\n{BFE44E}» {FFFFFF}Cambiar Tipo de Puerta.");
		ShowPlayerDialog(playerid, MENU_PUERT, DIALOG_STYLE_LIST, "{0080FF}Configuración {FFFFFF}» {FF4646}Puertas", string, "Aceptar", "Cancelar");
	}
	else
	{
	    SendClientMessageEx(playerid, -1, NO_ADMIN_PERMISSION);
	}
	return 1;
}

CMD:mefaccion(playerid, params[])
{
	if(PlayersData[playerid][Admin] >= 8)
	{
		new string[500];
		strcat(string, "{BFE44E}» {FFFFFF}Crear una Facción Nueva.\n{BFE44E}» {FFFFFF}Editar una Facción.\n");
		strcat(string, "{BFE44E}» {FFFFFF}Eliminar una Facción.\n{BFE44E}» {FFFFFF}Añadir un Rango a Facción.\n");
		strcat(string, "{BFE44E}» {FFFFFF}Editar Rango Facción.\n{BFE44E}» {FFFFFF}Ver Info Facción.\n");
		ShowPlayerDialog(playerid, DIALOG_GLOBAL_INPUT, DIALOG_STYLE_LIST, "{0080FF}Configuración {FFFFFF}» {FF4646}Facciones", string, "Aceptar", "Cancelar");
		SetPVarString(playerid, "InputType", "FaccionMenu");
	}
	else
	{
		SendClientMessageEx(playerid, -1, NO_ADMIN_PERMISSION);
	}
	return 1;
}

CMD:menegocio(playerid, params[])
{
	if(PlayersData[playerid][Admin] >= 8)
	{
        new string[220];
		strcat(string, "{BFE44E}» {FFFFFF}Crear Negocio Nuevo.\n{BFE44E}» {FFFFFF}Cambiar Tipo de Negocio.\n");
		strcat(string, "{BFE44E}» {FFFFFF}Cambiar Precio de Negocio.\n{BFE44E}» {FFFFFF}Obtener ID de Negocio.\n{BFE44E}» {FFFFFF}Ir a un Negocio.");
		ShowPlayerDialog(playerid, MENU_NEGOCIO, DIALOG_STYLE_LIST, "{0080FF}Configuración {FFFFFF}» {FF4646}Negocios", string, "Aceptar", "Cancelar");
	}
	else
	{
	    SendClientMessageEx(playerid, -1, NO_ADMIN_PERMISSION);
	}
	return 1;
}

CMD:paydaynow(playerid, params[])
{
	if(PlayersData[playerid][Admin] >= 8)
	{
		SendClientMessageEx(playerid, -1, "%s Haz forzado el PayDay.", InfoMsg);
		PayDay();
		SendAdminLog(playerid, 0, 8, "");
	}
	else
	{
		SendClientMessageEx(playerid, -1, NO_ADMIN_PERMISSION);
	}
	return 1;
}

CMD:ccoche(playerid, params[])
{
	if(PlayersData[playerid][Admin] >= 8)
	{
	    new model, tipo, owner;
		if(!sscanf(params, "iii", model, tipo, owner))
		{
            CreateVehicleEx(playerid, model, tipo, owner);
            SendClientMessageEx(playerid, -1, "%s Haz creado un coche Modelo: %d", InfoMsg, model);
		}
		else
		{
			SendClientMessageEx(playerid, -1, "%s Utiliza: /CCoche [Modelo] [Tipo] [Owner]", ERROR_ADMIN);
		}
	}
	else
	{
		SendClientMessageEx(playerid, -1, NO_ADMIN_PERMISSION);
	}
	return 1;
}

CMD:faccion(playerid, params[])
{
	//AQUI
	return 1;
}

CMD:gmx(playerid, params[])
{
	if(PlayersData[playerid][Admin] >= 9)
	{
		for(new i = 0; i < GetPlayerPoolSize(); i++)
		{
			if(Logged[i] == true)
			{
				SavePlayerData(i, 0);
			}
		}
		SendRconCommand("gmx");
	}
	return 1;
}

CMD:aforce(playerid, params[]) 
{
	if(PlayersData[playerid][Admin] >= 9)
	{
		new option[15];
		if(!sscanf(params, "s[15]", option))
		{
			if(!strcmp(option, "Seguro", true))
			{
				new NearVeh;
				if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER || GetPlayerState(playerid) == PLAYER_STATE_PASSENGER)
				{
					NearVeh=GetPlayerVehicleID(playerid);
				}
				else
				{
					NearVeh=GetNearestVehicle(playerid, 5.0);
				}
				if(NearVeh != INVALID_VEHICLE_ID)
				{
					new engine, lights, alarm, doors, bonnet, boot, objective;
					GetVehicleParamsEx(NearVeh, engine, lights, alarm, doors, bonnet, boot, objective);
					if(VehData[NearVeh][Key] == 0)
					{
						SetVehicleParamsEx(NearVeh, engine, lights, alarm, VEHICLE_PARAMS_OFF, bonnet, boot, objective);
						SendClientMessageEx(playerid, -1, "%s Abriste tu Coche.", InfoMsg);
						VehData[NearVeh][Key] = 1;
						PlayerPlaySound(playerid,1154,0.0,0.0,10.0);
						if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER){    PlayerTextDrawHide(playerid, Vel_Lock[playerid]);}
					}
					else
					{
						SetVehicleParamsEx(NearVeh, engine, lights, alarm, VEHICLE_PARAMS_ON, bonnet, boot, objective);
						SendClientMessageEx(playerid, -1, "%s Cerraste tu Coche.", InfoMsg);
						VehData[NearVeh][Key] = 0;
						PlayerPlaySound(playerid, 1154, 0.0, 0.0, 10.0);
						if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER){    PlayerTextDrawShow(playerid, Vel_Lock[playerid]);}
					}
					new query[250];
					mysql_format(g_MySQL, query, sizeof(query), "UPDATE vehicles SET `vKey`='%d' WHERE `IDDB` = '%d'",
					VehData[NearVeh][Key], VehData[NearVeh][IDDB]);
					new Cache:result = mysql_query(g_MySQL, query);
					cache_delete(result);
				}
				else
				{
					SendClientMessageEx(playerid, -1, "%s No te encuentras cerca de un coche.", ERROR_ADMIN);
				}
			}
			else if(!strcmp(option, "Respawn", true))
			{
				if(IsPlayerInAnyVehicle(playerid))
				{
					new vID = GetPlayerVehicleID(playerid);
					new query[500], Float:posi[3];
					
					GetPlayerPos(playerid, posi[0], posi[1], posi[2]);
					mysql_format(g_MySQL, query, sizeof(query), "UPDATE vehicles SET `vX` = '%f', `vY` = '%f', `vZ` = '%f' WHERE `IDDB` = '%d'", posi[0], posi[1], posi[2], VehData[VehData[vID][VehID]][IDDB]);
					new Cache:result = mysql_query(g_MySQL, query);
					VehData[VehData[vID][VehID]][vX] = posi[0];
					VehData[VehData[vID][VehID]][vY] = posi[1];
					VehData[VehData[vID][VehID]][vZ] = posi[2];
					VehData[VehData[vID][VehID]][vPx] = posi[0];
					VehData[VehData[vID][VehID]][vPy] = posi[1];
					VehData[VehData[vID][VehID]][vPz] = posi[2];
					cache_delete(result);
					SendClientMessageEx(playerid, -1, "%s Cambiaste el Respawn del Coche.", InfoMsg);
				}
				else
				{
					SendClientMessageEx(playerid, -1, "%s No te encuentras dentro de ningún vehículo.", ERROR_ADMIN);
				}
			}
		}
		else
		{
			SendClientMessageEx(playerid, -1, "%s Utiliza: /AForce [Opcion]", ERROR_ADMIN);
		}
	}
	else
	{
		SendClientMessageEx(playerid, -1, NO_ADMIN_PERMISSION);
	}
	return 1;
}
//////////////////////////////////////////////////////////////////////////////////////////////////77
CMD:mapeos(playerid, params[])
{
	if(PlayersData[playerid][Admin] >= 7)
	{
	    SendClientMessageEx(playerid, 0, "{D9E35B}|________________________________[ Mapper ]________________________________|");
	    SendClientMessageEx(playerid, 0, "{AEAEAE} /Map - /EditMap - /MovMap - /TMap - /DelMap - /IdMap");
	}
	else
	{
		SendClientMessageEx(playerid, -1, NO_ADMIN_PERMISSION);
	}
	return 1;
}

CMD:map(playerid, params[])
{
	if(PlayersData[playerid][Admin] >= 5 || PlayersData[playerid][Esp] >= 1)
	{
	    ShowPlayerDialog(playerid, DIALOG_MAPEAR, DIALOG_STYLE_INPUT, "{FF0984}Mapeo {FFFFFF}» {FF8000}Union {0080FF}Gamer", "{FF8000}Union {0080FF}Gamer{FFFFFF}\n\nIngresa la ID de un objeto valido.", "Insertar", "Cancelar");
	}
	else
	{
	    SendClientMessageEx(playerid, -1, "%s No tienes autorización.", InfoMsg);
	}
	return 1;
}

CMD:editmap(playerid, params[])
{
	if(PlayersData[playerid][Admin] >= 5 || PlayersData[playerid][Esp] >= 1)
	{
	    new iDO;
		if(!sscanf(params, "i", iDO))
		{
			if(iDO >= 0)
			{
				if(IsValidDynamicObject(Objetos[iDO][ID]))
				{
					EditDynamicObject(playerid, Objetos[iDO][ID]);
					Editando[playerid] = 1;
					EditObj[playerid] = iDO;
					SendClientMessageEx(playerid, -1, "%s Estás editando el Objeto ID: %d | Modelo: %d", MapMsg, iDO, Objetos[iDO][idobjeto]);
				}
				else
				{
					SendClientMessageEx(playerid, -1, "%s Este ID de Objeto es inválido o no existe.", InfoMsg);
				}
			}
			else
			{
				SendClientMessageEx(playerid, -1, "%s El ID debe ser mayor o igual que 0", InfoMsg);
			}
		}
		else
		{
			SendClientMessageEx(playerid, -1, "%s Utiliza: /EditMap [ID_Objeto]", InfoMsg);
		}
	}
	else
	{
		SendClientMessageEx(playerid, -1, "%s No tienes autorización.", InfoMsg);
	}
	return 1;
}

CMD:movmap(playerid, params[])
{
	if(PlayersData[playerid][Admin] >= 5 || PlayersData[playerid][Esp] >= 1)
	{
	    new iDO;
		if(!sscanf(params, "i", iDO))
		{
			if(iDO >= 0)
			{
				if(IsValidDynamicObject(Objetos[iDO][ID]))
				{
					EditDynamicObject(playerid, Objetos[iDO][ID]);
					Editando[playerid] = 3;
					EditObj[playerid] = iDO;
					SendClientMessageEx(playerid, -1, "%s Estás editando el Recorrido del Objeto ID: %d | Modelo: %d", MapMsg, iDO, Objetos[iDO][idobjeto]);
				}
				else
				{
					SendClientMessageEx(playerid, -1, "%s Este ID de Objeto es inválido o no existe.", InfoMsg);
				}
			}
			else
			{
				SendClientMessageEx(playerid, -1, "%s El ID debe ser mayor o igual que 0", InfoMsg);
			}
		}
		else
		{
			SendClientMessageEx(playerid, -1, "%s Utiliza: /MovMap [ID_Objeto]", InfoMsg);
		}
	}
	else
	{
		SendClientMessageEx(playerid, -1, "%s No tienes autorización.", InfoMsg);
	}
	return 1;
}

CMD:tmap(playerid, params[])
{
	if(PlayersData[playerid][Admin] >= 5 || PlayersData[playerid][Esp] >= 1)
	{
	    new iDO, type, value;
		if(!sscanf(params, "iii", iDO, type, value))
		{
			if(iDO >= 0)
			{
				if(IsValidDynamicObject(Objetos[iDO][ID]))
				{
					Objetos[iDO][Tipo] = type;
					Objetos[iDO][oOwner] = value;
					SendClientMessageEx(playerid, -1, "%s Seteaste el Tipo: %d al ID: %d", MapMsg, type, iDO);
				}
				else
				{
					SendClientMessageEx(playerid, -1, "%s Este ID de Objeto es inválido o no existe.", InfoMsg);
				}
			}
			else
			{
				SendClientMessageEx(playerid, -1, "%s El ID debe ser mayor o igual que 0", InfoMsg);
			}
		}
		else
		{
			SendClientMessageEx(playerid, -1, "%s Utiliza: /TMap [ID_Objeto] [1Publico/2Faccion] [Owner]", InfoMsg);
		}
	}
	else
	{
		SendClientMessageEx(playerid, -1, "%s No tienes autorización.", InfoMsg);
	}
	return 1;
}

CMD:delmap(playerid, params[])
{
	if(PlayersData[playerid][Admin] >= 5 || PlayersData[playerid][Esp] >= 1)
	{
		new iDO;
		if(!sscanf(params, "d", iDO))
		{
		    if(iDO >= 0 || iDO <= MAX_OBJETOS)
		    {
				if(IsValidDynamicObject(iDO))
				{
                    SendClientMessageEx(playerid, -1, "%s Haz eliminado el Objeto ID: %d | Modelo: %d", MapMsg, iDO, Objetos[iDO][idobjeto]);
					new query[150];
					mysql_format(g_MySQL, query, sizeof(query), "DELETE FROM `objects` WHERE `ID_DATABASE` = '%d'", Objetos[iDO][IDDB]);
					new Cache:result=mysql_query(g_MySQL, query);
					mysql_format(g_MySQL, query, sizeof(query), "ALTER TABLE `objects` AUTO_INCREMENT = 1;");
					result = mysql_query(g_MySQL, query);
					cache_delete(result);

					DestroyDynamicObject(Objetos[iDO][ID]);

					Objetos[iDO][ID] = 0;
					Objetos[iDO][idobjeto] = 0;
					Objetos[iDO][xobjeto] = 0;
					Objetos[iDO][yobjeto] = 0;
					Objetos[iDO][zobjeto] = 0;
					Objetos[iDO][rotx] = 0;
					Objetos[iDO][roty] = 0;
					Objetos[iDO][rotz] = 0;
					Objetos[iDO][vwobjeto] = 0;
					Objetos[iDO][intobjeto] = 0;
					Objetos[iDO][Owner] = 0;
					Objetos[iDO][IDDB] = 0;
                    Objetos[iDO][Tipo] = 0;
                    Objetos[iDO][oOwner] = 0;
                    Objetos[iDO][oPosX] = 0;
                    Objetos[iDO][oPosY] = 0;
                    Objetos[iDO][oPosZ] = 0;
                    Objetos[iDO][oRotX] = 0;
                    Objetos[iDO][oRotY] = 0;
                    Objetos[iDO][oRotZ] = 0;
				}
				else
				{
					SendClientMessageEx(playerid, -1, "%s Este ID de Objeto es inválido o no existe.", InfoMsg);
				}
			}
			else
			{
			    SendClientMessageEx(playerid, -1, "%s El ID debe ser Mayor o igual a 0 y menor o igual a %d.", InfoMsg, MAX_OBJETOS);
			}
		}
		else
		{
			SendClientMessageEx(playerid, -1, "%s Utiliza: /DelMap [ID_Objeto]", InfoMsg);
		}
	}
	else
	{
		SendClientMessageEx(playerid, -1, "%s No tienes autorización.", InfoMsg);
	}
	return 1;
}

CMD:idmap(playerid, params[])
{
	if(PlayersData[playerid][Admin] >= 5 || PlayersData[playerid][Esp] >= 1)
	{
		for(new i = 0; i <= TObjetos; i++)
		{
			if(IsPlayerInRangeOfPoint(playerid, 7.0, Objetos[i][xobjeto], Objetos[i][yobjeto], Objetos[i][zobjeto]))
			{
				SendClientMessageEx(playerid, -1, "%s El Objeto más cercano tiene la ID: %d", MapMsg, i);
			}
		}
	}
	else
	{
		SendClientMessageEx(playerid, -1, "%s No tienes autorización.", InfoMsg);
	}
	return 1;
}