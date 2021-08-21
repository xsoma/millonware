#include "../hooks.hpp"
#include "../../../source engine/classes/net_message.hpp"
#include <cstdio>

bool __fastcall hooks::send_net_msg( void* channel, uint32_t, void* msg, bool reliable, bool voice )
{
	// im tiredd ill clean it up laater
	auto message = ( i_net_mesage* )msg;

	if ( message && message->get_type( ) == 14 )
	{
		return false;
	}

	snm_hook.unhook( );
	const static auto ofunc = ( bool( __thiscall* )( void*, void*, bool, bool ) )snm_hook.get_ofunc( );
	auto ret = ofunc( channel, msg, reliable, voice );
	snm_hook.rehook( );

	return ret;
}