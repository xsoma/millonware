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
#include <cstdint>
#include <string.h>
#include <array>

namespace utils::crypto
{
	constexpr __declspec( noinline ) auto gen_crc32_table( )
	{
		constexpr auto num_bytes = 256;
		constexpr auto num_iterations = 8;
		constexpr auto polynomial = 0xEDB88320;

		auto crc32_table = std::array<int32_t, num_bytes>{};

		for ( auto byte = 0; byte < num_bytes; ++byte )
		{
			auto crc = byte;

			for ( auto i = 0; i < num_iterations; ++i )
			{
				auto mask = -( crc & 1 );
				crc = ( crc >> 1 ) ^ ( polynomial & mask );
			}

			crc32_table[ byte ] = crc;
		}

		return crc32_table;
	}
	static constexpr auto crc32_table = gen_crc32_table( );
	constexpr __declspec( noinline ) auto crc32( const char* in )
	{
		auto crc = 0xFFFFFFFFu;

		for ( auto i = 0u; auto c = in[ i ]; ++i )
		{
			crc = crc32_table[ ( crc ^ c ) & 0xFF ] ^ ( crc >> 8 );
		}

		return ~crc;
	}

	__forceinline uint64_t hash( const wchar_t* p )
	{
		size_t s = wcslen( p );
		size_t result = 0;
		const size_t prime = 31;
		for ( size_t i = 0; i < s; ++i )
		{
			result = p[ i ] + ( result * prime );
		}
		return result;
	}

	__forceinline uint64_t hash( const char* p )
	{
		size_t s = strlen( p );
		size_t result = 0;
		const size_t prime = 31;
		for ( size_t i = 0; i < s; ++i )
		{
			result = p[ i ] + ( result * prime );
		}
		return result;
	}
}

#define crc(s) ::utils::crypto::crc32(s)