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

#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <algorithm>
#include <functional>

#include "../renderer/renderer.hpp"
#include "../../engine/utilities/crypto.hpp"
#include "../../engine/utilities/xorstring.hpp"
typedef point point;

#include "../../engine/utilities/config.hpp"

#include "../features/skins.hpp"
#include "../../engine/utilities/crypto.hpp"
#include "../input/input.hpp"
// move me
struct hsv
{
	float hue;
	float sat;
	float val;
};

inline color hsv2rgb( float hue, float sat, float val )
{
	float red, grn, blu;
	float i, f, p, q, t;
	color result{ 0, 0, 0 };

	if ( val == 0 )
	{
		red = 0;
		grn = 0;
		blu = 0;
	}
	else
	{
		hue /= 60;
		i = floor( hue );
		f = hue - i;
		p = val * ( 1 - sat );
		q = val * ( 1 - ( sat * f ) );
		t = val * ( 1 - ( sat * ( 1 - f ) ) );
		if ( i == 0 )
		{
			red = val; grn = t; blu = p;
		}
		else if ( i == 1 )
		{
			red = q; grn = val; blu = p;
		}
		else if ( i == 2 )
		{
			red = p; grn = val; blu = t;
		}
		else if ( i == 3 )
		{
			red = p; grn = q; blu = val;
		}
		else if ( i == 4 )
		{
			red = t; grn = p; blu = val;
		}
		else if ( i == 5 )
		{
			red = val; grn = p; blu = q;
		}
	}
	result.r = red * 255;
	result.g = grn * 255;
	result.b = blu * 255;
	result.a = 255;
	return result;
}

inline hsv rgb2hsv( color a )
{
	float red, grn, blu;
	red = ( float )a.r / 255.f;
	grn = ( float )a.g / 255.f;
	blu = ( float )a.b / 255.f;
	float hue, sat, val;
	float x, f, i;
	hsv result;

	x = min( min( red, grn ), blu );
	val = max( max( red, grn ), blu );
	if ( x == val )
	{
		hue = 0;
		sat = 0;
	}
	else
	{
		f = ( red == x ) ? grn - blu : ( ( grn == x ) ? blu - red : red - grn );
		i = ( red == x ) ? 3 : ( ( grn == x ) ? 5 : 1 );
		hue = fmod( ( i - f / ( val - x ) ) * 60, 360 );
		sat = ( ( val - x ) / val );
	}
	result.hue = hue;
	result.sat = sat;
	result.val = val;
	return result;
}

namespace gui
{
	struct gui_ctx_t
	{
		color menu_color_nigger{ 0, 251, 255 };

		bool open;

		bool dragging;
		bool typing;

		point pos = point( 100, 100 );
		point size = point( 500, 485 );

		point inner_pos;
		point inner_size;

		point next_pos;
		point next_group_pos;

		point parent_size;

		std::vector<std::wstring> tabs;

		uint64_t blocking;

		void add_tab( const std::wstring& tab_name )
		{
			tabs.push_back( tab_name );
		}

		struct drop_down_info_t
		{
			uint64_t id;
			bool open = false;

			point pos = { 0, 0 };
			int width = 0;

			const wchar_t** options = { };
			int option_count;
			int* value;
		};
		drop_down_info_t drop_down_info;

		struct color_picker_info_t
		{
			uint64_t id;
			bool open = false;

			point pos = { 0, 0 };

			bool dragging_color;
			bool dragging_hue;
			bool dragging_alpha;

			bool has_alpha;

			color* c;
		};
		color_picker_info_t color_picker_info;
	};

	inline gui_ctx_t ctx;

	namespace utils
	{
		inline float map_number( float input, float input_min, float input_max, float output_min, float output_max )
		{
			return ( input - input_min ) / ( input_max - input_min ) * ( output_max - output_min ) + output_min;
		}

		inline std::vector<std::wstring> split_str( const std::wstring& str, char separator )
		{
			std::vector<std::wstring> output;
			std::wstring::size_type prev_pos = 0, pos = 0;

			while ( ( pos = str.find( separator, pos ) ) != std::wstring::npos )
			{
				std::wstring substring( str.substr( prev_pos, pos - prev_pos ) );
				output.push_back( substring );

				prev_pos = pos++;
			}

			output.push_back( str.substr( prev_pos, pos - prev_pos ) );
			return output;
		}
	}

	inline bool start( int* tab )
	{
		if ( !ctx.open )
			return false;

		render::filled_rect( ctx.pos, ctx.size, color( 10, 10, 10 ) );
		render::filled_rect( ctx.pos + 1, ctx.size - 2, color( 60, 60, 60 ) );
		render::filled_rect( ctx.pos + 2, ctx.size - 4, color( 40, 40, 40 ) );
		render::filled_rect( ctx.pos + 5, ctx.size - 10, color( 60, 60, 60 ) );
		render::filled_rect( ctx.pos + 6, ctx.size - 12, color( 30, 30, 30 ) );

		if ( input::hover( ctx.pos, point( ctx.size.x, 16 ) ) )
			ctx.dragging = true;
		if ( !input::hold( VK_LBUTTON ) )
			ctx.dragging = false;
		if ( ctx.dragging )
			ctx.pos = ctx.pos + input::cursor_delta;

		ctx.inner_pos = ctx.pos + 15;

		const auto tab_count = ctx.tabs.size( );

		render::rect( ctx.inner_pos + point( 1, 0 ), point( ctx.inner_size.x - 105, 40 ), color( 63, 63, 63 ) );
		render::rect( point( ctx.inner_pos.x + ctx.inner_size.x - 95, ctx.inner_pos.y ), point( 88, 40 ), color( 63, 63, 63 ) );

		int tab_container_width = ctx.inner_size.x - 105;
		int tab_width = tab_container_width / tab_count;
		point tab_pos;

		for ( int i = 0; i < tab_count; i++ )
		{
			tab_pos = point( ctx.inner_pos.x + ( ( i + 1 ) * tab_width ), ctx.inner_pos.y + 13 );

			if ( input::hover( tab_pos - point( tab_width, 15 ), point( tab_width, 40 ) ) && input::click( VK_LBUTTON ) )
			{
				*tab = i;
				ctx.blocking = 0;
			}

			render::text( tab_pos - point( tab_width / 2, 0 ), verdana10, font_centered_x | font_dropshadow, i != *tab ? color( 153, 153, 153 ) : ctx.menu_color_nigger, ctx.tabs[ i ].c_str( ) );
		}

		render::text( point( ctx.inner_pos.x + ctx.inner_size.x - 95 + 45, ctx.inner_pos.y + 13 ), verdana10, font_centered_x | font_dropshadow, ctx.menu_color_nigger, xor ( L"millionware" ) );

		ctx.inner_pos = ctx.inner_pos + point( 2, 60 );
		ctx.inner_size = ctx.size - 25 - point( -2, 56 );
		ctx.parent_size = ctx.inner_size;

		ctx.next_group_pos = ctx.inner_pos;

		return true;
	}

	inline void group( const wchar_t* name, float group_width, float group_height )
	{
		int height = ( int )( ( float )ctx.inner_size.y * group_height ) - 10;
		int width = ( int )( ( float )ctx.inner_size.x * group_width ) - 10;

		if ( ctx.next_group_pos.y >= ctx.inner_size.y + ctx.inner_pos.y - 1 )
		{
			ctx.next_group_pos.x += width + 10;
			ctx.next_group_pos.y = ctx.inner_pos.y;

			return group( name, group_width, group_height );
		}

		render::rect( ctx.next_group_pos, point( width, height ), color( 0, 0, 0 ) );
		render::rect( ctx.next_group_pos - 1, point( width, height ) + 2, color( 63, 63, 63 ) );
		auto text_size = render::text_size( utils::split_str( name, '##' )[ 0 ].data( ), verdana10 );

		render::filled_rect( ctx.next_group_pos + point( 10, -2 ), text_size + point( 4, 0 ), color( 30, 30, 30 ) );
		render::text( ctx.next_group_pos + point( 12, -8 ), verdana10, font_dropshadow, color( 140, 140, 140 ), utils::split_str( name, '##' )[ 0 ].data( ) );

		ctx.next_pos = ctx.next_group_pos + 10;
		ctx.next_group_pos.y += height + 11;

		ctx.parent_size = point( width - 10, height );
	}

	inline bool checkbox( const wchar_t* name, bool* option )
	{
		point size( 9, 9 );

		bool hovered = input::hover( ctx.next_pos - point( 0, 3 ), size + point( 16 + render::text_size( name, verdana10 ).x, 3 ) );

		render::text( ctx.next_pos + point( 16, -2 ), verdana10, font_dropshadow, color( 153, 153, 153 ), utils::split_str( name, '##' )[ 0 ].data( ) );
		render::filled_rect( ctx.next_pos, size, *option ? ctx.menu_color_nigger : color( 25, 25, 25 ) );
		render::rect( ctx.next_pos, size, ( hovered && ctx.blocking == 0 ) ? ctx.menu_color_nigger : color( 50, 50, 50 ) );

		if ( ctx.blocking == 0 )
		{
			if ( hovered && input::click( VK_LBUTTON ) )
				ctx.blocking = ::utils::crypto::hash( name );
		}
		else if ( ctx.blocking == ::utils::crypto::hash( name ) )
		{
			if ( !input::hold( VK_LBUTTON ) )
			{
				ctx.blocking = 0;

				if ( input::hover( ctx.next_pos - point( 0, 3 ), size + point( 16 + render::text_size( name, verdana10 ).x, 3 ) ) )
				{
					*option = !*option;
				}
			}
		}

		// make 6 an int in context and define it as control spacing?? 
		ctx.next_pos.y += ( size.y + 6 ); // ur mom is black? :D
		return *option;
	}

	inline void hotkey( const wchar_t* id, int* key )
	{
		auto get_key_name = [ ]( const int vk_key ) -> std::wstring
		{
			auto scan_code = MapVirtualKeyA( vk_key, MAPVK_VK_TO_VSC );

			int result;
			char buffer[ 128 ];

			switch ( vk_key )
			{
			case VK_LEFT: case VK_UP: case VK_RIGHT: case VK_DOWN:
			case VK_RCONTROL: case VK_RMENU:
			case VK_LWIN: case VK_RWIN: case VK_APPS:
			case VK_PRIOR: case VK_NEXT:
			case VK_END: case VK_HOME:
			case VK_INSERT: case VK_DELETE:
			case VK_DIVIDE:
			case VK_NUMLOCK:
			scan_code |= KF_EXTENDED;
			default:
			result = GetKeyNameTextA( scan_code << 16, buffer, 128 );
			}

			if ( result == 0 )
			{
				switch ( vk_key )
				{
				case VK_XBUTTON1:
				return xor ( L"[M4]" );
				case VK_XBUTTON2:
				return xor ( L"[M5]" );
				case VK_LBUTTON:
				return xor ( L"[M1]" );
				case VK_MBUTTON:
				return xor ( L"[M3]" );
				case VK_RBUTTON:
				return xor ( L"[M2]" );
				default:
				return xor ( L"[-]" );
				}
			}

			// lel
			std::string fag_shit( xor ( "[" ) );
			fag_shit += buffer;
			fag_shit += xor ( "]" );
			std::transform( fag_shit.begin( ), fag_shit.end( ), fag_shit.begin( ), ::toupper );

			return std::wstring( fag_shit.begin( ), fag_shit.end( ) );
		};

		point pos = ctx.next_pos;
		pos.x += ctx.parent_size.x - 20;
		pos.y -= 2;

		bool hovered = input::hover( pos - 7, point( 15, 15 ) );

		render::text( pos, small_font, font_centered_x | font_outline, ctx.blocking == ::utils::crypto::hash( id ) || ( hovered && ctx.blocking == 0 ) ?
					  ctx.menu_color_nigger : color( 107, 107, 107 ), get_key_name( *key ).data( ) );

		if ( ctx.blocking == 0 )
		{
			if ( hovered && input::click( VK_LBUTTON ) )
				ctx.blocking = ::utils::crypto::hash( id );
		}
		else if ( ctx.blocking == ::utils::crypto::hash( id ) )
		{
			for ( int i = 0; i < 250; i++ )
			{
				if ( input::click( i ) )
				{
					*key = i;
					if ( i == VK_ESCAPE )
						*key = 0;

					ctx.blocking = 0;
				}
			}
		}
	}

	inline void color_picker( const wchar_t* id, color* c, bool has_alpha = true )
	{
		point pos = ctx.next_pos;
		pos.x += ctx.parent_size.x - 28;

		render::filled_rect( pos + 1, point_t( 18, 9 ) - 1, *c );
		render::gradient_v( pos + 1, point_t( 18, 9 ) - 1, color( 0, 0, 0, 50 ), color( 0, 0, 0, 150 ), 40, 0 );

		bool hovered = input::hover( pos, point_t( 18, 9 ) );

		render::rect( pos, point_t( 18, 9 ), ( ( hovered && ctx.blocking == 0 ) || ctx.blocking == ::utils::crypto::hash( id ) ) ? ctx.menu_color_nigger : color( 10, 10, 10 ) );

		if ( ctx.blocking == 0 )
		{
			if ( hovered && input::click( VK_LBUTTON ) )
				ctx.blocking = ::utils::crypto::hash( id );
		}
		else if ( ctx.blocking == ::utils::crypto::hash( id ) )
		{
			if ( hovered )
			{
				ctx.color_picker_info.open = true;
				ctx.color_picker_info.c = c;
				ctx.color_picker_info.pos = pos + point( 20, 5 );
				ctx.color_picker_info.id = ::utils::crypto::hash( id );
				ctx.color_picker_info.has_alpha = has_alpha;
			}
		}
	}

	template<class t = int>
	inline t slider( const wchar_t* name, float* value, float min, float max, const wchar_t* format = xor ( L"%0.f" ) )
	{
		ctx.next_pos.y -= 5;
		render::text( ctx.next_pos + point( 16, 0 ), verdana10, font_dropshadow, color( 153, 153, 153 ), utils::split_str( name, '##' )[ 0 ].data( ) );

		int max_width = ctx.parent_size.x - 45;
		int fill_width = t( utils::map_number( *value, min, max, 0, max_width - 1 ) );

		bool hovered = input::hover( ctx.next_pos + point( 21, 12 ), point( max_width, 9 ) );

		render::filled_rect( ctx.next_pos + point( 18, 15 ), point( max_width, 8 ), color( 25, 25, 25 ) );
		render::filled_rect( ctx.next_pos + point( 18, 15 ), point( fill_width, 8 ), ctx.menu_color_nigger );
		render::rect( ctx.next_pos + point( 18, 15 ), point( max_width, 8 ), ( ( hovered && ctx.blocking == 0 ) || ( ctx.blocking == ::utils::crypto::hash( name ) ) ) ? ctx.menu_color_nigger : color( 50, 50, 50 ) );

		wchar_t buf[ 32 ] = { 0 };
		swprintf_s( buf, format, float( *value ) );

		point text_size = render::text_size( buf, verdana10 );

		render::text( ctx.next_pos + point( 18 + max_width - text_size.x, 0 ), verdana10, font_dropshadow, color( 153, 153, 153 ), buf );

		if ( ctx.blocking == 0 )
		{
			if ( hovered && input::click( VK_LBUTTON ) )
				ctx.blocking = ::utils::crypto::hash( name );
		}
		else if ( ctx.blocking == ::utils::crypto::hash( name ) )
		{
			if ( input::hold( VK_LBUTTON ) )
			{
				t offset = std::clamp<t>( ( t )point( input::cursor_pos - ctx.next_pos ).x - 16, 0, max_width );
				*value = std::clamp<t>( t( utils::map_number( offset, 0, max_width, min, max ) ), min, max );
			}
			else
			{
				ctx.blocking = 0;
			}
		}

		// make 6 an int in context and define it as control spacing?? 
		ctx.next_pos.y += 30;
		return *value;
	}

	inline bool combo( const wchar_t* name, const wchar_t** elements, int element_count, int* value )
	{
		point draw_pos = ctx.next_pos;
		draw_pos.y -= 3;
		draw_pos.x += 18;

		render::text( draw_pos + point( -2, 0 ), verdana10, font_dropshadow, color( 153, 153, 153 ), utils::split_str( name, '##' )[ 0 ].data( ) );
		draw_pos.y += 3;

		bool hovered = input::hover( draw_pos + point( 0, 12 ), point( ctx.parent_size.x - 46, 18 ) );

		render::filled_rect( draw_pos + point( 0, 12 ), point( ctx.parent_size.x - 46, 18 ), color( 25, 25, 25 ) );
		render::rect( draw_pos + point( 0, 12 ), point( ctx.parent_size.x - 46, 18 ), ( ( hovered && ctx.blocking == 0 ) || ( ctx.blocking == ::utils::crypto::hash( name ) ) ) ? ctx.menu_color_nigger : color( 50, 50, 50 ) );

		auto line = [ & ]( point pos, bool nigger = false )
		{
			for ( auto i = 5; i >= 2; --i )
			{
				auto offset = 5 - i;
				render::line( point( pos.x + offset, pos.y + offset ), point( pos.x + offset + std::clamp( i - offset, 0, 5 ), pos.y + offset ), nigger ? color( 0, 0, 0 ) : color( 152, 152, 152 ) );
			}
		};

		line( draw_pos + point( ctx.parent_size.x - 46, 32 ) - point( 10, 7 ) - point( 0, 6 ), true );
		line( draw_pos + point( ctx.parent_size.x - 46, 32 ) - point( 10, 7 ) + point( 0, 1 ) - point( 0, 6 ) );

		render::text( draw_pos + point( 4, 15 ), verdana10, font_dropshadow, color( 203, 203, 203 ), elements[ *value ] );

		if ( ctx.blocking == 0 )
		{
			if ( hovered && input::click( VK_LBUTTON ) )
				ctx.blocking = ::utils::crypto::hash( name );
		}
		else if ( ctx.blocking == ::utils::crypto::hash( name ) )
		{
			if ( hovered )
			{
				ctx.drop_down_info.options = elements;
				ctx.drop_down_info.option_count = element_count;
				ctx.drop_down_info.width = ctx.parent_size.x - 46;
				ctx.drop_down_info.value = value;
				ctx.drop_down_info.pos = draw_pos + point( 0, 30 );
				ctx.drop_down_info.id = ::utils::crypto::hash( name );
			}
		}

		ctx.next_pos.y += 35.f;
		return ctx.drop_down_info.id != 0;
	}

	inline bool button( const wchar_t* name, std::function<void( )> cb, bool new_line = true )
	{
		point draw_pos = ctx.next_pos;
		draw_pos.y -= 3;
		draw_pos.x += 18;

		int width = ( ctx.parent_size.x - 56 ) / 2;
		int height = 25;
		bool hovered = input::hover( draw_pos + point( 0, 12 ), point( width, height ) );

		render::filled_rect( draw_pos + point( 0, 12 ), point( width, height ), color( 25, 25, 25 ) );
		render::rect( draw_pos + point( 0, 12 ) + 1, point( width, height ) - 2, ( hovered && ctx.blocking == 0 ) ? ctx.menu_color_nigger : color( 50, 50, 50 ) );
		render::rect( draw_pos + point( 0, 12 ), point( width, height ), color( 0, 0, 0 ) );

		render::text( draw_pos + point( 0, 12 ) + point( width / 2, height / 2 ), verdana10, font_dropshadow | font_centered_x | font_centered_y, color( 203, 203, 203 ), utils::split_str( name, '##' )[ 0 ].data( ) );

		if ( ctx.blocking == 0 )
		{
			if ( hovered && input::click( VK_LBUTTON ) )
				ctx.blocking = ::utils::crypto::hash( name );
		}
		else if ( ctx.blocking == ::utils::crypto::hash( name ) )
		{
			if ( hovered && input::release( VK_LBUTTON ) )
			{
				cb( );
				ctx.blocking = 0;
			}
		}

		if ( new_line )
		{
			ctx.next_pos.y += 35.f;
		}
		else
		{
			ctx.next_pos.x += width + 10;
		}

		return ctx.drop_down_info.id != 0;
	}

	inline bool numberbox( const wchar_t* name, int* value )
	{
		point draw_pos = ctx.next_pos;
		draw_pos.y -= 3;
		draw_pos.x += 18;

		render::text( draw_pos + point( -2, 0 ), verdana10, font_dropshadow, color( 153, 153, 153 ), utils::split_str( name, '##' )[ 0 ].data( ) );
		draw_pos.y += 3;

		// nie pytaj
		static std::vector<char> chrs = {
			'_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_',
			'_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_',
			'_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_',
			'_', '_', '_', '_', '_', '_', '_', '_', '_', '0', '1', '2', '3',
			'4', '5', '6', '7', '8', '9'
		};

		static int preview{ };

		std::string temp = std::to_string( preview );

		int width = ctx.parent_size.x - 46;
		int height = 18;
		bool hovered = input::hover( draw_pos + point( 0, 12 ), point( width, height ) );

		bool typing = ctx.blocking == ::utils::crypto::hash( name );
		ctx.typing = typing;

		render::filled_rect( draw_pos + point( 0, 12 ), point( width, height ), color( 25, 25, 25 ) );
		render::rect( draw_pos + point( 0, 12 ) + 1, point( width, height ) - 2, ( hovered && !typing ) || typing ? ctx.menu_color_nigger : color( 50, 50, 50 ) );
		render::rect( draw_pos + point( 0, 12 ), point( width, height ), color( 0, 0, 0 ) );

		std::string print = typing ? ( preview == 0 ? "_" : temp + "_" ) : ( *value == 0 ? "" : std::to_string( *value ) );
		render::text( draw_pos + point( 0, 12 ) + point( 6, height / 2 ), verdana10, font_dropshadow | font_centered_y, color( 153, 153, 153 ), std::wstring( print.begin( ), print.end( ) ).data( ) );

		if ( ctx.blocking == 0 )
		{
			preview = *value;

			if ( hovered && input::click( VK_LBUTTON ) )
			{
				ctx.blocking = ::utils::crypto::hash( name );
				ctx.typing = true;
			}
		}
		else if ( ctx.blocking == ::utils::crypto::hash( name ) )
		{
			if ( input::click( VK_LBUTTON ) && !hovered )
			{
				ctx.blocking = 0;
				*value = preview;
			}

			for ( int i = 0; i < chrs.size( ); i++ )
			{
				if ( input::click( i ) )
				{
					if ( i == VK_ESCAPE || i == VK_RETURN )
					{
						ctx.blocking = 0;
						*value = preview;
					}
					if ( i != VK_BACK )
					{
						if ( chrs[ i ] != '_' && temp.size( ) < 3 )
						{
							temp.push_back( chrs[ i ] );
						}
					}
					else if ( temp.length( ) > 0 )
					{
						temp.pop_back( );
					}

					if ( temp.size( ) > 3 )
						temp.resize( 3 );
				}
			}

			preview = std::atof( temp.data( ) );
		}

		ctx.next_pos.y += 35.f;
		return *value > 0;
	}

	inline void end( )
	{
		if ( ctx.drop_down_info.id != 0 )
		{
			point pos = ctx.drop_down_info.pos + point( 0, 3 );
			int width = ctx.drop_down_info.width;

			for ( int i = 0; i < ctx.drop_down_info.option_count; i++ )
			{
				point option_pos = pos + point( 0, 20 * i );
				point option_size = point( width, 20 );

				if ( input::hover( option_pos, option_size ) )
				{
					render::filled_rect( option_pos, option_size, { 25, 25, 25 } );
					if ( input::click( VK_LBUTTON ) )
					{
						*ctx.drop_down_info.value = i;
						ctx.drop_down_info.id = 0;
						ctx.blocking = 0;
					}
				}
				else
				{
					render::filled_rect( option_pos, option_size, { 35, 35, 35 } );
				}

				if ( *ctx.drop_down_info.value != i )
					render::text( option_pos + point( 10, 4 ), verdana10, 0, color( 200, 200, 200 ), ctx.drop_down_info.options[ i ] );
				else
					render::text( option_pos + point( 10, 4 ), verdana10, 0, color( 200, 200, 200 ), ctx.drop_down_info.options[ i ] );
			}

			render::rect( ctx.drop_down_info.pos + point( 0, 3 ),
						  point( ctx.drop_down_info.width, 20 * ctx.drop_down_info.option_count ),
						  { 50, 50, 50 } );

			if ( input::click( VK_LBUTTON ) )
			{
				ctx.drop_down_info.id = 0;
				ctx.blocking = 0;
			}
		}

		static float color_picker_hue = -1.f;

		if ( ctx.color_picker_info.id != 0 )
		{
			point pos = ctx.color_picker_info.pos;
			color c = *ctx.color_picker_info.c;

			hsv v1 = rgb2hsv( c );

			float new_hue;

			if ( color_picker_hue == -1.f )
			{
				new_hue = v1.hue;
				color_picker_hue = new_hue;
			}
			else
				new_hue = color_picker_hue;
			float new_sat = v1.sat;
			float new_val = v1.val;
			float new_alpha = c.a;

			bool main_hovered = input::hover( pos, point( 178, 174 ) );

			render::filled_rect( pos + 1, point( 178, 174 - ( ctx.color_picker_info.has_alpha ? 0 : 12 ) ) - 1, color( 40, 40, 40 ) );
			render::rect( pos, point( 178, 174 - ( ctx.color_picker_info.has_alpha ? 0 : 12 ) ), color( 10, 10, 10 ) );
			render::rect( pos + 1, point( 178, 174 - ( ctx.color_picker_info.has_alpha ? 0 : 12 ) ) - 2, color( 60, 60, 60 ) );

			render::gradient_h( pos + 6, point( 151, 151 ), color( 255, 255, 255 ), hsv2rgb( new_hue, 1, 1 ), 255, 0 );

			interfaces::surface->set_drawing_color( 0, 0, 0 );
			interfaces::surface->filled_rect_fade( ( pos + 6 ).x, ( pos + 6 ).y, ( ( pos + 6 ) + point( 151, 151 ) ).x, ( ( pos + 6 ) + point( 151, 151 ) ).y, 0, 255, false );
			interfaces::surface->filled_rect_fade( ( pos + 6 ).x, ( pos + 6 ).y, ( ( pos + 6 ) + point( 151, 151 ) ).x, ( ( pos + 6 ) + point( 151, 151 ) ).y, 0, 160, false );

			//render::gradient_v(pos + 6, point(151, 151), color(0, 0, 0, 0), color(0, 0, 0), 255, 0);

			render::rect( pos + 5, point( 152, 152 ), color( 10, 10, 10 ) );

			point cursor_delta = input::cursor_pos - ( pos + 5 );

			bool hovered = input::hover( pos + 5, point( 152, 152 ) );


			if ( hovered && input::hold( VK_LBUTTON ) )
			{
				float s = ( float )cursor_delta.x / 150.f;
				float v = 1.f - ( float )cursor_delta.y / 150.f;

				new_sat = s;
				new_val = v;
			}

			point rect_pos;

			rect_pos.x = 150 * v1.sat;
			rect_pos.y = 150 * ( 1.f - v1.val );

			render::rect( pos + 5 + rect_pos + 1 - 2, point( 4, 4 ), color( 10, 10, 10 ) );

			point pos2 = pos + 5 + point( 155, 0 );

			for ( int i = 0; i < 152; i++ )
			{
				float xd = ( ( float )i / 152.f ) * 360.f;
				color d = hsv2rgb( xd, 1, 1 );

				render::line( pos2 + point( 0, i ), pos2 + point( 13, i ), d );

				bool hoverniger = input::hover( pos2 + point( 0, i ), point( 13, 2 ) );
				if ( hoverniger && input::hold( VK_LBUTTON ) )
				{
					new_hue = xd;
					color_picker_hue = xd;
				}
			}

			int gowno_height = ( new_hue / 360.f ) * 152;
			render::rect( point( pos2.x + 1, pos2.y + gowno_height ), point( 11, 3 ), color( 10, 10, 10 ) );

			render::rect( pos2, point( 13, 152 ), color( 10, 10, 10 ) );

			// autism 6000000)% im tired omg someone clean this shit up

			point pos3 = pos + 4 + point( 2, 155 );

			if ( ctx.color_picker_info.has_alpha )
			{
				render::filled_rect( pos3, point( 150, 10 ), color( 255, 255, 255, new_alpha ) );
				render::rect( pos3, point( 150, 10 ), color( 10, 10, 10 ) );

				if ( input::hold( VK_LBUTTON ) && input::hover( pos3, point( 150, 10 ) ) )
				{
					int delta_left = ( input::cursor_pos - pos3 ).x;
					new_alpha = ( ( float )delta_left / 150.f ) * 255;
				}

				int retard_x = ( ( float )new_alpha / 255.f ) * 150;

				render::rect( pos3 + point( retard_x - 2, 0 ), point( 4, 10 ), color( 10, 10, 10 ) );
			}
			else
			{
				new_alpha = 255;
			}

			if ( input::hold( VK_LBUTTON ) )
			{
				auto new_c = hsv2rgb( new_hue, new_sat, new_val );;
				//gg
				new_c.a = new_alpha > 250 ? 255 : ( new_alpha < 10 ? 0 : new_alpha );
				*ctx.color_picker_info.c = new_c;//config->set(ctx->color_picker_info.var_name, hsv2rgb(new_hue, new_sat, new_val).alpha(new_alpha) /* wow this is useful lol */);
			}
			if ( input::click( VK_LBUTTON ) && !main_hovered )
			{
				ctx.blocking = 0;
				ctx.color_picker_info.id = 0;
			}
		}
		else
		{
			color_picker_hue = -1.f;
		}
	}

	inline int gui_init;
	static int gui_tab;
	extern void gui_interface();
}