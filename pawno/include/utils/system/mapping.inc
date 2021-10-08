//»»»»»»»»»» RESOURCES ««««««««««
#include <core/player/data>
#include <core/server/database>

//»»»»»»»»»» VARIABLES ««««««««««
#define			MAX_OBJETOS				10000
new TObjetos;
#define		MapMsg					"{FF8040}[Map]: "

enum oInfo
{
	ID,
	idobjeto,
	Float:xobjeto,
	Float:yobjeto,
	Float:zobjeto,
	Float:rotx,
	Float:roty,
	Float:rotz,
	vwobjeto,
	intobjeto,
	Owner,
	IDDB,
	Tipo,
	oOwner,
	Move,
	Float:oPosX,
	Float:oPosY,
	Float:oPosZ,
	Float:oRotX,
	Float:oRotY,
	Float:oRotZ,
	Estado
};
new Objetos[MAX_OBJETOS][oInfo];

forward CargarObjetos();
forward GuardarObjetos();
forward CrearObjeto(playerid, idmodelo);

public CargarObjetos()
{
	new query[80];
	mysql_format(g_MySQL, query, sizeof(query), "SELECT * FROM objects");
	new Cache:result = mysql_query(g_MySQL, query);
	for(new idc = 0; idc < cache_num_rows(); idc++)
	{
		cache_get_value_name_int(idc, "idobjeto", Objetos[idc][idobjeto]);
		cache_get_value_name_float(idc, "xobjeto", Objetos[idc][xobjeto]);
		cache_get_value_name_float(idc, "yobjeto", Objetos[idc][yobjeto]);
		cache_get_value_name_float(idc, "zobjeto", Objetos[idc][zobjeto]);
		cache_get_value_name_float(idc, "rotx", Objetos[idc][rotx]);
		cache_get_value_name_float(idc, "roty", Objetos[idc][roty]);
		cache_get_value_name_float(idc, "rotz", Objetos[idc][rotz]);
		cache_get_value_name_int(idc, "vwobjeto", Objetos[idc][vwobjeto]);
		cache_get_value_name_int(idc, "intobjeto", Objetos[idc][intobjeto]);
		cache_get_value_name_int(idc, "Owner", Objetos[idc][Owner]);
		cache_get_value_name_int(idc, "ID_DATABASE", Objetos[idc][IDDB]);
		cache_get_value_name_int(idc, "Tipo", Objetos[idc][Tipo]);
		cache_get_value_name_int(idc, "oOwner", Objetos[idc][oOwner]);
		cache_get_value_name_float(idc, "oPosX", Objetos[idc][oPosX]);
		cache_get_value_name_float(idc, "oPosY", Objetos[idc][oPosY]);
		cache_get_value_name_float(idc, "oPosZ", Objetos[idc][oPosZ]);
		cache_get_value_name_float(idc, "oRotX", Objetos[idc][oRotX]);
		cache_get_value_name_float(idc, "oRotY", Objetos[idc][oRotY]);
		cache_get_value_name_float(idc, "oRotZ", Objetos[idc][oRotZ]);
		cache_get_value_name_int(idc, "Move", Objetos[idc][Move]);
		
		Objetos[idc][Estado] = 1;
		//----------------------------------------------------------
		Objetos[idc][ID] = CreateDynamicObject(Objetos[idc][idobjeto], Objetos[idc][xobjeto], Objetos[idc][yobjeto], Objetos[idc][zobjeto], Objetos[idc][rotx], Objetos[idc][roty], Objetos[idc][rotz], Objetos[idc][vwobjeto], Objetos[idc][intobjeto], -1, 300.00, 300.00);
		//----------------------------------------------------------
		TObjetos++;
	}
	cache_delete(result);
	return 1;
}

public GuardarObjetos()
{
	new query[400];
    for(new i=1; i <= TObjetos;i++)
    {
		mysql_format(g_MySQL, query, sizeof(query), "UPDATE objects SET `xobjeto`= '%f', `yobjeto`= '%f', `zobjeto`= '%f', `rotx`= '%f', `roty`= '%f', `rotz`= '%f', `Tipo`= '%d', `oOwner`= '%d' WHERE `ID_DATABASE`='%d'",
		Objetos[i][xobjeto], Objetos[i][yobjeto], Objetos[i][zobjeto],
		Objetos[i][rotx], Objetos[i][roty], Objetos[i][rotz], Objetos[i][Tipo], Objetos[i][oOwner],
		Objetos[i][IDDB]);
		new Cache:result = mysql_query(g_MySQL, query);
		cache_delete(result);
		//---------------------
		mysql_format(g_MySQL, query, sizeof(query), "UPDATE objects SET `oPosX`= '%f', `oPosY`= '%f', `oPosZ`= '%f', `oRotX`= '%f', `oRotY`= '%f', `oRotZ`= '%f', `Move`= '%d' WHERE `ID_DATABASE`='%d'",
		Objetos[i][oPosX], Objetos[i][oPosY], Objetos[i][oPosZ],
		Objetos[i][oRotX], Objetos[i][oRotY], Objetos[i][oRotZ],
		Objetos[i][Move], Objetos[i][IDDB]);
		result = mysql_query(g_MySQL, query);
		cache_delete(result);
	}
	return 1;
}

public CrearObjeto(playerid, idmodelo)
{
	new NObjeto=TObjetos+1;
	if(NObjeto <= MAX_OBJETOS)
	{
		new Float:pos[3];
		GetPlayerPos(playerid, pos[0], pos[1], pos[2]);
		new vw=GetPlayerVirtualWorld(playerid);
		new inte=GetPlayerInterior(playerid);

		Objetos[NObjeto][ID] = CreateDynamicObject(idmodelo, pos[0], pos[1]+2, pos[2], 0.0, 0.0, 0.0, vw, inte, -1, 300.00, 300.00);

		//-
		Objetos[NObjeto][idobjeto] = idmodelo;
		Objetos[NObjeto][xobjeto] = pos[0];
		Objetos[NObjeto][yobjeto] = pos[1];
		Objetos[NObjeto][zobjeto] = pos[2];
		Objetos[NObjeto][rotx] = 0.00;
		Objetos[NObjeto][roty] = 0.00;
		Objetos[NObjeto][rotz] = 0.00;
		Objetos[NObjeto][vwobjeto] = vw;
		Objetos[NObjeto][intobjeto] = inte;
		Objetos[NObjeto][Owner] = PlayersData[playerid][UUID];
		Objetos[NObjeto][Tipo] = 0;
		Objetos[NObjeto][oOwner] = 0;
		Objetos[NObjeto][oPosX] = 0;
		Objetos[NObjeto][oPosY] = 0;
		Objetos[NObjeto][oPosZ] = 0;
		Objetos[NObjeto][oRotX] = 0;
		Objetos[NObjeto][oRotY] = 0;
		Objetos[NObjeto][oRotZ] = 0;
		Objetos[NObjeto][Move] = 0;

		new query[400];
		mysql_format(g_MySQL, query, sizeof(query), "INSERT INTO `objects` (`idobjeto`, `xobjeto`, `yobjeto`, `zobjeto`, `rotx`, `roty`, `rotz`, `vwobjeto`, `intobjeto`, `Owner`) VALUES ('%d', '%f', '%f', '%f', '%f', '%f', '%f', '%d', '%d', '%d')",
		Objetos[NObjeto][idobjeto], Objetos[NObjeto][xobjeto],
		Objetos[NObjeto][yobjeto], Objetos[NObjeto][zobjeto], Objetos[NObjeto][rotx],
		Objetos[NObjeto][roty], Objetos[NObjeto][rotz], Objetos[NObjeto][vwobjeto],
		Objetos[NObjeto][intobjeto], Objetos[NObjeto][Owner]);
		new Cache:result=mysql_query(g_MySQL, query);
		Objetos[NObjeto][IDDB] = cache_insert_id();
		cache_delete(result);

		EditDynamicObject(playerid, Objetos[NObjeto][ID]);
		Editando[playerid] = 1;
		EditObj[playerid] = NObjeto;

		SendClientMessageEx(playerid, -1, "%s Creaste un Objeto nuevo ID: %d | Modelo: %d", MapMsg, NObjeto, Objetos[NObjeto][idobjeto]);
		TObjetos++;
	}
	else
	{
		SendClientMessageEx(playerid, -1, "%s Se ha superado el máximo de %d Objetos.", InfoMsg, MAX_OBJETOS);
	}
	return 1;
}