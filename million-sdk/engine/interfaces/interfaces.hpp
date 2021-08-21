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
#include "../utilities/engine.hpp"
#include "client.hpp"
#include "panel.hpp"
#include "surface.hpp"
#include "entity_list.hpp"
#include "../../source engine/classes/prediction.hpp"
#include "globals.hpp"
#include "../utilities/memory.hpp"
#include "../utilities/xorstring.hpp"
#include "engine.hpp"
#include "debug_overlay.hpp"
#include "weapon_system.hpp"
#include "i_localize.hpp"
#include "model_info_client.hpp"
#include "client_state.hpp"
#include "model_render.hpp"
#include "material_system.hpp"
#include "hud_chat.hpp"
#include "../../source engine/classes/gameevent.hpp"
#include "glow_object_manager.hpp"
#include "i_console.hpp"
#include "engine_trace.hpp"

namespace interfaces
{
	inline i_base_client_dll* client;
	inline i_panel* panel;
	inline i_surface* surface;
	inline i_client_entity_list* entity_list;
	inline void* client_mode;
	inline CPrediction* prediction;
	inline CGameMovement* movement;
	inline CMoveHelper* move_helper;
	inline c_global_vars_base* globals;
	inline iv_engine_client* engine;
	inline iv_debug_overlay* debug_overlay;
	inline i_weapon_system* weapon_system;
	inline i_localize* localize;
	inline iv_model_info_client* model_info;
	inline iv_model_render* model_render;
	inline void* engine_sound;
	inline i_client_state* client_state;
	inline i_material_system* material_system;
	inline c_hud_chat* hud_chat;
	inline i_game_event_manager* game_event_manager;
	inline c_glow_manager* glow_object;
	inline i_console* console;
	inline i_trace* trace;

	__forceinline void init( )
	{
		client = utils::engine::create_interface<i_base_client_dll>( xor ( "client.dll" ), xor ( "VClient018" ) );
		panel = utils::engine::create_interface<i_panel>( xor ( "vgui2.dll" ), xor ( "VGUI_Panel009" ) );
		surface = utils::engine::create_interface<i_surface>( xor ( "vguimatsurface.dll" ), xor ( "VGUI_Surface031" ) );
		entity_list = utils::engine::create_interface<i_client_entity_list>( xor ( "client.dll" ), xor ( "VClientEntityList003" ) );
		engine = utils::engine::create_interface<iv_engine_client>( xor ( "engine.dll" ), xor ( "VEngineClient014" ) );
		prediction = utils::engine::create_interface<CPrediction>( xor ( "client.dll" ), xor ( "VClientPrediction001" ) );
		movement = utils::engine::create_interface<CGameMovement>( xor ( "client.dll" ), xor ( "GameMovement001" ) );
		engine_sound = utils::engine::create_interface<void>( xor ( "engine.dll" ), xor ( "IEngineSoundClient003" ) );
		debug_overlay = utils::engine::create_interface<iv_debug_overlay>( xor ( "engine.dll" ), xor ( "VDebugOverlay004" ) );
		localize = utils::engine::create_interface<i_localize>( xor ( "localize.dll" ), xor ( "Localize_001" ) );
		model_info = utils::engine::create_interface<iv_model_info_client>( xor ( "engine.dll" ), xor ( "VModelInfoClient004" ) );
		model_render = utils::engine::create_interface<iv_model_render>( xor ( "engine.dll" ), xor ( "VEngineModel016" ) );
		material_system = utils::engine::create_interface<i_material_system>( xor ( "materialsystem.dll" ), xor ( "VMaterialSystem080" ) );
		game_event_manager = utils::engine::create_interface<i_game_event_manager>( xor ( "engine.dll" ), xor ( "GAMEEVENTSMANAGER002" ) );
		console = utils::engine::create_interface<i_console>( xor ( "vstdlib.dll" ), xor ( "VEngineCvar007" ) );
		trace = utils::engine::create_interface<i_trace>( xor ( "engine.dll" ), xor ( "EngineTraceClient004" ) );

		client_state = **( i_client_state*** )( utils::memory::pattern_scan( xor ( "engine.dll" ), xor ( "A1 ? ? ? ? 8B 80 ? ? ? ? C3" ) ) + 1 );
		move_helper = **reinterpret_cast< CMoveHelper*** >( ( utils::memory::pattern_scan( xor ( "client.dll" ), xor ( "8B 0D ? ? ? ? 8B 46 08 68" ) ) + 2 ) );
		weapon_system = *reinterpret_cast< i_weapon_system** >( ( utils::memory::pattern_scan( xor ( "client.dll" ), xor ( "8B 35 ? ? ? ? FF 10 0F B7 C0" ) ) + ( 69 - 67 ) ) );
		glow_object = *reinterpret_cast< c_glow_manager** >( ( utils::memory::pattern_scan( xor ( "client.dll" ), xor ( "0F 11 05 ? ? ? ? 83 C8 01" ) ) + 3 ) );

		client_mode = **reinterpret_cast< uintptr_t*** >( ( *reinterpret_cast< uintptr_t** >( client ) )[ 10 ] + 5 );
		globals = **reinterpret_cast<c_global_vars_base***>((utils::memory::pattern_scan(xor ("client.dll"), xor ("A1 ? ? ? ? 5E 8B 40 10")) + 1)); //A1 ? ? ? ? 5E 8B 40 10

		hud_chat = utils::engine::find_hud_element<c_hud_chat>( xor ( "CHudChat" ) );
	}
}