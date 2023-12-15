#ifndef CCMONOPLUGIN_METHODS_H
#define CCMONOPLUGIN_METHODS_H

#include <mono/metadata/debug-helpers.h> // mono_method_desc_new & mono_method_desc_search_in_image
#include <mono/metadata/object.h> // MonoMethod & MonoImage

MonoMethod* Method_FileCallback;

MonoMethod* Method_HandleCommand;
MonoMethod* Method_ListCommands;
MonoMethod* Method_InitCommands;

MonoMethod* Method_Free;
MonoMethod* Method_Reset;
MonoMethod* Method_OnNewMap;
MonoMethod* Method_OnNewMapLoaded;

/* Must provide namespace */
static MonoMethod* GetMethod (MonoImage* i, const char* d) {
	MonoMethodDesc* desc = mono_method_desc_new (d, true);
	return mono_method_desc_search_in_image (desc, i);
}

static void InitMethods(MonoImage* i) {
	Method_FileCallback    = GetMethod (i,"ClassiCube.PluginLoader:FileCallback");
	
	Method_HandleCommand   = GetMethod (i,"ClassiCube.Command:HandleCommand");
	Method_ListCommands    = GetMethod (i,"ClassiCube.Command:ListCommands");
	Method_InitCommands    = GetMethod (i,"ClassiCube.Command:InitCommands");
	
	Method_Free            = GetMethod (i,"ClassiCube.Events:RaiseFree");
	Method_Reset           = GetMethod (i,"ClassiCube.Events:RaiseReset");
	Method_OnNewMap        = GetMethod (i,"ClassiCube.Events:RaiseNewMap");
	Method_OnNewMapLoaded  = GetMethod (i,"ClassiCube.Events:RaiseMapLoaded");
}

#endif // CCMONOPLUGIN_METHODS_H