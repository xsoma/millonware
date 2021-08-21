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

#include "netvars.hpp"
#include <sstream>
#include <iomanip>

#include "../utilities/xorstring.hpp"

netvar_manager g_netvar_mgr;

void netvar_manager::dump_table_recursive( recv_table* table )
{
	for ( auto i = 0; i < table->props_count; ++i )
	{
		auto prop = &table->props[ i ];

		if ( !prop || isdigit( prop->prop_name[ 0 ] ) )
			continue;
		if ( strcmp( prop->prop_name, xor ( "baseclass" ) ) == 0 )
			continue;

		if ( prop->prop_type == send_prop_type::_data_table && prop->data_table != nullptr && prop->data_table->table_name[ 0 ] == 'D' )
		{
			dump_table_recursive( prop->data_table );
		}

		std::string hash_string = table->table_name;
		hash_string.append( "->" );
		hash_string.append( prop->prop_name );

		netvars_map[ fnv_hash( hash_string.c_str( ) ) ] = prop;
	}
}

void netvar_manager::dump_table_to_file_recursive( recv_table* table )
{
	for ( auto i = 0; i < table->props_count; ++i )
	{
		auto prop = &table->props[ i ];

		if ( !prop || isdigit( prop->prop_name[ 0 ] ) )
			continue;
		if ( strcmp( prop->prop_name, xor ( "baseclass" ) ) == 0 )
			continue;

		if ( prop->prop_type == send_prop_type::_data_table && prop->data_table != nullptr && prop->data_table->table_name[ 0 ] == 'D' )
		{
			dump_table_to_file_recursive( prop->data_table );
		}

		std::string hash_string = table->table_name;
		hash_string.append( " -> " );
		hash_string.append( prop->prop_name );

		auto hash = fnv_hash( hash_string.c_str( ) );

		hash_string.append( xor ( " (" ) );
		hash_string.append( std::to_string( unsigned int( hash ) ) );
		hash_string.append( xor ( ") [" ) );
		std::stringstream stream;
		stream << xor ( "0x" )
			<< std::setfill( '0' ) << std::setw( sizeof( int ) * 2 )
			<< std::hex << prop->offset;
		hash_string.append( stream.str( ) );
		hash_string.append( xor ( "]" ) );

		printf( xor ( "%s\n" ), hash_string.data( ) );

		//file << hash_string << std::endl;
	}
}

void netvar_manager::init( client_class* client_data )
{
	for ( auto data = client_data; data; data = data->next_ptr )
	{
		if ( data->recvtable_ptr )
		{
			dump_table_recursive( data->recvtable_ptr );
		}
	}
}

void netvar_manager::dump_netvars( client_class* client_data )
{
	for ( auto data = client_data; data; data = data->next_ptr )
	{
		if ( data->recvtable_ptr )
		{
			dump_table_to_file_recursive( data->recvtable_ptr );
		}
	}
}

unsigned short netvar_manager::get_offset( unsigned int hash )
{
	if ( !netvars_map[ hash ] ) return 0;
	return netvars_map[ hash ]->offset;
}

recv_prop* netvar_manager::get_prop( unsigned int hash )
{
	return netvars_map[ hash ];
}