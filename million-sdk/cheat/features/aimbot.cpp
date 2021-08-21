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

#include "aimbot.hpp"

#include "../../engine/utilities/config.hpp"
#include "../../engine/utilities/xorstring.hpp"
#include "../input/input.hpp"
#include "bt.hpp"

#include <random>

std::pair<int, bool> aimbot::get_active_weapon_type( ) {

	player_t* local = interfaces::entity_list->get<player_t>( interfaces::engine->get_local_player( ) );
	if ( !local ) {
		return std::make_pair( 0, false );
	}

	const auto active_weapon = local->active_weapon( );

	if ( !active_weapon ) {
		return std::make_pair( 0, false );
	}

	const auto econ_idx = reinterpret_cast< econ_view_item_t* >( active_weapon )->item_definition_index( );
	const auto data = interfaces::weapon_system->get_weapon_data( econ_idx );
	if ( !data ) {
		return std::make_pair( 0, false );
	}

	auto type = data->type;

	const auto weapon_type = data->item_definition_index( );

	if ( weapon_type == weapon_awp || weapon_type == weapon_scout || weapon_type == weapon_scar20 || weapon_type == weapon_g3sg1 )
		type = 6;

	return std::make_pair( type, weapon_type == weapon_deagle || weapon_type == weapon_revolver );
}

template<class T>
__forceinline T get_aimbot_config( const char* bruh )
{
	auto nice = [ ]( )-> const char*
	{
		switch ( aimbot::get_active_weapon_type( ).first )
		{
		case 2: return aimbot::get_active_weapon_type( ).second ? ":heavy_pistol" : ":pistol"; break;
		case 4: case 7: return ":rifle"; break;
		case 5: return ":other"; break;
		case 6: return ":sniper"; break;
		case 3: return ":smg"; break;
		}
	};

	// whoever made this is a nigger -paracord
	return *config::get<T>( crc( std::string{ bruh }.append( nice( ) ).c_str( ) ) );
}

int aimbot::find_target( const vec2_t& recoil ) {

	player_t* local = interfaces::entity_list->get<player_t>( interfaces::engine->get_local_player( ) );
	if ( !local )
	{
		return -1;
	}

	player_t* target = nullptr;
	float m_flFov = get_aimbot_config<float>( xor ( "ass:aimbot:fov" ) );

	vec3_t angle =
		interfaces::engine->get_view_angles( );

	angle.x += recoil.x;
	angle.y += recoil.y;

	for ( int32_t i = 1; i <= interfaces::globals->max_clients; i++ ) {

		auto ent = interfaces::entity_list->get<player_t>( i );

		if ( !ent )
			continue;

		if ( !ent->sane( true ) )
			continue;

		if ( ent->team( ) == local->team( ) )
			continue;

		matrix_t bones[ 128 ];
		if ( !ent->setup_bones( bones, 128, bone_used_by_hitbox, 0.f ) )
			continue;

		vec3_t m_vecHitbox = ent->hitbox_pos( find_hitbox( ent ), bones );

		if ( !local->can_see( ent, m_vecHitbox ) )	{
			continue;
		}

		float m_flTemp = utils::math::get_fov( angle, utils::math::calc_angle( local->eye_pos( ), m_vecHitbox ) );

		if ( m_flFov > m_flTemp ) {
			target = ent;
			m_flFov = m_flTemp;
		}
	}

	if ( target )
		return target->index( );
	else
		return -1;
}

int aimbot::find_hitbox( player_t* player )
{
	player_t* local = interfaces::entity_list->get<player_t>( interfaces::engine->get_local_player( ) );
	if ( !local || !player ) {
		return -1;
	}

	if ( !local->active_weapon( ) )	{
		return -1;
	}

	const auto cfg_hitbox = get_aimbot_config<int>( xor ( "ass:aimbot:hitbox" ) );

	return cfg_hitbox == 2 ? hitbox_chest : cfg_hitbox;
}

int aimbot::aimbot_target = -1;

void aimbot::run( c_usercmd* cmd )
{
	// cache the local player as a global variable instead of getting it 1000 times everywhere -paracord
	player_t* local = interfaces::entity_list->get<player_t>( interfaces::engine->get_local_player( ) );

	if ( !local ) {
		return;
	}

	if ( !local->active_weapon( ) )	{
		return;
	}

	if ( !local->active_weapon( )->weapon_data( ) )	{
		return;
	}

	bool rcs = get_aimbot_config<bool>( xor ( "ass:aimbot:rcs:enabled" ) );
	bool standalone = get_aimbot_config<bool>( xor ( "ass:aimbot:rcs:standalone" ) );

	vec2_t recoil_angle{};

	if ( rcs )	{
		const auto recoil_scale = interfaces::console->get_convar( "weapon_recoil_scale" )->get_float( );
		const auto aim_punch = local->aim_punch_angle( ) * 2.f;

		const auto rcs_x = get_aimbot_config<float>( xor ( "ass:aimbot:rcs:x" ) ) / 100.f;
		const auto rcs_y = get_aimbot_config<float>( xor ( "ass:aimbot:rcs:y" ) ) / 100.f;

		recoil_angle =
		{
			aim_punch.x * ( recoil_scale * rcs_x / 2),
			aim_punch.y * ( recoil_scale * rcs_y / 2)
		};
	}

	const auto weapon_type = get_active_weapon_type( ).first;

	if ( rcs && standalone && ( weapon_type == 4 || weapon_type == 7 || weapon_type == 3 ) ) {
		cmd->view_angles.x -= recoil_angle.x;
		cmd->view_angles.y -= recoil_angle.y;
	}

	if ( aimbot_target == -1 )
		aimbot_target = find_target( recoil_angle );

	if ( aimbot_target == -1 )
		return;

	player_t* ent = interfaces::entity_list->get<player_t>( aimbot_target );
	matrix_t bones[ 128 ];

	if ( !ent->sane( true ) || !ent || ent->team( ) == local->team( ) || !ent->setup_bones( bones, 128, bone_used_by_hitbox, 0.f ) )	{
		aimbot_target = -1;
		return;
	}

	if ( !local->can_see( ent, ent->hitbox_pos( find_hitbox( ent ), bones ) ) )	{
		aimbot_target = -1;
		return;
	}

	vec3_t hitbox = ent->hitbox_pos( find_hitbox( ent ), bones );
	vec3_t m_angPoint = utils::math::calc_angle( local->eye_pos( ), hitbox );

	// call before smoothing so the rcs gets smoothed later!!
	if ( rcs && !standalone && ( weapon_type == 4 || weapon_type == 7 || weapon_type == 3 ) )	{
		m_angPoint.x -= recoil_angle.x;
		m_angPoint.y -= recoil_angle.y;
	}

	if ( get_aimbot_config<bool>( xor ( "ass:aimbot:smoothing:enabled" ) ) )	{
		utils::math::smooth_angle( m_angPoint, get_aimbot_config<float>( xor ( "ass:aimbot:smoothing:value" )) * 2 , interfaces::engine->get_view_angles( ) );
	}

	m_angPoint.normalize( );
	m_angPoint.clamp( );

	auto is_aimbotting = [ cmd ]( ) -> bool	{
		if ( !get_aimbot_config<bool>( xor ( "ass:aimbot:key:enabled" ) ) )		{
			return cmd->buttons & in_attack;
		}
		else {
			return input::hold( get_aimbot_config<int>( xor ( "ass:aimbot:key:value" ) ) );
		}
	};

	if ( is_aimbotting( ) )	{
		cmd->view_angles = m_angPoint;
		interfaces::engine->set_view_angles( cmd->view_angles );
	}
	else {
		aimbot_target = -1;
	}
}