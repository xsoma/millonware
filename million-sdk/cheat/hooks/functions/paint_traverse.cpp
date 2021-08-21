#include "../hooks.hpp"
#include <cstdio>
#include <chrono>
#include <string.h>
#include <iomanip>
#include "../../renderer/renderer.hpp"
#include "../../input/input.hpp"
#include "../../gui/gui.hpp"
#include "../../../source engine/classes/c_usercmd.hpp"
#include "../../features/visuals.hpp"
#include "../../features/movement.hpp"
#include "../../features/jump_stats.hpp"
#include "../../features/misc.hpp"
#include "../../features/fake_backwards.hpp"
#include "../../features/hitmarkers.hpp"
#include "../../features/vel_graph.hpp"
#include "../../../global_ctx.hpp"
#include "../../features/walkbot.hpp"
#include "../../features/nade_prediction.hpp"

void __fastcall hooks::paint_traverse( void* ecx, void* edx, unsigned int vguiPanel, bool forceRepaint, bool allowForce )
{
	/*pt_hook.unhook( );
	const static auto ofunc = ( decltype( &paint_traverse ) )pt_hook.get_ofunc( );
	ofunc( ecx, edx, vguiPanel, forceRepaint, allowForce );
	pt_hook.rehook( );*/

	pt_holy_hook.call_original<decltype( &paint_traverse )>( ecx, edx, vguiPanel, forceRepaint, allowForce );

	//misc::change_server( );

	if ( !context::refreshed_fonts )
	{
		render::init( );
		context::refreshed_fonts = true;
	}

	static unsigned int focus_overlay_panel_id = 6969;
	if ( focus_overlay_panel_id == 6969 )
	{
		if ( strstr( interfaces::panel->get_panel_name( vguiPanel ), "FocusOverlayPanel" ) )
		{
			focus_overlay_panel_id = vguiPanel;
		}
	}

	if ( vguiPanel == focus_overlay_panel_id && context::refreshed_fonts )
	{
		input::update( );
		visuals::draw( );
		velocity_graph::draw( );
		movement::draw( );
		//walkbot::on_painttraverse();

		// xd
		static float last_time = GetTickCount64( ) * 0.001f;
		float cur_time = GetTickCount64( ) * 0.001f;
		float delta_time = cur_time - last_time;

		last_time = cur_time;

		static float anim_time = 0.f;
		static bool flip = false;

		if ( anim_time == 1.f || anim_time == 0.f )
		{
			flip = !flip;
		}

		anim_time = flip ? std::max< float >( anim_time - 0.69f * delta_time, 0.0f ) : std::min< float >( anim_time + 0.69f * delta_time, 1.0f );

		if ( *config::get<bool>( crc( "esp:misc:watermark" ) ) )
		{
			// calculate current time
			const auto current_time = std::chrono::duration_cast< std::chrono::seconds >( std::chrono::system_clock::now( ).time_since_epoch( ) ).count( );

			// divide by milliseconds in a second
			const auto expiration_time_seconds = context::user_info.sub_expiration / 1000;

			// divide by seconds in a day
			const auto days_remaining = static_cast< uint32_t >( ( expiration_time_seconds - current_time ) / 86400 );

			// idk
			char watermark[ 64 ]{ };
			if ( days_remaining >= 365 )
			{
				// xd
				sprintf( watermark, "%s | %s | lifetime", xor ( "millionware" ), context::user_info.username );
			}
			else if ( days_remaining >= 30 )
			{
				auto months = days_remaining / 30;
				sprintf( watermark, "%s | %s | %i %s left", xor ( "millionware" ), context::user_info.username, months, months > 1 ? "months" : "month" );
			}
			else
			{
				sprintf( watermark, "%s | %s | %i %s left", xor ( "millionware" ), context::user_info.username, days_remaining, days_remaining > 1 ? "days" : "day" );
			}

			wchar_t _watermark[ 64 ]{ };
			mbstowcs( _watermark, watermark, strlen( watermark ) );

			render::text( point( 5, 5 ), tahoma11, font_dropshadow,
						  color::blend( color( 255, 255, 255 ), color( 200, 200, 200 ), anim_time ), _watermark );

			render::filled_rect( point( 5, 5 + render::text_size( _watermark, tahoma11 ).y ), point( render::text_size( _watermark, tahoma11 ).x, 1 ),
								 color::blend( color( 255, 255, 255 ), color( 200, 200, 200 ), anim_time ) );

			render::filled_rect( point( 5, 5 + render::text_size( _watermark, tahoma11 ).y + 1 ),
								 point( render::text_size( _watermark, tahoma11 ).x, 1 ), color( 0, 0, 0, 220 ) );
		}

		misc::spectators( color::blend( color( 255, 255, 255 ), color( 200, 200, 200 ), anim_time ) );

		auto local = interfaces::entity_list->get<player_t>( interfaces::engine->get_local_player( ) );
		if ( input::click( *config::get<int>( crc( "misc:turn:key" ) ) ) && *config::get<bool>( crc( "misc:turn:enabled" ) ) && local&& local->alive( ) )
		{
			fake_backwards::angle_data.m_should_turn = !fake_backwards::angle_data.m_should_turn;
		}

		fake_backwards::visualise( );
		hitmarkers::draw( );
		nade_pred.draw( );

		gui::gui_interface( );
	}
}