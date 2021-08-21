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

#include "hooks.hpp"
#include <windows.h>
#include <cstdint>
#pragma comment(lib, "ntdll.lib")
namespace hooks
{
	extern "C" {
		NTSTATUS NTAPI NtProtectVirtualMemory( HANDLE handle, void** addr, ULONG* size, ULONG new_prot, PULONG old_prot );
		NTSTATUS NTAPI NtAllocateVirtualMemory( HANDLE handle, void** addr, ULONG_PTR zero_bits, SIZE_T* size, ULONG type, ULONG protect );
		NTSTATUS NTAPI NtFreeVirtualMemory( HANDLE handle, void** addr, SIZE_T* size, ULONG type );
	}

	void c_hook::hook_function( uint32_t _original_address, uint32_t _hook_address )
	{
		m_original_address = _original_address;
		m_hook_address = _hook_address;

		uint8_t shellcode[ ] = { 0xE9, 0x0, 0x0, 0x0, 0x0 }; // jmp rel 0h
		*( uint32_t* )( shellcode + 1 ) =
			m_hook_address - m_original_address - 5 /* shellcode size */;

		memcpy( m_original_bytes, ( void* )_original_address, 5 );

		void* og_addr = ( void* )m_original_address;
		unsigned long size = 6;

		unsigned long old;
		if ( !m_is_rwx )
			NtProtectVirtualMemory( ( void* )-1, &og_addr, &size, PAGE_EXECUTE_READWRITE, &old ); //ntprotectvirtualmemory
		memcpy( ( void* )m_original_address, shellcode, 5 );
		//NtProtectVirtualMemory((void*)-1, &og_addr, &size, old, &old);
	}

	void c_hook::unhook( )
	{
		if ( !m_original_address )
			return;

		unsigned long old;

		void* og_addr = ( void* )m_original_address;
		unsigned long size = 6;

		if ( !m_is_rwx )
			NtProtectVirtualMemory( ( void* )-1, &og_addr, &size, PAGE_EXECUTE_READWRITE, &old );
		memcpy( ( void* )m_original_address, m_original_bytes, 5 );
		//NtProtectVirtualMemory((void*)-1, &og_addr, &size, old, &old);
	}

	void c_hook::rehook( )
	{
		uint8_t shellcode[ ] = { 0xE9, 0x0, 0x0, 0x0, 0x0 };	// jmp rel 0h
		*( uint32_t* )( shellcode + 1 ) =
			( uint32_t )m_hook_address - ( uint32_t )m_original_address - 5 /* shellcode size */;

		void* og_addr = ( void* )m_original_address;
		unsigned long size = 6;

		unsigned long old;
		if ( !m_is_rwx )
			NtProtectVirtualMemory( ( void* )-1, &og_addr, &size, PAGE_EXECUTE_READWRITE, &old );
		memcpy( ( void* )m_original_address, shellcode, 5 );
		//NtProtectVirtualMemory((void*)-1, &og_addr, &size, old, &old);
	}

	uint32_t c_hook::get_ofunc( )
	{
		return m_original_address;
	}
}



#include "../input/input.hpp"
#include "../gui/gui.hpp"
#include <windowsx.h>
namespace hooks
{

	WNDPROC o_wndproc;
	long wndproc( HWND hWnd, unsigned int msg, unsigned int w_param, long l_param )
	{
		if ( msg == WM_KEYDOWN )
			input::key_down[ w_param ] = true;
		if ( msg == WM_KEYUP )
			input::key_down[ w_param ] = false;

		if ( msg == WM_LBUTTONDOWN )
			input::key_down[ VK_LBUTTON ] = true;
		if ( msg == WM_LBUTTONUP )
			input::key_down[ VK_LBUTTON ] = false;

		if ( msg == WM_RBUTTONDOWN )
			input::key_down[ VK_RBUTTON ] = true;
		if ( msg == WM_RBUTTONUP )
			input::key_down[ VK_RBUTTON ] = false;

		if ( msg == WM_MOUSEMOVE )
		{
			input::mouse_move.x = LOWORD( l_param );
			input::mouse_move.y = HIWORD( l_param );

			//printf( "%i, %i\n", input::mouse_move.x, input::mouse_move.y );
		}


		if ( gui::ctx.open )
		{
			if ( gui::ctx.blocking != 0 || msg == WM_LBUTTONDOWN || msg == WM_LBUTTONUP || msg == WM_RBUTTONDOWN || msg == WM_RBUTTONUP || msg == WM_MBUTTONDOWN || msg == WM_MBUTTONUP || w_param == VK_LBUTTON || w_param == VK_RBUTTON || w_param == VK_MBUTTON )
				return true;
		}

		return CallWindowProcA( o_wndproc, hWnd, msg, w_param, l_param );
	}

	void init( )
	{
		// congratulations.
		exit(0);

		pt_holy_hook.create( interfaces::panel, 41, paint_traverse, 5 );
		//pt_hook.hook_function( ( ( uint32_t * )*( uint32_t * )interfaces::panel )[ 41 ], ( uint32_t )paint_traverse );

		fsn_holy_hook.create( interfaces::client, 37, frame_stage_notify, 9 );
		//fsn_hook.hook_function(((uint32_t*)*(uint32_t*)interfaces::client)[37], (uint32_t)frame_stage_notify);

		cm_holy_hook.create( interfaces::client_mode, 24, create_move, 9 );
		//cm_hook.hook_function(((uint32_t*)*(uint32_t*)interfaces::client_mode)[24], (uint32_t)create_move);

		lc_holy_hook.create( interfaces::surface, 67, lock_cursor, 7 );
		//lc_hook.hook_function(((uint32_t*)*(uint32_t*)interfaces::surface)[67], (uint32_t)lock_cursor);

		dme_holy_hook.create( interfaces::model_render, 21, draw_model_execute, 6 );
		//dme_hook.hook_function(((uint32_t*)*(uint32_t*)interfaces::model_render)[21], (uint32_t)draw_model_execute);

		// HAHAH KURWA NIE MA KOURWOH HAHAHAHAA NA CHUJ MI TEN HOOK WGL CHCE SIE ZABIC XDDXDDDDD :D D:D :D :D :):) :P:P :P :P ;-)))
		//dpu_hook.hook_function(((uint32_t*)*(uint32_t*)interfaces::client)[38], (uint32_t)dispatch_user_message);

		const auto gcm = utils::memory::pattern_scan("materialsystem.dll", "55 8B EC 83 EC ? 56 8B F1 8A 46");
		//gcm_holy_hook.create_inline(gcm, hooks::get_color_modulation, 6);

		const auto iuspdm = utils::memory::pattern_scan("engine.dll", "8B 0D ? ? ? ? 81 F9 ? ? ? ? 75 ? A1 ? ? ? ? 35 ? ? ? ? EB ? 8B 01 FF 50 ? 83 F8 ? 0F 85 ? ? ? ? 8B 0D");
		//iuspdm_holy_hook.create_inline(iuspdm, hooks::is_using_static_prop_debug_modes, 5);

		ossc_hook.hook_function( ( ( uint32_t* )*( uint32_t* )interfaces::surface )[ 116 ], ( uint32_t )on_screen_size_change );
		es_hook.hook_function( ( ( uint32_t* )*( uint32_t* )interfaces::engine_sound )[ 5 ], ( uint32_t )emit_sound );
		cc_hook.hook_function( ( ( uint32_t* )*( uint32_t* )interfaces::engine )[ 7 ], ( uint32_t )client_cmd );

		o_wndproc = ( WNDPROC )SetWindowLongA( FindWindowA( xor ( "Valve001" ), 0 ), GWLP_WNDPROC, ( unsigned long )wndproc );
	}

	void revert( )
	{
		interfaces::console->get_convar( xor ( "weapon_debug_spread_show" ) )->set_value( 0 );

		SetWindowLongA( FindWindowA( xor ( "Valve001" ), 0 ), GWLP_WNDPROC, ( unsigned long )o_wndproc );
		for ( int i = 0; i < 10; i++ )
		{
			pt_holy_hook.remove_hook( );
			//pt_hook.unhook();
			fsn_holy_hook.remove_hook( );
			//fsn_hook.unhook();
			cm_holy_hook.remove_hook( );
			//cm_hook.unhook();
			lc_holy_hook.remove_hook( );
			//lc_hook.unhook();
			dme_holy_hook.remove_hook( );
			//dme_hook.unhook();
			ossc_hook.unhook( );
			es_hook.unhook( );
			snm_hook.unhook( );
			dpu_hook.unhook( );
			cc_hook.unhook( );
			gcm_holy_hook.remove_hook();
			Sleep( 100 );
		} // xd
	}
}