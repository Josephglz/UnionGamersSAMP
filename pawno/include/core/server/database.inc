#define         SQL_HOST                "localhost"
#define         SQL_USER                "user"
#define         SQL_PASS                "pass"
#define         SQL_DB                  "sampug"

new MySQL:g_MySQL;

stock ConnectDataBase()
{
    new MySQLOpt: option_id = mysql_init_options();
	mysql_set_option(option_id, AUTO_RECONNECT, true);
	g_MySQL = mysql_connect(SQL_HOST, SQL_USER, SQL_PASS, SQL_DB, option_id);
	print("[DATABASE] Conectando...");
	if(mysql_errno() != 0)
	{
		print("[DATABASE] No se pudo conectar.");
	}
	else
	{
		print("[DATABASE] Base de Datos Conectada.");
	}
    return 1;
}

stock DisconnectDataBase()
{
	mysql_close(g_MySQL);
	return 1;
}