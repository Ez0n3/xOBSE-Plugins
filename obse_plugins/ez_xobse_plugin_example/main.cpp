// User Defines
#include "config.h"
// OBSE
#include "obse/GameAPI.h"
#include "obse/PluginAPI.h"
#include "obse_common/SafeWrite.h"
// Legacy SDK
#include "obse/CommandTable.h" // Required for new functions
#include "obse/ParamInfos.h"
#include "obse/GameObjects.h"
#include "obse/GameOSDepend.h"
#include "obse/Script.h" // OBSE Only
#include <string>
// Windows
#include <shlobj.h>	// CSIDL_MYCODUMENTS

// ================================
// Handles
// ================================

// Handle for the plugin
PluginHandle g_pluginHandle = kPluginHandle_Invalid;

// Handle for other things...

/* // Uncomment to use the OBSE interface
// Handle for the interface
OBSEInterface* g_interface;
*/

/* // Uncomment to use the script interface
// Handle for the script interface
OBSEScriptInterface* g_script;
#define ExtractArgsEx(...) g_script->ExtractArgsEx(__VA_ARGS__)
#define ExtractFormatStringArgs(...) g_script->ExtractFormatStringArgs(__VA_ARGS__)
*/

/* // Uncomment to use the command table interface
// Handle for the command table interface
OBSECommandTableInterface* g_cmdTable;
const CommandInfo* g_TFC;
*/

/* // Uncomment to use messaging
// Handle for the messaging interface
static OBSEMessagingInterface* g_messaging = NULL;
*/

// ================================
// User Code
// ================================

// If is RUNTIME PreProc, not in the Editor
#ifdef RUNTIME

// Example test bool function to print Hello World! to the plugin log and console
// Note: New functions are prepended with "Cmd_" and appended with "_Execute"
// And are enclosed within the #ifdef RUNTIME preprocessor definition
bool Cmd_PluginExampleFunctionsTest_Execute(COMMAND_ARGS)
{
	_MESSAGE("Hello World!"); // print to the plugin log
	Console_Print("Hello Console!"); // print to the in-game console

	//*result = 42;

	return true;
}

#endif // RUNTIME

// Define the example test bool function, including a description of what it does
// Note: Outside of the RUNTIME def, for the editor also
DEFINE_COMMAND_PLUGIN(PluginExampleFunctionsTest, "Prints Hello to the Log and Console", 0, 0, NULL)

// ================================
// Plugin Listener
// ================================

/* // Uncomment to use messaging
// Listener for the plugin
static void PluginListener(OBSEMessagingInterface::Message* msg) noexcept
{
	switch (msg->type) {
		// case OBSEMessagingInterface::kMessage_PostLoad:
		case OBSEMessagingInterface::kMessage_PostPostLoad: // facilitate the correct dispatching/registering of messages/listeners
		{
			_MESSAGE("PluginListener: kMessage_PostPostLoad");
			break;
		}
		// case OBSEMessagingInterface::kMessage_ExitGame:
		// case OBSEMessagingInterface::kMessage_ExitToMainMenu:
		// case OBSEMessagingInterface::kMessage_LoadGame:
		// case OBSEMessagingInterface::kMessage_SaveGame:
		// case OBSEMessagingInterface::kMessage_Precompile:
		// case OBSEMessagingInterface::kMessage_ExitGame_Console:
		// case OBSEMessagingInterface::kMessage_RuntimeScriptError:
		// case OBSEMessagingInterface::kMessage_PostLoadGame:
		// case OBSEMessagingInterface::kMessage_PreLoadGame:
	}
}
*/

// ================================
// Plugin Compatibility Check
// ================================

// Check that the runtime and plugin versions are compatible
const bool IsCompatible(const OBSEInterface* obse)
{
	// check if it's being loaded into the editor
	if(obse->isEditor)
	{
		// FIXME - can i use the prop global variable here? it's only set for the editor which plugins don't need?
		// check that it's the supported editor
		if(obse->editorVersion < SUPPORTED_RUNTIME_VERSION_CS) { // CS_VERSION_1_4_0_518
			_MESSAGE("ERROR::IsCompatible: Editor incorrect editor version (got %08X need at least %08X)", obse->editorVersion, SUPPORTED_RUNTIME_VERSION_CS); // CS_VERSION_1_4_0_518
			_ERROR("ERROR::IsCompatible: Editor incorrect editor version (got %08X need at least %08X)", obse->editorVersion, SUPPORTED_RUNTIME_VERSION_CS); // CS_VERSION_1_4_0_518
			return false;
		}
	}
	// check for compatible version. if strict=true, runtime and supported versions must match. if strict=false, runtime version must be above the minimum
	else if (!IVersionCheck::IsCompatibleVersion(obse->oblivionVersion, MINIMUM_RUNTIME_VERSION, SUPPORTED_RUNTIME_VERSION, SUPPORTED_RUNTIME_VERSION_STRICT)) { // not strict
		_MESSAGE("ERROR::IsCompatible: Plugin is not compatible with runtime version, disabling");
		_FATALERROR("ERROR::IsCompatible: Plugin is not compatible with runtime version, disabling");
		
		// not compatible
		return false;
	}
	
	// compatible
	return true;
}

// ================================
// Plugin Export, Query and Load - Start Extern-C
// ================================

extern "C" { // Start: extern "C"

// ================================
// Plugin Version Data - Not Used In All SE SDK's
// ================================

/*
// OBSE does not use this
__declspec(dllexport) OBSEPluginVersionData OBSEPlugin_Version =
{
};
*/

// ================================
// Plugin Query - Not Used In All SE SDK's
// ================================

// OBSE Plugin Query - Called when the plugin is queried
bool OBSEPlugin_Query(const OBSEInterface* obse, PluginInfo* info)
{
	// open the plugin log file
	gLog.OpenRelative(CSIDL_MYDOCUMENTS, PLUGIN_LOG_FILE);
	
	_MESSAGE(PLUGIN_VERSION_INFO); // write the plugin version to the log
	_MESSAGE("Plugin_Query: Querying");

	// populate info structure
	info->infoVersion =	PluginInfo::kInfoVersion;
	info->name =		PLUGIN_NAME_LONG;		// set in config.h
	info->version =		PLUGIN_VERSION_DLL;		// set in config.h
	
	// check for compatible versions
	if (!IsCompatible(obse)) {
		_MESSAGE("ERROR::Plugin_Query: Incompatible | Disabling Plugin");
		_FATALERROR("ERROR::Plugin_Query: Incompatible | Disabling Plugin");
		// incompatible
		return false;
	}
	
	// ######################################################
	// Note: Nothing should be assigned below this point
	// Get the necessary info about the plugin and return
	// ######################################################
	
	_MESSAGE("Plugin_Query: Queried Successfully"); // log the successful query

	// supported runtime version
	return true;
}

// ================================
// Plugin Preload - Not Used In All SE SDK's
// ================================

/*
// OBSE does not use this
bool OBSEPlugin_Preload(const OBSEInterface* obse)
{
}
*/

// ================================
// Plugin Load - Used In All SE SDK's
// ================================

// OBSE Plugin Load - Called when the plugin loads everytime
bool OBSEPlugin_Load(const OBSEInterface* obse)
{
	// open the plugin log file
	gLog.OpenRelative(CSIDL_MYDOCUMENTS, PLUGIN_LOG_FILE);

	_MESSAGE(PLUGIN_VERSION_INFO); // write the plugin version to the log
	_MESSAGE("Plugin_Load: Loading");
	
	// check for compatible versions
	if (!IsCompatible(obse)) {
		_MESSAGE("ERROR::Plugin_Load: Incompatible | Disabling Plugin");
		_FATALERROR("ERROR::Plugin_Load: Incompatible | Disabling Plugin");
		// incompatible
		return false;
	}
	
	// store plugin handle for later
	g_pluginHandle = obse->GetPluginHandle();
	
	/* // Uncomment to use the OBSE interface
	// save the OBSEinterface in case we need it later
	g_interface = (OBSEInterface *)obse;
	*/
	
	/* // Uncomment to use the script interface
	// store script handle for later
	g_script = (OBSEScriptInterface*)obse->QueryInterface(kInterface_Script);
	*/
	
	/* // Uncomment to use messaging
	// register the listener
	g_messaging = (OBSEMessagingInterface*)obse->QueryInterface(kInterface_Messaging);
	if (g_messaging) {
		if (g_messaging->RegisterListener(g_pluginHandle, "OBSE", PluginListener)) {
			_MESSAGE("Plugin_Load: Listener Registered");
		}
	}
	*/
	
	/***************************************************************************
	 *	
	 *	IMPORTANT::READ THIS!
	 *	
	 *	Before releasing your plugin, you need to request an opcode range from
	 *	the OBSE team and set it in your first SetOpcodeBase call. If you do not
	 *	do this, your plugin will create major compatibility issues with other
	 *	plugins, and will not load in release versions of OBSE. See
	 *	obse_readme.txt for more information.
	 *	
	 **************************************************************************/
	 
	// register the new functions
	obse->SetOpcodeBase(0x2000);
	if (obse->RegisterCommand(&kCommandInfo_PluginExampleFunctionsTest)) {
		_MESSAGE("Plugin_Load: Functions Registered");
	}
	
	_MESSAGE("Plugin_Load: Loaded Successfully"); // log the successful load

	// initialized
	return true;
}

}; // Stop: extern "C"

// =======================================
