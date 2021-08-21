#include "../hooks.hpp"
#include <cstdio>
#include "../../features/pred.hpp"
#include "../../../source engine/sdk.hpp"
#include <windows.h>
#include "../../input/input.hpp"
#include "../../gui/gui.hpp"
#include "../../features/bt.hpp"
#include "../../features/movement.hpp"
#include "../../features/jump_stats.hpp"
#include "../../features/misc.hpp"
#include "../../features/aimbot.hpp"
#include "../../features/fake_backwards.hpp"
#include "../../features/triggerbot.hpp"
#include "../../features/vel_graph.hpp"
#include "../../features/walkbot.hpp"
#include "../../features/nade_prediction.hpp"

bool __fastcall hooks::create_move( void* ecx, void* edx, float frame_time, c_usercmd* cmd )
{
	auto local = interfaces::entity_list->get<player_t>( interfaces::engine->get_local_player( ) );
	if ( !cmd || !local || !cmd->command_number ) {
		return cm_holy_hook.call_original<bool>( ecx, edx, frame_time, cmd );
	}

	static bool netchan_hooked = false;
	if ( local ) {
		if ( interfaces::client_state->net_channel && !netchan_hooked )	{
			auto vtable = *( uintptr_t** )( interfaces::client_state->net_channel );

			auto fn = vtable[ 40 ];
			printf( xor ( "hooked SendNetMessage (0x%lx)\n" ), fn );
			hooks::snm_hook.hook_function( fn, ( uint32_t )hooks::send_net_msg );

			netchan_hooked = true;
		}
	}

	backtrack::create_move( cmd, local );
	velocity_graph::gather_data( );

	//walkbot::on_create_move(cmd);

	const auto pre_flags = local->flags( );

	fake_backwards::pre_move_fix( cmd );
	movement::pre_prediction( cmd, local, pre_flags );
	//jump_stats::update_unpredicted_info( pre_flags );

	engine_prediction::start( local, cmd );
	engine_prediction::finish( local );
	const auto post_flags = local->flags( );

	//jump_stats::update_predicted_info( post_flags );
	movement::post_prediction( cmd, local, pre_flags, post_flags );

	//jump_stats::update_info( cmd );

	if ( local && local->active_weapon( )->weapon_data( ) && local->active_weapon( ) && !( local->active_weapon( )->weapon_data( )->type == weapontype_knife
		 || local->active_weapon( )->weapon_data( )->type == weapontype_grenade
		 || local->active_weapon( )->item( ).item_definition_index( ) == weapon_healthshot
		 || local->active_weapon( )->item( ).item_definition_index( ) == weapon_snowball
		 || local->active_weapon( )->item( ).item_definition_index( ) == weapon_bumpmine
		 || local->active_weapon( )->item( ).item_definition_index( ) == weapon_c4
		 || ( local->active_weapon( )->item( ).item_definition_index( ) >= 43 && local->active_weapon( )->item( ).item_definition_index( ) <= 48 )
		 || local->active_weapon( )->reloading( )
		 || local->active_weapon( )->clip1_count( ) <= 0 ) )
	{
		aimbot::run( cmd );
	}
	else
	{
		aimbot::aimbot_target = -1;
	}

	//triggerbot::run( cmd );

	fake_backwards::run( cmd );

	misc::crosshair( );
	misc::disable_post_process( );
	misc::clantag( );
	misc::disable_panorama_blur( );
	misc::viewmodel_offset( );
	misc::name_spam( );
	nade_pred.trace( cmd );

	if ( local->move_type( ) != movetype_ladder && local->move_type( ) != movetype_noclip && !local->is_scoped( ) )
		fake_backwards::post_move_fix( cmd );

	if ( ( cmd->buttons & in_score ) && *config::get<bool>( crc( "misc:rank_reveal" ) ) )
	{
		// https://github.com/SteamDatabase/Protobufs/blob/master/csgo/cstrike15_usermessages.proto#L54
		interfaces::client->dispatch_user_msg( 50, 0, 0, nullptr );
	}

	if ( *config::get<bool>( crc( "esp:no_flash" ) ) )
	{
		// no need to back this shit up cos it wil just get reset 
		// next time u get flashed (if u have this off ofc)
		// fkn retards @ uc
		local->flash_duration( ) = 0.f;
	}

	static convar* cl_grenadepreview = interfaces::console->get_convar( xor ( "cl_grenadepreview" ) );
	if ( cl_grenadepreview )
	{
		cl_grenadepreview->callbacks.SetSize( 0 );
		cl_grenadepreview->set_value( int( *config::get<bool>( crc( "esp:nade_pred" ) ) ) );
	}

	cmd->view_angles.clamp( );

	return false;
}