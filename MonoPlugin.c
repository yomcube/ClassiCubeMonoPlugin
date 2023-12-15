/*
gcc -o MonoPlugin.so MonoPlugin.c \
	-shared -fPIC \
	-rdynamic `pkg-config --cflags --libs mono-2`
*/
#ifdef _WIN32
    #define CC_API __declspec(dllimport)
    #define CC_VAR __declspec(dllimport)
    #define EXPORT __declspec(dllexport)
#else
    #define CC_API
    #define CC_VAR
    #define EXPORT __attribute__((visibility("default")))
#endif

#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>
#include <mono/metadata/debug-helpers.h>
#include <mono/metadata/environment.h>
#include <mono/utils/mono-publib.h>
#include <mono/metadata/mono-config.h>
#include <stdlib.h>

#include "../ClassiCube-src/src/BlockPhysics.h"
#include "../ClassiCube-src/src/Chat.h"
#include "../ClassiCube-src/src/Event.h"
#include "../ClassiCube-src/src/Game.h"
#include "../ClassiCube-src/src/Platform.h"
#include "../ClassiCube-src/src/String.h"

#include "Api.h"

#define LoaderFile "MonoPluginLoader.dll"

static const cc_string MonoPlugin_PluginDirectory = String_FromConst("monoplugins");
static const cc_string errmsg = String_FromConst("&cAn error has occurred.");

MonoDomain *domain;
MonoAssembly* assembly;
MonoImage* image;

#include "Methods.h"

static void MonoInit(void) {
	mono_config_parse (NULL);
	domain = mono_jit_init ("ClassiCube");
	assembly = mono_domain_assembly_open (domain, LoaderFile);
	if (!assembly) {
		mono_jit_cleanup (domain);
		return;
	}
	image = mono_assembly_get_image (assembly);
	
	MonoPlugin_RegisterApi();
	InitMethods(image);
}

static void LoadPlugin(const cc_string* filename, void* obj) {
	if (!assembly)
		return;
	void *args[1];
	char* str[filename->length + 1];
	String_CopyToRaw(&str, filename->length + 1, filename);
	args[0] = mono_string_new_wrapper(str);
	mono_runtime_invoke (Method_FileCallback, NULL, args, NULL);
}

#define inv(m) mono_runtime_invoke(m,NULL,NULL,NULL);
static void MonoPlugin_Init(void) {
	Directory_Create(&MonoPlugin_PluginDirectory);
	MonoInit();
	Directory_Enum(&MonoPlugin_PluginDirectory, NULL, LoadPlugin);
	MPAPI_Command_InitCommands();
}

static void MonoPlugin_Free(void) {
	inv (Method_Free);
	mono_jit_cleanup (domain);
}
static void MonoPlugin_Reset(void) {
	inv (Method_Reset);
}
static void MonoPlugin_OnNewMap(void) {
	inv (Method_OnNewMap);
}
static void MonoPlugin_OnNewMapLoaded(void) {
	inv (Method_OnNewMapLoaded);
}

EXPORT int Plugin_ApiVersion = 1;
EXPORT struct IGameComponent Plugin_Component = {
	MonoPlugin_Init           /* | Init           | */,
	MonoPlugin_Free           /* | Free           | */,
	MonoPlugin_Reset          /* | Reset          | */,
	MonoPlugin_OnNewMap       /* | OnNewMap       | */,
	MonoPlugin_OnNewMapLoaded /* | OnNewMapLoaded | */
};