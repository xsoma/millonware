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

#include "hitmarkers.hpp"

#include "../renderer/renderer.hpp"
#include "../../engine/utilities/config.hpp"

void hitmarkers::update( )
{
	hit_info.m_alpha = 1.0f;
	hit_info.m_hurt_time = interfaces::globals->cur_time;

	int bruh = *config::get<int>( crc( "esp:misc:hitsound_type" ) );
	std::string str;
	if ( bruh == 0 )
	{
		str = ( xor ( "playvol survival/money_collect_05.wav " ) );
	}
	// xd
	else if ( bruh == 1 )
	{
		str = ( xor ( "playvol buttons/arena_switch_press_02.wav " ) );
	}
	else if (bruh == 2)
	{
		str = (xor ("playvol custom.wav "));
	}

	str += std::to_string( *config::get<float>( crc( "esp:misc:hitsound_volume" ) ) / 100.f );
	interfaces::engine->execute_cmd( str.c_str( ) );
}

void hitmarkers::draw( )
{
	if ( interfaces::globals->cur_time - hit_info.m_hurt_time >= 0.5f )
	{
		hit_info.m_alpha -= ( ( 1.0 / 0.5f ) * interfaces::globals->frame_time );
	}

	if ( hit_info.m_alpha <= 0.f )
	{
		hit_info.m_alpha = 0.f;
		return;
	}

	// draw hitmarker shibble here!!
}