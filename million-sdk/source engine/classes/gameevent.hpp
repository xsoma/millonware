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

class i_game_event
{
public:
	const char* get_name( )
	{
		using original_fn = const char* ( __thiscall* )( i_game_event* );
		return ( *( original_fn** )this )[ 1 ]( this );
	}
	int get_int( const char* name )
	{
		using original_fn = int( __thiscall* )( i_game_event*, const char*, int );
		return ( *( original_fn** )this )[ 6 ]( this, name, 0 );
	}
	const char* get_string( const char* keyname = nullptr )
	{
		using original_fn = const char* ( __thiscall* )( i_game_event*, const char*, const char* );
		return ( *( original_fn** )this )[ 9 ]( this, keyname, "" );
	}
	void set_string( const char* keyname, const char* value )
	{
		using original_fn = void( __thiscall* )( i_game_event*, const char*, const char* );
		return ( *( original_fn** )this )[ 16 ]( this, keyname, value );
	}
};

class i_game_event_listener
{
public:
	virtual ~i_game_event_listener( )
	{}

	virtual void fire_game_event( i_game_event* event ) = 0;
	virtual int get_debug_id( ) = 0;

public:
	int debug_id;
};

class i_game_event_manager
{
public:
	bool add_listener( i_game_event_listener* listener, const char* name, bool serverside )
	{
		using original_fn = bool( __thiscall* )( i_game_event_manager*, i_game_event_listener*, const char*, bool );
		return ( *( original_fn** )this )[ 3 ]( this, listener, name, serverside );
	}

	void remove_listener( i_game_event_listener* listener )
	{
		using original_fn = void( __thiscall* )( i_game_event_manager*, i_game_event_listener* );
		return ( *( original_fn** )this )[ 5 ]( this, listener );
	}

	void add_listener_global( i_game_event_listener* listener, bool serverside )
	{
		using original_fn = void( __thiscall* )( i_game_event_manager*, i_game_event_listener*, bool );
		return ( *( original_fn** )this )[ 6 ]( this, listener, serverside );
	}
};