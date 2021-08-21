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

#include "movement.hpp"
#include "../../engine/utilities/config.hpp"
#include "../input/input.hpp"
#include "../hooks/hooks.hpp"
#include "../renderer/renderer.hpp"

#include "../../engine/utilities/xorstring.hpp"

namespace movement
{
	bool jumpbugged;

	void pre_prediction( c_usercmd* cmd, player_t* local, int pre_flags )
	{
		if ( *config::get<bool>( crc( "misc:infinite_duck" ) ) )
		{
			cmd->buttons |= in_bullrush;
		}

		if ( *config::get<bool>( crc( "misc:bhop" ) ) )
			if ( !input::hold( *config::get<int>( crc( "misc:jb:key" ) ) ) && local->move_type( ) != 9 )
				if ( !( pre_flags & ( fl_onground ) ) && cmd->buttons & ( in_jump ) )
				{
					cmd->buttons &= ~( in_jump );
				}
	}

	void post_prediction( c_usercmd* cmd, player_t* local, int pre_flags, int post_flags )
	{
		if ( *config::get<bool>( crc( "misc:jb" ) ) )
		{
			if ( input::hold( *config::get<int>( crc( "misc:jb:key" ) ) ) )
			{
				hooks::b_predicting = true;
				if ( !( pre_flags & ( 1 << 0 ) ) && post_flags & ( 1 << 0 ) )
				{
					cmd->buttons |= in_duck;
				}

				if ( post_flags & fl_onground )
				{
					cmd->buttons &= ~in_jump;
					jumpbugged = true;
				}
			}
		}

		if ( *config::get<bool>( crc( "misc:ej" ) ) )
		{
			if ( input::hold( *config::get<int>( crc( "misc:ej:key" ) ) ) )
			{
				if ( pre_flags & ( 1 << 0 ) && !( post_flags & 1 << 0 ) )
				{
					cmd->buttons |= in_jump;
				}
			}
			if ( *config::get<bool>( crc( "misc:lj" ) ) )
			{
				// kinda weird, dont know why we need a seperate check. Prob because of tickrate. anyways you could remove this check and make a lj on every jump feature :sunglasses:
				if ( input::hold( *config::get<int>( crc( "misc:ej:key" ) ) ) )
				{
					if ( !( post_flags & 1 << 0 ) )
					{
						cmd->buttons |= in_duck;
					}
				}
			}
		}

		if ( *config::get<bool>( crc( "misc:eb" ) ) )
		{
			if ( !( pre_flags & ( 1 << 0 ) ) && post_flags & ( 1 << 0 ) && input::hold( *config::get<int>( crc( "misc:eb:key" ) ) ) )
			{
				cmd->buttons |= ( in_duck );
			}
		}
		//this is basically just the exact same as eb assist but you dont hold the key lOl
		if (*config::get<bool>(crc("misc:stathelper")))
		{
			if (!(pre_flags & (1 << 0)) && post_flags & (1 << 0))
			{
				cmd->buttons |= (in_duck);
				cmd->buttons |= (in_duck);
			}
		}
	}

	void draw( )
	{
		static float last_vel = 0.f;
		static int tick_prev = 0;

		static float take_off = 0.f;
		static float take_off_time = 0.f;

		static bool last_on_ground = false;

		point screen_size; interfaces::engine->get_screen_size( screen_size.x, screen_size.y );
		auto local = interfaces::entity_list->get<player_t>( interfaces::engine->get_local_player( ) );

		if ( local )
		{
			float vel = floorf( min( 10000, local->velocity( ).length_2d( ) + 0.5 ) );
			bool on_ground = ( local->flags( ) & fl_onground );
			if ( last_on_ground && !on_ground )
			{
				take_off = vel;
				take_off_time = interfaces::globals->cur_time + 2.f;
			}

			if ( *config::get<bool>( crc( "misc:vel" ) ) )
			{
				color c = vel == last_vel ? color( 255, 199, 89 ) : vel < last_vel ? color( 255, 119, 119 ) : color( 30, 255, 109 );

				bool should_draw_takeoff = ( !on_ground || ( take_off_time > interfaces::globals->cur_time ) ) && *config::get<bool>( crc( "misc:vel:takeoff" ) );

				render::text( point( screen_size.x / 2, screen_size.y - 100 ), fonts::velocity_indicator, font_centered_x | font_dropshadow, c, should_draw_takeoff ? L"%.0f (%.0f)\n" : L"%.0f", vel, take_off );
			}

			if ( *config::get<bool>( crc( "misc:jb:indicator" ) ) && *config::get<bool>( crc( "misc:jb" ) ) && input::hold( *config::get<int>( crc( "misc:jb:key" ) ) ) )
			{
				render::text( point( screen_size.x / 2, screen_size.y - 150 ), fonts::other_indicators, font_centered_x | font_dropshadow, jumpbugged ? color( 30, 255, 109 ) : color( 255, 255, 255 ), xor ( L"jb\n" ) );
			}
			else
			{
				jumpbugged = false;
			}

			if ( *config::get<bool>( crc( "misc:eb:indicator" ) ) && *config::get<bool>( crc( "misc:eb" ) ) && input::hold( *config::get<int>( crc( "misc:eb:key" ) ) ) )
			{
				render::text( point( screen_size.x / 2, screen_size.y - 170 ), fonts::other_indicators, font_centered_x | font_dropshadow, color( 255, 255, 255 ), xor ( L"eb\n" ) );
			}

			if ( *config::get<bool>( crc( "misc:ej:indicator" ) ) && *config::get<bool>( crc( "misc:ej" ) ) && input::hold( *config::get<int>( crc( "misc:ej:key" ) ) ) )
			{
				render::text( point( screen_size.x / 2, screen_size.y - 190 ), fonts::other_indicators, font_centered_x | font_dropshadow, color( 255, 255, 255 ), xor ( L"ej\n" ) );
			}

			if ( tick_prev + 5 < interfaces::globals->tick_count )
			{
				last_vel = vel;
				tick_prev = interfaces::globals->tick_count;
			}

			last_on_ground = on_ground;

			if ( jumpbugged && ( !on_ground || ( take_off_time > interfaces::globals->cur_time ) ) )
			{
				jumpbugged = false;
			}
		}
		else
		{
			last_vel = 0.f;
			tick_prev = 0;
			take_off = 0.f;
			take_off_time = 0.f;
		}
	}
}