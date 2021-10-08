#include <zcmd>
#include <sscanf2>
#include <core/player/data>
#include <gui/hud/chat>

new bool:Animation[MAX_PLAYERS];

CMD:rendirse(playerid, params[])
{
	if(TempInfo[playerid][IsDeath] == false)
	{
		Animation[playerid] = true;
		if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
		{
			SetPlayerSpecialAction(playerid,SPECIAL_ACTION_HANDSUP);
		}
	}
	else
	{
		SendClientMessageEx(playerid, -1, "%s No puedes usar animaciones en este momento.", InfoMsg);
	}
	return 1;
}

CMD:hablar(playerid, params[])
{
	if(TempInfo[playerid][IsDeath] == false)
	{
		Animation[playerid] = true;
		if(GetPlayerState(playerid) == PLAYER_STATE_ONFOOT)
		{
			ApplyAnimation(playerid,"PED","IDLE_chat",4.1,7,5,1,1,1);
		}
	}
	else
	{
		SendClientMessageEx(playerid, -1, "%s No puedes usar animaciones en este momento.",InfoMsg);
	}

	return 1;
}

CMD:paja(playerid, params[])
{
	if(TempInfo[playerid][IsDeath] == false)
	{
		Animation[playerid] = true;
		Animation[playerid] = true;
		ApplyAnimation(playerid, "PAULNMAC", "wank_loop", 4.0, 1, 0, 0, 1, 0);
		SendClientMessageEx(playerid, -1, "%s Para seguir utiliza /irsecortao", InfoMsg);
	}
	else
	{
		SendClientMessageEx(playerid, -1, "%s No puedes usar animaciones en este momento.",InfoMsg);
	}

	return 1;
}

CMD:irsecortao(playerid, pamras[])
{
	if(TempInfo[playerid][IsDeath] == false)
	{
		Animation[playerid] = true;
		Animation[playerid] = true;
		ApplyAnimation(playerid, "PAULNMAC", "wank_out", 4.0, 0, 0, 0, 0, 0);
	}
	else
	{
		SendClientMessageEx(playerid, -1, "%s No puedes usar animaciones en este momento.",InfoMsg);
	}

	return 1;
}

CMD:arrestado(playerid, params[])
{
	if(TempInfo[playerid][IsDeath] == false)
	{
		Animation[playerid] = true;
		Animation[playerid] = true;
		ApplyAnimation( playerid,"ped", "ARRESTgun", 4.0, 0, 1, 1, 1,500);
	}
	else
	{
		SendClientMessageEx(playerid, -1, "%s No puedes usar animaciones en este momento.",InfoMsg);
	}

	return 1;
}

CMD:apuntar(playerid, params[])
{
	if(TempInfo[playerid][IsDeath] == false)
	{
		Animation[playerid] = true;
		Animation[playerid] = true;
		ApplyAnimation(playerid, "SHOP", "ROB_Loop_Threat", 4.0, 0, 0, 0, 0,500);
	}
	else
	{
		SendClientMessageEx(playerid, -1, "%s No puedes usar animaciones en este momento.",InfoMsg);
	}

	return 1;
}

CMD:reirse(playerid, params[])
{
	if(TempInfo[playerid][IsDeath] == false)
	{
		Animation[playerid] = true;
		Animation[playerid] = true;
		ApplyAnimation(playerid, "RAPPING", "Laugh_01", 4.0, 0, 0, 0, 0,0);
	}
	else
	{
		SendClientMessageEx(playerid, -1, "%s No puedes usar animaciones en este momento.",InfoMsg);
	}

	return 1;
}

CMD:encender(playerid, params[])
{
	if(TempInfo[playerid][IsDeath] == false)
	{
		Animation[playerid] = true;
		Animation[playerid] = true;
		ApplyAnimation(playerid, "SMOKING", "M_smk_in", 4.000000, 0, 0, 1, 1, 0);
	}
	else
	{
		SendClientMessageEx(playerid, -1, "%s No puedes usar animaciones en este momento.",InfoMsg);
	}

	return 1;
}

CMD:vigilar(playerid, params[])
{
	if(TempInfo[playerid][IsDeath] == false)
	{
		Animation[playerid] = true;
		Animation[playerid] = true;
		ApplyAnimation(playerid, "COP_AMBIENT", "Coplook_loop", 4.0, 1, 1, 1, 0, 4000);
	}
	else
	{
		SendClientMessageEx(playerid, -1, "%s No puedes usar animaciones en este momento.",InfoMsg);
	}

	return 1;
}

CMD:recostarse(playerid, params[])
{
	if(TempInfo[playerid][IsDeath] == false)
	{
		Animation[playerid] = true;
		Animation[playerid] = true;
		ApplyAnimation(playerid,"SUNBATHE", "Lay_Bac_in", 4.0, 0, 0, 0, 1, 0);
		SendClientMessageEx(playerid, -1, "%s Para ponerte de pie utiliza /pararse", InfoMsg);
	}
	else
	{
		SendClientMessageEx(playerid, -1, "%s No puedes usar animaciones en este momento.",InfoMsg);
	}

	return 1;
}

CMD:pararse(playerid, params[])
{
	if(TempInfo[playerid][IsDeath] == false)
	{
		Animation[playerid] = true;
		Animation[playerid] = true;
		ApplyAnimation(playerid,"SUNBATHE", "Lay_Bac_out", 4.0, 0, 0, 0, 0, 0);
	}
	else
	{
		SendClientMessageEx(playerid, -1, "%s No puedes usar animaciones en este momento.",InfoMsg);
	}

	return 1;
}

CMD:cubrirse(playerid, params[])
{
	if(TempInfo[playerid][IsDeath] == false)
	{
		Animation[playerid] = true;
		Animation[playerid] = true;
		ApplyAnimation(playerid, "ped", "cower", 4.0, 1, 0, 0, 0, 0);
	}
	else
	{
		SendClientMessageEx(playerid, -1, "%s No puedes usar animaciones en este momento.",InfoMsg);
	}

	return 1;
}

CMD:vomitar(playerid, params[])
{
	if(TempInfo[playerid][IsDeath] == false)
	{
		Animation[playerid] = true;
		Animation[playerid] = true;
		ApplyAnimation(playerid, "FOOD", "EAT_Vomit_P", 3.0, 0, 0, 0, 0, 0);
	}
	else
	{
		SendClientMessageEx(playerid, -1, "%s No puedes usar animaciones en este momento.",InfoMsg);
	}

	return 1;
}

CMD:cenar(playerid, params[])
{
	if(TempInfo[playerid][IsDeath] == false)
	{
		Animation[playerid] = true;
		Animation[playerid] = true;
		ApplyAnimation(playerid, "FOOD", "EAT_Burger", 3.00, 0, 0, 0, 0, 0);
	}
	else
	{
		SendClientMessageEx(playerid, -1, "%s No puedes usar animaciones en este momento.",InfoMsg);
	}

	return 1;
}

CMD:chao(playerid, params[])
{
	if(TempInfo[playerid][IsDeath] == false)
	{
		Animation[playerid] = true;
		Animation[playerid] = true;
		ApplyAnimation(playerid, "KISSING", "BD_GF_Wave", 3.0, 0, 0, 0, 0, 0);
	}
	else
	{
		SendClientMessageEx(playerid, -1, "%s No puedes usar animaciones en este momento.",InfoMsg);
	}

	return 1;
}

CMD:palmada(playerid, params[])
{
	if(TempInfo[playerid][IsDeath] == false)
	{
		Animation[playerid] = true;
		Animation[playerid] = true;
		ApplyAnimation(playerid, "SWEET", "sweet_ass_slap", 4.0, 0, 0, 0, 0, 0);
	}
	else
	{
		SendClientMessageEx(playerid, -1, "%s No puedes usar animaciones en este momento.",InfoMsg);
	}

	return 1;
}

CMD:agonizar(playerid, params[])
{
	if(TempInfo[playerid][IsDeath] == false)
	{
		Animation[playerid] = true;
		Animation[playerid] = true;
		ApplyAnimation(playerid, "WUZI", "CS_Dead_Guy", 4.0, 0, 0, 0, 1, 0);
	}
	else
	{
		SendClientMessageEx(playerid, -1, "%s No puedes usar animaciones en este momento.",InfoMsg);
	}

	return 1;
}

CMD:traficar(playerid, params[])
{
	if(TempInfo[playerid][IsDeath] == false)
	{
		Animation[playerid] = true;
		Animation[playerid] = true;
		ApplyAnimation(playerid, "DEALER", "DEALER_DEAL", 4.0, 0, 0, 0, 0, 0);
	}
	else
	{
		SendClientMessageEx(playerid, -1, "%s No puedes usar animaciones en este momento.",InfoMsg);
	}

	return 1;
}

CMD:beso(playerid, params[])
{
	if(TempInfo[playerid][IsDeath] == false)
	{
		Animation[playerid] = true;
		Animation[playerid] = true;
		ApplyAnimation(playerid, "KISSING", "Playa_Kiss_02", 4.0, 0, 0, 0, 0, 0);
	}
	else
	{
		SendClientMessageEx(playerid, -1, "%s No puedes usar animaciones en este momento.",InfoMsg);
	}

	return 1;
}

CMD:crack(playerid, params[])
{
	if(TempInfo[playerid][IsDeath] == false)
	{
		Animation[playerid] = true;
		Animation[playerid] = true;
		ApplyAnimation(playerid, "CRACK", "crckdeth2", 4.0, 0, 0, 0, 1, 0);
	}
	else
	{
		SendClientMessageEx(playerid, -1, "%s No puedes usar animaciones en este momento.",InfoMsg);
	}

	return 1;
}

CMD:mear(playerid, params[])
{
	if(TempInfo[playerid][IsDeath] == false)
	{
		Animation[playerid] = true;
		Animation[playerid] = true;
		ApplyAnimation(playerid, "PAULNMAC", "Piss_in", 4.0, 0, 0, 0, 0, 0);
	}
	else
	{
		SendClientMessageEx(playerid, -1, "%s No puedes usar animaciones en este momento.",InfoMsg);
	}

	return 1;
}

CMD:sentarse(playerid, params[])
{
	if(TempInfo[playerid][IsDeath] == false)
	{
		Animation[playerid] = true;
		Animation[playerid] = true;
		ApplyAnimation(playerid, "SUNBATHE", "ParkSit_M_in", 4.000000, 0, 1, 1, 1, 0);
	}
	else
	{
		SendClientMessageEx(playerid, -1, "%s No puedes usar animaciones en este momento.",InfoMsg);
	}

	return 1;
}

CMD:depie(playerid, params[])
{
	if(TempInfo[playerid][IsDeath] == false)
	{
		Animation[playerid] = true;
		ApplyAnimation(playerid, "ped", "SEAT_up", 4.000000, 0, 1, 1, 1, 0);
	}
	else
	{
		SendClientMessageEx(playerid, -1, "%s No puedes usar animaciones en este momento.",InfoMsg);
	}

	return 1;
}

CMD:fokear(playerid, params[])
{
	if(TempInfo[playerid][IsDeath] == false)
	{
		Animation[playerid] = true;
		ApplyAnimation( playerid,"ped", "fucku", 4.0, 0, 1, 1, 1, 1 );
	}
	else
	{
		SendClientMessageEx(playerid, -1, "%s No puedes usar animaciones en este momento.",InfoMsg);
	}

	return 1;
}

CMD:siquiero(playerid, params[])
{
	if(TempInfo[playerid][IsDeath] == false)
	{
		Animation[playerid] = true;
		ApplyAnimation(playerid, "GANGS", "Invite_Yes", 4.0, 0, 0, 0, 0, 0);
	}
	else
	{
		SendClientMessageEx(playerid, -1, "%s No puedes usar animaciones en este momento.",InfoMsg);
	}

	return 1;
}

CMD:noquiero(playerid, params[])
{
	if(TempInfo[playerid][IsDeath] == false)
	{
		Animation[playerid] = true;
		ApplyAnimation(playerid, "GANGS", "Invite_No", 4.0, 0, 0, 0, 0, 0);
	}
	else
	{
		SendClientMessageEx(playerid, -1, "%s No puedes usar animaciones en este momento.",InfoMsg);
	}

	return 1;
}

CMD:comerciar(playerid, params[])
{
	if(TempInfo[playerid][IsDeath] == false)
	{
		Animation[playerid] = true;
		ApplyAnimation(playerid, "DEALER", "shop_pay", 4.000000, 0, 1, 1, 0, 0);
	}
	else
	{
		SendClientMessageEx(playerid, -1, "%s No puedes usar animaciones en este momento.",InfoMsg);
	}

	return 1;
}

CMD:taichi(playerid, params[])
{
	if(TempInfo[playerid][IsDeath] == false)
	{
		Animation[playerid] = true;
		ApplyAnimation(playerid, "PARK", "Tai_Chi_Loop",  4.1,7,5,1,1,0);
	}
	else
	{
		SendClientMessageEx(playerid, -1, "%s No puedes usar animaciones en este momento.",InfoMsg);
	}

	return 1;
}

CMD:beber(playerid, params[])
{
	if(TempInfo[playerid][IsDeath] == false)
	{
		Animation[playerid] = true;
		ApplyAnimation(playerid, "BAR", "dnk_stndM_loop", 4.0, 0, 1, 1, 0, 4000);
	}
	else
	{
		SendClientMessageEx(playerid, -1, "%s No puedes usar animaciones en este momento.",InfoMsg);
	}

	return 1;
}

CMD:boxear(playerid, params[])
{
	if(TempInfo[playerid][IsDeath] == false)
	{
		Animation[playerid] = true;
		ApplyAnimation(playerid, "GYMNASIUM", "gym_shadowbox",  4.1,7,5,1,1,1);
	}
	else
	{
		SendClientMessageEx(playerid, -1, "%s No puedes usar animaciones en este momento.",InfoMsg);
	}

	return 1;
}

CMD:fuerza(playerid, params[])
{
	if(TempInfo[playerid][IsDeath] == false)
	{
		Animation[playerid] = true;
		ApplyAnimation(playerid,"benchpress","gym_bp_celebrate",4.1,0,1,1,1,1);
	}
	else
	{
		SendClientMessageEx(playerid, -1, "%s No puedes usar animaciones en este momento.",InfoMsg);
	}

	return 1;
}

CMD:pelea(playerid, params[])
{
	if(TempInfo[playerid][IsDeath] == false)
	{
		Animation[playerid] = true;
		ApplyAnimation(playerid, "ped", "FIGHTIDLE", 4.000000, 0, 1, 1, 1, 1);
		SendClientMessageEx(playerid, -1, "%s Para continuar utiliza /boxear", InfoMsg);
	}
	else
	{
		SendClientMessageEx(playerid, -1, "%s No puedes usar animaciones en este momento.",InfoMsg);
	}

	return 1;
}

CMD:lanzar(playerid, params[])
{
	if(TempInfo[playerid][IsDeath] == false)
	{
		Animation[playerid] = true;
		ApplyAnimation(playerid, "BSKTBALL", "BBALL_Jump_Shot", 4.0, 0, 1, 1, 1, 500);
	}
	else
	{
		SendClientMessageEx(playerid, -1, "%s No puedes usar animaciones en este momento.",InfoMsg);
	}

	return 1;
}

CMD:llorar(playerid, params[])
{
	if(TempInfo[playerid][IsDeath] == false)
	{
		Animation[playerid] = true;
		ApplyAnimation(playerid,"GRAVEYARD","mrnF_loop",4.1,0,0,0,0,0);
	}
	else
	{
		SendClientMessageEx(playerid, -1, "%s No puedes usar animaciones en este momento.",InfoMsg);
	}

	return 1;
}

CMD:detener(playerid, params[])
{
	if(TempInfo[playerid][IsDeath] == false)
	{
		Animation[playerid] = true;
		ApplyAnimation(playerid,"POLICE","CopTraf_Stop",4.1,0,0,0,0,0);
	}
	else
	{
		SendClientMessageEx(playerid, -1, "%s No puedes usar animaciones en este momento.",InfoMsg);
	}

	return 1;
}

CMD:rapear(playerid, params[])
{
	if(TempInfo[playerid][IsDeath] == false)
	{
		Animation[playerid] = true;
		ApplyAnimation(playerid,"RAPPING","RAP_B_Loop",4.0,1,0,0,0,8000);
	}
	else
	{
		SendClientMessageEx(playerid, -1, "%s No puedes usar animaciones en este momento.",InfoMsg);
	}

	return 1;
}

CMD:alzar(playerid, params[])
{
	if(TempInfo[playerid][IsDeath] == false)
	{
		Animation[playerid] = true;
		ApplyAnimation(playerid,"GHANDS","gsign2LH",4.1,0,1,1,1,1);
	}
	else
	{
		SendClientMessageEx(playerid, -1, "%s No puedes usar animaciones en este momento.",InfoMsg);
	}

	return 1;
}

CMD:bomba(playerid, params[])
{
	if(TempInfo[playerid][IsDeath] == false)
	{
		Animation[playerid] = true;
		ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.0, 0, 1, 1, 0,0);
	}
	else
	{
		SendClientMessageEx(playerid, -1, "%s No puedes usar animaciones en este momento.",InfoMsg);
	}

	return 1;
}

CMD:sapiar(playerid, params[])
{
	if(TempInfo[playerid][IsDeath] == false)
	{
		Animation[playerid] = true;
		ApplyAnimation(playerid,"PED","roadcross_female",4.1,0,0,0,0,0);
	}
	else
	{
		SendClientMessageEx(playerid, -1, "%s No puedes usar animaciones en este momento.",InfoMsg);
	}

	return 1;
}

CMD:asiento(playerid, params[])
{
	if(TempInfo[playerid][IsDeath] == false)
	{
		Animation[playerid] = true;
		ApplyAnimation(playerid, "ped", "SEAT_down", 4.000000, 0, 0, 0, 1, 0);
		SendClientMessageEx(playerid, -1, "Para ponerte de pie utiliza /depie");
	}
	else
	{
		SendClientMessageEx(playerid, -1, "%s No puedes usar animaciones en este momento.",InfoMsg);
	}

	return 1;
}

CMD:asiento2(playerid, params[])
{
	if(TempInfo[playerid][IsDeath] == false)
	{
		Animation[playerid] = true;
		ApplyAnimation(playerid,"Attractors","Stepsit_in",4.1,0,0,0,1,0);
		SendClientMessageEx(playerid, -1, "Para ponerte de pie utiliza /depie2");
	}
	else
	{
		SendClientMessageEx(playerid, -1, "%s No puedes usar animaciones en este momento.",InfoMsg);
	}

	return 1;
}

CMD:depie2(playerid, params[])
{
	if(TempInfo[playerid][IsDeath] == false)
	{
		Animation[playerid] = true;
		ApplyAnimation(playerid,"Attractors","Stepsit_out",4.1,0,0,0,0,0);
	}
	else
	{
		SendClientMessageEx(playerid, -1, "%s No puedes usar animaciones en este momento.",InfoMsg);
	}

	return 1;
}

CMD:mmm(playerid, params[])
{
	if(TempInfo[playerid][IsDeath] == false)
	{
		Animation[playerid] = true;
		ApplyAnimation(playerid,"COP_AMBIENT","Coplook_think",4.1,0,0,0,0,0);
	}
	else
	{
		SendClientMessageEx(playerid, -1, "%s No puedes usar animaciones en este momento.",InfoMsg);
	}

	return 1;
}

CMD:saludo(playerid, params[])
{
	if(TempInfo[playerid][IsDeath] == false)
	{
		Animation[playerid] = true;
		SendClientMessageEx(playerid, -1, "Utiliza /saludo[1-4]");
	}
	else
	{
		SendClientMessageEx(playerid, -1, "%s No puedes usar animaciones en este momento.",InfoMsg);
	}

	return 1;
}

CMD:saludo1(playerid, params[])
{
	if(TempInfo[playerid][IsDeath] == false)
	{
		Animation[playerid] = true;
		ApplyAnimation(playerid,"GANGS","hndshkaa",4.1,0,0,0,0,0);
	}
	else
	{
		SendClientMessageEx(playerid, -1, "%s No puedes usar animaciones en este momento.",InfoMsg);
	}

	return 1;
}

CMD:saludo2(playerid, params[])
{
	if(TempInfo[playerid][IsDeath] == false)
	{
		Animation[playerid] = true;
		ApplyAnimation(playerid,"GANGS","hndshkba",4.1,0,0,0,0,0);
	}
	else
	{
		SendClientMessageEx(playerid, -1, "%s No puedes usar animaciones en este momento.",InfoMsg);
	}

	return 1;
}

CMD:saludo3(playerid, params[])
{
	if(TempInfo[playerid][IsDeath] == false)
	{
		Animation[playerid] = true;
		ApplyAnimation(playerid,"GANGS","hndshkca",4.1,0,0,0,0,0);
	}
	else
	{
		SendClientMessageEx(playerid, -1, "%s No puedes usar animaciones en este momento.",InfoMsg);
	}

	return 1;
}

CMD:saludo4(playerid, params[])
{
	if(TempInfo[playerid][IsDeath] == false)
	{
		Animation[playerid] = true;
		ApplyAnimation(playerid,"GANGS","hndshkfa_swt",4.1,0,0,0,0,0);
	}
	else
	{
		SendClientMessageEx(playerid, -1, "%s No puedes usar animaciones en este momento.",InfoMsg);
	}

	return 1;
}

CMD:echarse(playerid, params[])
{
	if(TempInfo[playerid][IsDeath] == false)
	{
		Animation[playerid] = true;
		ApplyAnimation(playerid,"SUNBATHE","SitnWait_in_W",4.000000, 0, 0, 0, 1, 0);
	}
	else
	{
		SendClientMessageEx(playerid, -1, "%s No puedes usar animaciones en este momento.",InfoMsg);
	}

	return 1;
}

CMD:asientosexi(playerid, params[])
{
	if(TempInfo[playerid][IsDeath] == false)
	{
		Animation[playerid] = true;
		ApplyAnimation(playerid,"SUNBATHE","ParkSit_W_idleA",4.000000, 0, 1, 1, 1, 0);
		SendClientMessageEx(playerid, -1, "%s Para ponerte de pie utiliza /pararse", InfoMsg);
	}
	else
	{
		SendClientMessageEx(playerid, -1, "%s No puedes usar animaciones en este momento.",InfoMsg);
	}

	return 1;
}

CMD:danzar(playerid, params[])
{
	if(TempInfo[playerid][IsDeath] == false)
	{
		Animation[playerid] = true;
		SendClientMessageEx(playerid, -1, "Utiliza /danzar[0-12]");
	}
	else
	{
		SendClientMessageEx(playerid, -1, "%s No puedes usar animaciones en este momento.",InfoMsg);
	}

	return 1;
}

CMD:danzar0(playerid, params[])
{
	if(TempInfo[playerid][IsDeath] == false)
	{
		Animation[playerid] = true;
		ApplyAnimation(playerid,"DANCING","bd_clap",4.1,7,5,1,1,1);
	}
	else
	{
		SendClientMessageEx(playerid, -1, "%s No puedes usar animaciones en este momento.",InfoMsg);
	}

	return 1;
}

CMD:danzar1(playerid, params[])
{
	if(TempInfo[playerid][IsDeath] == false)
	{
		Animation[playerid] = true;
		ApplyAnimation(playerid,"DANCING","bd_clap1",4.1,7,5,1,1,1);
	}
	else
	{
		SendClientMessageEx(playerid, -1, "%s No puedes usar animaciones en este momento.",InfoMsg);
	}

	return 1;
}

CMD:danzar2(playerid, params[])
{
	if(TempInfo[playerid][IsDeath] == false)
	{
		Animation[playerid] = true;
		ApplyAnimation(playerid,"DANCING","dance_loop",4.1,7,5,1,1,1);
	}
	else
	{
		SendClientMessageEx(playerid, -1, "%s No puedes usar animaciones en este momento.",InfoMsg);
	}

	return 1;
}

CMD:danzar3(playerid, params[])
{
	if(TempInfo[playerid][IsDeath] == false)
	{
		Animation[playerid] = true;
		ApplyAnimation(playerid,"DANCING","DAN_Down_A",4.1,7,5,1,1,1);
	}
	else
	{
		SendClientMessageEx(playerid, -1, "%s No puedes usar animaciones en este momento.",InfoMsg);
	}

	return 1;
}

CMD:danzar4(playerid, params[])
{
	if(TempInfo[playerid][IsDeath] == false)
	{
		Animation[playerid] = true;
		ApplyAnimation(playerid,"DANCING","DAN_Left_A",4.1,7,5,1,1,1);
	}
	else
	{
		SendClientMessageEx(playerid, -1, "%s No puedes usar animaciones en este momento.",InfoMsg);
	}

	return 1;
}

CMD:danzar5(playerid, params[])
{
	if(TempInfo[playerid][IsDeath] == false)
	{
		Animation[playerid] = true;
		ApplyAnimation(playerid,"DANCING","DAN_Loop_A",4.1,7,5,1,1,1);
	}
	else
	{
		SendClientMessageEx(playerid, -1, "%s No puedes usar animaciones en este momento.",InfoMsg);
	}

	return 1;
}

CMD:danzar6(playerid, params[])
{
	if(TempInfo[playerid][IsDeath] == false)
	{
		Animation[playerid] = true;
		ApplyAnimation(playerid,"DANCING","DAN_Right_A",4.1,7,5,1,1,1);
	}
	else
	{
		SendClientMessageEx(playerid, -1, "%s No puedes usar animaciones en este momento.",InfoMsg);
	}

	return 1;
}

CMD:danzar7(playerid, params[])
{
	if(TempInfo[playerid][IsDeath] == false)
	{
		Animation[playerid] = true;
		ApplyAnimation(playerid,"DANCING","DAN_Up_A",4.1,7,5,1,1,1);
	}
	else
	{
		SendClientMessageEx(playerid, -1, "%s No puedes usar animaciones en este momento.",InfoMsg);
	}

	return 1;
}

CMD:danzar8(playerid, params[])
{
	if(TempInfo[playerid][IsDeath] == false)
	{
		Animation[playerid] = true;
		ApplyAnimation(playerid,"DANCING","dnce_M_a",4.1,7,5,1,1,1);
	}
	else
	{
		SendClientMessageEx(playerid, -1, "%s No puedes usar animaciones en este momento.",InfoMsg);
	}

	return 1;
}

CMD:danzar9(playerid, params[])
{
	if(TempInfo[playerid][IsDeath] == false)
	{
		Animation[playerid] = true;
		ApplyAnimation(playerid,"DANCING","dnce_M_b",4.1,7,5,1,1,1);
	}
	else
	{
		SendClientMessageEx(playerid, -1, "%s No puedes usar animaciones en este momento.",InfoMsg);
	}

	return 1;
}

CMD:danzar10(playerid, params[])
{
	if(TempInfo[playerid][IsDeath] == false)
	{
		Animation[playerid] = true;
		ApplyAnimation(playerid,"DANCING","dnce_M_c",4.1,7,5,1,1,1);
	}
	else
	{
		SendClientMessageEx(playerid, -1, "%s No puedes usar animaciones en este momento.",InfoMsg);
	}

	return 1;
}

CMD:danzar11(playerid, params[])
{
	if(TempInfo[playerid][IsDeath] == false)
	{
		Animation[playerid] = true;
		ApplyAnimation(playerid,"DANCING","dnce_M_d",4.1,7,5,1,1,1);
	}
	else
	{
		SendClientMessageEx(playerid, -1, "%s No puedes usar animaciones en este momento.",InfoMsg);
	}

	return 1;
}

CMD:danzar12(playerid, params[])
{
	if(TempInfo[playerid][IsDeath] == false)
	{
		Animation[playerid] = true;
		ApplyAnimation(playerid,"DANCING","dnce_M_e",4.1,7,5,1,1,1);
	}
	else
	{
		SendClientMessageEx(playerid, -1, "%s No puedes usar animaciones en este momento.",InfoMsg);
	}

	return 1;
}

CMD:taxi(playerid, params[])
{
	if(TempInfo[playerid][IsDeath] == false)
	{
		Animation[playerid] = true;
		ApplyAnimation(playerid,"PED","IDLE_taxi",4.1,0,1,1,1,1);
	}
	else
	{
		SendClientMessageEx(playerid, -1, "%s No puedes usar animaciones en este momento.",InfoMsg);
	}

	return 1;
}

CMD:seacabo(playerid, params[])
{
	if(TempInfo[playerid][IsDeath] == false)
	{
		Animation[playerid] = true;
		ApplyAnimation(playerid,"PED","Shove_Partial",4.1,0,1,1,1,1);
	}
	else
	{
		SendClientMessageEx(playerid, -1, "%s No puedes usar animaciones en este momento.",InfoMsg);
	}

	return 1;
}

CMD:asco(playerid, params[])
{
	if(TempInfo[playerid][IsDeath] == false)
	{
		Animation[playerid] = true;
		ApplyAnimation(playerid,"FOOD","EAT_Vomit_SK",4.1,0,1,1,1,1);
	}
	else
	{
		SendClientMessageEx(playerid, -1, "%s No puedes usar animaciones en este momento.",InfoMsg);
	}

	return 1;
}

CMD:quepa(playerid, params[])
{
	if(TempInfo[playerid][IsDeath] == false)
	{
		Animation[playerid] = true;
		ApplyAnimation(playerid,"GANGS","hndshkea",4.1,0,1,1,1,1);
	}
	else
	{
		SendClientMessageEx(playerid, -1, "%s No puedes usar animaciones en este momento.",InfoMsg);
	}

	return 1;
}

CMD:wooo(playerid, params[])
{
	if(TempInfo[playerid][IsDeath] == false)
	{
		Animation[playerid] = true;
		ApplyAnimation(playerid,"ON_LOOKERS","shout_02",4.1,7,5,1,1,1);
	}
	else
	{
		SendClientMessageEx(playerid, -1, "%s No puedes usar animaciones en este momento.",InfoMsg);
	}

	return 1;
}

CMD:quepasa(playerid, params[])
{
	if(TempInfo[playerid][IsDeath] == false)
	{
		Animation[playerid] = true;
		ApplyAnimation(playerid,"GHANDS","gsign1LH",4.1,0,1,1,1,1);
	}
	else
	{
		SendClientMessageEx(playerid, -1, "%s No puedes usar animaciones en este momento.",InfoMsg);
	}

	return 1;
}

CMD:comodo(playerid, params[])
{
	if(TempInfo[playerid][IsDeath] == false)
	{
		Animation[playerid] = true;
		ApplyAnimation(playerid,"INT_HOUSE","LOU_In",4.1,0,1,1,1,1);
	}
	else
	{
		SendClientMessageEx(playerid, -1, "%s No puedes usar animaciones en este momento.",InfoMsg);
	}

	return 1;
}

CMD:p1(playerid, params[])
{
	if(TempInfo[playerid][IsDeath] == false)
	{
		Animation[playerid] = true;
		ApplyAnimation(playerid,"Freeweights", "gym_free_B",4.0,1,1,1,1,500);
	}
	else
	{
		SendClientMessageEx(playerid, -1, "%s No puedes usar animaciones en este momento.",InfoMsg);
	}

	return 1;
}

CMD:betasex(playerid, params[])
{
    if(!sscanf(params, "d", params[0]))
    {
		if(TempInfo[playerid][IsDeath] == false)
		{
			if(params[0] == 1)
			{
				ApplyAnimation(playerid, "BLOWJOBZ", "BJ_COUCH_START_W", 4.0, 0, 0, 0, 60000, 0);
			}
			else if(params[0] == 2)
			{
				ApplyAnimation(playerid, "BLOWJOBZ", "BJ_COUCH_START_P", 4.0, 0, 0, 0, 60000, 0);
			}
			else if(params[0] == 3)
			{
				ApplyAnimation(playerid, "BLOWJOBZ", "BJ_COUCH_LOOP_W", 4.0, 0, 0, 0, 60000, 0);
			}
			else if(params[0] == 4)
			{
				ApplyAnimation(playerid, "BLOWJOBZ", "BJ_COUCH_LOOP_P", 4.0, 0, 0, 0, 60000, 0);
			}
			else if(params[0] == 5)
			{
				ApplyAnimation(playerid, "BLOWJOBZ", "BJ_COUCH_END_W", 4.0, 0, 0, 0, 60000, 0);
			}
			else if(params[0] == 6)
			{
				ApplyAnimation(playerid, "BLOWJOBZ", "BJ_COUCH_END_P", 4.0, 0, 0, 0, 60000, 0);
			}
			else if(params[0] == 7)
			{
				ApplyAnimation(playerid, "BLOWJOBZ", "BJ_STAND_START_W", 4.0, 0, 0, 0, 60000, 0);
			}
			else if(params[0] == 8)
			{
				ApplyAnimation(playerid, "BLOWJOBZ", "BJ_STAND_START_P", 4.0, 0, 0, 0, 60000, 0);
			}
			else if(params[0] == 9)
			{
				ApplyAnimation(playerid, "BLOWJOBZ", "BJ_STAND_LOOP_W", 4.0, 0, 0, 0, 60000, 0);
			}
			else if(params[0] == 10)
			{
				ApplyAnimation(playerid, "BLOWJOBZ", "BJ_STAND_LOOP_P", 4.0, 0, 0, 0, 60000, 0);
			}
			else if (params[0] == 11)
			{
				ApplyAnimation(playerid, "BLOWJOBZ", "BJ_STAND_END_W", 4.0, 0, 0, 0, 60000, 0);
			}
			else if(params[0] == 12)
			{
				ApplyAnimation(playerid, "BLOWJOBZ", "BJ_STAND_END_P", 4.0, 0, 0, 0, 60000, 0);
			}
			else if(params[0] == 13)
			{
				ApplyAnimation(playerid, "BLOWJOBZ", "BJ_CAR_START_W", 4.0, 0, 0, 0, 60000, 0);
			}
			else if(params[0] == 14)
			{
				ApplyAnimation(playerid, "BLOWJOBZ", "BJ_CAR_START_P", 4.0, 0, 0, 0, 60000, 0);
			}
			else if(params[0] == 15)
			{
				ApplyAnimation(playerid, "BLOWJOBZ", "BJ_CAR_LOOP_W", 4.0, 0, 0, 0, 60000, 0);
			}
			else if(params[0] == 16)
			{
				ApplyAnimation(playerid, "BLOWJOBZ", "BJ_CAR_LOOP_P", 4.0, 0, 0, 0, 60000, 0);
			}
			else if(params[0] == 17)
			{
				ApplyAnimation(playerid, "BLOWJOBZ", "BJ_CAR_END_W", 4.0, 0, 0, 0, 60000, 0);
			}
			else if(params[0] == 18)
			{
				ApplyAnimation(playerid, "BLOWJOBZ", "BJ_CAR_END_P", 4.0, 0, 0, 0, 60000, 0);
			}
			else
			{
				SendClientMessageEx(playerid, -1, "%s Utilize: /BetaSex <1-18>", InfoMsg);
			}
		}
		else
		{
			SendClientMessageEx(playerid, -1, "%s No puedes usar animaciones en este momento.",InfoMsg);
		}

    }
	else SendClientMessageEx(playerid, -1, "%s Utiliza: /BetaSex <1-18>", InfoMsg);

    return 1;
}
CMD:betasex1(playerid, params[])
{
    if(!sscanf(params, "d", params[0]))
    {
		if(TempInfo[playerid][IsDeath] == false)
		{
			if(params[0] == 1)
			{
				ApplyAnimation(playerid, "SNM", "SPANKING_IDLEW", 4.0, 0, 0, 0, 60000, 0);
			}
			else if(params[0] == 2)
			{
				 ApplyAnimation(playerid, "SNM", "SPANKING_IDLEP", 4.0, 0, 0, 0, 60000, 0);
			}
			else if(params[0] == 3)
			{
				  ApplyAnimation(playerid, "SNM", "SPANKINGW", 4.0, 0, 0, 0, 60000, 0);
			}
			else if(params[0] == 4)
			{
				  ApplyAnimation(playerid, "SNM", "SPANKINGP", 4.0, 0, 0, 0, 60000, 0);
			}
			else if(params[0] == 5)
			{
				  ApplyAnimation(playerid, "SNM", "SPANKEDW", 4.0, 0, 0, 0, 60000, 0);
			}
			else if(params[0] == 6)
			{
				  ApplyAnimation(playerid, "SNM", "SPANKEDP", 4.0, 0, 0, 0, 60000, 0);
			}
			else if(params[0] == 7)
			{
				  ApplyAnimation(playerid, "SNM", "SPANKING_ENDW", 4.0, 0, 0, 0, 60000, 0);
			}
			else if(params[0] == 8)
			{
				  ApplyAnimation(playerid, "SNM", "SPANKING_ENDP", 4.0, 0, 0, 0, 60000, 0);
			}
			else
			{
				  SendClientMessageEx(playerid, -1, "%s Utilize: /BetaSex1 <1-8>", InfoMsg);
			}
		}
		else
		{
			SendClientMessageEx(playerid, -1, "%s No puedes usar animaciones en este momento.",InfoMsg);
		}

      }
	  else SendClientMessageEx(playerid, -1, "Utilize: /BetaSex1 <1-8>");
    return 1;
}