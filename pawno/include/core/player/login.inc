#include <core/server/database>
#include <core/player/data>
#include <gui/hud/textdraw>
#include <gui/hud/main>

#define             DIALOG_LOGIN        5

stock NameForHash(name[])
{
    new dest[MAX_PLAYER_NAME];
    dest[1] = strfind(name, "_", false);
    if(dest[1] != -1)
	{
		strcat(dest, name, dest[1]);
    }
	else
	{
        strcat(dest, name, sizeof dest);
    }
    return dest;
}

stock RegisterCamera(playerid)
{
    InterpolateCameraPos(playerid, 1660.466064, -2286.880859, 680.146240, 1658.428955, -2286.974121, -0.042309, 5000);
	InterpolateCameraLookAt(playerid, 1660.031127, -2286.854003, 675.165283, 1653.434326, -2287.022460, -0.268475, 4000);
	SetPVarInt(playerid, "CamaraRegistro", 1);
    TogglePlayerControllable(playerid, 0);
    return 1;
}

stock ResetPlayerVariables(playerid)
{
	Logged[playerid] = false;
    TryPass[playerid] = 0;
	TryRole[playerid] = false;
	PlayersData[playerid][UUID] = 0;
    PlayersData[playerid][ID] = 0;
    PlayersData[playerid][Gender] = 0;
    PlayersData[playerid][Age] = 0;
    PlayersData[playerid][City] = 0;
    PlayersData[playerid][Money] = 0;
    PlayersData[playerid][Skin] = 0;
    PlayersData[playerid][Admin] = 0;
    PlayersData[playerid][Esp] = 0;
    PlayersData[playerid][Vip] = 0;
    PlayersData[playerid][Level] = 0;
    PlayersData[playerid][Origin] = 0;
    PlayersData[playerid][Exp] = 0;
    PlayersData[playerid][pPosX] = 0.0;
    PlayersData[playerid][pPosY] = 0.0;
    PlayersData[playerid][pPosZ] = 0.0;
    PlayersData[playerid][pPosAng] = 0.0;
    PlayersData[playerid][pVW] = 0;
    PlayersData[playerid][pInterior] = 0;
    PlayersData[playerid][pHealth] = 0.0;
    PlayersData[playerid][pArmour] = 0.0;
    PlayersData[playerid][Faction] = 0;
    PlayersData[playerid][fRank] = 0;
    PlayersData[playerid][Adv] = 0;
    PlayersData[playerid][Banned] = 0;
    PlayersData[playerid][Gold] = 0;
    PlayersData[playerid][pFood] = 0.0;
    PlayersData[playerid][pDrink] = 0.0;
    PlayersData[playerid][WeaponID][0] = 0;
    PlayersData[playerid][WeaponID][1] = 0;
    PlayersData[playerid][WeaponID][2] = 0;
    PlayersData[playerid][WeaponID][3] = 0;
    PlayersData[playerid][WeaponAmmo][0] = 0;
    PlayersData[playerid][WeaponAmmo][1] = 0;
    PlayersData[playerid][WeaponAmmo][2] = 0;
    PlayersData[playerid][WeaponAmmo][3] = 0;
    PlayersData[playerid][InvObj][0] = 0;
    PlayersData[playerid][InvObj][1] = 0;
    PlayersData[playerid][InvObj][2] = 0;
    PlayersData[playerid][InvObj][3] = 0;
    PlayersData[playerid][InvObj][4] = 0;
    PlayersData[playerid][BankAccount] = 0;
}

//============================================================================
forward CreatePlayerAccount(playerid);
forward LoadPlayerData(playerid);
forward SetPlayerData(playerid);
forward SavePlayerData(playerid, SaveType);

public CreatePlayerAccount(playerid)
{
    new query[520], ip[16];

    /*===== [ Set Primary Data User ] =====*/
    PlayersData[playerid][Money] = 120;
    if(PlayersData[playerid][Gender] == 1)
    {
        PlayersData[playerid][Skin] = 35;
    } 
    else
    {
        PlayersData[playerid][Skin] = 12;
    }
    PlayersData[playerid][Admin] = 2;
    PlayersData[playerid][pFood] = 95.0;
    PlayersData[playerid][pDrink] = 95.0;
    PlayersData[playerid][pHealth] = 95.0;
    PlayersData[playerid][ID] = 1000+random(9999);
    PlayersData[playerid][BankAccount] = 80;

    SetSpawnInfo(playerid, NO_TEAM, PlayersData[playerid][Skin], 1649.1991, -2286.3701, -1.2096, 270.1755, 0,0,0,0,0,0);
	Logged[playerid] = true;
    SpawnPlayer(playerid);
    
    /*===== [ Do Query to Database ] =====*/

    mysql_format(g_MySQL, query, sizeof(query), "INSERT INTO `users` (`Name`, `Password`, `Mail`, `Gender`, `Age`, `City`, `Money`, `rName`, `Skin`, `Admin`, `pFood`, `pDrink`, `pHealth`, `ID`, `BankAccount`) VALUES ('%e', '%e', '%e', '%d', '%d', '%d', '%d', '%e', '%d', '%d', '%f', '%f', '%f', '%d', '%d')",
    GetPlayerNameEx(playerid), PlayersData[playerid][Password], PlayersData[playerid][Mail],
    PlayersData[playerid][Gender], PlayersData[playerid][Age], PlayersData[playerid][City],
    PlayersData[playerid][Money], GetPlayerNameEx(playerid), PlayersData[playerid][Skin],
    PlayersData[playerid][Admin], PlayersData[playerid][pFood], PlayersData[playerid][pDrink], 
    PlayersData[playerid][pHealth], PlayersData[playerid][ID], PlayersData[playerid][BankAccount]);
    mysql_tquery(g_MySQL, query);
    //---------------
    GetPlayerIp(playerid, ip, sizeof(ip));
    printf("[UG] Nueva Cuenta: %s | Mail: %s | IP: %s", GetPlayerNameEx(playerid), PlayersData[playerid][Mail], ip);
    //---------------
    RegisterCamera(playerid);
    return 1;
}

public LoadPlayerData(playerid)
{
    ResetPlayerVariables(playerid);
    if(cache_num_rows() > 0)
    {
        cache_get_value_name_int(0, "UUID", PlayersData[playerid][UUID]);
        cache_get_value_name(0, "rName", PlayersData[playerid][rName], 128);
        cache_get_value_name(0, "Password", PlayersData[playerid][Password], 65);
        cache_get_value_name(0, "Mail", PlayersData[playerid][Mail], 150);
        cache_get_value_name_int(0, "ID", PlayersData[playerid][ID]);
        cache_get_value_name_int(0, "Gender", PlayersData[playerid][Gender]);
        cache_get_value_name_int(0, "Age", PlayersData[playerid][Age]);
        cache_get_value_name_int(0, "City", PlayersData[playerid][City]);
        cache_get_value_name_int(0, "Money", PlayersData[playerid][Money]);
        cache_get_value_name_int(0, "Skin", PlayersData[playerid][Skin]);
        cache_get_value_name_int(0, "Admin", PlayersData[playerid][Admin]);
        cache_get_value_name_int(0, "Esp", PlayersData[playerid][Esp]);
        cache_get_value_name_int(0, "Level", PlayersData[playerid][Level]);
        cache_get_value_name_int(0, "Origin", PlayersData[playerid][Origin]);
        cache_get_value_name_int(0, "Exp", PlayersData[playerid][Exp]);
        cache_get_value_name_float(0, "pPosX", PlayersData[playerid][pPosX]);
        cache_get_value_name_float(0, "pPosY", PlayersData[playerid][pPosY]);
        cache_get_value_name_float(0, "pPosZ", PlayersData[playerid][pPosZ]);
        cache_get_value_name_float(0, "pPosAng", PlayersData[playerid][pPosAng]);
        cache_get_value_name_int(0, "pVW", PlayersData[playerid][pVW]);
        cache_get_value_name_int(0, "pInterior", PlayersData[playerid][pInterior]);
        cache_get_value_name_float(0, "pHealth", PlayersData[playerid][pHealth]);
        cache_get_value_name_float(0, "pArmour", PlayersData[playerid][pArmour]);
        cache_get_value_name_int(0, "Faction", PlayersData[playerid][Faction]);
        cache_get_value_name_int(0, "fRank", PlayersData[playerid][fRank]);
        cache_get_value_name_int(0, "Adv", PlayersData[playerid][Adv]);
        cache_get_value_name_int(0, "Banned", PlayersData[playerid][Banned]);
        cache_get_value_name_int(0, "Gold", PlayersData[playerid][Gold]);
        cache_get_value_name_float(0, "pFood", PlayersData[playerid][pFood]);
        cache_get_value_name_float(0, "pDrink", PlayersData[playerid][pDrink]);
        cache_get_value_name_int(0, "WeaponID1", PlayersData[playerid][WeaponID][0]);
        cache_get_value_name_int(0, "WeaponID2", PlayersData[playerid][WeaponID][1]);
        cache_get_value_name_int(0, "WeaponID3", PlayersData[playerid][WeaponID][2]);
        cache_get_value_name_int(0, "WeaponID4", PlayersData[playerid][WeaponID][3]);
        cache_get_value_name_int(0, "WeaponAmmo1", PlayersData[playerid][WeaponAmmo][0]);
        cache_get_value_name_int(0, "WeaponAmmo2", PlayersData[playerid][WeaponAmmo][1]);
        cache_get_value_name_int(0, "WeaponAmmo3", PlayersData[playerid][WeaponAmmo][2]);
        cache_get_value_name_int(0, "WeaponAmmo4", PlayersData[playerid][WeaponAmmo][3]);
        cache_get_value_name_int(0, "InvObj1", PlayersData[playerid][InvObj][0]);
        cache_get_value_name_int(0, "InvObj2", PlayersData[playerid][InvObj][1]);
        cache_get_value_name_int(0, "InvObj3", PlayersData[playerid][InvObj][2]);
        cache_get_value_name_int(0, "InvObj4", PlayersData[playerid][InvObj][3]);
        cache_get_value_name_int(0, "InvObj5", PlayersData[playerid][InvObj][4]);
        cache_get_value_name_int(0, "BankAccount", PlayersData[playerid][BankAccount]);

        Logged[playerid] = true;
        SetPVarInt(playerid, "CanJoin", 1);
        SetPlayerData(playerid);
    }
    else
    {
        if(TryPass[playerid] < 3)
        {
            ShowPlayerDialog(playerid, DIALOG_LOGIN, DIALOG_STYLE_PASSWORD, "{FF0984}Login {FFFFFF}» {FF8000}Union {0080FF}Gamers", "Contraseña {FF0000}Incorrecta!\n\nIngrese su contraseña porfavor.", "{00D200}»", "{FF0000}X");
            TryPass[playerid]++;
        }
        else
        {
            ShowPlayerDialog(playerid, 404, DIALOG_STYLE_MSGBOX, "{FF0984}Login {FFFFFF}» {FF8000}Union {0080FF}Gamers", "Pasaste el limite de intentos de iniciar sesión.\nContacta un administrador.", "Aceptar", "");
			SetTimerEx("KickPlayerEx", 400, false, "d", playerid);
        }
    }
    return 1;
}

public SetPlayerData(playerid)
{
    SetSpawnInfo(playerid, NO_TEAM, PlayersData[playerid][Skin], PlayersData[playerid][pPosX], PlayersData[playerid][pPosY], PlayersData[playerid][pPosZ], 10.0, -1, -1, -1, -1, -1, -1);
    SpawnPlayer(playerid);
    SetPlayerHealth(playerid, PlayersData[playerid][pHealth]);
    SetPlayerArmour(playerid, PlayersData[playerid][pArmour]);
    GivePlayerMoney(playerid, PlayersData[playerid][Money]);
    SetPlayerVirtualWorld(playerid, PlayersData[playerid][pVW]);
    SetPlayerInterior(playerid, PlayersData[playerid][pInterior]);
    SetPlayerScore(playerid, PlayersData[playerid][Level]);
    
    //DESBUG
    SetSpawnInfo(playerid, NO_TEAM, PlayersData[playerid][Skin], 1649.1991, -2286.3701, -1.2096, 270.1755, 0,0,0,0,0,0);
    return 1;
}

public SavePlayerData(playerid, SaveType)
{
    if(IsPlayerConnected(playerid) && Logged[playerid] == true)
    {
        new query[650], Cache:result;
        new Float:PosX, Float:PosY, Float:PosZ, Float:PosA;
        GetPlayerPos(playerid, PosX, PosY, PosZ);
        GetPlayerHealth(playerid, PlayersData[playerid][pHealth]);
        if(TempInfo[playerid][OnDuty] == true){PlayersData[playerid][pHealth] = TempInfo[playerid][dHealth];}
        GetPlayerArmour(playerid, PlayersData[playerid][pArmour]);
        PlayersData[playerid][pVW] = GetPlayerVirtualWorld(playerid);
        PlayersData[playerid][pInterior] = GetPlayerInterior(playerid);
        GetPlayerFacingAngle(playerid, PosA);

        switch(SaveType)
        {
            case 0: //Save All
            {
                mysql_format(g_MySQL, query, sizeof(query), "UPDATE `users` SET `ID`='%i', `Mail`='%e', `Password`='%e', `Age`='%i', `City`='%i', `Money`='%i', `Skin`='%i', `Admin`='%i', `Esp`='%i', `Vip`='%i', `Level`='%i' WHERE `UUID`='%i' AND `Name`='%e'", 
                PlayersData[playerid][ID], PlayersData[playerid][Mail], PlayersData[playerid][Password],
                PlayersData[playerid][Age], PlayersData[playerid][City], PlayersData[playerid][Money], 
                PlayersData[playerid][Skin], PlayersData[playerid][Admin], PlayersData[playerid][Esp],
                PlayersData[playerid][Vip], PlayersData[playerid][Level], PlayersData[playerid][UUID], 
                GetPlayerNameEx(playerid));
                result = mysql_query(g_MySQL, query);
                
                mysql_format(g_MySQL, query, sizeof(query), "UPDATE `users` SET `Origin`='%i', `Exp`='%i', `pPosX`='%f', `pPosY`='%f', `pPosZ`='%f', `pPosAng`='%f', `pVW`='%i', `pInterior`='%i', `pHealth`='%f', `pArmour`='%f' WHERE `UUID`='%i' AND `Name`='%e'",
                PlayersData[playerid][Origin], PlayersData[playerid][Exp], PosX,
                PosY, PosZ, PosA, PlayersData[playerid][pVW], PlayersData[playerid][pInterior], 
                PlayersData[playerid][pHealth], PlayersData[playerid][pArmour], PlayersData[playerid][UUID],
                GetPlayerNameEx(playerid));
                result = mysql_query(g_MySQL, query);
                
                mysql_format(g_MySQL, query, sizeof(query), "UPDATE `users` SET `Faction`='%i', `fRank`='%i', `Adv`='%i', `Banned`='%i', `Gold`='%i', `pFood`='%f', `pDrink`='%f', `BankAccount`='%d' WHERE `UUID`='%i' AND `Name`='%e'",
                PlayersData[playerid][Faction], PlayersData[playerid][fRank], PlayersData[playerid][Adv],
                PlayersData[playerid][Banned], PlayersData[playerid][Gold], PlayersData[playerid][pFood],
                PlayersData[playerid][pDrink], PlayersData[playerid][BankAccount], PlayersData[playerid][UUID],
                GetPlayerNameEx(playerid));
                result = mysql_query(g_MySQL, query);
                cache_delete(result);
            }
            case 1: //Save Money
            {

            }
        }
    }
    return 1;
}
