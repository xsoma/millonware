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

#include "../../engine/utilities/memory.hpp"
#include "../../engine/utilities/xorstring.hpp"

class key_values
{
public:
	key_values* init( const char* name )
	{
		using ctor_t = key_values * ( __thiscall* )( void*, const char* );

		static auto ctor = reinterpret_cast< ctor_t >( utils::memory::pattern_scan( xor ( "client.dll" ), "55 8B EC 51 33 C0 C7 45" ) );
		return ctor( this, name );
	};

	// xref '%s\\gameinfo.txt'
	bool load_from_buffer( const char* name, const char* buffer )
	{
		using load_t = bool( __thiscall* )( key_values*, const char*, const char*, void*, void*, void* );

		static auto load_from_buffer_fn = reinterpret_cast< load_t >( utils::memory::pattern_scan( xor ( "client.dll" ), "55 8B EC 83 E4 F8 83 EC 34 53 8B 5D 0C 89 4C 24 04" ) );
		return load_from_buffer_fn( this, name, buffer, 0, 0, 0 );
	}

	key_values* find_key( const char* name, bool bCreate )
	{
		using findkey_t = key_values * ( __thiscall* )( key_values*, const char*, bool );
		static auto find_key_fn = reinterpret_cast< findkey_t >( utils::memory::pattern_scan( xor ( "client.dll" ), "55 8B EC 83 EC 1C 53 8B D9 85 DB" ) );
		return find_key_fn( this, name, bCreate );
	}

	void set_int( const char* keyName, int val )
	{
		auto key_int = find_key( keyName, true );

		if ( key_int )
		{
			*reinterpret_cast< int* >( reinterpret_cast< uintptr_t >( key_int ) + 0xC ) = val;
			*reinterpret_cast< char* >( reinterpret_cast< uintptr_t >( key_int ) + 0x10 ) = 2;
		}
	}

	void set_string( const char* name, const char* a2 )
	{
		auto key = find_key( name, true );
		using setstring_t = void( __thiscall* )( void*, const char* );

		if ( key )
		{
			static auto set_string_fn = reinterpret_cast< setstring_t >( utils::memory::pattern_scan( xor ( "client.dll" ), "55 8B EC A1 ? ? ? ? 53 56 57 8B F9 8B 08 8B 01" ) );
			set_string_fn( key, a2 );
		}
	}
};