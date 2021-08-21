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

#include "fake_backwards.hpp"

#include "../renderer/renderer.hpp"

#include <algorithm>

#include "../../engine/utilities/config.hpp"
#include "../../engine/utilities/xorstring.hpp"
#include "../../engine/utilities/math.hpp"

#include "../input/input.hpp"

void fake_backwards::pre_move_fix( c_usercmd* cmd ) {
	angle_data.m_old_viewangle = cmd->view_angles;
	angle_data.m_old_forwardmove = cmd->forward_move;
	angle_data.m_old_sidemove = cmd->side_move;
}

void fake_backwards::post_move_fix( c_usercmd* cmd ) {
	const auto f1 = ( angle_data.m_old_viewangle.y < 0.f ) ? 360.f + angle_data.m_old_viewangle.y : angle_data.m_old_viewangle.y;
	const auto f2 = ( cmd->view_angles.y < 0.f ) ? 360.f + cmd->view_angles.y : cmd->view_angles.y;

	auto delta_view = ( f2 < f1 ) ? abs( f2 - f1 ) : 360.f - abs( f1 - f2 );
	delta_view = 360.f - delta_view;

	const auto delta_angle = utils::math::deg_to_rad( delta_view );
	const auto perpendicular_angle = delta_angle + 1.5707963268f; // 90 in radians ( pi / 2 )

	const auto backwards_angle_pitch = ( cos( delta_angle ) * angle_data.m_old_forwardmove ) + ( cos( perpendicular_angle ) * angle_data.m_old_sidemove );
	const auto backwards_angle_yaw = ( sin( delta_angle ) * angle_data.m_old_forwardmove ) + ( sin( perpendicular_angle ) * angle_data.m_old_sidemove );

	cmd->forward_move = backwards_angle_pitch;
	cmd->side_move = backwards_angle_yaw;
}

float fake_backwards::handle_turn( player_t* local ) {
	static float current_turn = 0.f;

	// calculate the turn speed based on frames
	// to make it look as legit as possible
	const float turn_speed = 180.f * ( ( ( *config::get<float>( crc( "misc:turn:turn_speed" ) ) / 100.f ) / 0.09f ) * interfaces::globals->frame_time );
	const float recover_speed = 180.f * ( ( ( *config::get<float>( crc( "misc:turn:recover_speed" ) ) / 100.f ) / 0.09f ) * interfaces::globals->frame_time );
	static bool can_recover = false;
	static bool recovered = false;
	static bool set_manual_angles = false;

	if ( local->move_type( ) == movetype_ladder || local->move_type( ) == movetype_noclip || local->is_scoped( ) ) {
		can_recover = true;

		// sorta like a force "recover and don't turn back"
		if ( recovered ) {
			angle_data.m_should_turn = false;
		}
	}

	if ( angle_data.m_should_turn && !angle_data.m_in_recovery && local->move_type( ) != movetype_ladder && local->move_type( ) != movetype_noclip && !local->is_scoped( ) ) {
		current_turn += turn_speed;

		if ( current_turn > 180.f )	{
			current_turn = 180.f;

			set_manual_angles = false;
			recovered = false;
			can_recover = true;
		}
	}
	else {
		if ( *config::get<bool>( crc( "misc:turn:manual_recovery" ) ) && !set_manual_angles ) {
			vec3_t angles( interfaces::engine->get_view_angles( ).x, interfaces::engine->get_view_angles( ).y + current_turn, 0.f );

			interfaces::engine->set_view_angles( angles );
			current_turn = 0.f;

			set_manual_angles = true;
			recovered = true;
		}
		else {
			if ( !recovered && can_recover ) {
				angle_data.m_in_recovery = true;
				current_turn += recover_speed;

				if ( current_turn > 360.f )	{
					current_turn = 0.f;

					recovered = true;
					angle_data.m_in_recovery = false;
				}
			}
			else {
				if ( *config::get<bool>( crc( "misc:turn:manual_recovery" ) ) )	{
					current_turn -= recover_speed;

					if ( current_turn < 0.f ) {
						current_turn = 0.f;
					}

					vec3_t angles( interfaces::engine->get_view_angles( ).x, interfaces::engine->get_view_angles( ).y + current_turn, 0.f );

					interfaces::engine->set_view_angles( angles );
					current_turn = 0.f;

					recovered = true;
				}
				else  {
					current_turn -= recover_speed;

					if ( current_turn < 0.f ) {
						current_turn = 0.f;
					}
				}
			}
		}
	}

	if ( !*config::get<bool>( crc( "misc:turn:manual_recovery" ) ) ) {
		if ( angle_data.m_in_recovery && !recovered ) {
			if ( current_turn > 360.f ) {
				current_turn = 0.f;
				recovered = true;
			}
		}
	}
	static float old_turn = current_turn;
	if ( old_turn != current_turn )	{
		fake_backwards::angle_data.m_last_activity = interfaces::globals->cur_time;
		old_turn = current_turn;
	}

	return current_turn;
}

void fake_backwards::run( c_usercmd* cmd ) {

	if ( !*config::get<bool>( crc( "misc:turn:enabled" ) ) || !cmd ) {
		return;
	}

	auto local = interfaces::entity_list->get<player_t>( interfaces::engine->get_local_player( ) );
	if ( !local || !local->alive( ) ) {
		return;
	}

	cmd->view_angles.y += handle_turn( local );

	angle_data.m_current_turn = cmd->view_angles.y;

	if ( angle_data.m_should_turn )	{
		// fix the buttons
		if ( cmd->buttons & in_moveleft ) {
			cmd->buttons &= ~in_moveleft;
			cmd->buttons |= in_moveright;
		}

		if ( cmd->buttons & in_moveright ) {
			cmd->buttons &= ~in_moveright;
			cmd->buttons |= in_moveleft;
		}

		// fix the leg slide
		if ( local->move_type( ) != movetype_ladder && local->move_type( ) != movetype_noclip && !local->is_scoped( ) )	{
			cmd->buttons &= ~( in_forward | in_back | in_moveright | in_moveleft );
		}
	}
}

void fake_backwards::visualise( )
{
	if ( !*config::get<bool>( crc( "misc:turn:enabled" ) ) || !*config::get<bool>( crc( "misc:turn:indicator" ) ) )
	{
		return;
	}

	auto local = interfaces::entity_list->get<player_t>( interfaces::engine->get_local_player( ) );
	if ( !local || !local->alive( ) )
	{
		return;
	}

	auto get_rotated_position = [ & ]( point_t start, const float rotation, const float distance )-> point_t
	{
		const auto rad = rotation * ( utils::math::pi / 180.f );
		start.x += cosf( rad ) * distance;
		start.y += sinf( rad ) * distance;

		return start;
	};

	static float alpha_multiplier = 1.f;
	int current_turn = int( ( ( angle_data.m_current_turn - angle_data.m_old_viewangle.y ) / 180.f ) * 100.f );
	int final_turn = current_turn > 100 ? 100 - ( current_turn - 100 ) : current_turn;

	// bandaid fix for jitter -_-
	final_turn = final_turn > 98 ? 100 : final_turn;

	if ( *config::get<bool>( crc( "misc:turn:indicator_always" ) ) )
	{
		alpha_multiplier = 1.f;
	}
	else
	{
		if ( fabs( interfaces::globals->cur_time - angle_data.m_last_activity ) < 7.f )
		{
			alpha_multiplier += ( 1.0f / 0.25f ) * interfaces::globals->frame_time;
		}
		else
		{
			alpha_multiplier -= ( 1.0f / 0.5f ) * interfaces::globals->frame_time;
		}

		alpha_multiplier = std::clamp<float>( alpha_multiplier, 0.f, 1.f );
	}

	int x = 0, y = 0;

	interfaces::engine->get_screen_size( x, y );
	x /= 2;
	y /= 4;

	const auto buffer = std::make_unique<wchar_t[ ]>( 18 );
	swprintf( buffer.get( ), 16, L"turn: %d%%", final_turn );

	point_t text_size = render::text_size( buffer.get( ), other_indicators );

	render::text( point_t( x - ( text_size.x / 2 ), y - ( text_size.y / 2 ) ), other_indicators, font_outline,
				  color( 255, 255, 255, 180 * alpha_multiplier ), buffer.get( ) );

	point_t visualise_pos = point_t( ( ( x - ( text_size.x / 2 ) ) + ( text_size.x / 2 ) ) - 10, y - ( text_size.y * 2 ) );

	render::circle( visualise_pos, 25, 128, true, color( 25, 25, 25, 150 * alpha_multiplier ) );
	render::circle( visualise_pos, 25, 128, false, color( 255, 255, 255, 180 * alpha_multiplier ) );

	if ( angle_data.m_in_recovery )
	{
		render::line( visualise_pos, get_rotated_position( visualise_pos, ( 180.f * ( final_turn / 100.f ) ) - 90, 24.f ), color( 255, 255, 255, 180 * alpha_multiplier ) );
	}
	else
	{
		render::line( visualise_pos, get_rotated_position( visualise_pos, 180.f - ( 180.f * ( final_turn / 100.f ) ) + 90, 24.f ), color( 255, 255, 255, 180 * alpha_multiplier ) );
	}
}