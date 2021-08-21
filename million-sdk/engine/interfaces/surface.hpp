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
#include "../../source engine/structs/vertex_t.hpp"

class i_surface
{
public:
	void set_drawing_color( int r, int g, int b, int a = 255 )
	{
		using original_fn = void( __thiscall* )( i_surface*, int, int, int, int );
		return ( *( original_fn** )this )[ 15 ]( this, r, g, b, a );
	}
	void set_text_color( int r, int g, int b, int a = 255 )
	{
		using original_fn = void( __thiscall* )( i_surface*, int, int, int, int );
		return ( *( original_fn** )this )[ 25 ]( this, r, g, b, a );
	}
	void draw_polygon( int n, vertex_t* vertice, bool clip_vertices = true )
	{
		using original_fn = void( __thiscall* )( i_surface*, int, vertex_t*, bool );
		return ( *( original_fn** )this )[ 106 ]( this, n, vertice, clip_vertices );
	}
	void draw_filled_rectangle( int x, int y, int x1, int y1 )
	{
		using original_fn = void( __thiscall* )( i_surface*, int, int, int, int );
		return ( *( original_fn** )this )[ 16 ]( this, x, y, x1, y1 );
	}
	void set_texture( int id )
	{
		using original_fn = void( __thiscall* )( i_surface*, int );
		return ( *( original_fn** )this )[ 38 ]( this, id );
	}
	void set_texture_rgba( int id, const unsigned char* rgba, int wide, int tall )
	{
		using original_fn = void( __thiscall* )( i_surface*, int, const unsigned char*, int, int, int, bool );
		return ( *( original_fn** )this )[ 37 ]( this, id, rgba, wide, tall, 0, false );
	}
	int create_new_texture_id( bool procedural = false )
	{
		using original_fn = int( __thiscall* )( i_surface*, bool );
		return ( *( original_fn** )this )[ 43 ]( this, procedural );
	}
	void draw_outlined_rect( int x, int y, int x1, int y1 )
	{
		using original_fn = void( __thiscall* )( i_surface*, int, int, int, int );
		return ( *( original_fn** )this )[ 18 ]( this, x, y, x1, y1 );
	}
	void draw_line( int x1, int y1, int x2, int y2 )
	{
		using original_fn = void( __thiscall* )( i_surface*, int, int, int, int );
		return ( *( original_fn** )this )[ 19 ]( this, x1, y1, x2, y2 );
	}
	void draw_poly_line( int* px, int* py, int num_points )
	{
		using original_fn = void( __thiscall* )( i_surface*, int*, int*, int );
		return ( *( original_fn** )this )[ 20 ]( this, px, py, num_points );
	}
	void draw_text_font( unsigned long font )
	{
		using original_fn = void( __thiscall* )( i_surface*, unsigned long );
		return ( *( original_fn** )this )[ 23 ]( this, font );
	}
	void draw_text_pos( int x, int y )
	{
		using original_fn = void( __thiscall* )( i_surface*, int, int );
		return ( *( original_fn** )this )[ 26 ]( this, x, y );
	}
	void draw_render_text( const wchar_t* text, int textLen )
	{
		using original_fn = void( __thiscall* )( i_surface*, const wchar_t*, int, int );
		return ( *( original_fn** )this )[ 28 ]( this, text, textLen, 0 );
	}
	unsigned long font_create( )
	{
		using original_fn = unsigned int( __thiscall* )( i_surface* );
		return ( *( original_fn** )this )[ 71 ]( this );
	}
	void set_font_glyph( unsigned long font, const char* windowsFontName, int tall, int weight, int blur, int scanlines, int flags )
	{
		using original_fn = void( __thiscall* )( i_surface*, unsigned long, const char*, int, int, int, int, int, int, int );
		return ( *( original_fn** )this )[ 72 ]( this, font, windowsFontName, tall, weight, blur, scanlines, flags, 0, 0 );
	}
	void get_text_size( unsigned long font, const wchar_t* text, int& wide, int& tall )
	{
		using original_fn = void( __thiscall* )( i_surface*, unsigned long, const wchar_t*, int&, int& );
		return ( *( original_fn** )this )[ 79 ]( this, font, text, wide, tall );
	}
	void set_clip( int x, int y, int x2, int y2 )
	{
		*( bool* )( this + 0x280 ) = true;
		using original_fn = void( __thiscall* )( i_surface*, int, int, int, int );
		return ( *( original_fn** )this )[ 147 ]( this, x, y, x2, y2 );
	}
	void reset_clip( )
	{
		set_clip( 0, 0, 10000, 10000 );
		*( bool* )( this + 0x280 ) = false;
	}
	bool is_texture_id_valid( int id )
	{
		using original_fn = bool( __thiscall* )( i_surface*, bool );
		return ( *( original_fn** )this )[ 42 ]( this, id );
	}
	void delete_texture_by_id( int id )
	{
		using original_fn = void( __thiscall* )( void*, bool );
		return ( *( original_fn** )this )[ 39 ]( this, id );
	}
	void filled_rect_fade( int x1, int y1, int x2, int y2, int a1, int a2, bool horiz = false )
	{
		using original_fn = void( __thiscall* )( void*, int, int, int, int, int, int, bool );
		return ( *( original_fn** )this )[ 123 ]( this, x1, y1, x2, y2, a1, a2, horiz );
	}
	void draw_textured_rect( int x, int y, int w, int h )
	{
		using original_fn = void( __thiscall* )( void*, int, int, int, int );
		return ( *( original_fn** )this )[ 41 ]( this, x, y, w, h );
	}
	void unlock_cursor( )
	{
		using original_fn = void( __thiscall* )( void* );
		return ( *( original_fn** )this )[ 66 ]( this );
	}
};