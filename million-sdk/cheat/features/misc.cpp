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

#include "misc.hpp"

#include "../renderer/renderer.hpp"
#include <algorithm>

#include "../../engine/utilities/config.hpp"
#include "../../engine/utilities/xorstring.hpp"
#include "../../engine/utilities/math.hpp"
#include "../input/input.hpp"

void misc::spectators( color_t clr ) {
	if ( !*config::get<bool>( crc( "esp:spectators" ) ) ) {
		return;
	}

	if ( !interfaces::engine->is_in_game( ) || !interfaces::engine->is_connected( ) ) {
		return;
	}

	std::wstring spectators;
	int index = 0;

	auto local = interfaces::entity_list->get<player_t>( interfaces::engine->get_local_player( ) );
	if ( !local ) {
		return;
	}

	for ( int i = 1; i <= interfaces::globals->max_clients; i++ ) {
		auto ent = interfaces::entity_list->get<player_t>( i );

		if ( ent && ent != local ) {
			if ( !ent->alive( ) && !ent->dormant( ) ) {
				auto observer = ent->observer_target( );
				if ( observer ) {
					auto target = reinterpret_cast< player_t * >( interfaces::entity_list->get_client_entity( ( uintptr_t )observer ) );
					if ( target ) {
						std::string name( ent->info( ).name );
						if ( name.length( ) > 15 ) {
							name.resize( 15 );
							name.append( "..." );
						}

						std::wstring wname( name.begin( ), name.end( ) );
						point_t size = render::text_size( wname.data( ), tahoma11 );

						if ( local->alive( ) ) {
							if ( target == local ) {
								// calling config::get ~64 times to enhance fps
								render::text( point_t( 5, ( *config::get<bool>( crc( "esp:misc:watermark" ) ) ? 18 : 5 ) + ( 13 * index++ ) ), tahoma11, font_dropshadow, clr, wname );
							}
						}
						else {
							//	get the player that we're spectating
							const auto spec_handle = local->observer_target( );
							if ( spec_handle ) {
								const auto spec = interfaces::entity_list->get_client_entity( ( uintptr_t )spec_handle );
								if ( target == spec && spec ) {
									// calling config::get ~64 times to enhance fps
									render::text( point_t( 5, ( *config::get<bool>( crc( "esp:misc:watermark" ) ) ? 18 : 5 ) + ( 13 * index++ ) ), tahoma11, font_dropshadow, clr, wname );
								}
							}
						}
					}
				}
			}
		}
	}
}

void misc::auto_accept( ) {

	if ( !*config::get<bool>( crc( "misc:autoaccept" ) ) ) {
		return;
	}

	static auto set_local_player_ready_fn = reinterpret_cast< bool( __stdcall * )( const char * ) >
		( utils::memory::pattern_scan( xor ( "client.dll" ), xor( "55 8B EC 83 E4 F8 8B 4D 08 BA ? ? ? ? E8 ? ? ? ? 85 C0 75 12" ) ) );

	// kurwa nie wiem ktory dziala mam wyjebane lolo
	set_local_player_ready_fn( "" );
	set_local_player_ready_fn( "duxe" );
	set_local_player_ready_fn( "is" );
	set_local_player_ready_fn( "a" );
	set_local_player_ready_fn( "paster" );
}

void misc::disable_post_process( ) {
	if ( !interfaces::engine->is_in_game( ) || !interfaces::engine->is_connected( ) ) {
		return;
	}

	static auto postprocess = interfaces::console->get_convar( "mat_postprocess_enable" );
	postprocess->set_value( !*config::get<bool>( crc( "esp:disable_post_processing" ) ) ? 1 : 0 );

	static auto blur_overlay = interfaces::material_system->find_material( "dev/scope_bluroverlay", nullptr );
	static auto lens_dirt = interfaces::material_system->find_material( "models/weapons/shared/scope/scope_lens_dirt", nullptr );

	blur_overlay->set_flag( /*MATERIAL_VAR_NO_DRAW*/4, true );
	lens_dirt->set_flag( /*MATERIAL_VAR_NO_DRAW*/4, true );
}

void misc::crosshair( )
{
	static const auto weapon_debug_spread_show = interfaces::console->get_convar( "weapon_debug_spread_show" );
	if ( !weapon_debug_spread_show )
	{
		return;
	}

	if ( !*config::get<bool>( crc( "esp:crosshair" ) ) )
	{
		return;
	}

	const auto local = interfaces::entity_list->get<player_t>( interfaces::engine->get_local_player( ) );
	if ( !local || !local->alive( ) )
	{
		return;
	}

	// TODO: check if player has a SCOPED weapon
	weapon_debug_spread_show->set_value( local->is_scoped( ) ? 0 : 3 );
}

void misc::clantag( ) {

	//sig
	static auto clan_tag = reinterpret_cast< int( __fastcall * )( const char *, const char * ) >
		( utils::memory::pattern_scan( xor ( "engine.dll" ), xor( "53 56 57 8B DA 8B F9 FF 15" ) ) );

	//clantag text
	static std::string tag = xor ( " millionware " );
	static float next_time = -1.f;

	//prefix
	std::string dollar = "$ ";
	dollar += tag;

	//reset shit
	static bool is_disabled = false;

	if ( *config::get<bool>( crc( "misc:clantag" ) ) )
	{
		auto local = interfaces::entity_list->get<player_t>( interfaces::engine->get_local_player( ) );

		if ( !local )
		{
			return;
		}

		if ( interfaces::globals->cur_time >= next_time )
		{
			if ( next_time != -1.f )
			{
				std::rotate( std::begin( tag ), std::next( std::begin( tag ) ), std::end( tag ) );
			}

			clan_tag( dollar.data( ), tag.data( ) );

			next_time = interfaces::globals->cur_time + 1.f;
		}
		is_disabled = false;
	}
	else
	{
		if ( !is_disabled )
		{
			clan_tag( "", "" );
			is_disabled = true;
		}
	}
}

void misc::disable_panorama_blur( ) {

	static auto blur = interfaces::console->get_convar( "@panorama_disable_blur" );
	blur->set_value( !*config::get<bool>( crc( "esp:misc:panoramablur" ) ) ? 0 : 1 );
}

void misc::viewmodel_offset( ) {

	if ( !*config::get<bool>( crc( "misc:viewmodel_offset" ) ) ) {
		return;
	}

	//making the callbacks null
	interfaces::console->get_convar( "viewmodel_offset_x" )->callbacks.SetSize( false );
	interfaces::console->get_convar( "viewmodel_offset_y" )->callbacks.SetSize( false );
	interfaces::console->get_convar( "viewmodel_offset_z" )->callbacks.SetSize( false );

	//self explanatory
	interfaces::console->get_convar( "viewmodel_offset_x" )->set_value( *config::get<float>( crc( "misc:viewmodel_offset_x" ) ) );
	interfaces::console->get_convar( "viewmodel_offset_y" )->set_value( *config::get<float>( crc( "misc:viewmodel_offset_y" ) ) );
	interfaces::console->get_convar( "viewmodel_offset_z" )->set_value( *config::get<float>( crc( "misc:viewmodel_offset_z" ) ) );
}

void misc::remove_smoke( )
{
	static constexpr const char *smokeMaterials[ ]{
		"particle/vistasmokev1/vistasmokev1_emods",
		"particle/vistasmokev1/vistasmokev1_emods_impactdust",
		"particle/vistasmokev1/vistasmokev1_fire",
		"particle/vistasmokev1/vistasmokev1_smokegrenade"
	};

	static auto smoke_count = *reinterpret_cast< uint32_t ** >
		( utils::memory::pattern_scan( xor ( "client.dll" ), xor( "A3 ? ? ? ? 57 8B CB" ) ) + 0x1 );

	static bool is_disabled = false;
	if ( *config::get<bool>( crc( "misc:remove_smoke" ) ) )
	{
		auto local = interfaces::entity_list->get<player_t>( interfaces::engine->get_local_player( ) );

		if ( !smoke_count || !interfaces::engine->is_connected( ) || !interfaces::engine->is_in_game( ) )
			return;

		for ( const auto mat : smokeMaterials )
		{
			auto material = interfaces::material_system->find_material( mat );

			if ( material )
				material->set_flag( 268435456, true );
		}

		*( int * )smoke_count = 0;
		is_disabled = false;
	}
	else
	{
		if ( !is_disabled )
		{
			auto local = interfaces::entity_list->get<player_t>( interfaces::engine->get_local_player( ) );

			if ( !smoke_count || !interfaces::engine->is_connected( ) || !interfaces::engine->is_in_game( ) )
				return;

			for ( const auto mat : smokeMaterials )
			{
				auto material = interfaces::material_system->find_material( mat );

				if ( material )
					material->set_flag( 268435456, false );
			}

			*( int * )smoke_count = 0;
			is_disabled = true;
		}
	}
}

void misc::name_spam( )
{
	if ( !*config::get<bool>( crc( "misc:name_spam" ) ) )
	{
		return;
	}

	auto name = interfaces::console->get_convar( "name" );
	name->callbacks.SetSize( 0 );
	name->set_value( "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" );
}

void misc::preserve_killfeed( )
{
	if ( !*config::get<bool>( crc( "misc:preserve_killfeed" ) ) )
	{
		return;
	}

	static void( __thiscall * clear_death_notice )( uintptr_t );
	static uintptr_t *death_notice;

	auto local = interfaces::entity_list->get<player_t>( interfaces::engine->get_local_player( ) );

	if ( !local ) {
		if ( clear_death_notice ) {
			clear_death_notice = nullptr;
		}

		if ( death_notice ) {
			death_notice = nullptr;
		}

		return;
	}

	if ( local->alive( ) ) {
		if ( !death_notice ) {
			death_notice = utils::engine::find_hud_element<uintptr_t>( xor ( "CCSGO_HudDeathNotice" ) );
		}

		if ( !clear_death_notice ) {
			clear_death_notice = reinterpret_cast< void( __thiscall * )( uintptr_t ) >( utils::memory::pattern_scan( xor ( "client.dll" ), xor( "55 8B EC 83 EC 0C 53 56 8B 71 58" ) ) );
		}

		static bool should_clear = false;
		if ( clear_death_notice && death_notice ) {
			if ( utils::engine::round_flags == 0 ) {
				float *local_death_notice = ( float * )( ( uintptr_t )death_notice + 0x50 );

				if ( local_death_notice && !*config::get<bool>( crc( "esp:preserve_killfeed" ) ) ) {
					*local_death_notice = FLT_MAX;
				}
			}

			if ( ( !*config::get<bool>( crc( "misc:preserve_killfeed" ) ) ) ) {
				should_clear = true;
			}

			if ( ( *config::get<bool>( crc( "misc:preserve_killfeed" ) ) ) ) {
				if ( utils::engine::round_flags == 1 && death_notice - 0x14 ) {
					should_clear = true;
				}
			}

			if ( should_clear ) {
				clear_death_notice( ( ( uintptr_t )death_notice - 0x14 ) );
				should_clear = false;
			}
		}
	}
	else {
		if ( clear_death_notice ) {
			clear_death_notice = nullptr;
		}

		if ( death_notice ) {
			death_notice = nullptr;
		}
	}
}

/*
void misc::change_server( )
{
	static std::string data_centers[ ]
	{
		"", "syd", "vie", "gru", "scl", "dxb", "par", "fra", "hkg",
		"maa", "bom", "tyo", "lux", "ams", "limc", "man", "waw", "sgp",
		"jnb", "mad", "sto", "lhr", "atl", "eat", "ord", "lax", "mwh",
		"okc", "sea", "iad"
	};

	static auto relay_cluster = *reinterpret_cast< std::string** >( utils::memory::pattern_scan( xor ( "steamnetworkingsockets.dll" ), "b8 ? ? ? ? b9 ? ? ? ? 0f 43" ) + 1 );

	const auto config_value = *config::get<int>( crc( "misc:data_center" ) );

	if ( config_value != 0 && config_value < 30 )
		*relay_cluster = data_centers[ config_value ];
}
*/