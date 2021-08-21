#include "../hooks.hpp"
#include "../../input/input.hpp"
#include "../../gui/gui.hpp"

#include"../../../engine/interfaces/interfaces.hpp"

void __fastcall hooks::lock_cursor( void* ecx, void* edx )
{
	if ( !gui::ctx.open )
	{
		lc_holy_hook.call_original<decltype( &lock_cursor )>( ecx, edx );
		return;
	}


	interfaces::surface->unlock_cursor( );
}