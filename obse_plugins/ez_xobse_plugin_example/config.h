#pragma once
#include "obse_common/obse_version.h" // OBSE
#include "IVersionCheck.h" // Common plugin version check, found in ..\plugins_common\
// #include "../plugin_common/common.h" // EG: Common plugin functions for this sdk if needed

// ================================
// Plugin Information
// ================================

// Plugin info
#define PLUGIN_AUTHOR				"Ez0n3"					// Author of the plugin

#define PLUGIN_NAME_SHORT			"ez_xobse_plugin_example"	// Plugin name without spaces
#define PLUGIN_NAME_LONG			"Ez xOBSE Plugin Example"	// Plugin name with spaces

// Plugin version, Major, Minor, Build. EG: (1.0.0) equals (Major.Minor.Build)
#define PLUGIN_VERSION_MAJOR		1
#define PLUGIN_VERSION_MINOR		0
#define PLUGIN_VERSION_BUILD		0

// ================================
// Nothing below this needs changing between plugins except maybe MINIMUM_RUNTIME_VERSION and/or SUPPORTED_RUNTIME_VERSION_STRICT
// ================================

// Plugin log file
#define PLUGIN_LOG_FILE				"\\My Games\\" GAME_SAVE_FOLDER_NAME("Oblivion") "\\OBSE\\" PLUGIN_LOG_FILE_NAME(PLUGIN_NAME_SHORT) // plugin log file location

// Common definitions
#define SDK_VERSION_STRING			VERSION_TO_STRING(OBSE_VERSION_INTEGER, OBSE_VERSION_INTEGER_MINOR, OBSE_VERSION_INTEGER_HOTIFX)
#define PLUGIN_VERSION_STRING		VERSION_TO_STRING(PLUGIN_VERSION_MAJOR, PLUGIN_VERSION_MINOR, PLUGIN_VERSION_BUILD)

#define PLUGIN_VERSION_DLL			MAKE_EXE_VERSION(PLUGIN_VERSION_MAJOR, PLUGIN_VERSION_MINOR, PLUGIN_VERSION_BUILD)
#define PLUGIN_VERSION_INFO			PLUGIN_NAME_SHORT " v%s (0x%08X) (SDK v%s)", PLUGIN_VERSION_STRING, PLUGIN_VERSION_DLL, SDK_VERSION_STRING

// ================================
// Plugin Version Information
// ================================

// The minimum runtime version allowed by the plugin. EG: I need function X, which was added in runtime Y, therefore Y is the minimum runtime version
#define MINIMUM_RUNTIME_VERSION				OBLIVION_VERSION_1_2_416	// The latest version

// The runtime version the plugin was designed for
// #define SUPPORTED_RUNTIME_VERSION		CURRENT_RELEASE_RUNTIME
#define SUPPORTED_RUNTIME_VERSION			RUNTIME_VERSION // Set in /config/_Plugins.props, controls core and plugin versions - normally latest

// Strict runtime version. If strict=true, runtime and supported versions must match. If strict=false, runtime version must be above the minimum
#define SUPPORTED_RUNTIME_VERSION_STRICT	false

// The compatible runtime version - set automatically
#define COMPATIBLE(runtimeVersion)			(runtimeVersion == SUPPORTED_RUNTIME_VERSION)

// The compatible editor version
// #define SUPPORTED_RUNTIME_VERSION_CS		CS_VERSION_1_2 // latest editor
#define SUPPORTED_RUNTIME_VERSION_CS		CS_VERSION // Set in /config/_Plugins.props

// ================================

/*
// xOBSE From obse_version.h 
#define OBLIVION_VERSION_1_2_416 MAKE_OBLIVION_VERSION(1, 2, 416)	// 0x010201A0

#define CS_VERSION_1_0 MAKE_OBLIVION_VERSION(1, 0, 303)				// 0x0100012F
#define CS_VERSION_1_2 MAKE_OBLIVION_VERSION(1, 2, 0)				// 0x01020000


// OBSE From obse_version.h - Note: OBLIVION_VERSION_0_1 rather than RUNTIME_VERSION_0_1 like most SDK's

#define OBLIVION_VERSION_0_1 MAKE_OBLIVION_VERSION(0, 1, 228)		// 0x000100E4
#define OBLIVION_VERSION_1_1 MAKE_OBLIVION_VERSION(1, 1, 511)		// 0x010101FF
#define OBLIVION_VERSION_1_2 MAKE_OBLIVION_VERSION(1, 2, 214)		// 0x010200D6
#define OBLIVION_VERSION_1_2_410 MAKE_OBLIVION_VERSION(1, 2, 410)	// 0x0102019A
#define OBLIVION_VERSION_1_2_416 MAKE_OBLIVION_VERSION(1, 2, 416)	// 0x010201A0

#define CS_VERSION_1_0 MAKE_OBLIVION_VERSION(1, 0, 303)				// 0x0100012F
#define CS_VERSION_1_2 MAKE_OBLIVION_VERSION(1, 2, 0)				// 0x01020000
*/
