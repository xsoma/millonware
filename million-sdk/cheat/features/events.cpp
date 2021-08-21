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

#include "events.hpp"

#include <algorithm>
#include <unordered_map>

#include "hitmarkers.hpp"
#include "skins.hpp"
#include "../../engine/utilities/config.hpp"

// static xdddd
static c_game_events events{};
void c_game_events::init( )
{
	interfaces::game_event_manager->add_listener_global( &events, false );
}

void c_game_events::revert( )
{
	interfaces::game_event_manager->remove_listener( &events );
}

// use a map -paracord
const char* hitgroup_to_str( int bruh )
{
	switch ( bruh )
	{
	case hitgroup_generic: return ( "body" ); break;
	case hitgroup_head: return ( "head" ); break;
	case hitgroup_chest: return ( "chest" ); break;
	case hitgroup_stomach: return ( "stomach" ); break;
	case hitgroup_leftarm: return ( "left arm" ); break;
	case hitgroup_rightarm: return ( "right arm" ); break;
	case hitgroup_leftleg: return ( "left leg" ); break;
	case hitgroup_rightleg: return ( "right leg" ); break;
	case hitgroup_gear: return ( "gear" ); break;
	}

	return xor ( "xd" );
}

bool is_knife_string( const char* str )
{
	return strstr( str, xor ( "knife" ) );
}

void c_game_events::fire_game_event( i_game_event* event )
{

	if ( !strcmp( event->get_name( ), xor ( "player_hurt" ) ) )
	{
		auto local = interfaces::entity_list->get<player_t>( interfaces::engine->get_local_player( ) );

		int dmg_health = event->get_int( xor ( "dmg_health" ) );

		auto attacker = interfaces::entity_list->get<player_t>( interfaces::engine->get_player_for_user_id( event->get_int( xor ( "attacker" ) ) ) );
		auto target = interfaces::entity_list->get<player_t>( interfaces::engine->get_player_for_user_id( event->get_int( xor ( ( "userid" ) ) ) ) );

		if ( local && attacker && target && attacker == local && target->team( ) != local->team( ) )
		{
			if ( *config::get<bool>( crc( "esp:misc:hurtinfo" ) ) )
			{
				interfaces::hud_chat->chat_print( xor ( "[" "\x0C" "millionware" "\x08" "]" " hurt %s in the %s for %i [%i remaining]" ),
												  target->info( ).name, hitgroup_to_str( event->get_int( xor ( "hitgroup" ) ) ),
												  event->get_int( xor ( "dmg_health" ) ), event->get_int( xor ( "health" ) ) );
			}

			if ( *config::get<bool>( crc( "esp:misc:hitsound" ) ) )
			{
				hitmarkers::update( );
			}
		}

	}
	if ( !strcmp( event->get_name( ), xor ( "player_death" ) ) )
	{
		auto attacker = interfaces::entity_list->get<player_t>( interfaces::engine->get_player_for_user_id( event->get_int( xor ( "attacker" ) ) ) );
		if ( attacker && attacker->index( ) == interfaces::engine->get_local_player( ) )
		{
			if ( is_knife_string( event->get_string( "weapon" ) ) )
			{
				event->set_string( "weapon", skins::knifes::update_kill_icons( ) );
			}
		}
	}
	if ( !strcmp( event->get_name( ), xor( "round_freeze_end" ) ) ) {
		utils::engine::round_flags = 0;
	}
	if ( !strcmp( event->get_name( ), xor( "round_start" ) ) || !strcmp( event->get_name( ), xor( "client_disconnect" ) ) ) {
		utils::engine::round_flags = 1;
	}

}

// ?
int c_game_events::get_debug_id( )
{
	return 42;
}