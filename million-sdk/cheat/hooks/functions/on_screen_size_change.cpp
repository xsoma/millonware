#include "../hooks.hpp"
#include "../../../global_ctx.hpp"

void __fastcall hooks::on_screen_size_change( void* ecx, void* edx, int old_w, int old_h )
{
	ossc_hook.unhook( );
	const static auto ofunc = ( decltype( &on_screen_size_change ) )ossc_hook.get_ofunc( );
	ofunc( ecx, edx, old_w, old_h );
	ossc_hook.rehook( );

	context::refreshed_fonts = false;
}