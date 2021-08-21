#include "../hooks.hpp"
#include "../../input/input.hpp"
#include "../../../source engine/misc/frame_stages.hpp"
#include "../../../engine/netvars/netvars.hpp"
#include "../../../source engine/sdk.hpp"
#include "../../../engine/utilities/config.hpp"
#include "../../features/visuals.hpp"
#include "../../features/skins.hpp"
#include "../../features/misc.hpp"

void __fastcall hooks::frame_stage_notify( void* ecx, void* edx, int stage )
{
	fsn_holy_hook.call_original<decltype( &frame_stage_notify )>( ecx, edx, stage );

	if ( stage == FRAME_NET_UPDATE_POSTDATAUPDATE_START )
	{
		if ( interfaces::engine->is_in_game( ) && interfaces::engine->is_connected( ) )
		{
			player_t* local = interfaces::entity_list->get<player_t>( interfaces::engine->get_local_player( ) );
			auto weapons = local->weapons( );

			for ( int i = 0; weapons[ i ] != 0xFFFFFFFF; i++ )
			{
				auto weapon = ( weapon_t* )interfaces::entity_list->get_client_entity( ( uintptr_t )( weapons[ i ] ) );
				if ( weapon )
				{
					skins::knifes::update_knife( weapon );
				}
			}

			skins::gloves::set_glove_model( );
		}
	}

	if ( stage == FRAME_RENDER_START /* i dont remember */ )
	{
		visuals::glow( );
		misc::remove_smoke( );
		misc::preserve_killfeed( );
	}
}