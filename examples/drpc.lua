require "drpc"
if not DiscordRPC then return end

local drpc = DiscordRPC
local presence = {
  details = "Playing with Discord RPC",
  state = "In the examples folder",
  large_image_key = "huggge_gmod_key",
  large_image_text = "huggge_gmod_text",
  small_image_key = "smol_gmod_key",
  small_image_text = "smol_gmod_text",
  start_timestamp = os.time(),
  buttons = {
    { label = "Garry's Mod Wiki", url = "https://gmodwiki.com/" },
    { label = "Facepunch", url = "https://facepunch.com/" }
  }
}

drpc.Initialize("your_application_id")
-- updates only once, and if you will use any kind of dynamic values, such as player count
-- it would be recommended to use it inside Think/Tick hook or timers.
drpc.UpdatePresence(presence)