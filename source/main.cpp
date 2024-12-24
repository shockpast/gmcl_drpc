#include <GarrysMod/Lua/Interface.h>
#include <dependencies/windows/include/discord_rpc.h>

#include "modules/drpc.h"

GMOD_MODULE_OPEN()
{
	DRPC::Initialize(LUA);

	return 0;
}

GMOD_MODULE_CLOSE()
{
	Discord_Shutdown();

	LUA->PushSpecial(GarrysMod::Lua::SPECIAL_GLOB);
	LUA->PushNil();
	LUA->SetField(-2, "DiscordRPC");
	LUA->Pop(1);

	return 0;
}