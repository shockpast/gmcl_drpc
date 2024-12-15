# Discord Rich Presence for Garry's Mod

A binary module that implements Discord Rich Presence functionality for Garry's Mod, allowing you to display detailed game status in your Discord profile.

## Installation

1. Download the latest release from the [releases page](https://github.com/gmcl_drpc/releases/latest)
2. Place the binary module in your Garry's Mod `garrysmod/lua/bin` folder

## Usage

```lua
-- Initialize Discord RPC with your application ID
DiscordRPC.Initialize("YOUR_APP_ID")

-- Update your presence
DiscordRPC.UpdatePresence({
  details = "Playing on a server",
  state = "In Game",
  large_image_key = "game_logo",
  large_image_text = "Garry's Mod",
  small_image_key = "status_icon",
  small_image_text = "Online",
  party_size = 1,
  party_max = 32,
  buttons = {
    {
      label = "Join Game",
      url = "steam://connect/..."
    }
  }
})

-- Shutdown when done
DiscordRPC.Shutdown()
```

## Building

### Prerequisites
- [garrysmod_common](https://github.com/danielga/garrysmod_common) *(x86-64-support-sourcesdk)*
- [Discord RPC SDK](https://github.com/harmonytf/discord-rpc)
- Premake5

### Steps
1. Clone the repository
2. Place Discord RPC SDK files in `source/dependencies/windows` *(from latest action)*
3. Run `premake5 vs2019` (or your preferred generator)
4. Build the solution