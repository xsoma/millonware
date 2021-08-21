/*
[PREDITLE]

Jumpshot, p100, millionware on top
Awp don't need no scope, hop around don't miss a shot
7 shots in my deagle always got me lookin' evil
p100 like it's cheat-codes just need one shot never reload

I hit the edgebug jumpbug spin around and flickshot (ooh)
Didn't even see you but your skull's eating my AWP shots (ahaheahey)
I hop through vent and spin around you didn't even see me there
It's 'cause I'm rich and flexing jumping around with my millionware

[DNZ]

I'm in the sky going high
Counting seconds in the air
Catch me if you can
bouncing like a frogman
It's 778 hopping 'round with 108
I don't stand around and wait
Jumpbug and accelerate

[SONAR]

Marijuana movement trail
Hip got locked up, county jail
Sold an invite paid for bail
You be moving like a snail
interium n***as bought a rat
paid my way into nohat
you're a nothing copycat
f**king noname acrobat

khmora gave me three day ban
bhopper from pakistan
blow it up, no taliban
You wannabes are hexa stans

UID 165
Drain Gang always sleep-deprived
Autostrafing cat-to-chair
Serversiding, millionware

[STELLAR]

Hotwheels sucks gonna breakaway
Spinning on mirage (yeah)
Hit you with the 1-tap AK
Now you all applause (yuh)

Free Clifton he didn't do sh*t
All the money it's counterfeit
Never missed bench to bricks
Swerving around 64-tick
[CHORUS/PREDITLE]

Jumpshot, p100, millionware on top
Awp don't need no scope, hop around don't miss a shot
7 shots in my deagle always got me lookin' evil
p100 like it's cheat-codes just need one shot never reload

I hit the edgebug jumpbug spin around and flickshot (ooh)
Didn't even see you but your skull's eating my AWP shots (ahaheahey)
I hop through vent and spin around you didn't even see me there
It's 'cause I'm rich and flexing jumping around with my millionware

[STELLAR]

They just added in-game chat
All these n***as got my back
Getting banned like every day
Message aiden, back in black

Hitting edgebugs de_nuke
Leaving discord call me duxe
Your strafes are dog, make me puke
My Fake Backward got you juked

Sold a paste, call me woke
f**ked your momma in the throat
Your movement is a f**king joke
Kill yourself retarded bloke
Daily dose of estrogen
No autostrafe I'm genuine
Jumping shot; adrenaline
OneShot turned me feminine

[AIDEN]

Knife behind; HNS
Tracing you like GPS
I check you like it's chess
I see Brooke, she undress (I see Brooke, she undress)

Like breezetix, don't need to hear
Sound ESP, know when you're near
Bounce off your head, I disappear
I made that one jumpbug tutorial (do you guys remember that?)
*/

#pragma once
#include "collideable.hpp"
#include "../structs/weaponinfo.hpp"

#include "../../engine/utilities/math.hpp"
#include "../../engine/interfaces/engine_trace.hpp"

enum move_type_t
{
	movetype_none = 0,	// never moves
	movetype_isometric,			// For players -- in TF2 commander view, etc.
	movetype_walk,				// Player only - moving on the ground
	movetype_step,				// gravity, special edge handling -- monsters use this
	movetype_fly,				// No gravity, but still collides with stuff
	movetype_flygravity,		// flies through the air + is affected by gravity
	movetype_vphysics,			// uses VPHYSICS for simulation
	movetype_push,				// no clip to world, push and crush
	movetype_noclip,			// No gravity, no collisions, still do velocity/avelocity
	movetype_ladder,			// Used by players only when going onto a ladder
	movetype_observer,			// Observer movement, depends on player's observer mode
	movetype_custom,			// Allows the entity to describe its own physics

	// should always be defined as the last item in the list
	movetype_last = movetype_custom,

	movetype_max_bits = 4
};

enum entity_flags
{
	fl_onground = ( 1 << 0 ),
	fl_ducking = ( 1 << 1 ),
	fl_waterjump = ( 1 << 2 ),
	fl_ontrain = ( 1 << 3 ),
	fl_inrain = ( 1 << 4 ),
	fl_frozen = ( 1 << 5 ),
	fl_atcontrols = ( 1 << 6 ),
	fl_client = ( 1 << 7 ),
	fl_fakeclient = ( 1 << 8 ),
	fl_inwater = ( 1 << 9 ),
	fl_fly = ( 1 << 10 ),
	fl_swim = ( 1 << 11 ),
	fl_conveyor = ( 1 << 12 ),
	fl_npc = ( 1 << 13 ),
	fl_godmode = ( 1 << 14 ),
	fl_notarget = ( 1 << 15 ),
	fl_aimtarget = ( 1 << 16 ),
	fl_partialground = ( 1 << 17 ),
	fl_staticprop = ( 1 << 18 ),
	fl_graphed = ( 1 << 19 ),
	fl_grenade = ( 1 << 20 ),
	fl_stepmovement = ( 1 << 21 ),
	fl_donttouch = ( 1 << 22 ),
	fl_basevelocity = ( 1 << 23 ),
	fl_worldbrush = ( 1 << 24 ),
	fl_object = ( 1 << 25 ),
	fl_killme = ( 1 << 26 ),
	fl_onfire = ( 1 << 27 ),
	fl_dissolving = ( 1 << 28 ),
	fl_transragdoll = ( 1 << 29 ),
	fl_unblockable_by_player = ( 1 << 30 )
};

enum weapon_type
{
	weapontype_knife = 1,
	weapontype_pistol,
	weapontype_submachinegun,
	weapontype_rifle,
	weapontype_shotgun,
	weapontype_sniper_rifle,
	weapontype_machinegun,
	weapontype_c4,
	weapontype_grenade,
	weapontype_unknown
};

enum item_definition_indexes : short
{
	weapon_none = 0,
	weapon_deagle = 1,
	weapon_elite = 2,
	weapon_fiveseven = 3,
	weapon_glock = 4,
	weapon_ak47 = 7,
	weapon_aug = 8,
	weapon_awp = 9,
	weapon_famas = 10,
	weapon_g3sg1 = 11,
	weapon_galilar = 13,
	weapon_m249 = 14,
	weapon_m4a1 = 16,
	weapon_mac10 = 17,
	weapon_p90 = 19,
	weapon_mp5sd = 23,
	weapon_ump45 = 24,
	weapon_xm1014 = 25,
	weapon_bizon = 26,
	weapon_mag7 = 27,
	weapon_negev = 28,
	weapon_sawedoff = 29,
	weapon_tec9 = 30,
	weapon_taser = 31,
	weapon_hkp2000 = 32,
	weapon_mp7 = 33,
	weapon_mp9 = 34,
	weapon_nova = 35,
	weapon_p250 = 36,
	weapon_shield = 37,
	weapon_scar20 = 38,
	weapon_sg556 = 39,
	weapon_scout = 40,
	weapon_knifegg = 41,
	weapon_knife = 42,
	weapon_flashbang = 43,
	weapon_hegrenade = 44,
	weapon_smokegrenade = 45,
	weapon_molotov = 46,
	weapon_decoy = 47,
	weapon_incgrenade = 48,
	weapon_c4 = 49,
	item_kevlar = 50,
	item_assaultsuit = 51,
	item_heavyassaultsuit = 52,
	item_nvg = 54,
	item_defuser = 55,
	item_cutters = 56,
	weapon_healthshot = 57,
	musickit_default = 58,
	weapon_knife_t = 59,
	weapon_m4a1_silencer = 60,
	weapon_usp_silencer = 61,
	recipe_trade_up = 62,
	weapon_cz75a = 63,
	weapon_revolver = 64,
	weapon_tagrenade = 68,
	weapon_fists = 69,
	weapon_breachcharge = 70,
	weapon_tablet = 72,
	weapon_melee = 74,
	weapon_axe = 75,
	weapon_hammer = 76,
	weapon_spanner = 78,
	weapon_knife_ghost = 80,
	weapon_firebomb = 81,
	weapon_diversion = 82,
	weapon_frag_grenade = 83,
	weapon_snowball = 84,
	weapon_bumpmine = 85,
	weapon_bayonet = 500,
	weapon_knife_css = 503,
	weapon_knife_flip = 505,
	weapon_knife_gut = 506,
	weapon_knife_karambit = 507,
	weapon_knife_m9_bayonet = 508,
	weapon_knife_tactical = 509,
	weapon_knife_falchion = 512,
	weapon_knife_survival_bowie = 514,
	weapon_knife_butterfly = 515,
	weapon_knife_push = 516,
	weapon_knife_ursus = 519,
	weapon_knife_gypsy_jackknife = 520,
	weapon_knife_stiletto = 522,
	weapon_knife_widowmaker = 523,
};

#include "../structs/models.hpp"
#include "../../engine/netvars/netvars.hpp"
#include "../../engine/interfaces/interfaces.hpp"
#include "../../engine/utilities/memory.hpp"
#include "anim_layers.hpp"

class entity_t
{
public:
	void* animating( )
	{
		return reinterpret_cast< void* >( uintptr_t( this ) + 0x4 );
	}

	i_client_networkable* networkable( )
	{
		return reinterpret_cast< i_client_networkable* >( uintptr_t( this ) + 0x8 );
	}

	collideable_t* collideable( )
	{
		using original_fn = collideable_t * ( __thiscall* )( void* );
		return ( *( original_fn** )this )[ 3 ]( this );
	}

	client_class* clientclass( )
	{
		using original_fn = client_class * ( __thiscall* )( void* );
		return ( *( original_fn** )networkable( ) )[ 2 ]( networkable( ) );
	}

	bool is_player( )
	{
		using original_fn = bool( __thiscall* )( entity_t* );
		return ( *( original_fn** )this )[ 157 ]( this );
	}

	bool is_weapon( )
	{
		using original_fn = bool( __thiscall* )( entity_t* );
		return ( *( original_fn** )this )[ 165 ]( this );
	}

	bool setup_bones( matrix_t* out, int max_bones, int mask, float time )
	{
		using original_fn = bool( __thiscall* )( void*, matrix_t*, int, int, float );
		return ( *( original_fn** )animating( ) )[ 13 ]( animating( ), out, max_bones, mask, time );
	}

	vec3 bone_pos( int bone )
	{ // god please help
		uint32_t matrix = *( uint32_t* )( this + 0x26A8 );
		uint8_t bones[ 64 ];
		memcpy( ( void* )bones, ( void* )( matrix + 0x30 * bone ), 64 );

		return vec3{ *( float* )( bones + 0x0c ), *( float* )( bones + 0x1c ), *( float* )( bones + 0x2c ) };
	}

	model_t* model( )
	{
		using original_fn = model_t * ( __thiscall* )( void* );
		return ( *( original_fn** )animating( ) )[ 8 ]( animating( ) );
	}

	void update( )
	{
		using original_fn = void( __thiscall* )( entity_t* );
		( *( original_fn** )this )[ 218 ]( this );
	}

	int draw_model( int flags, uint8_t alpha )
	{
		using original_fn = int( __thiscall* )( void*, int, uint8_t );
		return ( *( original_fn** )animating( ) )[ 9 ]( animating( ), flags, alpha );
	}

	void set_angles( vec3_t angles )
	{
		using original_fn = void( __thiscall* )( void*, const vec3_t& );
		static original_fn set_angles_fn = ( original_fn )( utils::memory::pattern_scan( "client.dll", "55 8B EC 83 E4 F8 83 EC 64 53 56 57 8B F1" ) );
		set_angles_fn( this, angles );
	}

	void set_position( vec3_t position )
	{
		using original_fn = void( __thiscall* )( void*, const vec3_t& );
		static original_fn set_abs_origin_fn = ( original_fn )( utils::memory::pattern_scan( "client.dll", "55 8B EC 83 E4 F8 51 53 56 57 8B F1" ) );
		set_abs_origin_fn( this, position );
	}

	vec3_t abs_origin( )
	{
		using original_fn = const vec3_t & ( __thiscall* )( entity_t* );
		return ( *( original_fn** )this )[ 10 ]( this );
	}

	netvar_fn( int, flags, "DT_BasePlayer->m_fFlags" );
	netvar_fn( unsigned long, owner_handle, "DT_BaseEntity->m_hOwnerEntity" );
	offset_fn( bool, dormant, 0xED );
	netvar_fn( float, simulation_time, "DT_BaseEntity->m_flSimulationTime" );
	offset_fn( vec3_t, origin, 0x134 );
	offset_fn( vec3_t, view_offset, 0x108 );
	netvar_fn( int, team, "DT_BaseEntity->m_iTeamNum" );
	netvar_fn( bool, spotted, "DT_BaseEntity->m_bSpotted" );
};

class viewmodel_t : public entity_t
{
public:
	offset_fn( int, model_index, 0x258 );
	//netvar_ptr_fn( int, model_index, "DT_BaseViewModel->m_nModelIndex" );
	netvar_fn( int, viewmodel_index, "DT_BaseViewModel->m_nViewModelIndex" );
};

class econ_view_item_t
{
public:
	netvar_offset_fn( bool, is_initialized, "DT_ScriptCreatedItem->m_bInitialized", g_netvar_mgr.get_offset( fnv_hash( "DT_AttributeContainer->m_Item" ) ) + g_netvar_mgr.get_offset( fnv_hash( "DT_BaseAttributableItem->m_AttributeManager" ) ) );
	netvar_offset_fn( short, item_definition_index, "DT_ScriptCreatedItem->m_iItemDefinitionIndex", g_netvar_mgr.get_offset( fnv_hash( "DT_AttributeContainer->m_Item" ) ) + g_netvar_mgr.get_offset( fnv_hash( "DT_BaseAttributableItem->m_AttributeManager" ) ) );
	netvar_offset_fn( int, entity_level, "DT_ScriptCreatedItem->m_iEntityLevel", g_netvar_mgr.get_offset( fnv_hash( "DT_AttributeContainer->m_Item" ) ) + g_netvar_mgr.get_offset( fnv_hash( "DT_BaseAttributableItem->m_AttributeManager" ) ) );
	netvar_offset_fn( int, account_id, "DT_ScriptCreatedItem->m_iAccountID", g_netvar_mgr.get_offset( fnv_hash( "DT_AttributeContainer->m_Item" ) ) + g_netvar_mgr.get_offset( fnv_hash( "DT_BaseAttributableItem->m_AttributeManager" ) ) );
	netvar_offset_fn( int, item_id_low, "DT_ScriptCreatedItem->m_iItemIDLow", g_netvar_mgr.get_offset( fnv_hash( "DT_AttributeContainer->m_Item" ) ) + g_netvar_mgr.get_offset( fnv_hash( "DT_BaseAttributableItem->m_AttributeManager" ) ) );
	netvar_offset_fn( int, item_id_high, "DT_ScriptCreatedItem->m_iItemIDHigh", g_netvar_mgr.get_offset( fnv_hash( "DT_AttributeContainer->m_Item" ) ) + g_netvar_mgr.get_offset( fnv_hash( "DT_BaseAttributableItem->m_AttributeManager" ) ) );
	netvar_offset_fn( int, entity_quality, "DT_ScriptCreatedItem->m_iEntityQuality", g_netvar_mgr.get_offset( fnv_hash( "DT_AttributeContainer->m_Item" ) ) + g_netvar_mgr.get_offset( fnv_hash( "DT_BaseAttributableItem->m_AttributeManager" ) ) );
};

class weapon_t : public entity_t
{
public:
	offset_fn( bool, reloading, 0x3285 );
	netvar_fn( float, next_primary_attack, "DT_BaseCombatWeapon->m_flNextPrimaryAttack" );
	netvar_fn( float, next_secondary_attack, "DT_BaseCombatWeapon->m_flNextSecondaryAttack" );
	netvar_fn( int, clip1_count, "DT_BaseCombatWeapon->m_iClip1" );
	netvar_fn( int, reserve_ammo, "DT_BaseCombatWeapon->m_iPrimaryReserveAmmoCount" );
	netvar_fn( int, clip2_count, "DT_BaseCombatWeapon->m_iClip2" );
	netvar_fn( float, recoil_index, "DT_WeaponCSBase->m_flRecoilIndex" );

	econ_view_item_t& item( )
	{
		return *( econ_view_item_t* )this;
	}

	short* item_definition_index( )
	{
		return ( short* )( uintptr_t( this ) + 0x2FAA );
	}

	float get_innacuracy( )
	{
		using original_fn = float( __thiscall* )( void* );
		return ( *( original_fn** )this )[481]( this );
	}

	float get_spread( )
	{
		using original_fn = float( __thiscall* )( void* );
		return ( *( original_fn** )this )[ 449 ]( this );
	}

	void update_accuracy_penalty( )
	{
		using original_fn = void( __thiscall* )( void* );
		( *( original_fn** )this )[ 480 ]( this );
	}

	bool is_knife( )
	{
		return clientclass( )->class_id == cknife || clientclass( )->class_id == cknifegg;
	}

	weapon_info_t* weapon_data( )
	{
		if ( !this )
		{
			return nullptr;
		}

		return interfaces::weapon_system->get_weapon_data( reinterpret_cast< econ_view_item_t* >( this )->item_definition_index( ) );
	}
};

class attributable_item_t : public entity_t
{
public:
	netvar_fn( unsigned long, original_owner_xuid, "DT_BaseAttributableItem->m_OriginalOwnerXuidLow" );
	netvar_fn( int, original_owner_xuid_low, "DT_BaseAttributableItem->m_OriginalOwnerXuidLow" );
	netvar_fn( int, original_owner_xuid_high, "DT_BaseAttributableItem->m_OriginalOwnerXuidHigh" );
	netvar_fn( int, fallback_stattrak, "DT_BaseAttributableItem->m_nFallbackStatTrak" );
	netvar_fn( int, fallback_paint_kit, "DT_BaseAttributableItem->m_nFallbackPaintKit" );
	netvar_fn( int, fallback_seed, "DT_BaseAttributableItem->m_nFallbackSeed" );
	netvar_fn( float, fallback_wear, "DT_BaseAttributableItem->m_flFallbackWear" );
	netvar_fn( unsigned long, world_model_handle, "DT_BaseCombatWeapon->m_hWeaponWorldModel" );

	econ_view_item_t& item( )
	{
		return *( econ_view_item_t* )this;
	}
};

class player_t : public entity_t
{
public:
	netvar_fn( bool, has_defuser, "DT_CSPlayer->m_bHasDefuser" );
	netvar_fn( bool, has_gun_game_immunity, "DT_CSPlayer->m_bGunGameImmunity" );
	netvar_fn( int, shots_fired, "DT_CSPlayer->m_iShotsFired" );
	netvar_fn( vec3_t, eye_angles, "DT_CSPlayer->m_angEyeAngles[0]" );
	netvar_fn( int, armor, "DT_CSPlayer->m_ArmorValue" );
	netvar_fn( bool, has_helmet, "DT_CSPlayer->m_bHasHelmet" );
	netvar_fn( bool, is_scoped, "DT_CSPlayer->m_bIsScoped" );
	netvar_fn( float, lower_body_yaw, "DT_CSPlayer->m_flLowerBodyYawTarget" );
	netvar_fn( float, flash_duration, "DT_CSPlayer->m_flFlashDuration" );
	netvar_fn( int, health, "DT_BasePlayer->m_iHealth" );
	netvar_fn( int, life_state, "DT_BasePlayer->m_lifeState" );
	//netvar_fn(int, move_type, "DT_CSPlayer->m_nRenderMode");
	netvar_fn( int, flags, "DT_BasePlayer->m_fFlags" );
	netvar_fn( int, tick_base, "DT_BasePlayer->m_nTickBase" );
	netvar_fn( vec3_t, punch_angle, "DT_BasePlayer->m_viewPunchAngle" );
	//netvar_fn( vec3_t, velocity, "DT_CSPlayer->m_vecVelocity[0]" );
	netvar_fn( float, max_speed, "DT_BasePlayer->m_flMaxspeed" );
	netvar_fn( unsigned long, observer_target, "DT_BasePlayer->m_hObserverTarget" );
	netvar_fn( unsigned long, active_weapon_handle, "DT_BaseCombatCharacter->m_hActiveWeapon" );
	netvar_fn( float, next_attack, "DT_BaseCombatCharacter->m_flNextAttack" );
	netvar_fn( unsigned long, view_model_handle, "DT_BasePlayer->m_hViewModel[0]" );
	netvar_fn( bool, is_defusing, "DT_CSPlayer", "m_bIsDefusing" );
	netvar_fn( int, account, "DT_CSPlayer", "m_iAccount" )

	netvar_fn( float, bomb_timer_length, "DT_PlantedC4->m_flTimerLength" );
	netvar_fn( float, bomb_blow_time, "DT_PlantedC4->m_flC4Blow" );
	netvar_fn( bool, bomb_defused, "DT_PlantedC4->m_bBombDefused" );

	int* wearables( )
	{
		//static auto _offset = g_netvar_mgr.get_offset( fnv_hash( "DT_BaseCombatCharacter->m_hMyWearables" ) );
		return ( int* )( ( std::uint32_t )this + 0x2f04 );
	}

	vec3_t velocity( )
	{ // fucking netvar broken someone help i hardcoded it for now
		return *( vec3* )( uintptr_t( this ) + 0x114 );
	}

	vec3_t aim_punch_angle( )
	{ // fucking netvar broken someone help i hardcoded it for now
		return *( vec3* )( uintptr_t( this ) + 0x302C );
	}

	float spawn_time( )
	{
		return *( float* )( ( uintptr_t )this + 0xA350 );
	}

	weapon_t* active_weapon( void )
	{
		uintptr_t handle = active_weapon_handle( );
		return ( weapon_t* )interfaces::entity_list->get_client_entity( handle );
	}

	viewmodel_t* view_model( )
	{
		uintptr_t handle = view_model_handle( );
		return ( viewmodel_t* )interfaces::entity_list->get_client_entity( handle );
	}

	vec3 eye_pos( )
	{
		return this->abs_origin( ) + this->view_offset( );
	}

	bool has_c4( )
	{
		static auto fn = reinterpret_cast< bool( __thiscall* )( void* ) >( utils::memory::pattern_scan( "client.dll", "56 8B F1 85 F6 74 31" ) );
		return fn( this );
	}

	bool is_flashed( )
	{
		if ( this->flash_duration( ) > 0.0f )
			return true;

		return false;
	}

	int* weapons( )
	{
		return ( int* )( uintptr_t( this ) + 0x2DF8 );
	}

	int move_type( )
	{
		return *( int* )( uintptr_t( this ) + 0x25C );
	}

	c_animation_layer& anim_overlays( int idx )
	{
		return ( *( c_animation_layer** )( ( uintptr_t )this + 0x2990 ) )[ idx ];
	}

	int activity( int sequence )
	{
		const auto studio = interfaces::model_info->get_studio_model( model( ) );

		if ( !studio )
			return -1;

		static auto ret = reinterpret_cast< int( __fastcall* )( player_t*, studio_hdr_t*, int ) >( utils::memory::pattern_scan( xor ( "client.dll" ), xor ( "55 8B EC 53 8B 5D 08 56 8B F1 83" ) ) );
		return ret( this, studio, sequence );
	}

	bool alive( )
	{
		return health( ) > 0;
	}

	int index( )
	{
		return *reinterpret_cast< int* >( uintptr_t( this ) + 0x64 );
	}

	bool sane( bool _dormant, bool _local = true, bool immunity = true )
	{
		if ( !this )
			return false;

		if(immunity)
		if ( this->has_gun_game_immunity( ) )
			return false;

		if ( this->index( ) == interfaces::engine->get_local_player( ) && _local )
			return false;

		if ( this->clientclass( )->class_id != 40 )
			return false;

		if ( this->dormant( ) && _dormant )
			return false;

		if ( !this->alive( ) )
			return false;

		return true;
	}

	player_info_t info( )
	{
		player_info_t i;
		interfaces::engine->get_player_info( this->index( ), &i );

		return i;
	}

	int glow_index( )
	{
		static auto _offset = g_netvar_mgr.get_offset( fnv_hash( "DT_CSPlayer->m_flFlashDuration" ) ) + 24;
		return *( int* )( ( uintptr_t )this + 0xA428 );
	}

	vec3_t hitbox_pos( int id, matrix_t* matrix )
	{
		auto studio_model = interfaces::model_info->get_studio_model( this->model( ) );

		if ( studio_model )
		{
			auto hitbox = studio_model->hitbox_set( 0 )->hitbox( id );

			if ( hitbox )
			{
				auto
					min = vec3_t{ },
					max = vec3_t{ };

				utils::math::vector_transform( hitbox->mins, matrix[ hitbox->bone ], min );
				utils::math::vector_transform( hitbox->maxs, matrix[ hitbox->bone ], max );

				return ( min + max ) * 0.5f;
			}
		}

		return vec3_t{ };
	}

	bool can_shoot( )
	{
		if ( !this )
			return false;

		if ( !this->active_weapon( ) )
			return false;

		if ( this->active_weapon( )->clip1_count( ) <= 0 )
			return false;

		if ( this->active_weapon( )->reloading( ) )
			return false;

		if ( this->next_attack( ) > interfaces::globals->cur_time )
			return false;

		if ( this->active_weapon( )->next_primary_attack( ) > interfaces::globals->cur_time )
			return false;

		return true;
	}

	bool can_see( player_t* player, vec3_t pos )
	{
		trace_t tr{};
		ray_t ray{};
		trace_filter filter;
		filter.skip = this;

		auto start = this->eye_pos( );
		auto dir = ( pos - start ).normalized( );

		ray.initialize( start, pos );
		interfaces::trace->trace_ray( ray, MASK_SHOT | CONTENTS_GRATE, &filter, &tr );

		return tr.entity == player || tr.flFraction > 0.97f;
	}
};