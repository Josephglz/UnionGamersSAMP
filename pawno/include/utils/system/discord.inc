#include <discord-connector>

#define         SERVER_NAME_MSG         876286324091535371

stock SetRichPresenceBot()
{
    DCC_SetBotPresenceStatus(ONLINE);
    DCC_SetBotActivity("UnionGamers - Una Nueva Aventura");
    return 1;
}