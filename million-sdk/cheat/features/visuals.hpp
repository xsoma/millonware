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

#include "../../source engine/classes/entities.hpp"

// forward declarations or define point here?
#include "../../source engine/math/point.hpp"

#include <unordered_map>

namespace visuals
{
	struct box_t
	{
		point_t pos;
		point_t size;
	};

	// general context to avoid calling get_box
	// and shit multiple times on players, if we
	// don't like this or have a better way of
	// going around this then change it and lmk ~alpha
	inline struct context_t
	{
		box_t bbox;

		player_t* player;
		player_t* local;

		std::vector< std::pair< int, float > > players;

		int offset;
		float alpha[ 64 ];
	} ctx;

	inline std::unordered_map<int, std::wstring> weapon_chars =
	{
		{ weapon_deagle, L"F" }, { weapon_elite, L"S" }, { weapon_revolver, L"" }, { weapon_taser, L"" }, { weapon_fiveseven, L"U" },
		{ weapon_awp, L"R" }, { weapon_famas, L"T" }, { weapon_g3sg1, L"I" }, { weapon_galilar, L"V" }, { weapon_m249, L"Z" }, { weapon_aug, L"E" },
		{ weapon_m4a1, L"W" }, { weapon_mac10, L"L" }, { weapon_p90, L"M" }, { weapon_ump45, L"Q" }, { weapon_xm1014, L"]" },
		{ weapon_bizon, L"D" }, { weapon_mag7, L"K" }, { weapon_negev, L"Z" }, { weapon_sawedoff, L"K" }, { weapon_tec9, L"C" },
		{ weapon_hkp2000, L"Y" }, { weapon_mp7, L"X" }, { weapon_mp9, L"D" }, { weapon_nova, L"K" }, { weapon_ak47, L"B" },
		{ weapon_p250, L"Y" }, { weapon_scar20, L"I" }, { weapon_sg556, L"[" }, { weapon_scout, L"N" }, { weapon_knife, L"J" },
		{ weapon_flashbang, L"G" }, { weapon_hegrenade, L"H" }, { weapon_smokegrenade, L"P" }, { weapon_molotov, L"P" }, { weapon_decoy, L"G" },
		{ weapon_incgrenade, L"P" }, { weapon_c4, L"\\" }, { weapon_knife_t, L"J" }, { weapon_m4a1_silencer, L"W" }, { weapon_usp_silencer, L"Y" },
		{ weapon_bayonet, L"J" }, { weapon_knife_flip, L"J" }, { weapon_knife_gut, L"J" }, { weapon_knife_karambit, L"J" }, { weapon_glock, L"C" },
		{ weapon_knife_m9_bayonet, L"J" }, { weapon_knife_tactical, L"J" }, { weapon_knife_falchion, L"J" }, { weapon_knife_survival_bowie, L"J" },
		{ weapon_knife_butterfly, L"J" }, { weapon_knife_push, L"J" }, { weapon_knife_gypsy_jackknife, L"J" }, { weapon_knife_stiletto, L"J" },
		{ weapon_knife_ursus, L"J" }, { weapon_knife_widowmaker, L"J" }, { weapon_mp5sd, L"X" }
	};

	void box( );
	void name( );
	void flashkill( );
	void weapon( );
	void health( );
	void flags( );
	void glow( );
	void skeleton( );

	void bomb( player_t* ent );
	void dropped( player_t* ent );

	void sort_players( );
	bool get_box( player_t* ent, box_t& bbox );

	bool begin( );

	void draw( );
}