#include <gui/hud/main>
#include <core/player/data>

forward TryTimer(playerid);
public TryTimer(playerid)
{
	TryRole[playerid] = false;
	return 1;
}

stock ServerChat(playerid, text[])
{
    if(Logged[playerid] == true)
    {
        new len = strlen(text), msg[256], cp = 0, bool:found = false;
        for(new i, s; i < len; i++)
        {
            if(text[i] != '+')
            {
                msg[s] = text[i];
                s++;
            }
            else if(!cp && text[i] == '+' && s < 118)
            {
                strcat(msg, "{C2A2DA}-");
                s += 9;
                cp++;
            }
            else if(cp && text[i] == '+' && s < 118)
            {
                strcat(msg, "-{ffffff}");
                s += 9;
                cp = 0;
                found = true;
            }
        }
        new string2[128], string[256];
        if(found)
		{
			if(strlen(msg) >= 80)
			{
				format(string2, sizeof(string2), "— %s", msg[80]);
				strdel(msg, 80, strlen(msg));
				format(string, sizeof(string), "%s%s dice: %s", Acentos(playerid), RemoveUnderScore(playerid), msg);
				ProxDetector(10.0, playerid, string, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xC0C0C0FF, 0xC0C0C0FF);
				ProxDetector(10.0, playerid, string2, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xC0C0C0FF, 0xC0C0C0FF);
			}
			else if(strlen(msg) <= 80)
			{
				format(string, sizeof(string), "%s%s dice: %s", Acentos(playerid), RemoveUnderScore(playerid), msg);
				ProxDetector(10.0, playerid, string, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xC0C0C0FF, 0xC0C0C0FF);
			}
		}
		else
		{
			if(strlen(text) >= 80)
			{
				format(string2, sizeof(string2), "— %s", text[80]);
				strdel(text, 80, strlen(text));
				format(string, sizeof(string), "%s%s dice: %s", Acentos(playerid), RemoveUnderScore(playerid), text);
				ProxDetector(10.0, playerid, string, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xC0C0C0FF, 0xC0C0C0FF);
				ProxDetector(10.0, playerid, string2, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xC0C0C0FF, 0xC0C0C0FF);
			}
			else if(strlen(text) <= 80)
			{
				format(string, sizeof(string), "%s%s dice: %s", Acentos(playerid), RemoveUnderScore(playerid), text);
				ProxDetector(10.0, playerid, string, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xC0C0C0FF, 0xC0C0C0FF);
			}
		}
        SetPlayerChatBubble(playerid, text, 0xFFFFFFFF, 10.0, 5000);
    }
    else
    {
        SendClientMessageEx(playerid, -1, "%s Has sido silenciado o no has ingresado al Servidor.", InfoMsg);
    }
    return 1;
}

stock RoleAction(playerid, text[])
{
	new string[256];
	if(strlen(text) > 80)
	{
	    new string2[128];
	    format(string2, sizeof(string2), "— %s", text[80]);
    	strdel(text, 80, strlen(text));
    	format(string, sizeof(string), "* %s %s", RemoveUnderScore(playerid), text);
    	ProxDetector(10.0, playerid, string, 0xC2A2DAAA,0xC2A2DAAA,0xC2A2DAAA,0xC2A2DAAA,0xC2A2DAAA);
    	ProxDetector(10.0, playerid, string2, 0xC2A2DAAA,0xC2A2DAAA,0xC2A2DAAA,0xC2A2DAAA,0xC2A2DAAA);
	}
	else if(strlen(text) < 80)
	{
        format(string, sizeof(string), "* %s %s", RemoveUnderScore(playerid), text);
    	ProxDetector(10.0, playerid, string, 0xC2A2DAAA,0xC2A2DAAA,0xC2A2DAAA,0xC2A2DAAA,0xC2A2DAAA);
	}
	return 1;
}

stock RoleTry(playerid, text[])
{
    new string[128], rand = random(100);
    if(rand < 50)
    {
        format(string, sizeof(string), "* %s intentó %s y lo consiguió!", RemoveUnderScore(playerid), text);
        ProxDetector(10.0, playerid, string, 0x008000FF,0x008000FF,0x008000FF,0x008000FF,0x008000FF);
    }
    else
    {
        format(string, sizeof(string), "* %s intentó %s pero no lo logró.", RemoveUnderScore(playerid), text);
        ProxDetector(10.0, playerid, string, 0xFF0000FF,0xFF0000FF,0xFF0000FF,0xFF0000FF,0xFF0000FF);
    }
    TryRole[playerid] = true;
    SetTimerEx("TryTimer", 7000, false, "d", playerid);
	return 1;
}

stock RoleEnviron(playerid, text[])
{
	new string[256];
	if(strlen(text) > 80)
	{
	    new string2[128];
	    format(string2, sizeof(string2), "— %s [ID: %d]", text[80], playerid);
    	strdel(text, 80, strlen(text));
    	format(string, sizeof(string), "** %s", text);
    	ProxDetector(10.0, playerid, string, 0x55FF80FF,0x84FFA3FF,0x84FFA3FF,0x84FFA3FF,0x84FFA3FF);
    	ProxDetector(10.0, playerid, string2, 0x55FF80FF,0x84FFA3FF,0x84FFA3FF,0x84FFA3FF,0x84FFA3FF);
	}
	else if(strlen(text) < 80)
	{
        format(string, sizeof(string), "** %s [ID:%d]", text, playerid);
		ProxDetector(10.0, playerid, string, 0x55FF80FF,0x84FFA3FF,0x84FFA3FF,0x84FFA3FF,0x84FFA3FF);
	}
	return 1;
}