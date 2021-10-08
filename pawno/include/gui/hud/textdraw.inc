#include    <progress2>
#include	<mselection>
#include 	<core/player/data>

/*===============       [ TEXTDRAW ]     =============== */
new Text:LoginBackground;
new Text:logoUG;

new Text:Reloj1;
new Text:Reloj2;

new Text:DeadTD1;
new Text:DeadTD_Button;
new Text:DeadTD2;
new Text:DeadTD3;

new Text:DNI0;

new Text:bank_base;
new Text:bank_retirar;
new Text:bank_depositar;
new Text:bank_transferir;
new Text:bank_consultar;
new Text:bank_close;
new PlayerText:bank_name[MAX_PLAYERS];
new PlayerText:bank_account[MAX_PLAYERS];
new PlayerText:bank_money[MAX_PLAYERS];

new PlayerText:DeadTD_Time[MAX_PLAYERS];
new PlayerText:DNIT[MAX_PLAYERS][11];

new PlayerText:Vel_Base[MAX_PLAYERS];
new PlayerText:Vel_Speed[MAX_PLAYERS];
new PlayerText:Vel_iAceite[MAX_PLAYERS];
new PlayerText:Vel_Luces[MAX_PLAYERS];
new PlayerText:Vel_Motor[MAX_PLAYERS];
new PlayerText:Vel_Seat[MAX_PLAYERS];
new PlayerText:Vel_Lock[MAX_PLAYERS];

new PlayerText:TNotif0[MAX_PLAYERS];
new PlayerText:TNotif1[MAX_PLAYERS];
new PlayerText:TNotif2[MAX_PLAYERS];
/*===============       [ PROGRESSBAR ]     =============== */
new PlayerBar:PJ_Food[MAX_PLAYERS];
new PlayerBar:PJ_Drink[MAX_PLAYERS];
new PlayerBar:Vel_AceiteBar[MAX_PLAYERS];
new PlayerBar:Vel_GasoBar[MAX_PLAYERS];

/*===============       [ Menu Models ]     =============== */
new				SkinList	 		=		mS_INVALID_LISTID;
/*==============================	[		DATA		]	==============================*/

new Float: Cajeros[ ] [11] =
{
    {1186.6648,-1373.9617,13.5654},
	{1454.7147,-1755.0813,13.5469},
	{2139.6604,-1158.6201,23.9922},
	{1918.1725,-1765.6124,13.5469},
	{1009.0899,-929.5151,42.3281},
	{563.8561,-1293.1998,17.2482},
	{512.9917,-1525.2611,14.7242},
	{2390.4744,-1899.0654,13.5469},
	{1387.2382,-1011.3671,27.0197},
	{370.7484,-1726.5264,7.1607},
	{1242.3656,759.0308,-20.0823}
};

new Float: Gasolineras[ ] [5] =
{
	{1382.31, 460.135, 20.345},
	{655.523, -565.018, 16.336},
	{1004.08, -937.536, 42.328},
	{-91.111, -1168.62, 2.429},
	{1940.92, -1772.82, 13.641}
};

new Float: VendingMachinePos[ ][45] =
{
    {-14.70,  1175.36,   18.95},
    {201.02,  -107.62,    0.90},
    {662.43,  -552.16,   15.71},
    {-76.03,  1227.99,   19.13},
    {1154.73, -1460.89,   15.16},
    {1277.84,   372.52,   18.95},
    {1398.84,  2222.61,   10.42},
    {1520.15,  1055.27,   10.00},
    {1634.11, -2237.53,   12.89},
    {1659.46,  1722.86,   10.22},
    {1729.79, -1943.05,   12.95},
    {1789.21, -1369.27,   15.16},
    {1928.73, -1772.45,   12.95},
    {2060.12, -1897.64,   12.93},
    {2085.77,  2071.36,   10.45},
    {2139.52, -1161.48,   23.36},
    {2153.23, -1016.15,   62.23},
    {2271.73,   -76.46,   25.96},
    {2319.99,  2532.85,   10.22},
    {2325.98, -1645.13,   14.21},
    {2352.18, -1357.16,   23.77},
    {2480.86, -1959.27,   12.96},
    {2503.14,  1243.70,   10.22},
    {-253.74,  2597.95,   62.24},
    {-253.74,  2599.76,   62.24},
    {2647.70,  1129.66,   10.22},
    {2845.73,  1295.05,   10.79},
    {-862.83,  1536.61,   21.98},
    {-1350.12,   492.29,   10.59},
    {-1350.12,   493.86,   10.59},
    {-1455.12,  2591.66,   55.23},
    {-1980.79,   142.66,   27.07},
    {-2005.65,  -490.05,   34.73},
    {-2011.14,  -398.34,   34.73},
    {-2034.46,  -490.05,   34.73},
    {-2039.85,  -398.34,   34.73},
    {-2063.27,  -490.05,   34.73},
    {-2068.56,  -398.34,   34.73},
    {-2092.09,  -490.05,   34.73},
    {-2097.27,  -398.34,   34.73},
    {-2118.62,  -422.41,   34.73},
    {-2118.97,  -423.65,   34.73},
    {-2229.19,   286.41,   34.70},
    {-2420.18,   985.95,   44.30},
    {-2420.22,   984.58,   44.30}
};
/*===============       [ STOCKS ]     =============== */
stock CreateTextDraws()
{
    LoginBackground = TextDrawCreate(0.000000, -1.000000, "mdl-2001:login");
	TextDrawFont(LoginBackground, 4);
	TextDrawLetterSize(LoginBackground, 0.600000, 2.000000);
	TextDrawTextSize(LoginBackground, 641.500000, 449.500000);
	TextDrawSetOutline(LoginBackground, 1);
	TextDrawSetShadow(LoginBackground, 0);
	TextDrawAlignment(LoginBackground, 1);
	TextDrawColor(LoginBackground, -1);
	TextDrawBackgroundColor(LoginBackground, 255);
	TextDrawBoxColor(LoginBackground, 50);
	TextDrawUseBox(LoginBackground, 1);
	TextDrawSetProportional(LoginBackground, 1);
	TextDrawSetSelectable(LoginBackground, 0);

    logoUG = TextDrawCreate(5.000000, 410.000000, "mdl-2002:logo");
    TextDrawFont(logoUG, 4);
    TextDrawLetterSize(logoUG, 0.600000, 2.000000);
    TextDrawTextSize(logoUG, 30.000000, 30.000000);
    TextDrawSetOutline(logoUG, 1);
    TextDrawSetShadow(logoUG, 0);
    TextDrawAlignment(logoUG, 1);
    TextDrawColor(logoUG, -1);
    TextDrawBackgroundColor(logoUG, 255);
    TextDrawBoxColor(logoUG, 50);
    TextDrawUseBox(logoUG, 1);
    TextDrawSetProportional(logoUG, 1);
    TextDrawSetSelectable(logoUG, 0);

	DNI0 = TextDrawCreate(176.449508, 123.499992, "mdl-2003:dni");//DNI
	TextDrawLetterSize(DNI0, 0.000000, 0.000000);//DNI
	TextDrawTextSize(DNI0, 295.000000, 177.000000);//DNI
	TextDrawAlignment(DNI0, 1);//DNI
	TextDrawColor(DNI0, -1);//DNI
	TextDrawSetShadow(DNI0, 0);//DNI
	TextDrawSetOutline(DNI0, 0);//DNI
	TextDrawBackgroundColor(DNI0, 255);//DNI
	TextDrawFont(DNI0, 4);//DNI
	TextDrawSetProportional(DNI0, 0);//DNI
	TextDrawSetShadow(DNI0, 0);//DNI

    Reloj1 = TextDrawCreate(551.000000,23.000000,"--");//RELOJ
    TextDrawAlignment(Reloj1,0);//RELOJ
    TextDrawBackgroundColor(Reloj1,0x000000FF);//RELOJ
    TextDrawLetterSize(Reloj1,0.399999,2.000000);//RELOJ
    TextDrawColor(Reloj1,0xFFFFFFFF);//RELOJ
    TextDrawSetOutline(Reloj1,1);//RELOJ
    TextDrawSetProportional(Reloj1,1);//RELOJ
    TextDrawSetShadow(Reloj1,1);//RELOJ

    Reloj2 = TextDrawCreate(470.000000,5.000000, "--");//RELOJ
    TextDrawAlignment(Reloj2,0);//RELOJ
    TextDrawBackgroundColor(Reloj2,0x000000FF);//RELOJ
    TextDrawLetterSize(Reloj2,0.399999,2.000000);//RELOJ
    TextDrawColor(Reloj2,0xFFFFFFFF);//RELOJ
    TextDrawSetOutline(Reloj2,1);//RELOJ
    TextDrawSetProportional(Reloj2,1);//RELOJ
    TextDrawSetShadow(Reloj2,1);//RELOJ

    DeadTD1 = TextDrawCreate(320.000000, 2.000000, "_");
    TextDrawFont(DeadTD1, 1);
    TextDrawLetterSize(DeadTD1, 0.708333, 49.300010);
    TextDrawTextSize(DeadTD1, 302.000000, 636.500000);
    TextDrawSetOutline(DeadTD1, 1);
    TextDrawSetShadow(DeadTD1, 0);
    TextDrawAlignment(DeadTD1, 2);
    TextDrawColor(DeadTD1, -1);
    TextDrawBackgroundColor(DeadTD1, 255);
    TextDrawBoxColor(DeadTD1, -1962934137);
    TextDrawUseBox(DeadTD1, 1);
    TextDrawSetProportional(DeadTD1, 1);
    TextDrawSetSelectable(DeadTD1, 0);

    DeadTD_Button = TextDrawCreate(306.000000, 321.000000, "Rendirse");
    TextDrawFont(DeadTD_Button, 2);
    TextDrawLetterSize(DeadTD_Button, 0.258332, 1.750000);
    TextDrawTextSize(DeadTD_Button, 16.500000, 90.500000);
    TextDrawSetOutline(DeadTD_Button, 1);
    TextDrawSetShadow(DeadTD_Button, 0);
    TextDrawAlignment(DeadTD_Button, 2);
    TextDrawColor(DeadTD_Button, -1);
    TextDrawBackgroundColor(DeadTD_Button, 255);
    TextDrawBoxColor(DeadTD_Button, 200);
    TextDrawUseBox(DeadTD_Button, 1);
    TextDrawSetProportional(DeadTD_Button, 1);
    TextDrawSetSelectable(DeadTD_Button, 1);

    DeadTD2 = TextDrawCreate(310.000000, 157.000000, "Te encuentras Herido");
    TextDrawFont(DeadTD2, 1);
    TextDrawLetterSize(DeadTD2, 0.604166, 3.500000);
    TextDrawTextSize(DeadTD2, 400.000000, 462.000000);
    TextDrawSetOutline(DeadTD2, 1);
    TextDrawSetShadow(DeadTD2, 1);
    TextDrawAlignment(DeadTD2, 2);
    TextDrawColor(DeadTD2, -1);
    TextDrawBackgroundColor(DeadTD2, 255);
    TextDrawBoxColor(DeadTD2, 50);
    TextDrawUseBox(DeadTD2, 0);
    TextDrawSetProportional(DeadTD2, 1);
    TextDrawSetSelectable(DeadTD2, 0);

    DeadTD3 = TextDrawCreate(393.000000, 207.000000, "Tiempo Restante");
    TextDrawFont(DeadTD3, 1);
    TextDrawLetterSize(DeadTD3, 0.600000, 2.000000);
    TextDrawTextSize(DeadTD3, 400.000000, 17.000000);
    TextDrawSetOutline(DeadTD3, 1);
    TextDrawSetShadow(DeadTD3, 0);
    TextDrawAlignment(DeadTD3, 3);
    TextDrawColor(DeadTD3, -1);
    TextDrawBackgroundColor(DeadTD3, 255);
    TextDrawBoxColor(DeadTD3, 50);
    TextDrawUseBox(DeadTD3, 0);
    TextDrawSetProportional(DeadTD3, 1);
    TextDrawSetSelectable(DeadTD3, 0);

	bank_base = TextDrawCreate(185.000000, 118.000000, "mdl-2004:bank");
	TextDrawFont(bank_base, 4);
	TextDrawLetterSize(bank_base, 0.600000, 2.000000);
	TextDrawTextSize(bank_base, 268.500000, 197.000000);
	TextDrawSetOutline(bank_base, 1);
	TextDrawSetShadow(bank_base, 0);
	TextDrawAlignment(bank_base, 1);
	TextDrawColor(bank_base, -1);
	TextDrawBackgroundColor(bank_base, 255);
	TextDrawBoxColor(bank_base, 50);
	TextDrawUseBox(bank_base, 1);
	TextDrawSetProportional(bank_base, 1);
	TextDrawSetSelectable(bank_base, 0);

	bank_retirar = TextDrawCreate(319.000000, 198.000000, "_");
	TextDrawFont(bank_retirar, 1);
	TextDrawLetterSize(bank_retirar, 0.600000, 2.100000);
	TextDrawTextSize(bank_retirar, 294.500000, 55.500000);
	TextDrawSetOutline(bank_retirar, 1);
	TextDrawSetShadow(bank_retirar, 0);
	TextDrawAlignment(bank_retirar, 2);
	TextDrawColor(bank_retirar, -1);
	TextDrawBackgroundColor(bank_retirar, 255);
	TextDrawBoxColor(bank_retirar, 0);
	TextDrawUseBox(bank_retirar, 1);
	TextDrawSetProportional(bank_retirar, 1);
	TextDrawSetSelectable(bank_retirar, 1);

	bank_depositar = TextDrawCreate(392.000000, 198.000000, "_");
	TextDrawFont(bank_depositar, 1);
	TextDrawLetterSize(bank_depositar, 0.600000, 2.100000);
	TextDrawTextSize(bank_depositar, 294.500000, 55.500000);
	TextDrawSetOutline(bank_depositar, 1);
	TextDrawSetShadow(bank_depositar, 0);
	TextDrawAlignment(bank_depositar, 2);
	TextDrawColor(bank_depositar, -1);
	TextDrawBackgroundColor(bank_depositar, 255);
	TextDrawBoxColor(bank_depositar, 0);
	TextDrawUseBox(bank_depositar, 1);
	TextDrawSetProportional(bank_depositar, 1);
	TextDrawSetSelectable(bank_depositar, 1);

	bank_transferir = TextDrawCreate(319.000000, 235.000000, "_");
	TextDrawFont(bank_transferir, 1);
	TextDrawLetterSize(bank_transferir, 0.600000, 2.100000);
	TextDrawTextSize(bank_transferir, 294.500000, 55.500000);
	TextDrawSetOutline(bank_transferir, 1);
	TextDrawSetShadow(bank_transferir, 0);
	TextDrawAlignment(bank_transferir, 2);
	TextDrawColor(bank_transferir, -1);
	TextDrawBackgroundColor(bank_transferir, 255);
	TextDrawBoxColor(bank_transferir, 0);
	TextDrawUseBox(bank_transferir, 1);
	TextDrawSetProportional(bank_transferir, 1);
	TextDrawSetSelectable(bank_transferir, 1);

	bank_consultar = TextDrawCreate(392.000000, 235.000000, "_");
	TextDrawFont(bank_consultar, 1);
	TextDrawLetterSize(bank_consultar, 0.600000, 2.100000);
	TextDrawTextSize(bank_consultar, 294.500000, 55.500000);
	TextDrawSetOutline(bank_consultar, 1);
	TextDrawSetShadow(bank_consultar, 0);
	TextDrawAlignment(bank_consultar, 2);
	TextDrawColor(bank_consultar, -1);
	TextDrawBackgroundColor(bank_consultar, 255);
	TextDrawBoxColor(bank_consultar, 0);
	TextDrawUseBox(bank_consultar, 1);
	TextDrawSetProportional(bank_consultar, 1);
	TextDrawSetSelectable(bank_consultar, 1);

	bank_close = TextDrawCreate(438.000000, 120.000000, "_");
	TextDrawFont(bank_close, 1);
	TextDrawLetterSize(bank_close, 0.600000, 2.100000);
	TextDrawTextSize(bank_close, 294.500000, 24.000000);
	TextDrawSetOutline(bank_close, 1);
	TextDrawSetShadow(bank_close, 0);
	TextDrawAlignment(bank_close, 2);
	TextDrawColor(bank_close, -1);
	TextDrawBackgroundColor(bank_close, 255);
	TextDrawBoxColor(bank_close, 0);
	TextDrawUseBox(bank_close, 1);
	TextDrawSetProportional(bank_close, 1);
	TextDrawSetSelectable(bank_close, 1);
    return 1;
}

stock CreatePlayerTextDrawEx(playerid)
{
    DeadTD_Time[playerid] = CreatePlayerTextDraw(playerid, 341.000000, 237.000000, "000 segundos");
    PlayerTextDrawFont(playerid, DeadTD_Time[playerid], 1);
    PlayerTextDrawLetterSize(playerid, DeadTD_Time[playerid], 0.229166, 2.000000);
    PlayerTextDrawTextSize(playerid, DeadTD_Time[playerid], 400.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, DeadTD_Time[playerid], 1);
    PlayerTextDrawSetShadow(playerid, DeadTD_Time[playerid], 0);
    PlayerTextDrawAlignment(playerid, DeadTD_Time[playerid], 3);
    PlayerTextDrawColor(playerid, DeadTD_Time[playerid], -1);
    PlayerTextDrawBackgroundColor(playerid, DeadTD_Time[playerid], 255);
    PlayerTextDrawBoxColor(playerid, DeadTD_Time[playerid], 50);
    PlayerTextDrawUseBox(playerid, DeadTD_Time[playerid], 0);
    PlayerTextDrawSetProportional(playerid, DeadTD_Time[playerid], 1);
    PlayerTextDrawSetSelectable(playerid, DeadTD_Time[playerid], 0);

    DNIT[playerid][0] = CreatePlayerTextDraw(playerid, 176.449508, 156.750076, "");//DNI
	PlayerTextDrawLetterSize(playerid, DNIT[playerid][0], 0.000000, 0.000000);//DNI
	PlayerTextDrawTextSize(playerid, DNIT[playerid][0], 115.000000, 107.000000);//DNI
	PlayerTextDrawAlignment(playerid, DNIT[playerid][0], 1);//DNI
	PlayerTextDrawColor(playerid, DNIT[playerid][0], -1);//DNI
	PlayerTextDrawSetShadow(playerid, DNIT[playerid][0], 0);//DNI
	PlayerTextDrawSetOutline(playerid, DNIT[playerid][0], 0);//DNI
	PlayerTextDrawBackgroundColor(playerid, DNIT[playerid][0], 0);//DNI
	PlayerTextDrawFont(playerid, DNIT[playerid][0], 5);//DNI
	PlayerTextDrawSetProportional(playerid, DNIT[playerid][0], 0);//DNI
	PlayerTextDrawSetShadow(playerid, DNIT[playerid][0], 0);//DNI
	PlayerTextDrawSetPreviewModel(playerid, DNIT[playerid][0], 35);//DNI
	PlayerTextDrawSetPreviewRot(playerid, DNIT[playerid][0], 0.000000, 0.000000, 0.000000, 1.000000);//DNI

	DNIT[playerid][1] = CreatePlayerTextDraw(playerid, 289.531494, 154.416687, "00000000");//DNI
	PlayerTextDrawLetterSize(playerid, DNIT[playerid][1], 0.254289, 2.329164);//DNI
	PlayerTextDrawAlignment(playerid, DNIT[playerid][1], 1);//DNI
	PlayerTextDrawColor(playerid, DNIT[playerid][1], -2147483393);//DNI
	PlayerTextDrawSetShadow(playerid, DNIT[playerid][1], 0);//DNI
	PlayerTextDrawSetOutline(playerid, DNIT[playerid][1], 0);//DNI
	PlayerTextDrawBackgroundColor(playerid, DNIT[playerid][1], 255);//DNI
	PlayerTextDrawFont(playerid, DNIT[playerid][1], 1);//DNI
	PlayerTextDrawSetProportional(playerid, DNIT[playerid][1], 1);//DNI
	PlayerTextDrawSetShadow(playerid, DNIT[playerid][1], 0);//DNI

	DNIT[playerid][2] = CreatePlayerTextDraw(playerid, 301.244415, 173.666717, "00");//DNI
	PlayerTextDrawLetterSize(playerid, DNIT[playerid][2], 0.310512, 1.920832);//DNI
	PlayerTextDrawAlignment(playerid, DNIT[playerid][2], 1);//DNI
	PlayerTextDrawColor(playerid, DNIT[playerid][2], -2147483393);//DNI
	PlayerTextDrawSetShadow(playerid, DNIT[playerid][2], 0);//DNI
	PlayerTextDrawSetOutline(playerid, DNIT[playerid][2], 0);//DNI
	PlayerTextDrawBackgroundColor(playerid, DNIT[playerid][2], 255);//DNI
	PlayerTextDrawFont(playerid, DNIT[playerid][2], 1);//DNI
	PlayerTextDrawSetProportional(playerid, DNIT[playerid][2], 1);//DNI
	PlayerTextDrawSetShadow(playerid, DNIT[playerid][2], 0);//DNI

	DNIT[playerid][3] = CreatePlayerTextDraw(playerid, 310.146514, 191.750030, "Union");//DNI
	PlayerTextDrawLetterSize(playerid, DNIT[playerid][3], 0.400000, 1.600000);//DNI
	PlayerTextDrawAlignment(playerid, DNIT[playerid][3], 1);//DNI
	PlayerTextDrawColor(playerid, DNIT[playerid][3], -2147483393);//DNI
	PlayerTextDrawSetShadow(playerid, DNIT[playerid][3], 0);//DNI
	PlayerTextDrawSetOutline(playerid, DNIT[playerid][3], 0);//DNI
	PlayerTextDrawBackgroundColor(playerid, DNIT[playerid][3], 255);//DNI
	PlayerTextDrawFont(playerid, DNIT[playerid][3], 1);//DNI
	PlayerTextDrawSetProportional(playerid, DNIT[playerid][3], 1);//DNI
	PlayerTextDrawSetShadow(playerid, DNIT[playerid][3], 0);//DNI

	DNIT[playerid][4] = CreatePlayerTextDraw(playerid, 314.363281, 206.916656, "Gamers");//DNI
	PlayerTextDrawLetterSize(playerid, DNIT[playerid][4], 0.400000, 1.600000);//DNI
	PlayerTextDrawAlignment(playerid, DNIT[playerid][4], 1);//DNI
	PlayerTextDrawColor(playerid, DNIT[playerid][4], -2147483393);//DNI
	PlayerTextDrawSetShadow(playerid, DNIT[playerid][4], 0);//DNI
	PlayerTextDrawSetOutline(playerid, DNIT[playerid][4], 0);//DNI
	PlayerTextDrawBackgroundColor(playerid, DNIT[playerid][4], 255);//DNI
	PlayerTextDrawFont(playerid, DNIT[playerid][4], 1);//DNI
	PlayerTextDrawSetProportional(playerid, DNIT[playerid][4], 1);//DNI
	PlayerTextDrawSetShadow(playerid, DNIT[playerid][4], 0);//DNI

	DNIT[playerid][5] = CreatePlayerTextDraw(playerid, 319.048614, 222.666610, "Faccion");//DNI
	PlayerTextDrawLetterSize(playerid, DNIT[playerid][5], 0.400000, 1.600000);//DNI
	PlayerTextDrawAlignment(playerid, DNIT[playerid][5], 1);//DNI
	PlayerTextDrawColor(playerid, DNIT[playerid][5], -2147483393);//DNI
	PlayerTextDrawSetShadow(playerid, DNIT[playerid][5], 0);//DNI
	PlayerTextDrawSetOutline(playerid, DNIT[playerid][5], 0);//DNI
	PlayerTextDrawBackgroundColor(playerid, DNIT[playerid][5], 255);//DNI
	PlayerTextDrawFont(playerid, DNIT[playerid][5], 1);//DNI
	PlayerTextDrawSetProportional(playerid, DNIT[playerid][5], 1);//DNI
	PlayerTextDrawSetShadow(playerid, DNIT[playerid][5], 0);//DNI

	DNIT[playerid][6] = CreatePlayerTextDraw(playerid, 315.300384, 238.999969, "Rango");//DNI
	PlayerTextDrawLetterSize(playerid, DNIT[playerid][6], 0.400000, 1.600000);//DNI
	PlayerTextDrawAlignment(playerid, DNIT[playerid][6], 1);//DNI
	PlayerTextDrawColor(playerid, DNIT[playerid][6], -2147483393);//DNI
	PlayerTextDrawSetShadow(playerid, DNIT[playerid][6], 0);//DNI
	PlayerTextDrawSetOutline(playerid, DNIT[playerid][6], 0);//DNI
	PlayerTextDrawBackgroundColor(playerid, DNIT[playerid][6], 255);//DNI
	PlayerTextDrawFont(playerid, DNIT[playerid][6], 1);//DNI
	PlayerTextDrawSetProportional(playerid, DNIT[playerid][6], 1);//DNI
	PlayerTextDrawSetShadow(playerid, DNIT[playerid][6], 0);//DNI

	DNIT[playerid][7] = CreatePlayerTextDraw(playerid, 325.139282, 273.416625, "M");//DNI
	PlayerTextDrawLetterSize(playerid, DNIT[playerid][7], 0.400000, 1.600000);//DNI
	PlayerTextDrawAlignment(playerid, DNIT[playerid][7], 1);//DNI
	PlayerTextDrawColor(playerid, DNIT[playerid][7], -2147483393);//DNI
	PlayerTextDrawSetShadow(playerid, DNIT[playerid][7], 0);//DNI
	PlayerTextDrawSetOutline(playerid, DNIT[playerid][7], 0);//DNI
	PlayerTextDrawBackgroundColor(playerid, DNIT[playerid][7], 255);//DNI
	PlayerTextDrawFont(playerid, DNIT[playerid][7], 1);//DNI
	PlayerTextDrawSetProportional(playerid, DNIT[playerid][7], 1);//DNI
	PlayerTextDrawSetShadow(playerid, DNIT[playerid][7], 0);//DNI

	DNIT[playerid][8] = CreatePlayerTextDraw(playerid, 360.278259, 269.916717, "0.00");//DNI
	PlayerTextDrawLetterSize(playerid, DNIT[playerid][8], 0.307231, 1.879999);//DNI
	PlayerTextDrawAlignment(playerid, DNIT[playerid][8], 1);//DNI
	PlayerTextDrawColor(playerid, DNIT[playerid][8], -2147483393);//DNI
	PlayerTextDrawSetShadow(playerid, DNIT[playerid][8], 0);//DNI
	PlayerTextDrawSetOutline(playerid, DNIT[playerid][8], 0);//DNI
	PlayerTextDrawBackgroundColor(playerid, DNIT[playerid][8], 255);//DNI
	PlayerTextDrawFont(playerid, DNIT[playerid][8], 1);//DNI
	PlayerTextDrawSetProportional(playerid, DNIT[playerid][8], 1);//DNI
	PlayerTextDrawSetShadow(playerid, DNIT[playerid][8], 0);//DNI

	DNIT[playerid][9] = CreatePlayerTextDraw(playerid, 410.410339, 268.166595, "00");//DNI
	PlayerTextDrawLetterSize(playerid, DNIT[playerid][9], 0.307231, 2.375833);//DNI
	PlayerTextDrawAlignment(playerid, DNIT[playerid][9], 1);//DNI
	PlayerTextDrawColor(playerid, DNIT[playerid][9], -2147483393);//DNI
	PlayerTextDrawSetShadow(playerid, DNIT[playerid][9], 0);//DNI
	PlayerTextDrawSetOutline(playerid, DNIT[playerid][9], 0);//DNI
	PlayerTextDrawBackgroundColor(playerid, DNIT[playerid][9], 255);//DNI
	PlayerTextDrawFont(playerid, DNIT[playerid][9], 1);//DNI
	PlayerTextDrawSetProportional(playerid, DNIT[playerid][9], 1);//DNI
	PlayerTextDrawSetShadow(playerid, DNIT[playerid][9], 0);//DNI

	DNIT[playerid][10] = CreatePlayerTextDraw(playerid, 237.994384, 258.833221, "Casado~N~Nombre_Apellido");//DNI
	PlayerTextDrawLetterSize(playerid, DNIT[playerid][10], 0.270218, 1.576665);//DNI
	PlayerTextDrawAlignment(playerid, DNIT[playerid][10], 2);//DNI
	PlayerTextDrawColor(playerid, DNIT[playerid][10], -1523963137);//DNI
	PlayerTextDrawSetShadow(playerid, DNIT[playerid][10], 0);//DNI
	PlayerTextDrawSetOutline(playerid, DNIT[playerid][10], 0);//DNI
	PlayerTextDrawBackgroundColor(playerid, DNIT[playerid][10], 255);//DNI
	PlayerTextDrawFont(playerid, DNIT[playerid][10], 1);//DNI
	PlayerTextDrawSetProportional(playerid, DNIT[playerid][10], 1);//DNI
	PlayerTextDrawSetShadow(playerid, DNIT[playerid][10], 0);//DNI

	bank_name[playerid] = CreatePlayerTextDraw(playerid, 215.000000, 191.000000, "Nombre_Apellido");
	PlayerTextDrawFont(playerid, bank_name[playerid], 1);
	PlayerTextDrawLetterSize(playerid, bank_name[playerid], 0.229166, 2.500000);
	PlayerTextDrawTextSize(playerid, bank_name[playerid], 400.000000, 17.000000);
	PlayerTextDrawSetOutline(playerid, bank_name[playerid], 1);
	PlayerTextDrawSetShadow(playerid, bank_name[playerid], 0);
	PlayerTextDrawAlignment(playerid, bank_name[playerid], 1);
	PlayerTextDrawColor(playerid, bank_name[playerid], -1);
	PlayerTextDrawBackgroundColor(playerid, bank_name[playerid], 255);
	PlayerTextDrawBoxColor(playerid, bank_name[playerid], 50);
	PlayerTextDrawUseBox(playerid, bank_name[playerid], 0);
	PlayerTextDrawSetProportional(playerid, bank_name[playerid], 1);
	PlayerTextDrawSetSelectable(playerid, bank_name[playerid], 0);

	bank_account[playerid] = CreatePlayerTextDraw(playerid, 215.000000, 229.000000, "#000000");
	PlayerTextDrawFont(playerid, bank_account[playerid], 1);
	PlayerTextDrawLetterSize(playerid, bank_account[playerid], 0.250000, 2.000000);
	PlayerTextDrawTextSize(playerid, bank_account[playerid], 400.000000, 17.000000);
	PlayerTextDrawSetOutline(playerid, bank_account[playerid], 1);
	PlayerTextDrawSetShadow(playerid, bank_account[playerid], 0);
	PlayerTextDrawAlignment(playerid, bank_account[playerid], 1);
	PlayerTextDrawColor(playerid, bank_account[playerid], -1);
	PlayerTextDrawBackgroundColor(playerid, bank_account[playerid], 255);
	PlayerTextDrawBoxColor(playerid, bank_account[playerid], 50);
	PlayerTextDrawUseBox(playerid, bank_account[playerid], 0);
	PlayerTextDrawSetProportional(playerid, bank_account[playerid], 1);
	PlayerTextDrawSetSelectable(playerid, bank_account[playerid], 0);

	bank_money[playerid] = CreatePlayerTextDraw(playerid, 215.000000, 264.000000, "~G~$~W~999999999");
	PlayerTextDrawFont(playerid, bank_money[playerid], 1);
	PlayerTextDrawLetterSize(playerid, bank_money[playerid], 0.437500, 1.600000);
	PlayerTextDrawTextSize(playerid, bank_money[playerid], 400.000000, 17.000000);
	PlayerTextDrawSetOutline(playerid, bank_money[playerid], 1);
	PlayerTextDrawSetShadow(playerid, bank_money[playerid], 0);
	PlayerTextDrawAlignment(playerid, bank_money[playerid], 1);
	PlayerTextDrawColor(playerid, bank_money[playerid], -1);
	PlayerTextDrawBackgroundColor(playerid, bank_money[playerid], 255);
	PlayerTextDrawBoxColor(playerid, bank_money[playerid], 50);
	PlayerTextDrawUseBox(playerid, bank_money[playerid], 0);
	PlayerTextDrawSetProportional(playerid, bank_money[playerid], 1);
	PlayerTextDrawSetSelectable(playerid, bank_money[playerid], 0);


	Vel_Base[playerid] = CreatePlayerTextDraw(playerid, 455.000000, 325.000000, "mdl-2005:velo_base");
	PlayerTextDrawFont(playerid, Vel_Base[playerid], 4);
	PlayerTextDrawLetterSize(playerid, Vel_Base[playerid], 0.600000, 2.000000);
	PlayerTextDrawTextSize(playerid, Vel_Base[playerid], 195.000000, 133.500000);
	PlayerTextDrawSetOutline(playerid, Vel_Base[playerid], 1);
	PlayerTextDrawSetShadow(playerid, Vel_Base[playerid], 0);
	PlayerTextDrawAlignment(playerid, Vel_Base[playerid], 1);
	PlayerTextDrawColor(playerid, Vel_Base[playerid], -1);
	PlayerTextDrawBackgroundColor(playerid, Vel_Base[playerid], 255);
	PlayerTextDrawBoxColor(playerid, Vel_Base[playerid], 50);
	PlayerTextDrawUseBox(playerid, Vel_Base[playerid], 1);
	PlayerTextDrawSetProportional(playerid, Vel_Base[playerid], 1);
	PlayerTextDrawSetSelectable(playerid, Vel_Base[playerid], 0);

	Vel_Speed[playerid] = CreatePlayerTextDraw(playerid, 597.000000, 349.000000, "400");
	PlayerTextDrawFont(playerid, Vel_Speed[playerid], 1);
	PlayerTextDrawLetterSize(playerid, Vel_Speed[playerid], 0.354166, 4.399994);
	PlayerTextDrawTextSize(playerid, Vel_Speed[playerid], 400.000000, 17.000000);
	PlayerTextDrawSetOutline(playerid, Vel_Speed[playerid], 1);
	PlayerTextDrawSetShadow(playerid, Vel_Speed[playerid], 0);
	PlayerTextDrawAlignment(playerid, Vel_Speed[playerid], 2);
	PlayerTextDrawColor(playerid, Vel_Speed[playerid], -1);
	PlayerTextDrawBackgroundColor(playerid, Vel_Speed[playerid], 255);
	PlayerTextDrawBoxColor(playerid, Vel_Speed[playerid], 0);
	PlayerTextDrawUseBox(playerid, Vel_Speed[playerid], 1);
	PlayerTextDrawSetProportional(playerid, Vel_Speed[playerid], 1);
	PlayerTextDrawSetSelectable(playerid, Vel_Speed[playerid], 0);

	Vel_iAceite[playerid] = CreatePlayerTextDraw(playerid, 582.000000, 418.000000, "mdl-2006:vel_icon_aceite");
	PlayerTextDrawFont(playerid, Vel_iAceite[playerid], 4);
	PlayerTextDrawLetterSize(playerid, Vel_iAceite[playerid], 0.600000, 2.000000);
	PlayerTextDrawTextSize(playerid, Vel_iAceite[playerid], 17.000000, 17.000000);
	PlayerTextDrawSetOutline(playerid, Vel_iAceite[playerid], 1);
	PlayerTextDrawSetShadow(playerid, Vel_iAceite[playerid], 0);
	PlayerTextDrawAlignment(playerid, Vel_iAceite[playerid], 1);
	PlayerTextDrawColor(playerid, Vel_iAceite[playerid], -1);
	PlayerTextDrawBackgroundColor(playerid, Vel_iAceite[playerid], 255);
	PlayerTextDrawBoxColor(playerid, Vel_iAceite[playerid], 50);
	PlayerTextDrawUseBox(playerid, Vel_iAceite[playerid], 1);
	PlayerTextDrawSetProportional(playerid, Vel_iAceite[playerid], 1);
	PlayerTextDrawSetSelectable(playerid, Vel_iAceite[playerid], 0);

	Vel_Luces[playerid] = CreatePlayerTextDraw(playerid, 556.000000, 418.000000, "mdl-2007:vel_icon_luces");
	PlayerTextDrawFont(playerid, Vel_Luces[playerid], 4);
	PlayerTextDrawLetterSize(playerid, Vel_Luces[playerid], 0.600000, 2.000000);
	PlayerTextDrawTextSize(playerid, Vel_Luces[playerid], 16.000000, 18.000000);
	PlayerTextDrawSetOutline(playerid, Vel_Luces[playerid], 1);
	PlayerTextDrawSetShadow(playerid, Vel_Luces[playerid], 0);
	PlayerTextDrawAlignment(playerid, Vel_Luces[playerid], 1);
	PlayerTextDrawColor(playerid, Vel_Luces[playerid], -1);
	PlayerTextDrawBackgroundColor(playerid, Vel_Luces[playerid], 255);
	PlayerTextDrawBoxColor(playerid, Vel_Luces[playerid], 50);
	PlayerTextDrawUseBox(playerid, Vel_Luces[playerid], 1);
	PlayerTextDrawSetProportional(playerid, Vel_Luces[playerid], 1);
	PlayerTextDrawSetSelectable(playerid, Vel_Luces[playerid], 0);

	Vel_Motor[playerid] = CreatePlayerTextDraw(playerid, 503.000000, 418.000000, "mdl-2008:vel_icon_motor");
	PlayerTextDrawFont(playerid, Vel_Motor[playerid], 4);
	PlayerTextDrawLetterSize(playerid, Vel_Motor[playerid], 0.600000, 2.000000);
	PlayerTextDrawTextSize(playerid, Vel_Motor[playerid], 17.000000, 17.000000);
	PlayerTextDrawSetOutline(playerid, Vel_Motor[playerid], 1);
	PlayerTextDrawSetShadow(playerid, Vel_Motor[playerid], 0);
	PlayerTextDrawAlignment(playerid, Vel_Motor[playerid], 1);
	PlayerTextDrawColor(playerid, Vel_Motor[playerid], -1);
	PlayerTextDrawBackgroundColor(playerid, Vel_Motor[playerid], 255);
	PlayerTextDrawBoxColor(playerid, Vel_Motor[playerid], 50);
	PlayerTextDrawUseBox(playerid, Vel_Motor[playerid], 1);
	PlayerTextDrawSetProportional(playerid, Vel_Motor[playerid], 1);
	PlayerTextDrawSetSelectable(playerid, Vel_Motor[playerid], 0);

	Vel_Seat[playerid] = CreatePlayerTextDraw(playerid, 530.000000, 419.000000, "mdl-2009:vel_icon_seat");
	PlayerTextDrawFont(playerid, Vel_Seat[playerid], 4);
	PlayerTextDrawLetterSize(playerid, Vel_Seat[playerid], 0.600000, 2.000000);
	PlayerTextDrawTextSize(playerid, Vel_Seat[playerid], 16.000000, 15.000000);
	PlayerTextDrawSetOutline(playerid, Vel_Seat[playerid], 1);
	PlayerTextDrawSetShadow(playerid, Vel_Seat[playerid], 0);
	PlayerTextDrawAlignment(playerid, Vel_Seat[playerid], 1);
	PlayerTextDrawColor(playerid, Vel_Seat[playerid], -1);
	PlayerTextDrawBackgroundColor(playerid, Vel_Seat[playerid], 255);
	PlayerTextDrawBoxColor(playerid, Vel_Seat[playerid], 50);
	PlayerTextDrawUseBox(playerid, Vel_Seat[playerid], 1);
	PlayerTextDrawSetProportional(playerid, Vel_Seat[playerid], 1);
	PlayerTextDrawSetSelectable(playerid, Vel_Seat[playerid], 0);

	Vel_Lock[playerid] = CreatePlayerTextDraw(playerid, 596.000000, 394.000000, "mdl-2010:vel_icon_seguro");
	PlayerTextDrawFont(playerid, Vel_Lock[playerid], 4);
	PlayerTextDrawLetterSize(playerid, Vel_Lock[playerid], 0.600000, 2.000000);
	PlayerTextDrawTextSize(playerid, Vel_Lock[playerid], 17.000000, 17.000000);
	PlayerTextDrawSetOutline(playerid, Vel_Lock[playerid], 1);
	PlayerTextDrawSetShadow(playerid, Vel_Lock[playerid], 0);
	PlayerTextDrawAlignment(playerid, Vel_Lock[playerid], 1);
	PlayerTextDrawColor(playerid, Vel_Lock[playerid], -1);
	PlayerTextDrawBackgroundColor(playerid, Vel_Lock[playerid], 255);
	PlayerTextDrawBoxColor(playerid, Vel_Lock[playerid], 50);
	PlayerTextDrawBoxColor(playerid, Vel_Lock[playerid], 1);
	PlayerTextDrawSetProportional(playerid, Vel_Lock[playerid], 1);
	PlayerTextDrawSetSelectable(playerid, Vel_Lock[playerid], 0);


	TNotif0[playerid] = CreatePlayerTextDraw(playerid, 12.400094, 310.213073, "Tienes una nueva notificacion.");
    PlayerTextDrawLetterSize(playerid, TNotif0[playerid], 0.232000, 1.204266);
    PlayerTextDrawAlignment(playerid, TNotif0[playerid], 1);
    PlayerTextDrawColor(playerid, TNotif0[playerid], -1);
    PlayerTextDrawSetShadow(playerid, TNotif0[playerid], 0);
    PlayerTextDrawSetOutline(playerid, TNotif0[playerid], -1);
    PlayerTextDrawBackgroundColor(playerid, TNotif0[playerid], 255);
    PlayerTextDrawFont(playerid, TNotif0[playerid], 1);
    PlayerTextDrawSetProportional(playerid, TNotif0[playerid], 1);
    PlayerTextDrawSetShadow(playerid, TNotif0[playerid], 0);

    TNotif1[playerid] = CreatePlayerTextDraw(playerid, 3.599962, 308.720092, "_");
    PlayerTextDrawLetterSize(playerid, TNotif1[playerid], 0.488800, 1.600000);
    PlayerTextDrawTextSize(playerid, TNotif1[playerid], 246.200012, 0.000000);
    PlayerTextDrawAlignment(playerid, TNotif1[playerid], 1);
    PlayerTextDrawColor(playerid, TNotif1[playerid], -1);
    PlayerTextDrawUseBox(playerid, TNotif1[playerid], 1);
    PlayerTextDrawBoxColor(playerid, TNotif1[playerid], 88);
    PlayerTextDrawSetShadow(playerid, TNotif1[playerid], 0);
    PlayerTextDrawSetOutline(playerid, TNotif1[playerid], 0);
    PlayerTextDrawBackgroundColor(playerid, TNotif1[playerid], 255);
    PlayerTextDrawFont(playerid, TNotif1[playerid], 1);
    PlayerTextDrawSetProportional(playerid, TNotif1[playerid], 1);
    PlayerTextDrawSetShadow(playerid, TNotif1[playerid], 0);

    TNotif2[playerid] = CreatePlayerTextDraw(playerid, 5.999997, 307.973449, "!");
    PlayerTextDrawLetterSize(playerid, TNotif2[playerid], 0.400000, 1.600000);
    PlayerTextDrawAlignment(playerid, TNotif2[playerid], 1);
    PlayerTextDrawColor(playerid, TNotif2[playerid], -16776961);
    PlayerTextDrawSetShadow(playerid, TNotif2[playerid], 0);
    PlayerTextDrawSetOutline(playerid, TNotif2[playerid], 0);
    PlayerTextDrawBackgroundColor(playerid, TNotif2[playerid], 255);
    PlayerTextDrawFont(playerid, TNotif2[playerid], 1);
    PlayerTextDrawSetProportional(playerid, TNotif2[playerid], 1);
    PlayerTextDrawSetShadow(playerid, TNotif2[playerid], 0);
    return 1;
}

stock CreatePlayerProgressBarEx(playerid)
{
	Vel_AceiteBar[playerid] = CreatePlayerProgressBar(playerid, 493.000000, 369.000000, 70.000000, 6.000000, 16777215, 100.000000, 0);
	SetPlayerProgressBarValue(playerid, Vel_AceiteBar[playerid], 50.000000);

	Vel_GasoBar[playerid] = CreatePlayerProgressBar(playerid, 493.000000, 392.000000, 70.000000, 6.000000, 852308735, 100.000000, 0);
	SetPlayerProgressBarValue(playerid, Vel_GasoBar[playerid], 50.000000);

    PJ_Food[playerid] = CreatePlayerProgressBar(playerid, 548.000000, 104.000000, 62.000000, 4.000000, -764862721, 100.000000, 0);
	SetPlayerProgressBarValue(playerid, PJ_Food[playerid], 50.000000);

	PJ_Drink[playerid] = CreatePlayerProgressBar(playerid, 548.000000, 114.000000, 62.000000, 4.000000, 1097458175, 100.000000, 0);
	SetPlayerProgressBarValue(playerid, PJ_Drink[playerid], 50.000000);
    return 1;
}

stock Create3DTextLabelEx()
{
	for(new i=0; i < sizeof(Cajeros); i++)
	{
		CreateDynamic3DTextLabel("{FF0000}M{FFFFFF}aze {FF0000}B{FFFFFF}ank\nUtiliza: {0000FF}/ATM", 0x000080FF, Cajeros[i][0], Cajeros[i][1], Cajeros[i][2]+0.75, 20.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0, 0, -1, 100.0);
	}
	for(new i=0; i < sizeof(Gasolineras); i++)
	{
		CreateDynamic3DTextLabel("{2475D1}Gaso {56D166}UG\n{FFFFFF}Utiliza: {A7ED02}/Llenar Combustible", 0x000080FF, Gasolineras[i][0], Gasolineras[i][1], Gasolineras[i][2], 20.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0, 0, -1, 100.0);
	}
	CreateDynamic3DTextLabel("{C3C3C3}Trabajo:\n{0000F0}Barrendero\n{390000}Utiliza: /Trabajar", 0xF0CC00FF, 1765.9205, -2023.2031, 14.1502+0.75,20.0,INVALID_PLAYER_ID,INVALID_VEHICLE_ID,0, 0, 0,-1, 100.0);
	CreateDynamic3DTextLabel("{C3C3C3}Trabajo:\n{0000F0}Granjero\n{390000}Utiliza: /Trabajar", 0xF0CC00FF, -382.633, -1426.26, 26.2327+0.75,20.0,INVALID_PLAYER_ID,INVALID_VEHICLE_ID,0, 0, 0,-1, 100.0);
	return 1;
}

stock ShowDNI(playerid, giveplayerid)
{
	new string[64];
	//------- Seteo de Variables
	PlayerTextDrawSetPreviewModel(giveplayerid, DNIT[giveplayerid][0], PlayersData[playerid][Skin]);

	format(string, sizeof(string), "%d", PlayersData[playerid][ID]);
	PlayerTextDrawSetString(giveplayerid,DNIT[giveplayerid][1], string);

	format(string, sizeof(string), "%d", PlayersData[playerid][Age]);
	PlayerTextDrawSetString(giveplayerid,DNIT[giveplayerid][2], string);

	format(string, sizeof(string), "%s", GetFirstName(playerid));
	PlayerTextDrawSetString(giveplayerid, DNIT[giveplayerid][3], FixSpecialString(string));

	format(string, sizeof(string), "%s", GetLastName(playerid));
	PlayerTextDrawSetString(giveplayerid, DNIT[giveplayerid][4], FixSpecialString(string));
	if(PlayersData[playerid][Faction] == 0)
	{
		PlayerTextDrawSetString(giveplayerid,DNIT[giveplayerid][5], "Ninguna");
		PlayerTextDrawSetString(giveplayerid,DNIT[giveplayerid][6], "Desempleado");
	}
	/*else
	{
		format(string, sizeof(string), "%s", FaccData[PlayersData[playerid][Faction][Name]);
		PlayerTextDrawSetString(giveplayerid,DNIT[giveplayerid][5], FixSpecialString(string));

		format(string, sizeof(string), "%s", RangoName(playerid));
		PlayerTextDrawSetString(giveplayerid,DNIT[giveplayerid][6], FixSpecialString(string));
	}*/

	new sexo[2];
	switch(PlayersData[playerid][Gender])
	{
	    case 0: { sexo="H";}    case 1: {   sexo="M";}
	}
	PlayerTextDrawSetString(giveplayerid,DNIT[giveplayerid][7], sexo);

	//format(string, sizeof(string), "%s", PlayersData[playerid][Estatura]);
	PlayerTextDrawSetString(giveplayerid,DNIT[giveplayerid][8], "1.80");

	//format(string, sizeof(string), "%d", PlayersData[playerid][Peso]);
	PlayerTextDrawSetString(giveplayerid,DNIT[giveplayerid][9], "70");

	/*new rel[120];
	switch(PlayersData[playerid][eCivil])
	{
	    case 0: {   rel="Soltero";}     case 1:{    format(rel, sizeof(rel), "Casado~N~%s", PlayersData[playerid][Relacion]);}
	}*/
	PlayerTextDrawSetString(giveplayerid,DNIT[giveplayerid][10], "Soltero");

	//------- Mostrar Textdraws
	TextDrawShowForPlayer(giveplayerid, DNI0);
	PlayerTextDrawShow(giveplayerid, DNIT[giveplayerid][0]);
	PlayerTextDrawShow(giveplayerid, DNIT[giveplayerid][1]);
	PlayerTextDrawShow(giveplayerid, DNIT[giveplayerid][2]);
	PlayerTextDrawShow(giveplayerid, DNIT[giveplayerid][3]);
	PlayerTextDrawShow(giveplayerid, DNIT[giveplayerid][4]);
	PlayerTextDrawShow(giveplayerid, DNIT[giveplayerid][5]);
	PlayerTextDrawShow(giveplayerid, DNIT[giveplayerid][6]);
	PlayerTextDrawShow(giveplayerid, DNIT[giveplayerid][7]);
	PlayerTextDrawShow(giveplayerid, DNIT[giveplayerid][8]);
	PlayerTextDrawShow(giveplayerid, DNIT[giveplayerid][9]);
	PlayerTextDrawShow(giveplayerid, DNIT[giveplayerid][10]);
	SetTimerEx("HideDNI", 7000, false, "i", giveplayerid);
	return 1;
}

stock Notificacion(playerid, text[])
{
	new string[128];
	PlayerTextDrawShow(playerid, TNotif0[playerid]);
	PlayerTextDrawShow(playerid, TNotif1[playerid]);
	PlayerTextDrawShow(playerid, TNotif2[playerid]);
	format(string, sizeof(string), "%s", text);
	PlayerTextDrawSetString(playerid, TNotif0[playerid], string);
	SetTimerEx("HideNotif", 2500, false, "d", playerid);
	PlayerPlaySound(playerid, 1058, 0.0, 0.0, 0.0);
	return 1;
}

stock ShowBankUI(playerid)
{
	TextDrawShowForPlayer(playerid, bank_base);
	TextDrawShowForPlayer(playerid, bank_retirar);
	TextDrawShowForPlayer(playerid, bank_depositar);
	TextDrawShowForPlayer(playerid, bank_transferir);
	TextDrawShowForPlayer(playerid, bank_consultar);
	TextDrawShowForPlayer(playerid, bank_close);
	PlayerTextDrawShow(playerid, bank_name[playerid]);
	PlayerTextDrawShow(playerid, bank_account[playerid]);
	PlayerTextDrawShow(playerid, bank_money[playerid]);
	return 1;
}

stock HideBankUI(playerid)
{
	TextDrawHideForPlayer(playerid, bank_base);
	TextDrawHideForPlayer(playerid, bank_retirar);
	TextDrawHideForPlayer(playerid, bank_depositar);
	TextDrawHideForPlayer(playerid, bank_transferir);
	TextDrawHideForPlayer(playerid, bank_consultar);
	TextDrawHideForPlayer(playerid, bank_close);
	PlayerTextDrawHide(playerid, bank_name[playerid]);
	PlayerTextDrawHide(playerid, bank_account[playerid]);
	PlayerTextDrawHide(playerid, bank_money[playerid]);
	CancelSelectTextDraw(playerid);
	TempInfo[playerid][InATM] = false;
	return 1;
}

forward HideDNI(playerid);
forward HideNotif(playerid);

public HideDNI(playerid)
{
	TextDrawHideForPlayer(playerid, DNI0);
	PlayerTextDrawHide(playerid, DNIT[playerid][0]);
	PlayerTextDrawHide(playerid, DNIT[playerid][1]);
	PlayerTextDrawHide(playerid, DNIT[playerid][2]);
	PlayerTextDrawHide(playerid, DNIT[playerid][3]);
	PlayerTextDrawHide(playerid, DNIT[playerid][4]);
	PlayerTextDrawHide(playerid, DNIT[playerid][5]);
	PlayerTextDrawHide(playerid, DNIT[playerid][6]);
	PlayerTextDrawHide(playerid, DNIT[playerid][7]);
	PlayerTextDrawHide(playerid, DNIT[playerid][8]);
	PlayerTextDrawHide(playerid, DNIT[playerid][9]);
	PlayerTextDrawHide(playerid, DNIT[playerid][10]);
	return 1;
}

public HideNotif(playerid)
{
    PlayerTextDrawHide(playerid, TNotif0[playerid]);
	PlayerTextDrawHide(playerid, TNotif1[playerid]);
	PlayerTextDrawHide(playerid, TNotif2[playerid]);
	return 1;
}