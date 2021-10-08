//========== [ VARIABLES ] ==========
/*---- USERS ----*/
new bool:Logged[MAX_PLAYERS];
new TryPass[MAX_PLAYERS];
new bool:TryRole[MAX_PLAYERS];
new bool:Cinturon[MAX_PLAYERS];
new EnNegocio[MAX_PLAYERS];
new EditandoNegocio[MAX_PLAYERS];
new Editando[MAX_PLAYERS];
new EditObj[MAX_PLAYERS];
/*---- OTHERS ----*/
//===================================
enum jInfo
{
	UUID,
	rName[128],
	Password[65],
	Mail[150],
	ID,
	Gender,
	Age,
	City,
	Money,
	Skin,
	Admin,
	Esp,
	Vip,
	Level,
	Origin,
	Exp,
	Float:pPosX,
	Float:pPosY,
	Float:pPosZ,
	Float:pPosAng,
	pVW,
	pInterior,
	Float:pHealth,
	Float:pArmour,
	Faction,
	fRank,
	Adv,
	Banned,
	Gold,
	Float:pFood,
	Float:pDrink,
	WeaponID[4],
	WeaponAmmo[4],
	InvObj[5],
	BankAccount
}
new PlayersData[MAX_PLAYERS][jInfo];

//»»»»»»»»»» Datos Temporales ««««««««««
enum tempInf
{
	rName[128],
	DeathCooldown,
	bool:IsDeath,
	Float:dPosX,
	Float:dPosY,
	Float:dPosZ,
	Float:dPosX2,
	Float:dPosY2,
	Float:dPosZ2,
	Float:dHealth,
	dInt,
	dInt2,
	dVW,
	dVW2,
	bool:OnDuty,
	bool:InATM,
	cacheID,
	Work
}
new TempInfo[MAX_PLAYERS][tempInf];

//»»»»»»»»»» Datos ETC ««««««««««