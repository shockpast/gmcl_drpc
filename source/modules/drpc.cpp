#include <GarrysMod/Lua/Interface.h>
#include <dependencies/windows/include/discord_rpc.h>

#include "drpc.h"

#include <stdio.h>
#include <string.h>

LUA_FUNCTION_STATIC(L_UpdatePresence)
{
	LUA->CheckType(1, GarrysMod::Lua::Type::TABLE);

	DiscordRichPresence _presence;
	memset(&_presence, 0, sizeof(_presence));

	LUA->GetField(-1, "details");
	_presence.details = LUA->GetString(-1);
	LUA->Pop();

	LUA->GetField(-1, "state");
	_presence.state = LUA->GetString(-1);
	LUA->Pop();

	LUA->GetField(-1, "large_image_key");
	_presence.largeImageKey = LUA->GetString(-1);
	LUA->Pop();

	LUA->GetField(-1, "large_image_text");
	_presence.largeImageText = LUA->GetString(-1);
	LUA->Pop();

	LUA->GetField(-1, "small_image_key");
	_presence.smallImageKey = LUA->GetString(-1);
	LUA->Pop();

	LUA->GetField(-1, "small_image_text");
	_presence.smallImageText = LUA->GetString(-1);
	LUA->Pop();

	LUA->GetField(-1, "start_timestamp");
	_presence.startTimestamp = LUA->GetNumber(-1);
	LUA->Pop();

	LUA->GetField(-1, "end_timestamp");
	_presence.endTimestamp = LUA->GetNumber(-1);
	LUA->Pop();

	LUA->GetField(-1, "party_id");
	_presence.partyId = LUA->GetString(-1);
	LUA->Pop();

	LUA->GetField(-1, "party_size");
	_presence.partySize = LUA->GetNumber(-1);
	LUA->Pop();

	LUA->GetField(-1, "party_max");
	_presence.partyMax = LUA->GetNumber(-1);
	LUA->Pop();

	LUA->GetField(-1, "party_privacy");
	_presence.partyPrivacy = LUA->GetNumber(-1);
	LUA->Pop();

	LUA->GetField(-1, "match_secret");
	_presence.matchSecret = LUA->GetString(-1);
	LUA->Pop();

	LUA->GetField(-1, "join_secret");
	_presence.joinSecret = LUA->GetString(-1);
	LUA->Pop();

	LUA->GetField(-1, "spectate_secret");
	_presence.spectateSecret = LUA->GetString(-1);
	LUA->Pop();

	LUA->GetField(-1, "instance");
	_presence.instance = LUA->GetBool(-1);
	LUA->Pop();

	LUA->GetField(-1, "buttons");
	if (LUA->IsType(-1, GarrysMod::Lua::Type::Table)) {
		int buttonCount = LUA->ObjLen(-1);

		DiscordButton* buttons = new DiscordButton[buttonCount + 1];
		memset(buttons, 0, sizeof(DiscordButton) * (buttonCount + 1));

		for (int i = 1; i <= buttonCount; i++) {
			LUA->PushNumber(i);
			LUA->GetTable(-2);

			if (LUA->IsType(-1, GarrysMod::Lua::Type::Table)) {
				LUA->GetField(-1, "label");
				const char* label = LUA->GetString(-1);
				LUA->Pop();

				LUA->GetField(-1, "url");
				const char* url = LUA->GetString(-1);
				LUA->Pop();

				buttons[i - 1].label = label;
				buttons[i - 1].url = url;
			}

			LUA->Pop();
		}

		_presence.buttons = buttons;
	}
	LUA->Pop();

	Discord_UpdatePresence(&_presence);

	return 0;
}

//
LUA_FUNCTION_STATIC(L_Initialize)
{
	DiscordEventHandlers _handlers;
	Discord_Initialize(LUA->CheckString(1), &_handlers, 1, LUA->GetType(-2) == GarrysMod::Lua::Type::String ? LUA->GetString(2) : nullptr);

	return 0;
}

LUA_FUNCTION_STATIC(L_Shutdown)
{
	Discord_Shutdown();
	return 0;
}

//
LUA_FUNCTION_STATIC(L_RunCallbacks__Internal)
{
	Discord_RunCallbacks();
	return 0;
}

void DRPC::Initialize(GarrysMod::Lua::ILuaBase* LUA)
{
	LUA->PushSpecial(GarrysMod::Lua::SPECIAL_GLOB);
		LUA->CreateTable();
			LUA->PushCFunction(L_UpdatePresence);
			LUA->SetField(-2, "UpdatePresence");
			LUA->PushCFunction(L_Initialize);
			LUA->SetField(-2, "Initialize");
			LUA->PushCFunction(L_Shutdown);
			LUA->SetField(-2, "Shutdown");

			LUA->PushCFunction(L_RunCallbacks__Internal);
			LUA->SetField(-2, "RunCallbacks__Internal");
		LUA->SetField(-2, "DiscordRPC");
	LUA->Pop();
}
