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

class key_values;
using material_handle_t = unsigned short;
class i_material
{
public:
	const char* get_name( )
	{
		using original_fn = const char* ( __thiscall* )( i_material* );
		return ( *( original_fn** )this )[ 0 ]( this );
	}
	const char* get_group_name( )
	{
		using original_fn = const char* ( __thiscall* )( i_material* );
		return ( *( original_fn** )this )[ 1 ]( this );
	}
	void set_alpha( float alpha )
	{
		using original_fn = void( __thiscall* )( i_material*, float );
		return ( *( original_fn** )this )[ 27 ]( this, alpha );
	}
	void set_alpha( int alpha )
	{
		using original_fn = void( __thiscall* )( i_material*, float );
		return ( *( original_fn** )this )[ 27 ]( this, static_cast< float >( alpha ) / 255.f );
	}
	void set_color( float r, float g, float b )
	{
		using original_fn = void( __thiscall* )( i_material*, float, float, float );
		return ( *( original_fn** )this )[ 28 ]( this, r, g, b );
	}
	void set_color( int r, int g, int b )
	{
		using original_fn = void( __thiscall* )( i_material*, float, float, float );
		return ( *( original_fn** )this )[ 28 ]( this, r / 255.f, g / 255.f, b / 255.f );
	}
	void set_color( int color32 )
	{
		int r1 = ( color32 >> 16 ) & 0xff;
		int g1 = ( color32 >> 8 ) & 0xff;
		int b1 = color32 & 0xff;
		i_material::set_color( r1, g1, b1 );
	}
	void set_flag( int flag, bool on )
	{
		using original_fn = void( __thiscall* )( i_material*, int, bool );
		return ( *( original_fn** )this )[ 29 ]( this, flag, on );
	}
	void set_shader_and_params( key_values* kv )
	{
		using original_fn = void( __thiscall* )( i_material*, key_values* );
		return ( *( original_fn** )this )[ 48 ]( this, kv );
	}
};