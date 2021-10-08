//»»»»»»»»»» RESOURCES ««««««««««
#include <core/player/data>
#include <core/server/database>
#include <gui/hud/textdraw>

//»»»»»»»»»» VARIABLES ««««««««««
#define         MAX_NEGOCIOS            500

new TNegocios;
/*===============       [ LABELS ]     =============== */
new Text3D:LabelNE[MAX_NEGOCIOS];
new Text3D:LabelNI[MAX_NEGOCIOS];

enum bInfo
{
	nID,
	nName[128],
	nOwnerN[128],
	nOwnerID,
	nType,
	Float:nPEx,
	Float:nPEy,
	Float:nPEz,
	Float:nPIx,
	Float:nPIy,
	Float:nPIz,
	nIntE,
	nIntI,
	nVwE,
	nVwI,
	nPrice,
	nMats,
	nMoney,
	nPickE,
	nPickI,
	nEntrada
};
new Negocios[MAX_NEGOCIOS][bInfo];

//»»»»»»»»»» STOCKS ««««««««««

stock GetNearNegocio(playerid)
{
	new NnID;
	for(new i=0; i < sizeof(Negocios); i++)
	{
		if(IsPlayerInRangeOfPoint(playerid, 1.0, Negocios[i][nPEx], Negocios[i][nPEy], Negocios[i][nPEz]))
		{
		    NnID = i;
		}
	}
	return NnID;
}

//»»»»»»»»»» FUNCIONES ««««««««««

forward LoadNegocios();
forward SaveNegocios();

public LoadNegocios()
{
	new query[80], string[300], tipo[20];
 	mysql_format(g_MySQL, query, sizeof(query), "SELECT * FROM business");
	new Cache:result = mysql_query(g_MySQL, query);
	if(cache_num_rows()>0)
	{
	    TNegocios++;
		for(new i=0; i < cache_num_rows(); i++)
		{
			Negocios[TNegocios][nID] = TNegocios;
			cache_get_value_name(i, "nName", Negocios[TNegocios][nName], 128);
			cache_get_value_name(i, "nOwnerN", Negocios[TNegocios][nOwnerN], 128);
			cache_get_value_name_int(i, "nOwnerID", Negocios[TNegocios][nOwnerID]);
			cache_get_value_name_int(i, "nType", Negocios[TNegocios][nType]);
			cache_get_value_name_float(i, "nPEx", Negocios[TNegocios][nPEx]);
			cache_get_value_name_float(i, "nPEy", Negocios[TNegocios][nPEy]);
			cache_get_value_name_float(i, "nPEz", Negocios[TNegocios][nPEz]);
			cache_get_value_name_float(i, "nPIx", Negocios[TNegocios][nPIx]);
			cache_get_value_name_float(i, "nPIy", Negocios[TNegocios][nPIy]);
			cache_get_value_name_float(i, "nPIz", Negocios[TNegocios][nPIz]);
			cache_get_value_name_int(i, "nIntE", Negocios[TNegocios][nIntE]);
			cache_get_value_name_int(i, "nIntI", Negocios[TNegocios][nIntI]);
			cache_get_value_name_int(i, "nVwE", Negocios[TNegocios][nVwE]);
			cache_get_value_name_int(i, "nVwI", Negocios[TNegocios][nVwI]);
			cache_get_value_name_int(i, "nPrice", Negocios[TNegocios][nPrice]);
			cache_get_value_name_int(i, "nMats", Negocios[TNegocios][nMats]);
			cache_get_value_name_int(i, "nMoney", Negocios[TNegocios][nMoney]);
			cache_get_value_name_int(i, "nEntrada", Negocios[TNegocios][nEntrada]);
			//--------------------------------------------------------------
			Negocios[TNegocios][nPickE] = CreateDynamicPickup(19135, 23, Negocios[TNegocios][nPEx], Negocios[TNegocios][nPEy], Negocios[TNegocios][nPEz], Negocios[TNegocios][nVwE], Negocios[TNegocios][nIntE], -1, 150.0 );
			Negocios[TNegocios][nPickI] = CreateDynamicPickup(19135, 23, Negocios[TNegocios][nPIx], Negocios[TNegocios][nPIy], Negocios[TNegocios][nPIz], Negocios[TNegocios][nVwI], Negocios[TNegocios][nIntI], -1, 150.0 );
			//------------------------------------------------------------------
			switch(Negocios[TNegocios][nType])
			{
				case 1:{    tipo="24/7";}   case 2:{    tipo="Ropa";}   case 3:{    tipo="Comida";}   case 4:{    tipo="Electrónica";}   case 5:{    tipo="Armeria";}
			}
			if(Negocios[TNegocios][nOwnerID] == 0)
			{
				format(string, sizeof(string), "{00E100}¡En Venta!\n{B8D900}Precio: {FFFFFF}$%d\n{B8D900}Tipo: {FFFFFF}%s\n{B8D900}Acceso: {FFFFFF}%d\n{B8D900}Dirección: {FFFFFF}GN-%d", Negocios[TNegocios][nPrice], tipo, Negocios[TNegocios][nEntrada], Negocios[TNegocios][nID]);
				LabelNE[TNegocios] = CreateDynamic3DTextLabel(string, 0xF0CC00FF, Negocios[TNegocios][nPEx], Negocios[TNegocios][nPEy], Negocios[TNegocios][nPEz]+0.75, 20.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, Negocios[TNegocios][nVwE], Negocios[TNegocios][nIntE], -1, 100.0);
				format(string, sizeof(string), "{00E100}¡En Venta!\n{B8D900}Precio: {FFFFFF}$%d\n{B8D900}Tipo: {FFFFFF}%s\n{B8D900}Acceso: {FFFFFF}%d\n{B8D900}Dirección: {FFFFFF}GN-%d", Negocios[TNegocios][nPrice], tipo, Negocios[TNegocios][nEntrada], Negocios[TNegocios][nID]);
				LabelNI[TNegocios] = CreateDynamic3DTextLabel(string, 0xF0CC00FF, Negocios[TNegocios][nPIx], Negocios[TNegocios][nPIy], Negocios[TNegocios][nPIz]+0.75,20.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, Negocios[TNegocios][nVwI], Negocios[TNegocios][nIntI], -1, 100.0);
			}
			else
			{
				format(string, sizeof(string), "{FFFFFF}%s\n{B8D900}Dueño: {FFFFFF}%s\n{B8D900}Tipo: {FFFFFF}%s\n{B8D900}Acceso: {FFFFFF}%d\n{B8D900}Dirección: {FFFFFF}GN-%d", Negocios[TNegocios][nName], Negocios[TNegocios][nOwnerN], tipo, Negocios[TNegocios][nEntrada], Negocios[TNegocios][nID]);
				LabelNE[TNegocios] = CreateDynamic3DTextLabel(string, 0xF0CC00FF, Negocios[TNegocios][nPEx], Negocios[TNegocios][nPEy], Negocios[TNegocios][nPEz]+0.75, 20.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, Negocios[TNegocios][nVwE], Negocios[TNegocios][nIntE], -1, 100.0);
				format(string, sizeof(string), "{FFFFFF}%s\n{B8D900}Dueño: {FFFFFF}%s\n{B8D900}Tipo: {FFFFFF}%s\n{B8D900}Acceso: {FFFFFF}%d\n{B8D900}Dirección: {FFFFFF}GN-%d", Negocios[TNegocios][nName], Negocios[TNegocios][nOwnerN], tipo, Negocios[TNegocios][nEntrada], Negocios[TNegocios][nID]);
				LabelNI[TNegocios] = CreateDynamic3DTextLabel(string, 0xF0CC00FF, Negocios[TNegocios][nPIx], Negocios[TNegocios][nPIy], Negocios[TNegocios][nPIz]+0.75,20.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, Negocios[TNegocios][nVwI], Negocios[TNegocios][nIntI], -1, 100.0);
			}
			TNegocios++;
		}
		cache_delete(result);
	}
	return 1;
}

public SaveNegocios()
{
	new query[500];
	for(new i=0; i <=TNegocios; i++)
	{
		format(query, sizeof(query), "UPDATE `business` SET `nName`='%s', `nOwnerN`='%s', `nOwnerID`='%i', `nType`='%i', `nPrice`='%i', `nMats`='%i', `nMoney`='%i', `nEntrada`='%i' WHERE `nID`='%i'", Negocios[i][nName],
		Negocios[i][nOwnerN], Negocios[i][nOwnerID], Negocios[i][nType],
		Negocios[i][nPrice], Negocios[i][nMats], Negocios[i][nMoney],
		Negocios[i][nEntrada], Negocios[i][nID]);
		new Cache:result = mysql_query(g_MySQL, query);
		cache_delete(result);
	}
	return 1;
}