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

#include "bt.hpp"
#include "../../engine/utilities/math.hpp"
#include "../../engine/utilities/config.hpp"

namespace backtrack
{
	std::vector<c_record> records[ 65 ];

	int max_backtrack_amount( )
	{
		static int max_record_size{};

		switch ( *config::get<int>( crc( "ass::backtrack::intensity" ) ) )
		{
		case 0: max_record_size = 4; break;
		case 1: max_record_size = 8; break;
		case 2: max_record_size = 12; break;
		}

		return max_record_size;
	}

	std::optional<c_record> find_last_record( int idx )
	{
		if ( records[ idx ].empty( ) )
		{
			return std::nullopt;
		}

		return std::make_optional( records[ idx ].back( ) );
	}

	void create_move( c_user_cmd* cmd, c_entity* local )
	{
		int closest = -1;
		float delta = FLT_MAX;

		auto view = cmd->view_angles;

		for ( int i = 1; i <= 64; i++ )
		{
			auto ent = ( interfaces::entity_list->get<player_t>( i ) );

			if ( !ent )
			{
				if ( !records[ i ].empty( ) )
				{
					records[ i ].clear( );
				}

				continue;
			}

			if ( !ent->health( ) )
			{
				if ( !records[ i ].empty( ) )
				{
					records[ i ].clear( );
				}

				continue;
			}

			if ( !*config::get<bool>( crc( "ass:backtrack" ) ) )
			{
				if ( !records[ i ].empty( ) )
				{
					records[ i ].clear( );
				}

				return;
			}

			records[ i ].insert( records[ i ].begin( ), c_record( cmd->tick_count, ent->bone_pos( 8 ), ent->abs_origin( ) ) );

			if ( records[ i ].size( ) > max_backtrack_amount( ) )
			{
				records[ i ].pop_back( );
			}

			if ( !ent->setup_bones( records[ i ].front( ).m_matrix, 128, bone_used_by_anything, 0.f ) )
			{
				continue;
			}

			auto fov = utils::math::get_fov( local->eye_pos( ), ent->eye_pos( ), view );
			if ( fov < delta )
			{
				closest = i;
				delta = fov;
			}
		}

		int index = 0;

		if ( closest != -1 )
		{
			for ( uint32_t i = 0; i < records[ closest ].size( ); i++ )
			{
				float fov = utils::math::get_fov( local->eye_pos( ), records[ closest ][ i ].m_headpos, view );

				if ( fov < delta )
				{
					index = i;
					delta = fov;
				}
			}

			if ( index && cmd->buttons & in_attack )
			{
				cmd->tick_count = records[ closest ].at( index ).m_tickcount;
			}
		}
	}
}
