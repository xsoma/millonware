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

#include "visuals.hpp"

#include "../renderer/renderer.hpp"

#include <windows.h>
#include <algorithm>

#include "../../engine/utilities/config.hpp"
#include "../../engine/utilities/xorstring.hpp"
#include "../../cheat/features/bt.hpp"

#include "pred.hpp"

#include <iomanip>
#include <sstream>

void visuals::box( )
{
	if ( !*config::get<bool>( crc( "esp:box" ) ) )
	{
		return;
	}

	auto c = config::get<color>( crc( "esp:box:color" ) )->alpha( 255.f * ctx.alpha[ ctx.player->index( ) ], true );
	auto black = color( 0, 0, 0, c.a ).alpha( 255.f * ctx.alpha[ ctx.player->index( ) ] );

	if ( *config::get<bool>( crc( "esp:glow:alpha_override" ) ) )
	{
		c = c.alpha( *config::get<float>( crc( "esp:glow:alpha_override:value" ) ) * ctx.alpha[ ctx.player->index( ) ] );
		black = black.alpha( *config::get<float>( crc( "esp:glow:alpha_override:value" ) ) * ctx.alpha[ ctx.player->index( ) ] );
	}

	render::rect( ctx.bbox.pos - 1, ctx.bbox.size + 2, black );
	render::rect( ctx.bbox.pos + 1, ctx.bbox.size - 2, black );
	render::rect( ctx.bbox.pos, ctx.bbox.size, c );

	// 1px box, 1px space
	ctx.offset += 2;
}

void visuals::name( )
{
	if ( !*config::get<bool>( crc( "esp:name" ) ) )
	{
		return;
	}

	// are u fkn kidding me why are we doing
	// wchar's for text.........................
	// because unicode superior
	char player_name[ 256 ];
	strcpy( player_name, ctx.player->info( ).name );

	if ( strlen( player_name ) > 15 )
	{
		memcpy( player_name + 15, "...\0", 4 );
	}

	wchar_t player_wide[ 256 ];
	if ( !SUCCEEDED( MultiByteToWideChar( CP_UTF8, 0, player_name, -1, player_wide, 256 ) ) )
		return;

	auto c = color( 255, 255, 255 );
	c = c.alpha( 220.f * ctx.alpha[ ctx.player->index( ) ] );

	if ( *config::get<bool>( crc( "esp:glow:alpha_override" ) ) )
	{
		c = c.alpha( *config::get<float>( crc( "esp:glow:alpha_override:value" ) ) * ctx.alpha[ ctx.player->index( ) ] );
	}

	render::text( ctx.bbox.pos + point_t( ctx.bbox.size.x / 2, -12 ),
				  tahoma11, font_centered_x, c, player_wide );
}

void visuals::flashkill( )
{

	if ( !*config::get<bool>( crc( "esp:flashkill" ) ) || ctx.player->health( ) > 4 )
	{
		return;
	}

	wchar_t* name = xor ( L"flash kill" );

	auto c = color( 0, 150, 255 );
	c = c.alpha( 220.f * ctx.alpha[ ctx.player->index( ) ] );

	if ( *config::get<bool>( crc( "esp:glow:alpha_override" ) ) )
	{
		c = c.alpha( *config::get<float>( crc( "esp:glow:alpha_override:value" ) ) * ctx.alpha[ ctx.player->index( ) ] );
	}

	render::text( ctx.bbox.pos + point_t( ctx.bbox.size.x / 2, -22 ),
				  tahoma11, font_centered_x, c, name );
}

void visuals::weapon( )
{
	if ( !ctx.player->active_weapon( ) )
	{
		return;
	}

	const auto data = interfaces::weapon_system->get_weapon_data( reinterpret_cast< econ_view_item_t* >( ctx.player->active_weapon( ) )->item_definition_index( ) );
	if ( !data )
	{
		return;
	}

	auto layer = ctx.player->anim_overlays( 1 );
	if ( !layer.owner )
	{
		return;
	}

	auto activity = ctx.player->activity( layer.sequence );

	// change to checkbox later lol
	// don't draw ammo on tasers/nades/knifes
	if ( ctx.player->active_weapon( )->clip1_count( ) >= 0 && *config::get<bool>( crc( "esp:ammo" ) ) )
	{
		int ACT_CSGO_RELOAD = 967;
		float reload_amt = layer.cycle;

		render::filled_rect( ctx.bbox.pos + point_t( 0, ctx.bbox.size.y + ctx.offset ), point_t( ctx.bbox.size.x, 3 ),
							 color( 0, 0, 0 ).alpha( ( *config::get<bool>( crc( "esp:glow:alpha_override" ) ) ? *config::get<float>( crc( "esp:glow:alpha_override:value" ) ) : 200.f ) * ctx.alpha[ ctx.player->index( ) ] ) );

		if ( activity == ACT_CSGO_RELOAD && layer.weight != 0.f )
		{
			render::filled_rect( ctx.bbox.pos + point_t( 1, ctx.bbox.size.y + 1 + ctx.offset ),
								 point_t( ( ctx.bbox.size.x - 2 ) * reload_amt, 1 ), color( 0, 150, 255 ).alpha( ( *config::get<bool>( crc( "esp:glow:alpha_override" ) ) ? *config::get<float>( crc( "esp:glow:alpha_override:value" ) ) : 220 ) * ctx.alpha[ ctx.player->index( ) ] ) );
		}
		else
		{
			render::filled_rect( ctx.bbox.pos + point_t( 1, ctx.bbox.size.y + 1 + ctx.offset ),
								 point_t( ( ctx.bbox.size.x - 2 ) * ctx.player->active_weapon( )->clip1_count( ) / data->max_clip, 1 ),
								 color( 0, 150, 255 ).alpha( ( *config::get<bool>( crc( "esp:glow:alpha_override" ) ) ? *config::get<float>( crc( "esp:glow:alpha_override:value" ) ) : 220 ) * ctx.alpha[ ctx.player->index( ) ] ) );
		}

		// fix this i cba
		if ( activity == ACT_CSGO_RELOAD && layer.weight != 0.f )
		{
			//swprintf_s( final_name, L"%s [%.0f%%]", localised_name, 100.f * reload_amt );
		}
		else
		{
			//swprintf_s( final_name, L"%s [%i|%i]", localised_name, ctx.player->active_weapon( )->clip1_count( ),
			//			ctx.player->active_weapon( )->reserve_ammo( ) );
		}

		// 3px outline, 1px space
		ctx.offset += 4;
	}

	if ( *config::get<bool>( crc( "esp:weapon" ) ) )
	{
		wchar_t* localised_name = interfaces::localize->find( data->hud_name );

		render::text( ctx.bbox.pos + point_t( ctx.bbox.size.x / 2, ctx.bbox.size.y + ctx.offset ), tahoma11, font_centered_x,
					  color( 255, 255, 255 ).alpha( ( *config::get<bool>( crc( "esp:glow:alpha_override" ) ) ? *config::get<float>( crc( "esp:glow:alpha_override:value" ) ) : 220 ) * ctx.alpha[ ctx.player->index( ) ] ),
					  localised_name );

		ctx.offset += render::text_size( localised_name, tahoma11 ).y;
	}

	
	auto id = *ctx.player->active_weapon()->item_definition_index();

	if ( *config::get<bool>( crc( "esp:weapon_icons" ) ) && id >=0 && id <= weapon_chars.size( ) - 1 && !weapon_chars.at( id ).empty( ) )
	{
		if ( !weapon_chars.empty( ) && weapon_chars.size( ) > 0 )
		{

			render::text( ctx.bbox.pos + point_t( ctx.bbox.size.x / 2, ctx.bbox.size.y + ctx.offset ), csgo, font_centered_x,
						  color( 255, 255, 255 ).alpha( ( *config::get<bool>( crc( "esp:glow:alpha_override" ) ) ? *config::get<float>( crc( "esp:glow:alpha_override:value" ) ) : 220 ) * ctx.alpha[ ctx.player->index( ) ] ),
						  weapon_chars.at( *ctx.player->active_weapon( )->item_definition_index( ) ).data( ) );

			ctx.offset += render::text_size( weapon_chars.at( *ctx.player->active_weapon( )->item_definition_index( ) ).data( ), csgo ).y;
		}
	}

}

void visuals::health( )
{
	if ( !*config::get<bool>( crc( "esp:health" ) ) ) {
		return;
	}

	int height = ( ctx.bbox.size.y - ( static_cast< int >( ( ctx.bbox.size.y * ctx.player->health( ) ) / 100 ) ) );

	render::filled_rect( ctx.bbox.pos - point_t( 5, 0 ), point_t( 3, ctx.bbox.size.y ), color( 0, 0, 0 ).alpha( ( *config::get<bool>( crc( "esp:glow:alpha_override" ) ) ? *config::get<float>( crc( "esp:glow:alpha_override:value" ) ) : 200 ) * ctx.alpha[ ctx.player->index( ) ] ) );
	render::filled_rect( ctx.bbox.pos + point_t( -4, height + 1 ), point_t( 1, ctx.bbox.size.y - height - 2 ), color( 0, 255, 0 ).alpha( ( *config::get<bool>( crc( "esp:glow:alpha_override" ) ) ? *config::get<float>( crc( "esp:glow:alpha_override:value" ) ) : 220 ) * ctx.alpha[ ctx.player->index( ) ] ) );

	wchar_t buf[ 16 ] = { 0 };
	_itow( ctx.player->health( ), buf, 10 );

	if ( ctx.player->health( ) < 90 ) {
		render::text( ctx.bbox.pos + point_t( -5 - render::text_size( buf, tahoma11 ).x, height ), tahoma11, 0,
					  color( 255, 255, 255 ).alpha( ( *config::get<bool>( crc( "esp:glow:alpha_override" ) ) ? *config::get<float>( crc( "esp:glow:alpha_override:value" ) ) : 200 ) * ctx.alpha[ ctx.player->index( ) ] ), buf );
	}
}

void visuals::flags( )
{
	if ( !*config::get<bool>( crc( "esp:flags" ) ) ) {
		return;
	}

	std::vector<std::pair<std::wstring, color_t>> flags;

	//we should be using "emplace_back" instead of "push_back"
	if ( ctx.player->is_scoped( ) )	{
		flags.push_back( { xor ( L"scoped" ), color( 0, 150, 255 ) } );
	}

	if ( ctx.player->armor( ) )	{
		if ( ctx.player->has_helmet( ) ) {
			flags.push_back( { xor ( L"hk" ), color( 255, 255, 255 ) } );
		}
		else {
			flags.push_back( { xor ( L"h" ), color( 255, 255, 255 ) } );
		}
	}

	if ( ctx.player->has_defuser( ) ) {
		flags.push_back( { xor ( L"kit" ), color( 255, 255, 255 ) } );
	}

	if ( ctx.player->has_c4( ) ) {
		flags.push_back( { xor ( L"bomb" ), color( 255, 255, 255 ) } );
	}

	if ( ctx.player->is_flashed( ) ) {
		flags.push_back( { xor ( L"flashed" ), color( 255, 255, 255 ) } );
	}

	// use the manual offset, for some reason netvar manager fucks up (m_iAccount)
	const auto buffer = std::make_unique<wchar_t[ ]>( 12 );
	std::swprintf( buffer.get( ), 10, L"$%lu", *reinterpret_cast< int32_t* >( uint32_t( ctx.player ) + 0xb354 ) );
	flags.push_back( { buffer.get( ), color( 120, 180, 10 ) } );

	int offset = 0;
	for ( auto& f : flags )
	{
		render::text( ctx.bbox.pos + point_t( ctx.bbox.size.x + 3, ( 10 * offset++ ) ), tahoma11, 0,
					  f.second.alpha( ( *config::get<bool>( crc( "esp:glow:alpha_override" ) ) ? *config::get<float>( crc( "esp:glow:alpha_override:value" ) ) : 220 ) * ctx.alpha[ ctx.player->index( ) ] ), f.first.c_str( ) );
	}
}

void visuals::glow( )
{
	if ( !ctx.local )
		return;

	if ( *config::get<bool>( crc( "esp:glow" ) ) ) {
		auto glow_color = *config::get<color>( crc( "esp:glow:color" ) );
		for ( int i = 0; i < interfaces::glow_object->m_size; ++i )
		{
			auto& object = interfaces::glow_object->m_definitions[ i ];
			if ( object.unused( ) )	{
				continue;
			}

			auto* entity = reinterpret_cast< player_t* >( object.entity( ) );
			if ( !entity || !entity->is_player( ) )	{
				continue;
			}

			if ( entity->team( ) == ctx.local->team( ) ) {
				continue;
			}

			if ( entity->clientclass( )->class_id == 40 )  {
				object.set(
					static_cast< float >( glow_color.r ) / 255.f,
					static_cast< float >( glow_color.g ) / 255.f,
					static_cast< float >( glow_color.b ) / 255.f,
					static_cast< float >( glow_color.a ) / 255.f );
			}
		}
	}
}

// plz don't paste from aristois xd ~alpha
void visuals::skeleton( )
{
	if ( !*config::get<bool>( crc( "esp:skeleton" ) ) )	{
		return;
	}

	vec3 bone1, bone2;

	auto* model = interfaces::model_info->get_studio_model( ctx.player->model( ) );

	if ( model ) {
		static matrix_t bone_out[ 128 ];

		if ( ctx.player->setup_bones( bone_out, 128, 256, 0.0f ) ) {
			for ( int i = 0; i < model->bones_count; ++i )
			{
				auto* bone = model->bone( i );

				if ( !bone || !( bone->flags & bone_used_by_hitbox ) || bone->parent == -1 ) {
					continue;
				}

				auto bone_pos = [ ]( int n ) -> vec3 {
					return vec3(
						bone_out[ n ][ 0 ][ 3 ],
						bone_out[ n ][ 1 ][ 3 ],
						bone_out[ n ][ 2 ][ 3 ]
					);
				};

				if ( !interfaces::debug_overlay->world_to_screen( bone_pos( i ), bone1 ) || !interfaces::debug_overlay->world_to_screen( bone_pos( bone->parent ), bone2 ) ) {
					continue;
				}

				render::line( point_t( bone1.x, bone1.y ), point_t( bone2.x, bone2.y ), color_t( 255, 255, 255 ).alpha( ( *config::get<bool>( crc( "esp:glow:alpha_override" ) ) ?
							  *config::get<float>( crc( "esp:glow:alpha_override:value" ) ) : 220 ) * ctx.alpha[ ctx.player->index( ) ] ) );
			}
		}
	}
}

/*
void visuals::skybox_changer()
{
	pasted from sapphyrus's gamesense lua, will eventually implement this.

	Tibet		 cs_tibet
	Baggage		 cs_baggage_skybox_
	Monastery 	 embassy
	Italy	     italy
	Aztec	 	 jungle
	Vertigo		 office
	Daylight	 sky_cs15_daylight01_hdr
	Daylight 2   vertigoblue_hdr
	Clouds		 sky_cs15_daylight02_hdr
	Clouds 2	 vertigo
	Gray		 sky_day02_05_hdr
	Clear		 nukeblank
	Canals		 sky_venice
	Cobblestone  sky_cs15_daylight03_hdr
	Assault		 sky_cs15_daylight04_hdr
	Clouds Dark  sky_csgo_cloudy01
	Night		 sky_csgo_night02
	Night 2		 sky_csgo_night02b
	Night Flat	 sky_csgo_night_flat
	Dusty		 sky_dust
	Rainy		 vietnam
}
*/

void visuals::bomb( player_t* ent )
{
	if ( !*config::get<bool>( crc( "esp:bomb" ) ) ) {
		return;
	}

	// planted c4
	if ( ent->clientclass( )->class_id != 128 )	{
		return;
	}

	box_t bbox;
	int offset{ };

	if ( !ent->bomb_defused( ) ) {
		const float time_remaining = std::clamp< float >( ent->bomb_blow_time( ) - engine_prediction::prev_curtime, 0.0f, ent->bomb_timer_length( ) );

		if ( time_remaining > 0.1f ) {
			vec3_t pos;

			if ( !interfaces::debug_overlay->world_to_screen( ent->abs_origin( ), pos ) ) {
				return;
			}

			render::text( point_t( pos.x, pos.y ), tahoma11, font_centered_x, *config::get<color>( crc( "esp:bomb:color" ) ), L"bomb [%.0f]", time_remaining );
		}
	}
}

void visuals::dropped( player_t* ent )
{
	if ( !*config::get<bool>( crc( "esp:dropped" ) ) ) {
		return;
	}

	// dropped wpns
	if ( !ent || !ent->is_weapon( ) ) {

		return;
	}

	if ( ent->owner_handle( ) != -1 ) {
		return;
	}

	vec3_t pos;

	if ( !interfaces::debug_overlay->world_to_screen( ent->abs_origin( ), pos ) ) {
		return;
	}

	const auto data = interfaces::weapon_system->get_weapon_data( reinterpret_cast< econ_view_item_t* >( ent )->item_definition_index( ) );
	if ( !data ) {
		return;
	}

	auto clip = reinterpret_cast< weapon_t* >( ent )->clip1_count( );
	wchar_t* localised_name = interfaces::localize->find( data->hud_name );

	render::text( point_t( pos.x, pos.y ), tahoma11, font_centered_x, color( 255, 255, 255 ), L"%s", localised_name );
}

void visuals::sort_players( )
{
	// sort players by distance relative to us, closer
	// players will be prioritised and drawn last
	auto local = interfaces::entity_list->get<player_t>( interfaces::engine->get_local_player( ) );

	if ( !local ) {
		return;
	}

	point screen_size;
	interfaces::engine->get_screen_size( screen_size.x, screen_size.y );

	for ( int i = 1; i <= interfaces::globals->max_clients; ++i ) {
		auto player = interfaces::entity_list->get<player_t>( i );

		if ( !player ) {
			continue;
		}

		if ( !player->is_player( ) || player->clientclass( )->class_id != 40 ) {
			continue;
		}

		if ( !player->health( ) ) {
			continue;
		}

		if ( player->team( ) == local->team( ) ) {
			continue;
		}

		vec3 temp;
		if ( !interfaces::debug_overlay->world_to_screen( player->abs_origin( ) + vec3_t( 0, 0, player->collideable( )->maxs( ).z / 2 ), temp ) ) {
			continue;
		}

		if ( temp.x > screen_size.x || temp.y > screen_size.y || temp.x < 0 || temp.y < 0 )	{
			continue;
		}

		float distance = player->origin( ).dist_to( local->origin( ) );
		ctx.players.push_back( std::pair< int, float >( i, distance ) );
	}

	//std::sort( ctx.players.begin( ), ctx.players.end( ), [ ] ( const std::pair< int, float > &left,
	//		   const std::pair< int, float > &right ) { return left.second > right.second; } );
}

bool visuals::get_box( player_t* ent, box_t& bbox )
{
	vec3_t pos = ent->abs_origin( );
	vec3_t top = pos + vec3_t( 0, 0, ent->collideable( )->maxs( ).z );

	vec3_t pos_screen, top_screen;

	if ( !interfaces::debug_overlay->world_to_screen( pos, pos_screen ) ||
		 !interfaces::debug_overlay->world_to_screen( top, top_screen ) )
	{
		return false;
	}

	bbox.pos.x = static_cast< int >( top_screen.x - ( ( pos_screen.y - top_screen.y ) / 2 ) / 2 );
	bbox.pos.y = static_cast< int >( top_screen.y );

	bbox.size.x = static_cast< int >( ( ( pos_screen.y - top_screen.y ) ) / 2 );
	bbox.size.y = static_cast< int >( ( pos_screen.y - top_screen.y ) );

	point_t screen_size;
	interfaces::engine->get_screen_size( screen_size.x, screen_size.y );

	// out of pov
	if ( pos_screen.x + bbox.size.x + 20 < 0 || pos_screen.x - bbox.size.x - 20 > screen_size.x || pos_screen.y + 20 < 0 || pos_screen.y - bbox.size.y - 20 > screen_size.y )
	{
		return false;
	}

	return true;
}

bool visuals::begin( )
{
	// make sure we're good to draw and
	// all players are valid, sanity checks
	// can also go into here 

	ctx.local = interfaces::entity_list->get<player_t>( interfaces::engine->get_local_player( ) );
	if ( !ctx.local )
	{
		return false;
	}

	if ( !ctx.player )
	{
		return false;
	}

	// we can have a teammate checkbox in esp, up to u guys ~alpha
	if ( ctx.player->team( ) == ctx.local->team( ) && ctx.player != ctx.local )
	{
		return false;
	}

	// reset offset on each player
	ctx.offset = 0;

	return get_box( ctx.player, ctx.bbox );
}

void visuals::draw( )
{
	sort_players( );

	// drop loop
	for ( int i = 0; i <= interfaces::entity_list->get_highest_entity_index( ); ++i )
	{
		auto* entity = interfaces::entity_list->get< player_t >( i );

		if ( !entity || entity->dormant( ) )
		{
			continue;
		}

		bomb( entity );
		dropped( entity );
	}

	if ( ctx.players.empty( ) )
	{
		return;
	}

	// player loop
	for ( int i = 0; i < ctx.players.size( ); ++i )
	{
		ctx.player = interfaces::entity_list->get<player_t>( ctx.players[ i ].first );

		if ( !ctx.player )
		{
			continue;
		}

		if ( !ctx.player->alive( ) )
		{
			continue;
		}

		if ( ctx.player == ctx.local )
		{
			continue;
		}

		// duxe = nigger duxe = nigger duxe = nigger
		if ( *config::get<bool>( crc( "esp:radar" ) ) )
		{
			ctx.player->spotted( ) = true;
		}

		// calculate the fade multiplier respective to frametime
		// the esp will reach full fade-in in 200ms and full fade-out in 500ms
		float fade = ( ( ctx.player->dormant( ) ? ( 1.0f / 0.5f ) : ( 1.0f / 0.2f ) ) * interfaces::globals->frame_time );

		ctx.player->dormant( ) ? ctx.alpha[ ctx.player->index( ) ] -= fade : ctx.alpha[ ctx.player->index( ) ] += fade;

		if ( ctx.alpha[ ctx.player->index( ) ] >= 1.0f )
		{
			ctx.alpha[ ctx.player->index( ) ] = 1.0f;
		}

		// dont draw esp if alpha is 0 obviously,
		// i see a lot of people not doing this
		// you see retards ~duxe
		if ( ctx.alpha[ ctx.player->index( ) ] <= 0.0f )
		{
			ctx.alpha[ ctx.player->index( ) ] = 0.0f;
			continue;
		}

		if ( begin( ) )
		{
			box( );
			name( );
			flashkill( );
			weapon( );
			health( );
			flags( );
			skeleton( );
		}
		else
		{
			// out of pov!!
			// draw arrows 
		}
	}

	// saves us fps
	// doesnt matter theyre fucked anyways
	ctx.players.clear( );
}