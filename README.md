# ClassiCubeMonoPlugin

ClassiCubeMonoPlugin is a plugin for [ClassiCube](https://www.classicube.net/) that allows for scripting functionality with [mono](https://www.mono-project.com/).

## Table of contents
[How to use](#how-to-use)  
[Feedback](#feedback)  
[Developer info](#developer-info)  
[API](#api)  
[Example plugins](example-plugins)  
[Compiling](#compiling)

## How to use

Plugins DLLs are loaded from the `monoplugins` directory.

## Feedback

ClassiCubeMonoPlugin is by no means complete. Please open an issue to report bugs and provide feedback.

## Developer info

Plugins must be compiled in reference to `MonoPluginLoader.dll`.

```
mcs -target:library -r:path/to/MonoPluginLoader.dll path/to/file.cs
```
### Limitations

Plugins may not contain anything that calls `System.IO.FileSystem.FileExists`, or it will crash ClassiCube.

## API

The API is similar to the API found [here](https://github.com/ClassiCube/ClassiCube-Plugins/blob/master/Scripting/readme.md), except for the following differences:

### Adds
- `bool Camera.IsSmooth`
- `bool World.PhysicsEnabled`
- `int World.GetSeed()`
	- Returns `0` most of the time.
- `Platform` module
	- `Platform.Process_Exit(int code)`
	- `Platform.Process_StartOpen(string url)`
	- `Platform.Directory_Create(string path)`
	- `Platform.File_Exists(string path)`

### Not implemented yet
- Events except
	- `Events.Free`
	- `Events.Reset`
	- `Events.NewMap`
	- `Events.MapLoaded`
- `Server.SendDatas`
- `Window.GetHandle`

## Example plugins

Example plugins can be found in [here](https://github.com/yomcube/ClassiCubeMonoPlugin/tree/main/examples)

## Compiling

**IMPORTANT:** Header files that have been included from ClassiCube have a hardcoded path. Before compiling, please replace all instances of `../ClassiCube-src/src/` in `Api.h` and `MonoPlugin.c` with the path to the ClassiCube `src` directory.

### Compiling for Linux

```
gcc -o MonoPlugin.so MonoPlugin.c -shared -fPIC -rdynamic `pkg-config --cflags --libs mono-2`
mcs -target:library -out:MonoPluginLoader.dll MonoPluginLoader*.cs
```

### Compiling for Windows

TODO: Add documentation

### Compiling for MacOS

TODO: Add documentation
