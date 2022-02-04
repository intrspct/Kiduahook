#pragma once

typedef float matrix4x4[ 4 ][ 4 ]; 

class CBaseEntity;
class CUserCmd;
class CBaseCombatWeapon;
class CTrace;
class ISpatialQuery;
class shitnigger;
struct mstudiobbox_t;
typedef unsigned short MDLHandle_t;

#define OFFSET(funcname, type, offset) type& funcname() \
{ \
	static unsigned short _offset = offset; \
	return *reinterpret_cast<type*>( uintptr_t( this ) + _offset ); \
}

#include "main.h"
#include "dt_recv2.h"
#include "netvarmanager.h"
#include "defines.h"
#include "color.h"
#include "clientclass.h"
#include "cweapondata.h"
#include "hlclient.h"
#include "inetchannel.h"
#include "clientstate.h"
#include "vengineclient.h"
#include "chudchat.h"
#include "vcliententitylist.h"
#include "globalvars.h"
#include "cbaseentity.h"
#include "cbasecombatweapon.h"
#include "cusercmd.h"
#include "cinput.h"
#include "vclientprediction.h"
#include "cgamemovement.h"
#include "vdebugoverlay.h"
#include "vphysicssurfaceprops.h"
#include "cglowobjectmanager.h"
#include "imovehelper.h"
#include "vgui_surface.h"
#include "vgui_panel.h"
#include "imaterial.h"
#include "vmodelinfoclient.h"
#include "iCvar.h"
#include "vengineeffects.h"
#include "irecipienfilter.h"
#include "ienginesoundclient.h"
#include "iinputsystem.h"
#include "gameevents.h"
#include "cenginetraceclient.h"
#include "imemalloc.h"
#include "iviewrenderbeams.h"
#include "eventlogs.h"

#define FCVAR_NONE				0

#define FCVAR_UNREGISTERED				(1 << 0)	// If this is set, don't add to linked list, etc.
#define FCVAR_DEVELOPMENTONLY			(1 << 1)	// Hidden in released products. Flag is removed automatically if ALLOW_DEVELOPMENT_CVArs is defined.
#define FCVAR_GAMEDLL					(1 << 2)	// defined by the game DLL
#define FCVAR_CLIENTDLL					(1 << 3)    // defined by the client DLL
#define FCVAR_HIDDEN					(1 << 4)	// Hidden. Doesn't appear in find or auto complete. Like DEVELOPMENTONLY, but can't be compiled out.

#define FCVAR_PROTECTED					(1 << 5)    // It's a server cvar, but we don't send the data since it's a password, etc.  Sends 1 if it's not bland/zero, 0 otherwise as value
#define FCVAR_SPONLY					(1 << 6)    // This cvar cannot be changed by clients connected to a multiplayer server.
#define	FCVAR_ARCHIVE					(1 << 7)	// set to cause it to be saved to vars.rc
#define	FCVAR_NOTIFY					(1 << 8)	// notifies players when changed
#define	FCVAR_USERINFO					(1 << 9)	// changes the client's info string

#define FCVAR_PRINTABLEONLY				(1 << 10)   // This cvar's string cannot contain unprintable characters ( e.g., used for player name etc ).
#define FCVAR_UNLOGGED					(1 << 11)   // If this is a FCVAR_SERVER, don't log changes to the log file / console if we are creating a log
#define FCVAR_NEVER_AS_STRING			(1 << 12)   // never try to print that cvar

#define FCVAR_REPLICATED				(1 << 13)	// server setting enforced on clients, TODO rename to FCAR_SERVER at some time
#define FCVAR_CHEAT						(1 << 14)   // Only useable in singleplayer / debug / multiplayer & sv_cheats
#define FCVAR_SS						(1 << 15)   // causes varnameN where N == 2 through max splitscreen slots for mod to be autogenerated
#define FCVAR_DEMO						(1 << 16)   // record this cvar when starting a demo file
#define FCVAR_DONTRECORD				(1 << 17)   // don't record these command in demofiles
#define FCVAR_SS_ADDED					(1 << 18)   // This is one of the "added" FCVAR_SS variables for the splitscreen players
#define FCVAR_RELEASE					(1 << 19)   // Cvars tagged with this are the only cvars avaliable to customers
#define FCVAR_RELOAD_MATERIALS			(1 << 20)	// If this cvar changes, it forces a material reload
#define FCVAR_RELOAD_TEXTURES			(1 << 21)	// If this cvar changes, if forces a texture reload

#define FCVAR_NOT_CONNECTED				(1 << 22)	// cvar cannot be changed by a client that is connected to a server
#define FCVAR_MATERIAL_SYSTEM_THREAD	(1 << 23)	// Indicates this cvar is read from the material system thread
#define FCVAR_ARCHIVE_XBOX				(1 << 24)   // cvar written to config.cfg on the Xbox

#define FCVAR_SERVER_CAN_EXECUTE		(1 << 28)   // the server is allowed to execute this command on clients via ClientCommand/NET_StringCmd/CBaseClientState::ProcessStringCmd.
#define FCVAR_SERVER_CANNOT_QUERY		(1 << 29)   // If this is set, then the server is not allowed to query this cvar's value (via IServerPluginHelpers::StartQueryCvarValue).
#define FCVAR_CLIENTCMD_CAN_EXECUTE		(1 << 30)	// IVEngineClient::ClientCmd is allowed to execute this command.

#define FCVAR_ACCESSIBLE_FROM_THREADS	(1 << 25)	// used as a debugging tool necessary to check material system thread convars

#define FCVAR_MATERIAL_THREAD_MASK ( FCVAR_RELOAD_MATERIALS | FCVAR_RELOAD_TEXTURES | FCVAR_MATERIAL_SYSTEM_THREAD )

#define FLOW_OUTGOING	0		
#define FLOW_INCOMING	1
#define MAX_FLOWS		2		// in & out

extern DWORD dwClient;
extern DWORD dwVGUIMAT;
extern DWORD dwVGUI2;
extern DWORD dwEngine;

extern IMaterial* BubbleMat;
extern IMaterial* FlatMat;
extern IMaterial* Ghost2Mat;
extern IMaterial* TvMat;
extern IMaterial* CryptsMat;
extern IMaterial* PulseMat;
extern IMaterial* BanannaMat;
extern IMaterial* Ghost3Mat;
extern IMaterial* NetMat;
extern IMaterial* AnimMat;