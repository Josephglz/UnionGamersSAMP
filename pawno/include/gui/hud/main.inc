#include <core/player/data>
#include <gui/hud/textdraw>

#define         InfoMsg         "{AEAEAE}[Info]:"
#define			HelpMsg			"{E96BDC}[Ayuda]:"
#define         DudaMsg         "{FF80C0}[Dudas]:"
#define         WhisperMsg      "{FF9DFF}[Whisper]:"
#define         AlertMsg        "{FF4040}[Admin]"
#define         RadioMsg        "{62B0FF}* [Radio]:"
#define         FamilyMsg       "{84FFFF}* [Family]:"
#define         MapperMsg       "{8000FF}[Mapper]:"

new AdminsRangosColorsHEX[9] =
{
	0x00FFFFFF, //Auxiliar
	0x00FF80FF, //Staff
	0x80FF00FF, //Moderador 1
	0x00FF00FF, //Moderador 2
	0x008000FF, //Moderador 3
	0x804040FF, //Moderador Global
	0x800000FF, //Co-Administrador
    0xFF0000FF, //Administrador
    0x808080FF, //Scripter
};

stock GetAdminColorTag(AdminRank, TagType)
{
    new tag[30];
    switch(TagType)
    {
        case 1: //Just Color ({000000})
        {
            switch(AdminRank)
            {
                case 0: {   tag = "";   }
                case 1: {   tag = "{00FFFF}";    }    case 2: {   tag = "{00FF80}";    }    case 3: {   tag = "{80FF00}";    }
                case 4: {   tag = "{00FF00}";    }    case 5: {   tag = "{008000}";    }    case 6: {   tag = "{804040}";    }
                case 7: {   tag = "{800000}";    }    case 8: {   tag = "{FF0000}";    }    case 9: {   tag = "{808080}";    }
            }
        }
        case 2: //Admin Colored Name ({000000}Moderador)
        {
            switch(AdminRank)
            {
                case 0: {   tag = "";   }
                case 1: {   tag = "{00FFFF}Auxiliar";    }    case 2: {   tag = "{00FF80}Staff";    }    case 3: {   tag = "{80FF00}Moderador 1";    }
                case 4: {   tag = "{00FF00}Moderador 2";    }    case 5: {   tag = "{008000}Moderador 3";    }    case 6: {   tag = "{804040}Coordinador";    }
                case 7: {   tag = "{800000}Co-Admin";    }    case 8: {   tag = "{FF0000}Administrador";    }    case 9: {   tag = "{808080}Scripter";    }
            }
        }
        case 3: //Admin Name (Moderador)
        {
            switch(AdminRank)
            {
                case 0: {   tag = "";   }
                case 1: {   tag = "Auxiliar";    }    case 2: {   tag = "Staff";    }    case 3: {   tag = "Moderador 1";    }
                case 4: {   tag = "Moderador 2";    }    case 5: {   tag = "Moderador 3";    }    case 6: {   tag = "Coordinador";    }
                case 7: {   tag = "Co-Admin";    }    case 8: {   tag = "Administrador";    }    case 9: {   tag = "Scripter";    }
            }
        }
    }
    return tag;
}

stock RemoveUnderScore(playerid)
{
    new name[MAX_PLAYER_NAME];
    GetPlayerName(playerid,name,sizeof(name));
    for(new i = 0; i < MAX_PLAYER_NAME; i++)
    {
        if(name[i] == '_') name[i] = ' ';
    }
    return name;
}

stock Acentos(playerid)
{
	new acento[65];
	switch(PlayersData[playerid][Origin])
	{
	    case 0:		{	acento="";}
		case 1:		{acento="[Acento Inglés] ";}
		case 2:		{acento="[Acento Ruso] ";}
		case 3:     {acento="[Acento Italiano] ";}
		case 4:     {acento="[Acento Aleman] ";}
	    case 5:     {acento="[Acento Japones] ";}
		case 6:     {acento="[Acento Latino] ";}
		case 7:     {acento="[Acento Francés] ";}
		case 8:     {acento="[Acento Chino] ";}
		case 9:     {acento="[Acento Portugues] ";}
		case 10:    {acento="[Acento Mexicano] ";}
		case 11:    {acento="[Acento Colombiano] ";}
		case 12:    {acento="[Acento Venezolano] ";}
		case 13:    {acento="[Acento Peruano] ";}
		case 14:    {acento="[Acento Ecuatoriano] ";}
		case 15:    {acento="[Acento Argentino] ";}
		case 16:    {acento="[Acento Chileno] ";}
		case 17:    {acento="[Acento Uruguayo] ";}
		case 18:    {acento="[Acento Dominicano] ";}
		case 19:    {acento="[Acento Puerto Rico] ";}
	}
	return acento;
}

stock ProxDetector(Float:DistaciaRadio, playerid, stringg[],coll1,coll2,coll3,coll4,coll5)
{
    if(IsPlayerConnected(playerid))
    {
        new Float:posx, Float:posy, Float:posz;
        new Float:oldposx, Float:oldposy, Float:oldposz;
        new Float:tempposx, Float:tempposy, Float:tempposz;
        GetPlayerPos(playerid, oldposx, oldposy, oldposz);
        for(new i = 0; i < MAX_PLAYERS; i++)
        {
            if(IsPlayerConnected(i) && (GetPlayerVirtualWorld(playerid) == GetPlayerVirtualWorld(i)))
            {
                GetPlayerPos(i, posx, posy, posz);
                tempposx = (oldposx -posx);
                tempposy = (oldposy -posy);
                tempposz = (oldposz -posz);
                if (((tempposx < DistaciaRadio/16) && (tempposx > -DistaciaRadio/16)) && ((tempposy < DistaciaRadio/16) && (tempposy > -DistaciaRadio/16)) && ((tempposz < DistaciaRadio/16) && (tempposz > -DistaciaRadio/16)))
                {
                    SendClientMessage(i, coll1, stringg);
                }
                else if (((tempposx < DistaciaRadio/8) && (tempposx > -DistaciaRadio/8)) && ((tempposy < DistaciaRadio/8) && (tempposy > -DistaciaRadio/8)) && ((tempposz < DistaciaRadio/8) && (tempposz > -DistaciaRadio/8)))
                {
                    SendClientMessage(i, coll2, stringg);
                }
                else if (((tempposx < DistaciaRadio/4) && (tempposx > -DistaciaRadio/4)) && ((tempposy < DistaciaRadio/4) && (tempposy > -DistaciaRadio/4)) && ((tempposz < DistaciaRadio/4) && (tempposz > -DistaciaRadio/4)))
                {
                    SendClientMessage(i, coll3, stringg);
                }
                else if (((tempposx < DistaciaRadio/2) && (tempposx > -DistaciaRadio/2)) && ((tempposy < DistaciaRadio/2) && (tempposy > -DistaciaRadio/2)) && ((tempposz < DistaciaRadio/2) && (tempposz > -DistaciaRadio/2)))
                {
                    SendClientMessage(i, coll4, stringg);
                }
                else if (((tempposx < DistaciaRadio) && (tempposx > -DistaciaRadio)) && ((tempposy < DistaciaRadio) && (tempposy > -DistaciaRadio)) && ((tempposz < DistaciaRadio) && (tempposz > -DistaciaRadio)))
                {
                    SendClientMessage(i, coll5, stringg);
                }
            }
        }
    }
    return 1;
}

stock ShowDeathTextDraw(playerid)
{
    SelectTextDraw(playerid, 0x00FF00FF);
    TextDrawShowForPlayer(playerid, DeadTD1);
	TextDrawShowForPlayer(playerid, DeadTD2);
	TextDrawShowForPlayer(playerid, DeadTD3);
	TextDrawShowForPlayer(playerid, DeadTD_Button);
	PlayerTextDrawShow(playerid, DeadTD_Time[playerid]);
    return 1;
}

stock HideDeathTextDraw(playerid)
{
    TextDrawHideForPlayer(playerid, DeadTD1);
	TextDrawHideForPlayer(playerid, DeadTD2);
	TextDrawHideForPlayer(playerid, DeadTD3);
	TextDrawHideForPlayer(playerid, DeadTD_Button);
	PlayerTextDrawHide(playerid, DeadTD_Time[playerid]);
    CancelSelectTextDraw(playerid);
    return 1;
}