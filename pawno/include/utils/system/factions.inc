//»»»»»»»»»» RESOURCES ««««««««««
#include <core/player/data>
#include <core/server/database>

//»»»»»»»»»» VARIABLES ««««««««««
new TFacciones;
new TRangos;

#define         MAX_FACCIONES           30
#define         MAX_RANGOS              100

enum fInfo
{
	ID,
	Name[40],
	fType,
	Money,
	Radio,
	Family,
	Mats,
	Drugs
};
new FaccData[MAX_FACCIONES][fInfo];

enum rfInfo
{
	IDF,
	Rank,
	Name[40],
	Skin1,
	Skin2,
	Skin3,
	Skin4
};
new RankFacc[MAX_RANGOS][rfInfo];

stock FactionList()
{
    new name[45], type, id, tipo[25], str[700], str1[250];
    new Cache:result = mysql_query(g_MySQL, "SELECT * FROM factions");
    if(cache_num_rows() > 0)
    {
        for(new i=0; i < cache_num_rows(); i++)
        {
            cache_get_value_name_int(i, "ID", id);
            cache_get_value_name(i, "Name", name, 45);
            cache_get_value_name_int(i, "Type", type);
			switch(type)
			{
				case 1:{    tipo="{00E100}Legal";}      case 2:{    tipo="{FF8000}Privada";}        case 3:{    tipo="{FF2424}Ilegal";}     case 4:{    tipo="{A60000}Ilegal*";}
			}
            format(str1, sizeof(str1),"{FFFFFF}%s\t%d\t%s\n",name, id, tipo);
            strcat(str, str1);
        }
    }
    cache_delete(result);
    return str;
}

forward LoadFactions();
forward LoadFacRanks();
forward SaveFactions();

public LoadFactions()
{
	new query[50];
	mysql_format(g_MySQL, query, sizeof(query), "SELECT * FROM factions");
	new Cache:result = mysql_query(g_MySQL, query);
	if(cache_num_rows() > 0)
	{
		TFacciones++;
		for(new i = 0; i < cache_num_rows(); i++)
		{
			cache_get_value_name_int(i, "ID", FaccData[TFacciones][ID]);
			cache_get_value_name(i, "Name", FaccData[TFacciones][Name], 40);
			cache_get_value_name_int(i, "Type", FaccData[TFacciones][fType]);
			cache_get_value_name_int(i, "Money", FaccData[TFacciones][Money]);
			cache_get_value_name_int(i, "Radio", FaccData[TFacciones][Radio]);
			cache_get_value_name_int(i, "Family", FaccData[TFacciones][Family]);
			cache_get_value_name_int(i, "Mats", FaccData[TFacciones][Mats]);
			cache_get_value_name_int(i, "Drugs", FaccData[TFacciones][Drugs]);
			TFacciones++;
		}
	}
	LoadFacRanks();
	cache_delete(result);
	return 1;
}

public LoadFacRanks()
{
	new Cache:result = mysql_query(g_MySQL, "SELECT * FROM `ranks`");
	if(cache_num_rows() > 0)
	{
		TRangos++;
		for(new i = 0; i < cache_num_rows(); i++)
		{
			cache_get_value_index_int(i, 1, RankFacc[TRangos][IDF]);
			cache_get_value_index_int(i, 2, RankFacc[TRangos][Rank]);
			cache_get_value_index(i, 3, RankFacc[TRangos][Name], 40);
			cache_get_value_index_int(i, 4, RankFacc[TRangos][Skin1]);
			cache_get_value_index_int(i, 5, RankFacc[TRangos][Skin2]);
			cache_get_value_index_int(i, 6, RankFacc[TRangos][Skin3]);
			cache_get_value_index_int(i, 7, RankFacc[TRangos][Skin4]);
			TRangos++;
		}
	}
	cache_delete(result);
	return 1;
}

public SaveFactions()
{
    new query[300];
	for(new i=0; i <= TFacciones; i++)
	{
		format(query, sizeof(query), "UPDATE `factions` SET `Money` = '%d', `Mats` = '%d', `Drugs` = '%d' WHERE `ID` ='%d'",
		FaccData[i][Money], FaccData[i][Mats], FaccData[i][Drugs], FaccData[i][ID]);
		new Cache:result = mysql_query(g_MySQL, query);
		cache_delete(result);
	}
	return 1;
}