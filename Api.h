#ifndef CCMONOPLUGIN_API_H
#define CCMONOPLUGIN_API_H

#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>
#include <mono/metadata/debug-helpers.h>
#include <mono/metadata/environment.h>
#include <mono/metadata/object.h>
#include <mono/utils/mono-publib.h>
#include <mono/metadata/mono-config.h>
#include <stdlib.h>

#include "../ClassiCube-src/src/Block.h"
#include "../ClassiCube-src/src/BlockPhysics.h"
#include "../ClassiCube-src/src/Camera.h"
#include "../ClassiCube-src/src/Chat.h"
#include "../ClassiCube-src/src/Commands.h"
#include "../ClassiCube-src/src/Constants.h"
#include "../ClassiCube-src/src/Entity.h"
#include "../ClassiCube-src/src/Event.h"
#include "../ClassiCube-src/src/ExtMath.h"
#include "../ClassiCube-src/src/Game.h"
#include "../ClassiCube-src/src/Inventory.h"
#include "../ClassiCube-src/src/Platform.h"
#include "../ClassiCube-src/src/Server.h"
#include "../ClassiCube-src/src/String.h"
#include "../ClassiCube-src/src/Vectors.h"
#include "../ClassiCube-src/src/Window.h"
#include "../ClassiCube-src/src/World.h"

#include "Methods.h"

#define String_Empty { NULL, 0, 0 };
#define STRLEN 80
#define c_to_cc(cstr) String_Init(cstr, String_CalcLen(cstr, STRLEN), STRLEN)

void MonoPlugin_RegisterApi(void);

/* TODO

	- Add commands
	
	- Document stuff not in Scripting.h:
		- Camera.GetIsSmooth
		- World.GetPhysicsEnabled
		- World.GetSeed
		- Platform module
		
	- Implement functions
		- Server.SendData
		- Window.GetHandle
*/

//
// Block module
//

static int MPAPI_Block_Parse(MonoString* value) {
	char* cstr = mono_string_to_utf8(value);
	cc_string ccstr = c_to_cc(cstr);
	return Block_Parse(&ccstr);
}
static int MPAPI_Block_GetIsLiquid(int id) {
	return Blocks.IsLiquid[id];
}

//
// Camera module
//

static int MPAPI_Camera_GetFov(void) {
	return Camera.Fov;
}
static int MPAPI_Camera_GetIsThird(void) {
	return Camera.Active->isThirdPerson;
}
static int MPAPI_Camera_GetX(void) {
	return Camera.CurrentPos.X;
}
static int MPAPI_Camera_GetY(void) {
	return Camera.CurrentPos.Y;
}
static int MPAPI_Camera_GetZ(void) {
	return Camera.CurrentPos.Z;
}
static int MPAPI_Camera_GetYaw(void) {
	Vec2 orientation = Camera.Active->GetOrientation();
	return MATH_RAD2DEG * orientation.X;
}
static int MPAPI_Camera_GetPitch(void) {
	Vec2 orientation = Camera.Active->GetOrientation();
	return MATH_RAD2DEG * orientation.Y;
}
static int MPAPI_Camera_GetIsSmooth(void) {
	return Camera.Smooth;
}

//
// Chat module
//

static void MPAPI_Chat_Add (MonoString* mmsg) {
	char* cmsg = mono_string_to_utf8(mmsg);
	cc_string msg = c_to_cc(cmsg);
	Chat_Add(&msg);	
}
static void MPAPI_Chat_AddOf (MonoString* mmsg, int msgType) {
	char* cmsg = mono_string_to_utf8(mmsg);
	cc_string msg = c_to_cc(cmsg);
	Chat_AddOf(&msg, msgType);
}
static void MPAPI_Chat_Send (MonoString* mmsg, int logUsage) {
	char* cmsg = mono_string_to_utf8(mmsg);
	cc_string msg = c_to_cc(cmsg);
	Chat_Send(&msg, logUsage);
}

//
// Command module
//

static void MonoPlugin_CommandExecute (const cc_string* args, int argsCount) {
	if (!argsCount) {
		mono_runtime_invoke(Method_ListCommands, NULL, NULL, NULL);
		return;
	}
	void *a[1];
	char* str[args->length + 1];
	String_CopyToRaw(&str, args->length + 1, args);
	a[0] = mono_string_new_wrapper(str);
	mono_runtime_invoke(Method_HandleCommand, NULL, a, NULL);
}
static struct ChatCommand MonoPlugin_Command = {
	"monocmd", MonoPlugin_CommandExecute,
	COMMAND_FLAG_UNSPLIT_ARGS,
	{
		"&a/client monocmd [command name] [args]",
		"&eRuns the mono command specified."
	}
};
static void MPAPI_Command_InitCommands(void) {
	mono_runtime_invoke (Method_InitCommands, NULL,NULL,NULL);
	Commands_Register(&MonoPlugin_Command);
}

//
// Env module
//

static void MPAPI_Env_SetEdgeBlock(int id) {
	Env_SetEdgeBlock(id);
}
static void MPAPI_Env_SetEdgeHeight(int height) {
	Env_SetEdgeHeight(height);
}
static void MPAPI_Env_SetSidesBlock(int id) {
	Env_SetSidesBlock(id);
}
static void MPAPI_Env_SetSidesOffset(int offset) {
	Env_SetSidesOffset(offset);
}
static void MPAPI_Env_SetCloudsHeight(int height) {
	Env_SetCloudsHeight(height);
}
static void MPAPI_Env_SetCloudsSpeed(float speed) {
	Env_SetCloudsSpeed(speed);
}
static void MPAPI_Env_SetWeather(int weather) {
	Env_SetWeather(weather);
}
static void MPAPI_Env_SetWeatherSpeed(float speed) {
	Env_SetWeatherSpeed(speed);
}
static void MPAPI_Env_SetWeatherFade(float rate) {
	Env_SetWeatherFade(rate);
}

//
// Game module
//

static void MPAPI_Game_SetBlock(int x, int y, int z, int id) {
	Game_UpdateBlock(x, y, z, id);
}
static void MPAPI_Game_ChangeBlock(int x, int y, int z, int id) {
	Game_ChangeBlock(x, y, z, id);
}
static double MPAPI_Game_GetTime(void) {
	return Game.Time;
}

//
// Inventory module
//

static int MPAPI_Inventory_GetSelected(void) {
	return Inventory_SelectedBlock;
}

//
// Player module
//

// From Scripting.h
#define GetPlayer() ((struct LocalPlayer*)Entities.List[ENTITIES_SELF_ID])

static int MPAPI_Player_GetReach(void) {
	struct LocalPlayer* p = GetPlayer();
	return p->ReachDistance;
}
static int MPAPI_Player_GetX(void) {
	struct LocalPlayer* p = GetPlayer();
	return p->Base.Position.X;
}
static int MPAPI_Player_GetY(void) {
	struct LocalPlayer* p = GetPlayer();
	return p->Base.Position.Y;
}
static int MPAPI_Player_GetZ(void) {
	struct LocalPlayer* p = GetPlayer();
	return p->Base.Position.Z;
}
static int MPAPI_Player_GetYaw(void) {
	struct LocalPlayer* p = GetPlayer();
	return p->Base.Yaw;
}
static int MPAPI_Player_GetPitch(void) {
	struct LocalPlayer* p = GetPlayer();
	return p->Base.Pitch;
}

//
// Server module
//

static MonoString* MPAPI_Server_GetMotd(void) {
	return mono_string_new_wrapper (Server.MOTD.buffer);
}
static MonoString* MPAPI_Server_GetName(void) {
	return mono_string_new_wrapper (Server.Name.buffer);
}
static MonoString* MPAPI_Server_GetAppName(void) {
	return mono_string_new_wrapper (Server.AppName.buffer);
}
static MonoString* MPAPI_Server_GetAddress(void) {
	return mono_string_new_wrapper (Server.Address.buffer);
}
static int MPAPI_Server_GetPort(void) {
	return Server.Port;
}
static void MPAPI_Server_SetAppName(MonoString* name) {
	char* cstr = mono_string_to_utf8(name);
	cc_string ccstr = c_to_cc(cstr);
	String_Copy(&Server.AppName, &ccstr);
}
static int MPAPI_Server_GetIsSingleplayer(void) {
	return Server.IsSinglePlayer;
}

//
// Tablist module
//

static MonoString* MPAPI_Tablist_GetPlayer(int id) {
	cc_string name = String_Empty;
	if (TabList.NameOffsets[id]) name = TabList_UNSAFE_GetPlayer(id);
	return mono_string_new_wrapper (name.buffer);
}
static MonoString* MPAPI_Tablist_GetName(int id) {
	cc_string name = String_Empty;
	if (TabList.NameOffsets[id]) name = TabList_UNSAFE_GetList(id);
	return mono_string_new_wrapper (name.buffer);
}
static MonoString* MPAPI_Tablist_GetGroup(int id) {
	cc_string name = String_Empty;
	if (TabList.NameOffsets[id]) name = TabList_UNSAFE_GetGroup(id);
	return mono_string_new_wrapper (name.buffer);
}
static int MPAPI_Tablist_GetRank(int id) {
	return TabList.GroupRanks[id];
}
static void MPAPI_Tablist_Remove(int id) {
	TabList_Remove(id);
}
static void MPAPI_Tablist_Set(int id, MonoString* player, MonoString* name, MonoString* group, int groupRank) {
	char* c_player = mono_string_to_utf8(player);
	char* c_name   = mono_string_to_utf8(name);
	char* c_group  = mono_string_to_utf8(group);
	cc_string cc_player = c_to_cc(c_player);
	cc_string cc_name   = c_to_cc(c_name);
	cc_string cc_group  = c_to_cc(c_group);
	TabList_Set(id, &cc_player, &cc_name, &cc_group, groupRank);
}

//
// Window module
//

static void MPAPI_Window_SetTitle(MonoString* title) {
	char* cstr = mono_string_to_utf8(title);
	cc_string ccstr = c_to_cc(cstr);
	Window_SetTitle(&ccstr);
}

//
// World module
//

static int MPAPI_World_GetWidth(void) {
	return World.Width;
}
static int MPAPI_World_GetHeight(void) {
	return World.Height;
}
static int MPAPI_World_GetLength(void) {
	return World.Length;
}
static int MPAPI_World_GetBlock(int x, int y, int z) {
	return World_GetBlock(x, y, z);
}
static int MPAPI_World_GetPhysicsEnabled(void) {
	return Physics.Enabled;
}
static int MPAPI_World_GetSeed(void) {
	return World.Seed;
}

//
// Platform module
//

static void MPAPI_Process_Exit(int code) {
	Process_Exit(code);
}
static int MPAPI_Process_StartOpen(MonoString* args) {
	char* cstr = mono_string_to_utf8(args);
	cc_string ccstr = c_to_cc(cstr);
	return Process_StartOpen(&ccstr);
}

static int MPAPI_Directory_Create(MonoString* path) {
	char* cstr = mono_string_to_utf8(path);
	cc_string ccstr = c_to_cc(cstr);
	return Directory_Create(&ccstr);
}
static int MPAPI_File_Exists(MonoString* path) {
	char* cstr = mono_string_to_utf8(path);
	cc_string ccstr = c_to_cc(cstr);
	return File_Exists(&ccstr);
}

////////////////////////////////////////////////////////////////
void MonoPlugin_RegisterApi(void) {
	mono_add_internal_call("ClassiCube.Block::Parse(string)",    (const void *)MPAPI_Block_Parse);
	mono_add_internal_call("ClassiCube.Block::GetIsLiquid(int)", (const void *)MPAPI_Block_GetIsLiquid);
	
	mono_add_internal_call("ClassiCube.Camera::GetFov()",      (const void *)MPAPI_Camera_GetFov);
	mono_add_internal_call("ClassiCube.Camera::GetIsThird()",  (const void *)MPAPI_Camera_GetIsThird);
	mono_add_internal_call("ClassiCube.Camera::GetX()",        (const void *)MPAPI_Camera_GetX);
	mono_add_internal_call("ClassiCube.Camera::GetY()",        (const void *)MPAPI_Camera_GetY);
	mono_add_internal_call("ClassiCube.Camera::GetZ()",        (const void *)MPAPI_Camera_GetZ);
	mono_add_internal_call("ClassiCube.Camera::GetYaw()",      (const void *)MPAPI_Camera_GetYaw);
	mono_add_internal_call("ClassiCube.Camera::GetPitch()",    (const void *)MPAPI_Camera_GetPitch);
	mono_add_internal_call("ClassiCube.Camera::GetIsSmooth()", (const void *)MPAPI_Camera_GetIsSmooth);
	
	mono_add_internal_call("ClassiCube.Chat::Add(string)",       (const void *)MPAPI_Chat_Add);
	mono_add_internal_call("ClassiCube.Chat::AddOf(string,int)", (const void *)MPAPI_Chat_AddOf);
	mono_add_internal_call("ClassiCube.Chat::Send(string,int)",  (const void *)MPAPI_Chat_Send);
	
	mono_add_internal_call("ClassiCube.Env::SetEdgeBlock(int)",      (const void *)MPAPI_Env_SetEdgeBlock);
	mono_add_internal_call("ClassiCube.Env::SetEdgeHeight(int)",     (const void *)MPAPI_Env_SetEdgeHeight);
	mono_add_internal_call("ClassiCube.Env::SetSidesBlock(int)",     (const void *)MPAPI_Env_SetSidesBlock);
	mono_add_internal_call("ClassiCube.Env::SetSidesOffset(int)",    (const void *)MPAPI_Env_SetSidesOffset);
	mono_add_internal_call("ClassiCube.Env::SetCloudsHeight(int)",   (const void *)MPAPI_Env_SetCloudsHeight);
	mono_add_internal_call("ClassiCube.Env::SetCloudsSpeed(float)",  (const void *)MPAPI_Env_SetCloudsSpeed);
	mono_add_internal_call("ClassiCube.Env::SetWeather(int)",        (const void *)MPAPI_Env_SetWeather);
	mono_add_internal_call("ClassiCube.Env::SetWeatherSpeed(float)", (const void *)MPAPI_Env_SetWeatherSpeed);
	mono_add_internal_call("ClassiCube.Env::SetWeatherFade(float)",  (const void *)MPAPI_Env_SetWeatherFade);
	
	mono_add_internal_call("ClassiCube.Game::SetBlock(int,int,int,int)",    (const void *)MPAPI_Game_SetBlock);
	mono_add_internal_call("ClassiCube.Game::ChangeBlock(int,int,int,int)", (const void *)MPAPI_Game_ChangeBlock);
	
	mono_add_internal_call("ClassiCube.Inventory::GetSelected()", (const void *)MPAPI_Inventory_GetSelected);
	
	mono_add_internal_call("ClassiCube.Player::GetReach()", (const void *)MPAPI_Player_GetReach);
	mono_add_internal_call("ClassiCube.Player::GetX()",     (const void *)MPAPI_Player_GetX);
	mono_add_internal_call("ClassiCube.Player::GetY()",     (const void *)MPAPI_Player_GetY);
	mono_add_internal_call("ClassiCube.Player::GetZ()",     (const void *)MPAPI_Player_GetZ);
	mono_add_internal_call("ClassiCube.Player::GetYaw()",   (const void *)MPAPI_Player_GetYaw);
	mono_add_internal_call("ClassiCube.Player::GetPitch()", (const void *)MPAPI_Player_GetPitch);
	
	mono_add_internal_call("ClassiCube.Server::GetMotd()",           (const void *)MPAPI_Server_GetMotd);
	mono_add_internal_call("ClassiCube.Server::GetName()",           (const void *)MPAPI_Server_GetName);
	mono_add_internal_call("ClassiCube.Server::GetAppName()",        (const void *)MPAPI_Server_GetAppName);
	mono_add_internal_call("ClassiCube.Server::GetAddress()",        (const void *)MPAPI_Server_GetAddress);
	mono_add_internal_call("ClassiCube.Server::GetPort()",           (const void *)MPAPI_Server_GetPort);
	mono_add_internal_call("ClassiCube.Server::SetAppName(string)",  (const void *)MPAPI_Server_SetAppName);
	mono_add_internal_call("ClassiCube.Server::GetIsSingleplayer()", (const void *)MPAPI_Server_GetIsSingleplayer);
	
	mono_add_internal_call("ClassiCube.Tablist::GetPlayer(int)",                    (const void *)MPAPI_Tablist_GetPlayer);
	mono_add_internal_call("ClassiCube.Tablist::GetName(int)",                      (const void *)MPAPI_Tablist_GetName);
	mono_add_internal_call("ClassiCube.Tablist::GetGroup(int)",                     (const void *)MPAPI_Tablist_GetGroup);
	mono_add_internal_call("ClassiCube.Tablist::GetRank(int)",                      (const void *)MPAPI_Tablist_GetRank);
	mono_add_internal_call("ClassiCube.Tablist::Remove(int)",                       (const void *)MPAPI_Tablist_Remove);
	mono_add_internal_call("ClassiCube.Tablist::Set(int,string,string,string,int)", (const void *)MPAPI_Tablist_Set);
	
	mono_add_internal_call("ClassiCube.Window::SetTitle(string)", (const void *)MPAPI_Window_SetTitle);
	
	mono_add_internal_call("ClassiCube.World::GetWidth()",            (const void *)MPAPI_World_GetWidth);
	mono_add_internal_call("ClassiCube.World::GetHeight()",           (const void *)MPAPI_World_GetHeight);
	mono_add_internal_call("ClassiCube.World::GetLength()",           (const void *)MPAPI_World_GetLength);
	mono_add_internal_call("ClassiCube.World::GetBlock(int,int,int)", (const void *)MPAPI_World_GetBlock);
	mono_add_internal_call("ClassiCube.World::GetPhysicsEnabled()",   (const void *)MPAPI_World_GetPhysicsEnabled);
	mono_add_internal_call("ClassiCube.World::GetSeed()",             (const void *)MPAPI_World_GetSeed);
	
	mono_add_internal_call("ClassiCube.Platform::Process_Exit(int)",         (const void *)MPAPI_Process_Exit);
	mono_add_internal_call("ClassiCube.Platform::Process_StartOpen(string)", (const void *)MPAPI_Process_StartOpen);
	mono_add_internal_call("ClassiCube.Platform::Directory_Create(string)",  (const void *)MPAPI_Directory_Create);
	mono_add_internal_call("ClassiCube.Platform::GetFile_Exists(string)",       (const void *)MPAPI_File_Exists);
}

#endif // CCMONOPLUGIN_API_H