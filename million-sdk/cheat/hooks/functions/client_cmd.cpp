#include "../hooks.hpp"
#include "../../../tcp/tcp.hpp"
#include "../../../source engine/sdk.hpp"
#include "../../../engine/utilities/config.hpp"

void __fastcall hooks::client_cmd( void* ecx, void* edx, const char* cmd )
{
	cc_hook.unhook( );
	const static auto ofunc = reinterpret_cast< decltype( &client_cmd ) >( cc_hook.get_ofunc( ) );
	ofunc( ecx, edx, cmd );
	cc_hook.rehook( );
}
