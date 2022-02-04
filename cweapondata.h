#pragma once

#include "sdk.h"

#ifndef CONCAT_IMPL
#define CONCAT_IMPL(x, y) x##y
#ifndef MACRO_CONCAT
#define MACRO_CONCAT(x, y) CONCAT_IMPL(x, y)
#ifndef PAD
#define PAD(SIZE) BYTE MACRO_CONCAT(_pad, __COUNTER__)[SIZE];
#endif
#endif
#endif

struct WeaponInfo
{
	int _id = 0;
	std::string _name = "";
};

class CHudTexture 
{
public:
	PAD( 0x82 );
	char cCharacterInFont;
};

/*struct weapon_info_t
{
	char pad_0x0000[0x4]; //0x0000
	char* weapon_name; //0x0004 
	char pad_0x0008[0xC]; //0x0008
	__int32 max_clip_ammo; //0x0014 
	char pad_0x0018[0xC]; //0x0018
	__int32 max_ammo; //0x0024 
	char pad_0x0028[0x4]; //0x0028
	char* world_model; //0x002C 
	char* view_model; //0x0030 
	char* dropped_model; //0x0034 
	char pad_0x0038[0x4]; //0x0038
	char* shot_type_name; //0x003C 
	char pad_0x0040[0x28]; //0x0040
	char* silenced_shot_type_name; //0x0068 
	char pad_0x006C[0xC]; //0x006C
	char* nearly_empty_shot_type_name; //0x0078 
	char pad_0x007C[0x4]; //0x007C
	char* ammo_type; //0x0080 
	char pad_0x0084[0x4]; //0x0084
	char* hud_name; //0x0088 
	char* weapon_name2; //0x008C 
	char pad_0x0090[0x34]; //0x0090
	some_weird_struct* some_weird_pointer; //0x00C4 
	__int32 weapon_type; //0x00C8 
	char pad_0x00CC[0x4]; //0x00CC
	__int32 price; //0x00D0 
	__int32 kill_reward; //0x00D4 
	char* weapon_name_readable; //0x00D8 
	float N00000038; //0x00DC 
	float N00000039; //0x00E0 
	float N0000003A; //0x00E4 
	float N0000003B; //0x00E8 
	__int8 full_auto; //0x00EC 
	char pad_0x00ED[0x3]; //0x00ED
	__int32 damage; //0x00F0 
	float armor_ratio; //0x00F4 
	char pad_0x00F8[0x4]; //0x00F8
	float penetration; //0x00FC 
	float N00000041; //0x0100 
	float N00000042; //0x0104 
	float range; //0x0108 
	float range_modifier; //0x010C 
	char pad_0x0110[0x10]; //0x0110
	__int8 has_silencer; //0x0120 
	char pad_0x0121[0x3]; //0x0121
	void** some_weird_string_list; //0x0124 
	char pad_0x0128[0x8]; //0x0128
	float max_speed; //0x0130 
	float max_speed_alt; //0x0134 
	float move_speed_modifier; //0x0138 
	float spread; //0x013C 
	float spread_alt; //0x0140 
	float inaccuracy_crouch; //0x0144 
	float inaccuracy_crouch_alt; //0x0148 
	float inaccuracy_stand; //0x014C 
	float inaccuracy_stand_alt; //0x0150 
	float inaccuracy_jump_start; //0x0154 
	float inaccuracy_jump; //0x0158 
	float inaccuracy_jump_alt; //0x015C 
	float inaccuracy_land; //0x0160 
	float inaccuracy_land_alt; //0x0164 
	float inaccuracy_ladder; //0x0168 
	float inaccuracy_ladder_alt; //0x016C 
	float inaccuracy_fire; //0x0170 
	float inaccuracy_fire_alt; //0x0174 
	float inaccuracy_move; //0x0178 
	float inaccuracy_move_alt; //0x017C 
	char pad_0x0180[0x48]; //0x0180
	__int32 zoom_levels; //0x01C8 
	__int32 zoom_fov1; //0x01CC 
	__int32 zoom_fov2; //0x01D0 
	char pad_0x01D4[0xC]; //0x01D4
	char* weapon_type_name; //0x01E0 
	char pad_0x01E4[0x8]; //0x01E4
	char* ammo_shell_name; //0x01EC 
	char* tracer_name; //0x01F0 
	char pad_0x01F4[0x8]; //0x01F4
	char* N00000080; //0x01FC 
	char pad_0x0200[0x4]; //0x0200
	char* muzzleflash_name; //0x0204 
	char pad_0x0208[0x4]; //0x0208
	char* muzzlesmoke_name; //0x020C 
	char pad_0x0210[0x4]; //0x0210
	char* zoom_name; //0x0214 
	char* zoom_name_2; //0x0218 
	char pad_0x021C[0x24]; //0x021C

}; //Size=0x0240*/

//class CWeaponData
//{
//public:
//	char pad_0x0000[ 0x4 ]; //0x0000
//	char* weapon_name; //0x0004 
//	char pad_0x0008[ 0xC ]; //0x0008
//	__int32 max_clip_ammo; //0x0014 
//	char pad_0x0018[ 0xC ]; //0x0018
//	__int32 max_reserved_ammo; //0x0024 
//	char pad_0x0028[ 0x4 ]; //0x0028
//	char* world_model; //0x002C 
//	char* view_model; //0x0030 
//	char* dropped_model; //0x0034 
//	char pad_0x0038[ 0x4 ]; //0x0038
//	char* sound_single_shot; //0x003C 
//	char pad_0x0040[ 0x38 ]; //0x0040
//	char* sound_nearlyempty; //0x0078 
//	char pad_0x007C[ 0x4 ]; //0x007C
//	char* ammo_type; //0x0080 
//	char pad_0x0084[ 0x4 ]; //0x0084
//	char* hud_name; //0x0088 
//	char* weapon_name2; //0x008C 
//	char pad_0x0090[ 0x38 ]; //0x0090
//	__int32 weapon_type; //0x00C8 
//	char pad_0x00CC[ 0x4 ]; //0x00CC
//	__int32 weapon_price; //0x00D0 
//	char pad_0x00D4[ 0x8 ]; //0x00D4
//	float cycletime; //0x00DC 
//	char pad_0x00E0[ 0x4 ]; //0x00E0
//	float time_to_idle; //0x00E4 
//	float idle_interval; //0x00E8 
//	char pad_0x00EC[ 0x4 ]; //0x00EC
//	__int32 damage; //0x00F0 
//	char headshot_multipier [ 0x4 ];
//	float armor_ratio; //0x00F4 
//	char pad_0x00F8[ 0x4 ]; //0x00F8
//	float penetration; //0x00FC 
//	char pad_0x0100[ 0x8 ]; //0x0100
//	float range; //0x0108 
//	float range_modifier; //0x010C 
//	char pad_0x0110[ 0x18 ]; //0x0110
//	__int32 crosshair_min_distance; //0x0128 
//	__int32 crosshair_delta_distance; //0x012C 
//	float movement_speed; //0x0130 
//	float movement_speed_zoom; //0x0134 
//	char pad_0x0138[ 0x4C ]; //0x0138
//	__int32 recoil_seed; //0x0184 
//	char pad_0x0188[ 0x40 ]; //0x0188
//	__int32 zoom_levels; //0x01C8 
//	__int32 zoom_fov_1; //0x01CC 
//	__int32 zoom_fov_2; //0x01D0 
//	float zoom_time_0; //0x01D4 
//	float zoom_time_1; //0x01D8 
//	float zoom_time_2; //0x01DC 
//	char* addon_location; //0x01E0 
//	char pad_0x01E4[ 0x8 ]; //0x01E4
//	char* eject_brass_effect; //0x01EC 
//	char* tracer_effect; //0x01F0 
//	char pad_0x01F4[ 0x8 ]; //0x01F4
//	char* muzzle_flash_effect_1st_person; //0x01FC 
//	char pad_0x0200[ 0x4 ]; //0x0200
//	char* muzzle_flash_effect_3rd_person; //0x0204 
//	char pad_0x0208[ 0x4 ]; //0x0208
//	char* heat_effect; //0x020C 
//	char pad_0x0210[ 0x4 ]; //0x0210
//	char* zoom_in_sound; //0x0214 
//	char* zoom_out_sound; //0x0218 
//	char pad_0x021C[ 0xCC ]; //0x021C
//
//	char *bulletType()
//	{
//		return ( char* ) ( ( DWORD )this + 0x0080 );
//	}
//};

class CWeaponData
{
public:
public:
	void* pVTable;                       // 0x0000
	char m_strConsoleName;                   // 0x0004
	char pad_0008[12];                   // 0x0008
	int m_iMaxClip1;                       // 0x0014
	int m_iMaxClip2;                       // 0x0018
	int m_iDefaultClip1;                   // 0x001C
	int m_iDefaultClip2;                   // 0x0020
	char pad_0024[8];                    // 0x0024
	char* m_szWorldModel;                  // 0x002C
	char* m_szViewModel;                   // 0x0030
	char* m_szDroppedMode;                 // 0x0034
	char pad_0038[4];                    // 0x0038
	char* m_szShotSound;                   // 0x003C
	char pad_0040[56];                   // 0x0040
	char* m_szEmptySound;                  // 0x0078
	char pad_007C[4];                    // 0x007C
	char* m_szBulletType;                  // 0x0080
	char pad_0084[4];                    // 0x0084
	char* m_szHudName;                     // 0x0088
	char* m_szWeaponName;                  // 0x008C
	char pad_0090[56];                   // 0x0090
	int m_iWeaponType;            // 0x00C8
	char pad_00CC[4];                    // 0x00CC
	int m_iWeaponPrice;                    // 0x00D0
	int m_iKillAward;                      // 0x00D4
	char* m_szAnimationPrefix;             // 0x00D8
	float m_flCycleTime;                   // 0x00DC
	float m_flCycleTimeAlt;                // 0x00E0
	float m_flTimeToIdle;                  // 0x00E4
	float m_flIdleInterval;                // 0x00E8
	bool m_bFullAuto;                      // 0x00EC
	char pad_00ED[3];                    // 0x00ED
	int m_iDamage;                         // 0x00F0
	char valve_are_gays[4];
	float m_flArmorRatio;                  // 0x00F4
	int m_iBullets;                        // 0x00F8
	float m_flPenetration;                 // 0x00FC
	float m_flFlinchVelocityModifierLarge; // 0x0100
	float m_flFlinchVelocityModifierSmall; // 0x0104
	float m_flRange;                       // 0x0108
	float m_flRangeModifier;               // 0x010C
	float m_flThrowVelocity;               // 0x0110
	char pad_0114[12];                   // 0x0114
	bool m_bHasSilencer;                   // 0x0120
	char pad_0121[3];                    // 0x0121
	char* m_pSilencerModel;                // 0x0124
	int m_iCrosshairMinDistance;           // 0x0128
	int m_iCrosshairDeltaDistance;         // 0x012C
	float m_flMaxPlayerSpeed;              // 0x0130
	float m_flMaxPlayerSpeedAlt;           // 0x0134
	float m_flMaxPlayerSpeedMod;           // 0x0138
	float m_flSpread;                      // 0x013C
	float m_flSpreadAlt;                   // 0x0140
	float m_flInaccuracyCrouch;            // 0x0144
	float m_flInaccuracyCrouchAlt;         // 0x0148
	float m_flInaccuracyStand;             // 0x014C
	float m_flInaccuracyStandAlt;          // 0x0150
	float m_flInaccuracyJumpInitial;       // 0x0154
	float m_flInaccuracyJump;              // 0x0158
	float m_flInaccuracyJumpAlt;           // 0x015C
	float m_flInaccuracyLand;              // 0x0160
	float m_flInaccuracyLandAlt;           // 0x0164
	float m_flInaccuracyLadder;            // 0x0168
	float m_flInaccuracyLadderAlt;         // 0x016C
	float m_flInaccuracyFire;              // 0x0170
	float m_flInaccuracyFireAlt;           // 0x0174
	float m_flInaccuracyMove;              // 0x0178
	float m_flInaccuracyMoveAlt;           // 0x017C
	float m_flInaccuracyReload;            // 0x0180
	int m_iRecoilSeed;                     // 0x0184
	float m_flRecoilAngle;                 // 0x0188
	float m_flRecoilAngleAlt;              // 0x018C
	float m_flRecoilAngleVariance;         // 0x0190
	float m_flRecoilAngleVarianceAlt;      // 0x0194
	float m_flRecoilMagnitude;             // 0x0198
	float m_flRecoilMagnitudeAlt;          // 0x019C
	float m_flRecoilMagnitudeVariance;     // 0x01A0
	float m_flRecoilMagnitudeVarianceAlt;  // 0x01A4
	float m_flRecoveryTimeCrouch;          // 0x01A8
	float m_flRecoveryTimeStand;           // 0x01AC
	float m_flRecoveryTimeCrouchFinal;     // 0x01B0
	float m_flRecoveryTimeStandFinal;      // 0x01B4
	char pad_01B8[40];                   // 0x01B8
	char* m_szWeaponClass;                 // 0x01E0
	char pad_01E4[8];                    // 0x01E4
	char* m_szEjectBrassEffect;            // 0x01EC
	char* m_szTracerEffect;                // 0x01F0
	int m_iTracerFrequency;                // 0x01F4
	int m_iTracerFrequencyAlt;             // 0x01F8
	char* m_szMuzzleFlashEffect_1stPerson; // 0x01FC
	char pad_0200[4];                    // 0x0200
	char* m_szMuzzleFlashEffect_3rdPerson; // 0x0204
	char pad_0208[4];                    // 0x0208
	char* m_szMuzzleSmokeEffect;           // 0x020C
	float m_flHeatPerShot;                 // 0x0210
	char* m_szZoomInSound;                 // 0x0214
	char* m_szZoomOutSound;                // 0x0218
	float m_flInaccuracyPitchShift;        // 0x021C
	float m_flInaccuracySoundThreshold;    // 0x0220
	float m_flBotAudibleRange;             // 0x0224
	char pad_0228[12];                   // 0x0228
	bool m_bHasBurstMode;                  // 0x0234
	bool m_bIsRevolver;                    // 0x0235
};