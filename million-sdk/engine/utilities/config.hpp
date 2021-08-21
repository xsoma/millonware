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

#include <string>
#include <unordered_map>
#include <sstream>
#include <algorithm>

#include "../../source engine/math/point.hpp"
#include "crypto.hpp"

namespace config
{
	struct config_node_t
	{
		char buffer[32];
	};

	inline std::unordered_map<uint64_t, config_node_t> config_map{};

	template<typename t>
	t* get(uint64_t hash)
	{
		if (config_map.find(hash) == config_map.end())
			config_map.insert({ hash, {} });

		return (t*)&config_map.at(hash);
	}

	__forceinline std::vector<char> dump()
	{
		std::vector<char> cfg_buf;
		std::for_each(config_map.begin(), config_map.end(), [&](std::pair<uint64_t, config_node_t> element)
		{
			for (int i = 0; i < 8; i++)
				cfg_buf.push_back(*(char*)((uintptr_t)&element.first + i));

			for (int i = 0; i < 32; i++)
				cfg_buf.push_back(*(char*)((uintptr_t)element.second.buffer + i));
		});

		return cfg_buf;
	}

	__forceinline void load(std::vector<char> cfg_buf)
	{
		for (int i = 0; i < cfg_buf.size(); i += 40)
		{
			auto buf = (const char*)((uintptr_t)cfg_buf.data() + i);

			const auto hash = *(uint64_t*)buf;
			buf += 8;

			*get<config_node_t>(hash) = *(config_node_t*)buf;
		}
	}

	void load_from_file(const char* file_name);
	void save_to_file(const char* file_name);
};