#include <core/player/data>
#include <core/server/database>
#include <dini>
#include <streamer>

#define			MAX_BUILDINGS           500

#define			MENU_PUERT				1000
#define			MENU_PUERT1             1001
#define			MENU_PUERT2				1002
#define			MENU_PUERT6				1003
#define			MENU_PUER2 				1004
#define			MENU_PUERT7 			1005
#define			MENU_PUER1 				1006
#define			MENU_PUERT4 			1007
#define			MENU_PUERT5 			1008
#define			MENU_PUERT3 			1009
#define			MENU_PUER3 				1010
#define			MENU_PUER7 				1011
#define         MENU_PUERT8             1012
#define			MENU_PUER4              1013
#define         MENU_PUERT9             1014
#define         MENU_PUER5             	1015

enum dInfo
{
	bOwner[255],
    bName[255],
    bPickupID,
    bPickupID1,
    bLocked,
    bType, //1 - Publico, 2 - Faccion, 3 - SuperMercados, 4 - PuertaInterna
    Float: bInteriorX[4], // X,Y,Z,A
    bInteriorID, // Interior ID del Interior
    bVirWorldINT,
	bVirWorldEXT,
    Float: bExteriorX[4], // X,Y,Z,A
    bExteriorID, // Interior ID del Exterior
    bFacc,
};
new PuertaInfor[MAX_BUILDINGS][dInfo];

enum Info
{
	Float:pPos_x,
    Float:pPos_y,
    Float:pPos_z,
    Float:pPos_r,
    pInterior,
    pVirtualWorld,
    buildingInterior,
    buildingExterior,
    cIntID,
    cExtID,
    Float: cExtX,
    Float: cExtY,
    Float: cExtZ,
    Float: cIntX,
    Float: cIntY,
    Float: cIntZ,
    InBuilding
};
new Informacion[MAX_PLAYERS][Info];

new Text3D:LabelDE[MAX_BUILDINGS];		//Etiqueta Puerta Exterior
new Text3D:LabelDI[MAX_BUILDINGS];		//Etiqueta Puerta Interior

new PuertaEliminarID[MAX_PLAYERS];      //ID Puerta Eliminar
new PuertaMoverID[MAX_PLAYERS];         //ID Puerta Mover
new Spawnedbuildings;                   //Cantidad de Puertas

forward SaveDoor(doorID);
forward LoadDoors();
forward LoadObjects(playerid);
forward SafeLoadObjects(playerid);

stock SaveDoorsMain()
{
    for(new i = 0; i < Spawnedbuildings; i++)
	{
        SaveDoor(i);
    }
    return 1;
}

public LoadObjects(playerid)
{
    TogglePlayerControllable(playerid, 0);
    GameTextForPlayer(playerid, "Cargando...", 2000, 5);
    SetPVarInt(playerid, "CargandoObjetos", 1);
    return SetTimerEx("SafeLoadObjects", 2000, 0, "d", playerid);
}

public SafeLoadObjects(playerid)
{
    if(GetPVarType(playerid, "CargandoObjetos"))
	{
        DeletePVar(playerid, "CargandoObjetos");
        TogglePlayerControllable(playerid, 1);
    }
}


public SaveDoor(doorID)
{
	new ArchivoNombre[128];
	format(ArchivoNombre, sizeof(ArchivoNombre), "PuertasD/PUERTA_%d.ini", doorID);
	if(dini_Exists(ArchivoNombre))
	{
		dini_Set(ArchivoNombre, "Name", PuertaInfor[doorID][bName]);                        dini_IntSet(ArchivoNombre, "Locked", PuertaInfor[doorID][bLocked]);
		dini_IntSet(ArchivoNombre, "Tipo", PuertaInfor[doorID][bType]);                    dini_IntSet(ArchivoNombre, "ExteriorID", PuertaInfor[doorID][bExteriorID]);
		dini_IntSet(ArchivoNombre, "InteriorID", PuertaInfor[doorID][bInteriorID]);        dini_IntSet(ArchivoNombre, "VWExt", PuertaInfor[doorID][bVirWorldEXT]);
		dini_FloatSet(ArchivoNombre, "InteriorX", PuertaInfor[doorID][bInteriorX][0]);        dini_FloatSet(ArchivoNombre, "InteriorY", PuertaInfor[doorID][bInteriorX][1]);
		dini_FloatSet(ArchivoNombre, "InteriorZ", PuertaInfor[doorID][bInteriorX][2]);        dini_FloatSet(ArchivoNombre, "ExteriorX", PuertaInfor[doorID][bExteriorX][0]);
		dini_FloatSet(ArchivoNombre, "ExteriorY", PuertaInfor[doorID][bExteriorX][1]);        dini_FloatSet(ArchivoNombre, "ExteriorZ", PuertaInfor[doorID][bExteriorX][2]);
		dini_IntSet(ArchivoNombre, "Faccion", PuertaInfor[doorID][bFacc]);                  dini_IntSet(ArchivoNombre, "VWInt", PuertaInfor[doorID][bVirWorldINT]);
	}
	return 1;
}

public LoadDoors()
{
    new FileName[128], string[128];
    for(new i = 0; i < MAX_BUILDINGS; i++)
	{
        format(FileName, sizeof(FileName), "PuertasD/PUERTA_%d.ini", i);
        if(dini_Exists(FileName))
		{
  			PuertaInfor[i][bOwner] = dini_Get( FileName, "Owner" );
            PuertaInfor[i][bName] = dini_Get( FileName, "Name" );
            PuertaInfor[i][bPickupID] = dini_Int(FileName, "PickupID" );
            PuertaInfor[i][bPickupID1] = dini_Int(FileName, "PickupID1" );
            PuertaInfor[i][bLocked] = dini_Int(FileName, "Locked" );
            PuertaInfor[i][bType] = dini_Int(FileName, "Tipo" );
            PuertaInfor[i][bExteriorID] = dini_Int(FileName, "ExteriorID" );
            PuertaInfor[i][bInteriorID] = dini_Int(FileName, "InteriorID" );
            PuertaInfor[i][bVirWorldINT] = dini_Int(FileName, "VWInt");
			PuertaInfor[i][bVirWorldEXT] = dini_Int(FileName, "VWExt");
            PuertaInfor[i][bInteriorX][0] = dini_Float(FileName, "InteriorX" );
            PuertaInfor[i][bInteriorX][1] = dini_Float(FileName, "InteriorY" );
            PuertaInfor[i][bInteriorX][2] = dini_Float(FileName, "InteriorZ" );
            PuertaInfor[i][bExteriorX][0] = dini_Float(FileName, "ExteriorX" );
            PuertaInfor[i][bExteriorX][1] = dini_Float(FileName, "ExteriorY" );
            PuertaInfor[i][bExteriorX][2] = dini_Float(FileName, "ExteriorZ" );
            PuertaInfor[i][bFacc] = dini_Int(FileName, "Faccion" );
            Spawnedbuildings++;
            switch(PuertaInfor[i][bType])
            {
                case 1: //Publico
                {
					PuertaInfor[i][bPickupID] = CreateDynamicPickup(1239, 23, PuertaInfor[i][bExteriorX][0], PuertaInfor[i][bExteriorX][1], PuertaInfor[i][bExteriorX][2], PuertaInfor[i][bVirWorldEXT], PuertaInfor[i][bExteriorID], -1, 150.0 );
					PuertaInfor[i][bPickupID1] = CreateDynamicPickup(1239, 23, PuertaInfor[i][bInteriorX][0], PuertaInfor[i][bInteriorX][1], PuertaInfor[i][bInteriorX][2], PuertaInfor[i][bVirWorldINT], PuertaInfor[i][bInteriorID], -1, 150.0 );
				}
                case 2: //Faccion
                {
					PuertaInfor[i][bPickupID] = CreateDynamicPickup(1314, 23, PuertaInfor[i][bExteriorX][0], PuertaInfor[i][bExteriorX][1], PuertaInfor[i][bExteriorX][2], PuertaInfor[i][bVirWorldEXT], PuertaInfor[i][bExteriorID], -1, 150.0 );
					PuertaInfor[i][bPickupID1] = CreateDynamicPickup(1314, 23, PuertaInfor[i][bInteriorX][0], PuertaInfor[i][bInteriorX][1], PuertaInfor[i][bInteriorX][2], PuertaInfor[i][bVirWorldINT], PuertaInfor[i][bInteriorID], -1, 150.0 );
                }
                case 3: //SuperMercados
                {
					PuertaInfor[i][bPickupID] = CreateDynamicPickup(19134, 23, PuertaInfor[i][bExteriorX][0], PuertaInfor[i][bExteriorX][1], PuertaInfor[i][bExteriorX][2], PuertaInfor[i][bVirWorldEXT], PuertaInfor[i][bExteriorID], -1, 150.0 );
					PuertaInfor[i][bPickupID1] = CreateDynamicPickup(19134, 23, PuertaInfor[i][bInteriorX][0], PuertaInfor[i][bInteriorX][1], PuertaInfor[i][bInteriorX][2], PuertaInfor[i][bVirWorldINT], PuertaInfor[i][bInteriorID], -1, 150.0 );
                }
                case 4: //PuertaInterior
                {
					PuertaInfor[i][bPickupID] = CreateDynamicPickup(19198, 23, PuertaInfor[i][bExteriorX][0], PuertaInfor[i][bExteriorX][1], PuertaInfor[i][bExteriorX][2], PuertaInfor[i][bVirWorldEXT], PuertaInfor[i][bExteriorID], -1, 150.0 );
					PuertaInfor[i][bPickupID1] = CreateDynamicPickup(19198, 23, PuertaInfor[i][bInteriorX][0], PuertaInfor[i][bInteriorX][1], PuertaInfor[i][bInteriorX][2], PuertaInfor[i][bVirWorldINT], PuertaInfor[i][bInteriorID], -1, 150.0 );
                }
			}
            //------------------------------------------------------------------
			format(string, sizeof(string), "\t{BFE44E}%s{FFFFFF}\n\n{0000FF}Dirección: {BFE44E}%s%d", PuertaInfor[i][bName], GetGPSFromDoor(i), i);
			LabelDE[i] = CreateDynamic3DTextLabel(string, 0xF0CC00FF, PuertaInfor[i][bExteriorX][0], PuertaInfor[i][bExteriorX][1], PuertaInfor[i][bExteriorX][2]+0.75,20.0,INVALID_PLAYER_ID,INVALID_VEHICLE_ID,0, PuertaInfor[i][bVirWorldEXT], PuertaInfor[i][bExteriorID],-1, 100.0);
			format(string, sizeof(string), "\t{BFE44E}%s{FFFFFF}\n\n{0000FF}Dirección: {BFE44E}%s%d", PuertaInfor[i][bName], GetGPSFromDoor(i), i);
            LabelDI[i] = CreateDynamic3DTextLabel(string, 0xF0CC00FF, PuertaInfor[i][bInteriorX][0], PuertaInfor[i][bInteriorX][1], PuertaInfor[i][bInteriorX][2]+0.75,20.0,INVALID_PLAYER_ID,INVALID_VEHICLE_ID, 0, PuertaInfor[i][bVirWorldINT], PuertaInfor[i][bInteriorID],-1, 100.0);
       }
    }
    return 1;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
stock GetGPSFromDoor(doorid)
{
	new gps[5];
	switch(PuertaInfor[doorid][bType])
	{
		case 1://publica
		{
			format(gps, sizeof(gps), "GP-");
		}
		case 2://faccion
		{
			format(gps, sizeof(gps), "GF-");
		}
		case 3://supermercado
		{
			format(gps, sizeof(gps), "GS-");
		}
		case 4://puerta interior
		{
			format(gps, sizeof(gps), "GI-");
		}
	}
	return gps;
}

stock GetNearDoor(playerid)
{
	new dID;
	for(new i = 0; i < sizeof(PuertaInfor); i++)
	{
		if(IsPlayerInRangeOfPoint(playerid, 1, PuertaInfor[i][bExteriorX][0], PuertaInfor[i][bExteriorX][1], PuertaInfor[i][bExteriorX][2]) || IsPlayerInRangeOfPoint(playerid, 1, PuertaInfor[i][bInteriorX][0], PuertaInfor[i][bInteriorX][1], PuertaInfor[i][bInteriorX][2]))
		{
			if(GetPlayerInterior(playerid) == PuertaInfor[i][bExteriorID] && GetPlayerVirtualWorld(playerid) == PuertaInfor[i][bVirWorldEXT] || GetPlayerInterior(playerid) == PuertaInfor[i][bInteriorID] && GetPlayerVirtualWorld(playerid) == PuertaInfor[i][bVirWorldINT])
			{
				dID = i;
			}
		}
	}
	return dID;
}