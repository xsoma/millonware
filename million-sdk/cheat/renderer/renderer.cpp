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

#include "renderer.hpp"

namespace render
{
	std::vector<c_texture*> textures;
	std::vector<c_font*> fonts;

	void set_clip( point_t pos, point_t size )
	{
		interfaces::surface->set_clip( pos.x, pos.y, pos.x + size.x, pos.y + size.y );
	}

	void rect( point_t pos, point_t size, color_t c )
	{
		interfaces::surface->set_drawing_color( c.r, c.g, c.b, c.a );
		interfaces::surface->draw_outlined_rect( pos.x, pos.y, pos.x + size.x, pos.y + size.y );
	}																									

	void filled_rect( point_t pos, point_t size, color_t c )
	{
		interfaces::surface->set_drawing_color( c.r, c.g, c.b, c.a );
		interfaces::surface->draw_filled_rectangle( pos.x, pos.y, pos.x + size.x, pos.y + size.y );
	}

	void line( point_t a, point_t b, color_t c )
	{
		interfaces::surface->set_drawing_color( c.r, c.g, c.b, c.a );
		interfaces::surface->draw_line( a.x, a.y, b.x, b.y );
	}

	point_t text_size( const wchar_t* text, int font_id )
	{
		if ( fonts[ font_id ] )
			return fonts[ font_id ]->get_text_size( text );

		return point_t( 0, 0 );
	}

	void reset_clip( )
	{
		interfaces::surface->reset_clip( );
	}

	void init( )
	{
	}

	void destroy( )
	{
		for ( const auto texture : textures )
			texture->destroy( );

		for ( const auto font : fonts )
			font->destory( );
	}

	bool c_font::is_valid( )
	{
		return m_font_id != -1;
	}

	void c_font::init( std::string_view font_name, int size, int weight, int flags )
	{
		m_font_id = interfaces::surface->font_create( );

		interfaces::surface->set_font_glyph( m_font_id, font_name.data( ), size, weight, 0, 0, flags );
	}

	void c_font::draw_text( point_t pos, color_t c, const wchar_t* text )
	{
		if ( is_valid( ) )
		{
			interfaces::surface->draw_text_font( m_font_id );
			interfaces::surface->draw_text_pos( pos.x, pos.y );
			interfaces::surface->set_text_color( c.r, c.g, c.b, c.a );
			interfaces::surface->draw_render_text( text, wcslen( text ) );
		}
	}

	point_t c_font::get_text_size( const wchar_t* text )
	{
		int w, h;
		interfaces::surface->get_text_size( m_font_id, text, w, h );
		return point_t( w, h );
	}

	void c_font::destory( )
	{
		m_font_id = -1;
	}

	bool c_texture::is_valid( )
	{
		return interfaces::surface->is_texture_id_valid( m_texture_id );
	}

	void c_texture::init( std::vector<uint8_t> _bytes, int _width, int _height )
	{
		m_bytes = _bytes;
		m_width = _width;
		m_height = _height;

		m_texture_id = interfaces::surface->create_new_texture_id( true );
		interfaces::surface->set_texture_rgba( m_texture_id, m_bytes.data( ), m_width, m_height );
	}

	void c_texture::destroy( )
	{
		if ( interfaces::surface->is_texture_id_valid( m_texture_id ) )
			interfaces::surface->delete_texture_by_id( m_texture_id );
	}

	void c_texture::draw( int x, int y, int w, int h )
	{
		interfaces::surface->set_drawing_color( 255, 255, 255, 255 );
		interfaces::surface->set_texture( m_texture_id );
		if ( w == 0 )
			w = m_width;

		if ( h == 0 )
			h = m_height;

		interfaces::surface->draw_textured_rect( x, y, x + w, y + h );
		interfaces::surface->set_texture( 0 );
	}

	void texture( int texture_id, point_t pos )
	{
		if ( textures[ texture_id ] )
			textures[ texture_id ]->draw( pos.x, pos.y );
	}

	void gradient_h( point pos, point size, color a, color b, int alpha1 = 255, int alpha2 = 0 )
	{
		interfaces::surface->set_drawing_color( a.r, a.g, a.b );
		interfaces::surface->filled_rect_fade( pos.x, pos.y, pos.x + size.x, pos.y + size.y, alpha1, alpha2, true );
		interfaces::surface->set_drawing_color( b.r, b.g, b.b );
		interfaces::surface->filled_rect_fade( pos.x, pos.y, pos.x + size.x, pos.y + size.y, alpha2, alpha1, true );

		/*filled_rect(pos, size, a);
		int first = b.r;
		int second = b.g;
		int third = b.b;
		float fw = size.x;
		for (int i = 0; i < size.x; i++)
		{
			float fi = i;
			float a = fi / fw;
			int ia = a * 255;
			filled_rect(point(pos.x + i, pos.y), point(1, size.y), color(first, second, third, ia));
		}*/
	}

	void gradient_v( point pos, point size, color a, color b, int alpha1 = 255, int alpha2 = 0 )
	{
		interfaces::surface->set_drawing_color( a.r, a.g, a.b );
		interfaces::surface->filled_rect_fade( pos.x, pos.y, pos.x + size.x, pos.y + size.y, alpha1, alpha2, false );
		interfaces::surface->set_drawing_color( b.r, b.g, b.b );
		interfaces::surface->filled_rect_fade( pos.x, pos.y, pos.x + size.x, pos.y + size.y, alpha2, alpha1, false );
	}

	void circle( point_t center, float radius, float points, bool filled, color_t c )
	{
		static bool once = true;

		static std::vector<float> temppointsx;
		static std::vector<float> temppointsy;

		if ( once )
		{
			float step = ( float )utils::math::pi * 2.0f / points;
			for ( float a = 0; a < ( utils::math::pi * 2.0f ); a += step )
			{
				temppointsx.push_back( cosf( a ) );
				temppointsy.push_back( sinf( a ) );
			}
			once = false;
		}

		std::vector<int> pointsx;
		std::vector<int> pointsy;
		std::vector<vertex_t> vertices;

		for ( int i = 0; i < temppointsx.size( ); i++ )
		{
			float x = radius * temppointsx[ i ] + center.x;
			float y = radius * temppointsy[ i ] + center.y;
			pointsx.push_back( x );
			pointsy.push_back( y );

			vertices.push_back( vertex_t( vec2_t( x, y ) ) );
		}

		static int texture_id = interfaces::surface->create_new_texture_id( true );
		static unsigned char buf[ 4 ] = { 255, 255, 255, 255 };

		if ( filled )
		{
			interfaces::surface->set_drawing_color( c.r, c.g, c.b, c.a );
			interfaces::surface->set_texture( texture_id );
			interfaces::surface->draw_polygon( points, vertices.data( ) );
		}

		interfaces::surface->set_drawing_color( c.r, c.g, c.b, c.a );
		interfaces::surface->draw_poly_line( pointsx.data( ), pointsy.data( ), points );
	}
};