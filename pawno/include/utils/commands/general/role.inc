#include <zcmd>
#include <sscanf2>
#include <core/player/data>
#include <gui/hud/chat>

CMD:me(playerid, params[])
{
    if(IsPlayerConnected(playerid) && Logged[playerid] == true)
    {
        if(isnull(params))
        {
            SendClientMessageEx(playerid, -1, "%s Utiliza /me (acción)", InfoMsg);
        }
        else
        {
            RoleAction(playerid, params);
        }
    }
    else
    {
        SendClientMessageEx(playerid, -1, "%s Has sido silenciado o no has ingresado al Servidor.", InfoMsg);
    }
    return 1;
}

CMD:intentar(playerid, params[])
{
    if(IsPlayerConnected(playerid) && Logged[playerid] == true)
    {
        if(TryRole[playerid] == true)
        {
            SendClientMessageEx(playerid, -1, "{A7A7A7}** Debes esperar 7 segundos para volver a utilizar el comando.");
        }
        else
        {
            if(isnull(params))
            {
                SendClientMessageEx(playerid, -1, "%s Utiliza /Intentar (acción)", InfoMsg);
            }
            else
            {
                if(strlen(params) <= 83)
                {
                    RoleTry(playerid, params);
                }
                else
                {
                    SendClientMessageEx(playerid, -1, "%s La acción debe contener entre 3 y 80 carácteres.", InfoMsg);
                }
            }
        }
    }
    else
    {
        SendClientMessageEx(playerid, -1, "%s Has sido silenciado o no has ingresado al Servidor.", InfoMsg);
    }
    return 1;
}

CMD:env(playerid, params[])
{
    if(IsPlayerConnected(playerid) && Logged[playerid] == true)
    {
        if(isnull(params))
        {
            SendClientMessageEx(playerid, -1, "%s Utiliza /Env (entorno)", HelpMsg);
        }
        else
        {
            RoleEnviron(playerid, params);
        }
    }
    else
    {
        SendClientMessageEx(playerid, -1, "%s Has sido silenciado o no has ingresado al Servidor.", InfoMsg);
    }
	return 1;
}

CMD:gritar(playerid, params[])
{
    if(IsPlayerConnected(playerid) && Logged[playerid] == true)
    {
        if(isnull(params)) return SendClientMessageEx(playerid, -1, "%s Utiliza /Gritar (Grito)", HelpMsg);
        new string[256];
        if(strlen(params) > 80)
        {
            new string2[128];
            format(string2, sizeof(string2), "— %s!!", params[80]);
            strdel(params, 80, strlen(params));
            format(string, sizeof(string), "%s grita: ¡¡%s", RemoveUnderScore(playerid), params);
            ProxDetector(20.0, playerid, string, 0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF);
            ProxDetector(20.0, playerid, string2, 0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF);
        }
        else if(strlen(params) < 80)
        {
            format(string, sizeof(string), "%s grita: ¡¡%s!!", RemoveUnderScore(playerid), params);
            ProxDetector(20.0, playerid, string, 0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF);
        }
    }
    else
    {
        SendClientMessageEx(playerid, -1, "%s Has sido silenciado o no has ingresado al Servidor.", InfoMsg);
    }
    return 1;
}

CMD:susurrar(playerid, params[])
{
    if(IsPlayerConnected(playerid) && Logged[playerid] == true)
    {
        if(isnull(params)) return SendClientMessageEx(playerid, -1, "%s Utiliza /Susurrar (texto)", HelpMsg);
        new string[256];
        if(strlen(params) > 80)
        {
            new string2[128];
            format(string2, sizeof(string2), "— %s", params[80]);
            strdel(params, 80, strlen(params));
            format(string, sizeof(string), "%s susurra: %s", RemoveUnderScore(playerid), params);
            ProxDetector(5.0, playerid, string, 0xBB00BBFF,0xBB00BBFF,0xBB00BBFF,0xBB00BBFF,0xBB00BBFF);
            ProxDetector(5.0, playerid, string2, 0xBB00BBFF,0xBB00BBFF,0xBB00BBFF,0xBB00BBFF,0xBB00BBFF);
        }
        else if(strlen(params) < 80)
        {
            format(string, sizeof(string), "%s susurra: %s", RemoveUnderScore(playerid), params);
            ProxDetector(5.0, playerid, string, 0xBB00BBFF,0xBB00BBFF,0xBB00BBFF,0xBB00BBFF,0xBB00BBFF);
        }
    }
    else
    {
        SendClientMessageEx(playerid, -1, "%s Has sido silenciado o no has ingresado al Servidor.", InfoMsg);
    }
    return 1;
}

CMD:b(playerid, params[])
{
    if(IsPlayerConnected(playerid) && Logged[playerid] == true)
    {
        if(isnull(params)) return SendClientMessageEx(playerid, -1, "%s Utiliza /B (texto)", HelpMsg);
        new string[256];
        if(strlen(params) > 80)
        {
            new string2[128];
            format(string2, sizeof(string2), "— %s))", params[80]);
            strdel(params, 80, strlen(params));
            format(string, sizeof(string), "[OOC]%s: (( %s ", RemoveUnderScore(playerid), params);
            ProxDetector(5.0, playerid, string, 0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF);
            ProxDetector(5.0, playerid, string2, 0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF);
        }
        else if(strlen(params) < 80)
        {
            format(string, sizeof(string), "[OOC]%s: (( %s ))", RemoveUnderScore(playerid), params);
            ProxDetector(5.0, playerid, string, 0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF);
        }
    }
    else
    {
        SendClientMessageEx(playerid, -1, "%s Has sido silenciado o no has ingresado al Servidor.", InfoMsg);
    }
    return 1;
}

CMD:i(playerid, params[]) return cmd_intentar(playerid, params);
CMD:g(playerid, params[]) return cmd_gritar(playerid, params);
CMD:m(playerid, params[]) return cmd_me(playerid, params);