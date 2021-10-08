#include <zcmd>
#include <sscanf2>
#include <mselection>
#include <core/player/data>
#include <gui/hud/chat>
#include <gui/hud/textdraw>
#include <core/server/main>
#include <utils/system/vehicles>

#define         DIALOG_CONFIG           100
#define         DIALOG_COMPRAR247       18
#define         DIALOG_COMIDA           19
#define         DIALOG_ELECTRONICA      20

/*==============================	[		Stocks		]	==============================*/


/*==============================	[		Commands		]	==============================*/
CMD:ayuda(playerid, params[])
{
    new option[15];
	if(!sscanf(params,"s[15]",option))
	{
        if(!strcmp(option, "rol", true))
        {
            SendClientMessageEx(playerid, -1, "{C0C0C0}|____________________________________ {C9FF80}Centro de Ayuda {C0C0C0}____________________________________|");
            SendClientMessageEx(playerid, -1, "%s /Me - /Intertar - /Env - /Gritar - /Susurro - /B", HelpMsg);
        }
        else if(!strcmp(option, "coche", true))
        {
            SendClientMessageEx(playerid, -1, "{C0C0C0}|____________________________________ {C9FF80}Centro de Ayuda {C0C0C0}____________________________________|");
            SendClientMessageEx(playerid, -1, "%s /Seguro - /Luces - /Cinturon - /Llenar Combustible", HelpMsg);
			SendClientMessageEx(playerid, 0, "{BE7E7E}Presiona 'N' para encender/apagar el Motor.");
			SendClientMessageEx(playerid, 0, "{BE7E7E}Presiona 'Q' y 'E' para luces direccionales.");
		}
        else if(!strcmp(option, "negocio", true))
		{
            SendClientMessageEx(playerid, -1, "{C0C0C0}|____________________________________ {C9FF80}Centro de Ayuda {C0C0C0}____________________________________|");
            SendClientMessageEx(playerid, -1, "%s /Comprar", HelpMsg);
		}
		else if(!strcmp(option, "trabajo", true))
		{
            SendClientMessageEx(playerid, -1, "{C0C0C0}|____________________________________ {C9FF80}Centro de Ayuda {C0C0C0}____________________________________|");
            SendClientMessageEx(playerid, -1, "%s /Trabajar - /Renunciar - /Ruta [Iniciar/Fin]", HelpMsg);
		}
        else
        {
            SendClientMessageEx(playerid, -1, "%s ConstrucciÛn...", InfoMsg);
        }
    }
    else
    {
        SendClientMessageEx(playerid, -1, "{C0C0C0}|____________________________________ {C9FF80}Centro de Ayuda {C0C0C0}____________________________________|");
        SendClientMessageEx(playerid, -1, "%s /Cuenta - /Animaciones - /Copyright - /DNI - /ATM - /Pagar - /Comprar", HelpMsg);
        SendClientMessageEx(playerid, -1, "%s /Ayuda Rol, /Ayuda Coche, /Ayuda Negocio, /Ayuda Trabajo", HelpMsg);
    }
    return 1;
}

CMD:cuenta(playerid, params[])
{
    if(IsPlayerConnected(playerid) && Logged[playerid] == true)
    {
        new str[256+1];
        format(str, sizeof(str), "{F2FF00}1. {FFFFFF}Cambiar ContraseÒa\n{F2FF00}2. {FFFFFF}Cambiar Correo ElectrÛnico\n{F2FF00}3. {FFFFFF}Cambiar Edad\n{F2FF00}4. {FFFFFF}Cambiar Acento\n{F2FF00}5. {FF0000}Reiniciar Cuenta");
        ShowPlayerDialog(playerid, DIALOG_CONFIG, DIALOG_STYLE_LIST, "{0080FF}ConfiguraciÛn {FFFFFF}ª {FF8000}Cuenta", str, "{00D200}ª", "{FF0000}X");
    }
    else
    {
        SendClientMessageEx(playerid, -1, "%s Has sido silenciado o no has ingresado al Servidor.", InfoMsg);
    }
    return 1;
}

CMD:animaciones(playerid, params[])
{
    new string[900];
	strcat(string, "{8080FF}- Animaciones disponibles:\n\n");
	strcat(string, "{FFFFFF}/rendirse /hablar /paja /irsecortao /arrestado /apuntar /reirse /encender\n/vigilar /recostarse ");
	strcat(string, "{FFFFFF}/pararse /cubrirse /vomitar\n/cenar /chao /palmada /agonizar /traficar /beso /crack /mear\n");
	strcat(string, "{FFFFFF}/sentarse /depie /fokear /siquiero /noquiero /comerciar /taichi /beber\n/boxear /fuerza /pelea /lanzar ");
	strcat(string, "{FFFFFF}/llorar /detener /rapear /alzar\n/bomba /sapiar /asiento /asiento2 /depie2 /mmm /saludo [1-4] ");
	strcat(string, "{FFFFFF}/echarse\n/asientosexi /danzar [1-12] /taxi /seacabo /asco /quepa /wooo /quepasa\n/comodo /p1 /stop ");
    strcat(string, "{FFFFFF}/betasex [1-18] /betasex1 [1-8]\n\n{8080FF}Presione la letra 'F' para detener las animaciones.");
    ShowPlayerDialog(playerid, 404, DIALOG_STYLE_MSGBOX, "{CE0000}Lista {FFFFFF}ª {9D9DFF}Animaciones", string, "Aceptar", "");
    return 1;
}

CMD:facciones(playerid, params[])
{
	new string[800];
	format(string, sizeof(string), "Faccion\tID\tTipo\n%s", FactionList());
    ShowPlayerDialog(playerid, 404, DIALOG_STYLE_TABLIST_HEADERS, "Lista de Facciones", string, "Ok","");
	return 1;
}

CMD:copyright(playerid, params[])
{
    new MsgDialogCopyright[500];
	format(MsgDialogCopyright, sizeof(MsgDialogCopyright),
	"{00F50A}EspecÌficaciones:\n\n{00A5FF}VersiÛn: {F0F0F0}%s\n",
	Server_Version);
	strcat(MsgDialogCopyright, "{00A5FF}Desarrollo: {F0F0F0}Equipo de UnionGamers.\n\n");
	strcat(MsgDialogCopyright, "{F5FF00}Agradecimientos: \n{F0F0F0}San Andreas Multiplayer (SA-MP)\n{F0F0F0}Rockstar Games");
	strcat(MsgDialogCopyright, "\n\n\n{F5FF00}Copyright © 2021 UnionGamers. Todos los derechos reservados.");
	ShowPlayerDialog(playerid, 404, DIALOG_STYLE_MSGBOX, "{00A5FF}Copyright {FFFFFF}© {0080FF}UnionGamers", MsgDialogCopyright, "Aceptar", "");
    return 1;
}

CMD:dni(playerid, params[])
{
	new pID;
	if(!sscanf(params, "u", pID))
	{
		if(IsPlayerConnected(pID))
		{
		    new Float:pPos[3];
		    GetPlayerPos(pID, pPos[0], pPos[1], pPos[2]);
			if(IsPlayerInRangeOfPoint(playerid, 4.0, pPos[0], pPos[1], pPos[2]))
			{
				ShowDNI(playerid, pID);
				SendClientMessageEx(pID, -1, "%s El jugador %s te ha mostrado su DNI", InfoMsg, RemoveUnderScore(playerid));
				SendClientMessageEx(playerid, -1, "%s le haz mostrado tu DNI a %s", InfoMsg, RemoveUnderScore(pID));
			}
			else
			{
				SendClientMessageEx(playerid, -1, "%s El jugador est· demasiado lejos.", InfoMsg);
			}
		}
		else
		{
		    SendClientMessageEx(playerid, -1, "%s Este Jugador no se encuentra conectado.", InfoMsg);
		}
	}
	else
	{
	    SendClientMessageEx(playerid, -1, "%s Utiliza: /DNI [ID]", InfoMsg);
	}
	return 1;
}

CMD:atm(playerid, params[])
{
	if(IsPlayerNearCajero(playerid) == 1)
	{
		new string[128];
		format(string, sizeof(string), "%s", GetPlayerNameEx(playerid));
		PlayerTextDrawSetString(playerid, bank_name[playerid], string);
		format(string, sizeof(string), "#%d", PlayersData[playerid][ID]);
		PlayerTextDrawSetString(playerid, bank_account[playerid], string);
		format(string, sizeof(string), "~G~$~W~%d", PlayersData[playerid][BankAccount]);
		PlayerTextDrawSetString(playerid, bank_money[playerid], string);
		ShowBankUI(playerid);
		SelectTextDraw(playerid, 0xA3B4C5FF);
		TempInfo[playerid][InATM] = true;
	}
	else
	{
	    SendClientMessageEx(playerid, -1, "%s No te encuentras cerca de ning˙n Cajero.", InfoMsg);
	}
	return 1;
}

CMD:pagar(playerid, params[])
{
	new pID, cant;
	if(!sscanf(params, "ui", pID, cant))
	{
		if(IsPlayerConnected(pID) && Logged[pID] == true)
		{
			if(cant > 0)
			{
				if(PlayersData[playerid][Money] >= cant)
				{
					new Float:pay[3];
					GetPlayerPos(playerid, pay[0], pay[1], pay[2]);
					if(IsPlayerInRangeOfPoint(pID, 4.0, pay[0], pay[1], pay[2]))
					{
						PlayersData[playerid][Money] -= cant;
						PlayersData[pID][Money] += cant;
						GivePlayerMoney(playerid, -cant);
						GivePlayerMoney(pID, cant);

						SendClientMessageEx(playerid, -1, "%s Le has pagado $%d a %s [ID: %d]", InfoMsg, cant, RemoveUnderScore(pID), pID);
						SendClientMessageEx(pID, -1, "%s %s [ID: %d] te ha pagado $%d", InfoMsg, RemoveUnderScore(playerid), playerid, cant);
					}
					else
					{
						SendClientMessageEx(playerid, -1, "%s El usuario no se encuentra cerca de ti.", InfoMsg);
					}
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
		else
		{
			SendClientMessageEx(playerid, -1, "%s Este jugador no se encuentra conectado.", InfoMsg);
		}
	}
	else
	{
		SendClientMessageEx(playerid, -1, "%s Utiliza /Pagar [ID] [Cantidad]", InfoMsg);
	}
	return 1;
}

CMD:comprar(playerid, params[])
{
	new option[15];
	if(!sscanf(params, "s[15]", option))
	{
	    if(!strcmp(option, "negocio", true))
	    {
			SendClientMessageEx(playerid, -1, "{NO_SIGNAL}");
			/*
			new nid = GetNearNegocio(playerid);
			if(nid == 666666)
			{
			    SendClientMessageEx(playerid, -1, "%s No te encuentras cerca de ningun Negocio.", InfoMsg);
			}
			else
			{
			    if(Negocios[nid][nOwnerID] == 0)
			    {
					if(PlayersData[playerid][BancoB] >= Negocios[nid][nPrice])
					{
					    PlayersData[playerid][BancoB] -= Negocios[nid][nPrice];
						FaccData[0][Money] += Negocios[nid][nPrice];
					    SendClientMessageEx(playerid, -1, "%s Haz comprado el Negocio (ID: %d) por un precio de: $%d.", InfoMsg, Negocios[nid][nID], Negocios[nid][nPrice]);
						new string[128];
						format(string, sizeof(string), "%s", NombreJugador(playerid));
						Negocios[nid][nOwnerN] = string;
						format(string, sizeof(string), "Negocio de %s", NombreJugador(playerid));
						Negocios[nid][nName] = string;
						Negocios[nid][nOwnerID] = PlayersData[playerid][IDDB];
						new tipo[20], labelN[300];
						switch(Negocios[nid][nType])
						{
							case 1:{    tipo="24/7";}   case 2:{    tipo="Ropa";}   case 3:{    tipo="Comida";}   case 4:{    tipo="ElectrÛnica";}   case 5:{    tipo="Armeria";}
						}
						format(labelN, sizeof(labelN), "{FFFFFF}%s\n{B8D900}DueÒo: {FFFFFF}%s\n{B8D900}Tipo: {FFFFFF}%s\n{B8D900}Acceso: {FFFFFF}%d\n{B8D900}DirecciÛn: {FFFFFF}GN-%d", Negocios[nid][nName], Negocios[nid][nOwnerN], tipo, Negocios[nid][nEntrada], Negocios[nid][nID]);
						UpdateDynamic3DTextLabelText(LabelNE[nid], 0xF0CC00FF, labelN);
						UpdateDynamic3DTextLabelText(LabelNI[nid], 0xF0CC00FF, labelN);
					}
					else
					{
					    SendClientMessageEx(playerid, -1, "%s No tienes suficiente saldo en tu cuenta bancaria.", InfoMsg);
					}
			    }
			    else
			    {
			        SendClientMessageEx(playerid, -1, "%s Este negocio no est· en Venta.", InfoMsg);
			    }
			}*/
		}
		else if(!strcmp(option, "nada", true))
		{
			SendClientMessageEx(playerid, -1, "Nada.", InfoMsg);
		}
	}
	else
	{
	    if(EnNegocio[playerid] != 0)
	    {
			switch(Negocios[EnNegocio[playerid]][nType])
			{
				case 1: //24/7
				{
				    if(IsPlayerInRangeOfPoint(playerid, 2.0, -28.8428,-185.1317,1003.5469) || IsPlayerInRangeOfPoint(playerid, 2.0, 2.1769,-29.0143,1003.5494))
				    {
				        new string[200];
				        format(string, sizeof(string), "{FFFFFF}ª {B3FFFF}Radio 20W\n{FFFFFF}ª {B3FFFF}Radio 50W\n{FFFFFF}ª {B3FFFF}Radio 70W");
				        ShowPlayerDialog(playerid, DIALOG_COMPRAR247, DIALOG_STYLE_LIST, Negocios[EnNegocio[playerid]][nName], string, "Comprar", "Cancelar");
				    }
				    else
				    {
				        SendClientMessageEx(playerid, -1, "%s No te encuentras en el Vestidor del Negocio.", InfoMsg);
				    }
				}
				case 2: //Ropa
				{
				    if(IsPlayerInRangeOfPoint(playerid, 2.0, 217.1451,-98.5520,1005.2578) && GetPlayerInterior(playerid) == 15 || IsPlayerInRangeOfPoint(playerid, 2.0, 215.5318,-155.6535,1000.5234) && GetPlayerInterior(playerid) == 14 ||
					IsPlayerInRangeOfPoint(playerid, 2.0, 199.5842,-127.5658,1003.5152) && GetPlayerInterior(playerid) == 3 || IsPlayerInRangeOfPoint(playerid, 2.0, 214.5939,-41.5723,1002.0234) && GetPlayerInterior(playerid) == 1 ||
					IsPlayerInRangeOfPoint(playerid, 2.0, 206.3746,-8.0713,1001.2109) && GetPlayerInterior(playerid) == 5 || IsPlayerInRangeOfPoint(playerid, 2.0, 180.8182,-88.1369,1002.0307) && GetPlayerInterior(playerid) == 18)
				    {
						ShowModelSelectionMenu(playerid, SkinList, "Cambiar de Ropa");
				    }
				    else
				    {
				        SendClientMessageEx(playerid, -1, "%s No te encuentras en el Vestidor del Negocio.", InfoMsg);
				    }
				}
				case 3: //Comida
				{
				    if(IsPlayerInRangeOfPoint(playerid, 3.0, 376.417, -67.435, 1001.51) && GetPlayerInterior(playerid) == 10 || IsPlayerInRangeOfPoint(playerid, 3.0, 368.763, -6.017, 1001.85) && GetPlayerInterior(playerid) == 9 ||
					IsPlayerInRangeOfPoint(playerid, 3.0, 373.711, -118.884, 1001.49) && GetPlayerInterior(playerid) == 5 || IsPlayerInRangeOfPoint(playerid, 3.0, 375.694, -67.434, 1001.51) && GetPlayerInterior(playerid) == 10 ||
					IsPlayerInRangeOfPoint(playerid, 3.0, 369.902, -6.016, 1001.86) && GetPlayerInterior(playerid) == 9 || IsPlayerInRangeOfPoint(playerid, 3.0, 373.611, -118.803, 1001.49) && GetPlayerInterior(playerid) == 5)
				    {
				        new string[400];
						strcat(string, "{FFFFFF}ª {B3FFFF}Soda\t\t\t{FFFFFF}Costo:{008000} $5\n{FFFFFF}ª {B3FFFF}Hamburguesa\t\t{FFFFFF}Costo:{008000} $10\n{FFFFFF}ª {B3FFFF}Pizza\t\t\t{FFFFFF}Costo:{008000} $12\n");
						strcat(string, "{FFFFFF}ª {B3FFFF}HotDog\t\t{FFFFFF}Costo:{008000} $7\n{FFFFFF}ª {B3FFFF}Ensalada\t\t{FFFFFF}Costo:{008000} $15\n{FFFFFF}ª {B3FFFF}Pollo Frito\t\t{FFFFFF}Costo:{008000} $20\n");
						strcat(string, "{FFFFFF}ª {B3FFFF}Donut's\t\t{FFFFFF}Costo:{008000} $5");
						ShowPlayerDialog(playerid, DIALOG_COMIDA, DIALOG_STYLE_LIST, Negocios[EnNegocio[playerid]][nName], string, "Comprar", "Cancelar");
				    }
				    else
				    {
				        SendClientMessageEx(playerid, -1, "%s No te encuentras en el Mostrador del Negocio.", InfoMsg);
				    }
				}
				case 4: //ElectrÛnica
				{
				    if(IsPlayerInRangeOfPoint(playerid, 3.0, -2237.12, 130.179, 1035.41) && GetPlayerInterior(playerid) == 6)
				    {
						new string[250];
						strcat(string, "{FFFFFF}ª {B3FFFF}MÛvil\t\t\t{FFFFFF}Costo:{008000} $110\n{FFFFFF}ª {B3FFFF}C·mara\t\t{FFFFFF}Costo:{008000} $150\n{FFFFFF}ª {B3FFFF}Saldo\t\t\t{FFFFFF}Costo:{008000} $1 x Saldo\n");
						ShowPlayerDialog(playerid, DIALOG_ELECTRONICA, DIALOG_STYLE_LIST, Negocios[EnNegocio[playerid]][nName], string, "Comprar", "Cancelar");
				    }
				    else
				    {
				        SendClientMessageEx(playerid, -1, "%s No te encuentras en el Mostrador del Negocio.", InfoMsg);
				    }
				}
				case 5: //Armeria
				{
				}
			}
		}
		else
		{
		    SendClientMessageEx(playerid, -1, "%s No te encuentras en ninguna tienda.",InfoMsg);
		}
	}
	return 1;
}

CMD:seguro(playerid, params[])
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
	    new engine, lights, alarm, doors, bonnet, boot, objective, perm;
		GetVehicleParamsEx(NearVeh, engine, lights, alarm, doors, bonnet, boot, objective);
		switch(VehData[NearVeh][vType])
		{
		    case 1: //Personal
		    {
		        if(VehData[NearVeh][Owner] == PlayersData[playerid][UUID])
		        {
		            perm=1;
		        }
		        else
		        {
		            perm=0;
		        }
		    }
		    case 2: //Faccion
		    {
		        if(VehData[NearVeh][Faccion] == PlayersData[playerid][Faction])
		        {
		            if(VehData[NearVeh][FKey] == PlayersData[playerid][UUID] || PlayersData[playerid][fRank] <= 1 && VehData[NearVeh][Faccion] == PlayersData[playerid][Faction])
		            {
		                perm=1;
		            }
		            else
		            {
		                perm=0;
		            }
		        }
		    }
		}
		if(perm == 1)
		{
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
		}
		else
		{
			SendClientMessageEx(playerid, -1, "%s No tienes llaves de Èste coche.", InfoMsg);
		}
	}
	else
	{
	    SendClientMessageEx(playerid, -1, "%s No te encuentras cerca de ning˙n coche.", InfoMsg);
	}
	return 1;
}

CMD:luces(playerid, params[])
{
	new vehicleid = GetPlayerVehicleID(playerid);
	if(IsPlayerInAnyVehicle(playerid) == 0)
	{
	    SendClientMessageEx(playerid, -1, "%s No est·s dentro de un vehÌculo.",InfoMsg);
	}
	else if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
	{
        new engine, lights, alarm, doors, bonnet, boot, objective;
		GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);
		if(VehData[vehicleid][Luces] == 1)
		{
		    SetVehicleParamsEx(vehicleid, engine, VEHICLE_PARAMS_OFF, alarm, doors, bonnet, boot, objective);
		    VehData[vehicleid][Luces] = 0;
		    RoleAction(playerid, "apagÛ las luces del vehÌculo");
		    if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER){	PlayerTextDrawHide(playerid, Vel_Luces[playerid]);}
		}
		else
		{
		    SetVehicleParamsEx(vehicleid, engine, VEHICLE_PARAMS_ON, alarm, doors, bonnet, boot, objective);
		    VehData[vehicleid][Luces] = 1;
			RoleAction(playerid, "encendiÛ las luces del vehÌculo");
			if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER){	PlayerTextDrawShow(playerid, Vel_Luces[playerid]);}

		}
	}
	else
	{
	    SendClientMessageEx(playerid, -1, "%s Debes estar en el puesto de conductor.",InfoMsg);
	}
	return 1;
}

CMD:cinturon(playerid, params[])
{

	if(IsPlayerInAnyVehicle(playerid) == 0)
	{
	    SendClientMessageEx(playerid, -1, "%s No est·s dentro de un vehÌculo.",InfoMsg);
	    return 1;
	}
 	else if(Cinturon[playerid] == false)
	{
	    RoleAction(playerid, "se abrochÛ el cinturon de seguridad");
	    Cinturon[playerid] = true;
	    if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER){	PlayerTextDrawHide(playerid, Vel_Seat[playerid]);}
	}
	else
	{
	    RoleAction(playerid, "se desabrochÛ el cinturon de seguridad");
		Cinturon[playerid] = false;
		if(GetPlayerState(playerid) == PLAYER_STATE_DRIVER){	PlayerTextDrawShow(playerid, Vel_Seat[playerid]);}
	}
	return 1;
}

CMD:llenar(playerid, params[])
{
	new option[15];
	if(!sscanf(params, "s[15]", option))
	{
		if(!strcmp(option, "combustible", true))
		{
		    if(IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
		    {
		        new vID;
		        vID = GetPlayerVehicleID(playerid);
		        if(vID != INVALID_VEHICLE_ID)
		        {
		        	if(IsPlayerInGasStation(playerid) == 1)
					{
					    if(VehData[vID][Engine] == 0)
						{
							new pay = floatround(((100 - VehData[vID][Fuel]) * 200) / 99, floatround_ceil);
							if(PlayersData[playerid][Money] >= pay)
							{
							    PlayersData[playerid][Money] -= pay;
							    GivePlayerMoney(playerid, -pay);
							    SendClientMessageEx(playerid, -1, "%s Llenando Deposito Combustible por $%d", InfoMsg, pay);
							    LlenarGas[playerid] = true;
							    TimerLlenado[playerid] = SetTimerEx("LlenarGasolina", 1000, true, "ui", vID, playerid);
							}
							else
							{
							    SendClientMessageEx(playerid, -1, "%s No tienes suficiente dinero para comprar Gasolina.", InfoMsg);
							}
						}
						else
						{
						    SendClientMessageEx(playerid, -1, "%s Debes apagar el motor del coche.", InfoMsg);
						}
					}
					else
					{
					    SendClientMessageEx(playerid, -1, "%s No te encuentras cerca de ninguna Gasolinera.", InfoMsg);
					}
				}
				else
				{
				    SendClientMessageEx(playerid, -1, "%s OcurriÛ un problema con tu vehÌculo, cont·cta un administrador.", InfoMsg);
				}
		    }
		    else
		    {
		        SendClientMessageEx(playerid, -1, "%s Debes estar encima de un auto como conductor para poder utilizar este comando.", InfoMsg);
		    }
		}
		else if(!strcmp(option, "OpciÛn", true))
		{
      		SendClientMessageEx(playerid, -1, "%s No disponible.", InfoMsg);
		}
		else
		{
		    SendClientMessageEx(playerid, -1, "%s Utiliza: /Llenar [Combustible/OpciÛn]", InfoMsg);
		}
	}
	else
	{
	    SendClientMessageEx(playerid, -1, "%s Utiliza: /Llenar [Combustible/Opcion]", InfoMsg);
	}
	return 1;
}

CMD:trabajar(playerid, params[])
{
	if(IsPlayerInRangeOfPoint(playerid, 3.0, 1765.9205,-2023.2031,14.1502))
	{
		if(TempInfo[playerid][Work] == 0)
		{
			TempInfo[playerid][Work] = 1;
			SetPlayerSkin(playerid, 27);
			SendClientMessageEx(playerid, -1, "%s Excelente, ahora trabajar·s como barrendero!", InfoMsg);
			SendClientMessageEx(playerid, -1, "%s Sube al coche de limpieza y utiliza: /Ruta.", InfoMsg);
		}
		else if(TempInfo[playerid][Work] == 1)
		{
			SendClientMessageEx(playerid, -1, "%s Haz dejado tu trabajo como barrendero.", InfoMsg);
			SetPlayerSkin(playerid, PlayersData[playerid][Skin]);
			TempInfo[playerid][Work] = 0;
		}
		else
		{
			SendClientMessageEx(playerid, -1, "%s Ya tienes un trabajo.", InfoMsg);
		}

	}
	else if(IsPlayerInRangeOfPoint(playerid, 3.0, -382.633, -1426.26, 26.2327))
	{
		if(TempInfo[playerid][Work] == 0)
		{
			TempInfo[playerid][Work] = 2;
			SetPlayerSkin(playerid, 261);
			SendClientMessageEx(playerid, -1, "%s Excelente, ahora trabajar·s como Grangero!", InfoMsg);
			SendClientMessageEx(playerid, -1, "%s Sube al coche y utiliza: /Ruta.", InfoMsg);
		}
		else if(TempInfo[playerid][Work] == 2)
		{
			SendClientMessageEx(playerid, -1, "%s Haz dejado tu trabajo como granjero.", InfoMsg);
			SetPlayerSkin(playerid, PlayersData[playerid][Skin]);
			TempInfo[playerid][Work] = 0;
		}
		else
		{
			SendClientMessageEx(playerid, -1, "%s Ya tienes un trabajo.", InfoMsg);
		}
	}
	return 1;
}

CMD:renunciar(playerid, params[])
{
	if(TempInfo[playerid][Work] == 1)
	{
		TempInfo[playerid][Work] = 0;
		SetPlayerSkin(playerid, PlayersData[playerid][Skin]);
		SendClientMessageEx(playerid, -1, "%s Haz abandonado tu trabajo.", InfoMsg);
	}
	else
	{
		SendClientMessageEx(playerid, -1, "%s No tienes ningun trabajo.", InfoMsg);
	}
	return 1;
}

CMD:ruta(playerid, params[])
{
	new option[15];
	if(!sscanf(params, "s[15]", option))
	{
		if(!strcmp(option, "iniciar", true))
		{
			if(IsPlayerInAnyVehicle(playerid) && GetVehicleModel(GetPlayerVehicleID(playerid)) == 574)
			{
			    if(GetPlayerSkin(playerid) == 27)
			    {
			        if(Trabajando[playerid] == false)
			        {
						SendClientMessageEx(playerid, -1, "%s Ve a los puntos y limpia, al final recibirùs tu recompensa.", InfoMsg);
						new rand = random(sizeof(jobChecks));
						SetPlayerCheckpoint(playerid, jobChecks[rand][0], jobChecks[rand][1], jobChecks[rand][2], 3.0 );
						Trabajando[playerid] = true;
						JobCount[playerid] = 0;
					}
					else
					{
					    SendClientMessageEx(playerid, -1, "%s Ya te encuentras trabajando.", InfoMsg);
					}
			    }
			    else
			    {
			        SendClientMessageEx(playerid, -1, "%s No tienes el uniforme de trabajo.", InfoMsg);
			    }
			}
			else if(IsPlayerInAnyVehicle(playerid) && GetVehicleModel(GetPlayerVehicleID(playerid)) == 478)
			{
				if(GetPlayerSkin(playerid) == 261)
				{
					if(Trabajando[playerid] == false)
					{
						SendClientMessageEx(playerid, -1, "%s Ve al punto para llevar t˙ carga, al final recibir·s tu recompensa.", InfoMsg);
						new rand = random(sizeof(jobChecksGranjero));
						SetPlayerCheckpoint(playerid, jobChecksGranjero[rand][0], jobChecksGranjero[rand][1], jobChecksGranjero[rand][2], 3.0 );
						Trabajando[playerid] = true;
						JobCount[playerid] = 0;
					}
					else
					{
						SendClientMessageEx(playerid, -1, "%s Ya te encuentras trabajando.");
					}
				}
				else
				{
					SendClientMessageEx(playerid, -1, "%s No tienes el uniforme de trabajo.", InfoMsg);
				}
			}
			else
			{
				SendClientMessageEx(playerid, -1, "%s No est·s en un vehiculo de trabajo.", InfoMsg);
			}
		}
		else if(!strcmp(option, "fin", true))
		{
			if(Trabajando[playerid] == true && IsPlayerInAnyVehicle(playerid))
			{
				DisablePlayerCheckpoint(playerid);
				if(TempInfo[playerid][Work] == 1)
				{
					new paga;
					if(JobCount[playerid] <= 9)
					{
						paga = JobCount[playerid]*5;
					}
					else if(JobCount[playerid] >= 10 && JobCount[playerid] <= 19)
					{
						paga = JobCount[playerid]*8;
					}
					else if(JobCount[playerid] >= 20)
					{
						paga = 150;
					}
					JobCount[playerid] = 22 + paga;
					SendClientMessageEx(playerid, -1, "%s Lleva el vehiculo de regreso para recibir tu paga.", InfoMsg);
					SetPlayerCheckpoint(playerid, 1751.56, -2057.02, 13.7534, 3.0 );
				}
				else if(TempInfo[playerid][Work] == 2)
				{
					JobCount[playerid] = 2;
					SendClientMessageEx(playerid, -1, "%s Lleva el coche de regreso para terminar.", InfoMsg);
					SetPlayerCheckpoint(playerid, -397.723, -1442.86, 25.7209, 3.0);	
				}
			}
		}
	}
	else
	{
	    SendClientMessageEx(playerid, -1, "%s Utiliza: /Ruta [Iniciar/Fin]", InfoMsg);
	}
	return 1;
}