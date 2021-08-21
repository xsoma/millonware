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

#include "nade_prediction.hpp"
#include "../../engine/utilities/config.hpp"
#include "../../cheat/renderer/renderer.hpp"

c_nade_prediction nade_pred;

//credits :)
//https://github.com/EternityX/DEADCELL-CSGO/blob/master/csgo/features/nade_pred/nade_pred.cpp

void c_nade_prediction::predict( c_usercmd* user_cmd ) noexcept
{
	if ( !interfaces::engine->is_connected( ) && !interfaces::engine->is_in_game( ) )
		return;

	auto local_player = reinterpret_cast< player_t* >( interfaces::entity_list->get_client_entity( interfaces::engine->get_local_player( ) ) );
	//	readability
	constexpr float restitution = 0.45f;
	constexpr float power[ ] = { 1.0f, 1.0f, 0.5f, 0.0f };
	constexpr float velocity = 403.0f * 0.9f;

	float step, gravity, new_velocity, unk01;
	int index{}, grenade_act{ 1 };
	vec3_t pos, thrown_direction, start, eye_origin;
	vec3_t angles, thrown;

	//	first time setup
	static auto sv_gravity = interfaces::console->get_convar( "sv_gravity" );

	//	calculate step and actual gravity value
	gravity = sv_gravity->get_float( ) / 8.0f;
	step = interfaces::globals->interval_per_tick;

	//	get local view and eye origin
	eye_origin = local_player->eye_pos( );
	angles = user_cmd->view_angles;

	//	copy current angles and normalise pitch
	thrown = angles;

	if ( thrown.x < 0 )
	{
		thrown.x = -10 + thrown.x * ( ( 90 - 10 ) / 90.0f );
	}
	else
	{
		thrown.x = -10 + thrown.x * ( ( 90 + 10 ) / 90.0f );
	}

	//	find out how we're throwing the grenade
	auto primary_attack = user_cmd->buttons & in_attack;
	auto secondary_attack = user_cmd->buttons & in_attack2;

	if ( primary_attack && secondary_attack )
	{
		grenade_act = ACT_LOB;
	}
	else if ( secondary_attack )
	{
		grenade_act = ACT_DROP;
	}

	//	apply 'magic' and modulate by velocity
	unk01 = power[ grenade_act ];

	unk01 = unk01 * 0.7f;
	unk01 = unk01 + 0.3f;

	new_velocity = velocity * unk01;

	//	here's where the fun begins
	utils::math::angle_vectors( thrown, &thrown_direction );

	start = eye_origin + thrown_direction * 16.0f;
	thrown_direction = ( thrown_direction * new_velocity ) + local_player->velocity( );

	//	let's go ahead and predict
	for ( auto time = 0.0f; index < 500; time += step )
	{

		pos = start + thrown_direction * step;
		trace_t trace;
		ray_t ray;
		trace_filter_skip_one_entity filter( local_player );

		ray.initialize( start, pos );
		interfaces::trace->trace_ray( ray, MASK_SOLID, &filter, &trace );

		//	modify path if we have hit something
		if ( trace.flFraction != 1.0f )
		{
			thrown_direction = trace.plane.normal * -2.0f * thrown_direction.dot( trace.plane.normal ) + thrown_direction;

			thrown_direction *= restitution;

			pos = start + thrown_direction * trace.flFraction * step;

			time += ( step * ( 1.0f - trace.flFraction ) );
		}

		//	check for detonation
		auto detonate = detonated( local_player->active_weapon( ), time, trace );

		//	emplace nade point
		_points.at( index++ ) = c_nadepoint( start, pos, trace.flFraction != 1.0f, true, trace.plane.normal, detonate );
		start = pos;

		//	apply gravity modifier
		thrown_direction.z -= gravity * trace.flFraction * step;

		if ( detonate )
		{
			break;
		}
	}

	//	invalidate all empty points and finish prediction
	for ( auto n = index; n < 500; ++n )
	{
		_points.at( n ).m_valid = false;
	}

	_predicted = true;
}

bool c_nade_prediction::detonated( weapon_t* weapon, float time, trace_t& trace )noexcept
{

	if ( !weapon )
	{
		return true;
	}

	//	get weapon item index
	const auto index = *weapon->item_definition_index( );

	switch ( index )
	{
		//	flash and HE grenades only live up to 2.5s after thrown
	case weapon_hegrenade:
	case weapon_flashbang:
	if ( time > 2.5f )
	{
		return true;
	}
	break;

	//	fire grenades detonate on ground hit, or 3.5s after thrown
	case weapon_molotov:
	case weapon_incgrenade:
	if ( trace.flFraction != 1.0f && trace.plane.normal.z > 0.7f || time > 3.5f )
	{
		return true;
	}
	break;

	//	decoy and smoke grenades were buggy in prediction, so i used this ghetto work-around
	case weapon_decoy:
	case weapon_smokegrenade:
	if ( time > 5.0f )
	{
		return true;
	}
	break;
	}

	return false;
}

void c_nade_prediction::trace( c_usercmd* user_cmd ) noexcept
{
	if ( !interfaces::engine->is_connected( ) && !interfaces::engine->is_in_game( ) )
		return;


	auto local_player = reinterpret_cast< player_t* >( interfaces::entity_list->get_client_entity( interfaces::engine->get_local_player( ) ) );

	if ( !*config::get<bool>( crc( "misc:nade_pred2" ) ) )
	{
		return;
	}

	if ( !( user_cmd->buttons & in_attack ) && !( user_cmd->buttons & in_attack2 ) )
	{
		_predicted = false;
		return;
	}

	const static std::vector< int > nades{
		weapon_flashbang,
		weapon_smokegrenade,
		weapon_hegrenade,
		weapon_molotov,
		weapon_decoy,
		weapon_incgrenade
	};

	//	grab local weapon
	auto weapon = local_player->active_weapon( );

	if ( !weapon )
	{
		return;
	}

	if ( std::find( nades.begin( ), nades.end( ), *weapon->item_definition_index( ) ) != nades.end( ) )
	{
		return predict( user_cmd );
	}

	_predicted = false;
}

void c_nade_prediction::draw( ) noexcept
{
	if ( !interfaces::engine->is_connected( ) && !interfaces::engine->is_in_game( ) )
		return;

	auto local_player = reinterpret_cast< player_t* >( interfaces::entity_list->get_client_entity( interfaces::engine->get_local_player( ) ) );
	if ( !local_player )
	{
		return;
	}

	if ( !*config::get<bool>( crc( "misc:nade_pred2" ) ) )
	{
		return;
	}

	if ( !interfaces::engine->is_in_game( ) )
	{
		return;
	}

	if ( !local_player->alive( ) )
	{
		return;
	}

	//auto draw_3d_dotted_circle = [ ]( vec3_t position, float points, float radius ) {
	//	float step = 3.141592654f * 2.0f / points;
	//	for ( float a = 0; a < 3.141592654f * 2.0f; a += step )
	//	{
	//		vec3_t start( radius * cosf( a ) + position.x, radius * sinf( a ) + position.y, position.z );
	//
	//		point_t start2d;
	//		if ( interfaces::debug_overlay->world_to_screen( start, start2d ) )
	//			render::line( start2d, { start2d.x + 1, start2d.y + 1 }, color( 255, 255, 255 ) );
	//	}
	//};

	point_t start, end;

	//	draw nade path
	if ( _predicted )
	{
		for ( auto& p : _points )
		{
			if ( !p.m_valid )
			{
				break;
			}

			if ( interfaces::debug_overlay->world_to_screen( p.m_start, start ) && interfaces::debug_overlay->world_to_screen( p.m_end, end ) )
			{

				render::line( start, end, color( 0, 125, 255 ) );

				if ( p.m_detonate || p.m_plane )
				{
					;
					render::rect( { start.x - 2, start.y - 2 }, { 5, 5 }, p.m_detonate ? color( 255, 0, 0 ) : color( 255, 255, 255 ) );
				}
			//	if ( p.m_detonate )
			//		draw_3d_dotted_circle( p.m_end, 100, 150 );
			}
		}
	}
}
