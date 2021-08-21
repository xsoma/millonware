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
#include "../../source engine/math/vector3d.hpp"
#pragma pack(push, 1)

class i_net_channel
{
public:
	char pad_0000[ 20 ];
	bool is_processing_messages;
	bool should_delete;
	char pad_0016[ 2 ];
	int32_t out_sequence_nr;
	int32_t in_sequence_nr;
	int32_t out_sequence_nr_ack;
	int32_t out_reliable_state_count;
	int32_t in_reliable_state_count;
	int32_t choked_packets;
	char pad_0030[ 1044 ];

	bool transmit( bool only_reliable )
	{
		using fn = bool( __thiscall* )( void*, bool );
		return ( *( fn** )this )[ 49 ]( this, only_reliable );
	}
};

class i_client_state
{
public:
	char pad_0000[ 156 ];
	uint32_t net_channel;
	uint32_t challenge_count;
	double reconnect_time;
	int32_t retry_count;
	char pad_00A8[ 88 ];
	int32_t signon_state_count;
	char pad_0104[ 8 ];
	float next_cmd_time;
	int32_t server_count;
	uint32_t current_sequence;
	char pad_0118[ 8 ];
	char pad_0120[ 0x4C ];
	int32_t delta_tick;
	bool is_paused;
	char pad_0171[ 3 ];
	int32_t view_entity;
	int32_t player_slot;
	char pad_017C[ 4 ];
	char level_name[ 260 ];
	char level_name_short[ 40 ];
	char pad_02AC[ 92 ];
	int32_t max_clients;
	char pad_030C[ 4083 ];
	uint32_t string_table_container;
	char pad_1303[ 14737 ];
	float last_server_tick_time;
	bool is_in_simulation;
	char pad_4C99[ 3 ];
	uint32_t old_tick_count;
	float tick_remainder;
	float frame_time;
	int32_t last_outgoing_command;
	int32_t choked_commands;
	int32_t last_command_ack;
	int32_t command_ack;
	int32_t sound_sequence;
	char pad_4CBC[ 80 ];
	vec3_t view_angles;

	void full_update( )
	{
		delta_tick = -1;
	}
};

#pragma pack(pop)