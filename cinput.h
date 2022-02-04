#pragma once

#include "sdk.h"

class CInput
{
public:
	char pad0[0xC]; // 0x0
	bool m_trackir_available; // 0xC
	bool m_mouse_initialized; // 0xD
	bool m_mouse_active; // 0xE
	char pad1[0x9E]; // 0xF
	bool m_fCameraInThirdPerson; // 0xAD
	char pad2[0x2]; // 0xAE
	Vector m_vecCameraOffset; // 0xB0
	char pad3[0x38]; // 0xBC
	CUserCmd* m_pCommands; // 0xF4
	CVerifiedUserCmd* m_pVerifiedCommands; // 0xF8

	CUserCmd* GetUserCmd( int slot, int seq )
	{
		typedef CUserCmd* ( __thiscall* OriginalFn )( PVOID, int, int );
		return getvfunc<OriginalFn>( this, 8 )( this, slot, seq );
	}

	CUserCmd* CAM_ToThirdPerson( )
	{
		typedef CUserCmd* ( __thiscall* OriginalFn )( PVOID );
		return getvfunc<OriginalFn>( this, 35 )( this );
	}

	CUserCmd* CAM_ToFirstPerson( )
	{
		typedef CUserCmd* ( __thiscall* OriginalFn )( PVOID );
		return getvfunc<OriginalFn>( this, 36 )( this );
	}
};

extern CInput* g_pInput;