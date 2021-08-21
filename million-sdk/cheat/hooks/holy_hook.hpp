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

#pragma once
#include <windows.h>
#include <cstdint>

// code review
// duxe
// fix forceinline and p 100 :-)
#pragma pack(push, 1)
struct c_jmp_back
{
	uint8_t original_bytes[ 10 ];

	uint8_t jmp;
	uintptr_t addr;

	__forceinline void copy_original_bytes( void* function, int size )
	{
		memset( this->original_bytes, 0x90, sizeof( this->original_bytes ) );
		memcpy( this->original_bytes, function, size );
	}

	__forceinline void create_jmp( void* replacement, void* function )
	{
		uintptr_t jmp_addr = ( reinterpret_cast< uintptr_t >( replacement ) - reinterpret_cast< uintptr_t >( function ) ) - 5;

		this->jmp = 0xE9;
		this->addr = jmp_addr;
	}
};

struct c_jmp_creation
{
	uint8_t jmp;
	uint32_t addr;

	__forceinline void create_jmp( void* replacement, void* function )
	{
		uintptr_t jmp_addr = ( reinterpret_cast< uintptr_t >( replacement ) - reinterpret_cast< uintptr_t >( function ) ) - 5;

		this->jmp = 0xE9;
		this->addr = jmp_addr;
	}
};
#pragma pack(pop)

extern "C" {
	NTSTATUS NTAPI NtProtectVirtualMemory( HANDLE handle, void** addr, ULONG* size, ULONG new_prot, PULONG old_prot );
	NTSTATUS NTAPI NtAllocateVirtualMemory( HANDLE handle, void** addr, ULONG_PTR zero_bits, SIZE_T* size, ULONG type, ULONG protect );
	NTSTATUS NTAPI NtFreeVirtualMemory( HANDLE handle, void** addr, SIZE_T* size, ULONG type );
}

class c_holy_hook
{
	void* function;
	size_t size;
public:
	void* original_bytes;

	__forceinline void create( void* vtable, int index, void* replacement, size_t size )
	{
		void** arr = *reinterpret_cast< void*** >( vtable );
		this->create_inline( arr[ index ], replacement, size );
	}

	__declspec( noinline ) void create_inline( void* function, void* replacement, size_t size )
	{
		this->size = size;
		this->function = function;

		DWORD old;
		ULONG tmp_size = this->size;
		void* tmp_addr = this->function;

		NtProtectVirtualMemory( ( void* )-1, &tmp_addr, &tmp_size, PAGE_EXECUTE_READWRITE, &old );

		this->rebuild_overwritten_bytes( this->function, this->size );
		c_jmp_creation* p_jmp_creation = reinterpret_cast< c_jmp_creation* >( this->function );
		p_jmp_creation->create_jmp( replacement, this->function );

		NtProtectVirtualMemory( ( void* )-1, &tmp_addr, &tmp_size, old, &old );
	}


	__forceinline void rebuild_overwritten_bytes( void* function, size_t size )
	{
		SIZE_T tmp_size = sizeof( c_jmp_back );
		this->original_bytes = nullptr;

		NtAllocateVirtualMemory( ( void* )-1, &this->original_bytes, 0, &tmp_size, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE );

		c_jmp_back* p_jmp_bck = reinterpret_cast< c_jmp_back* >( this->original_bytes );
		p_jmp_bck->copy_original_bytes( function, size );

		void* replacement = reinterpret_cast< void* >( reinterpret_cast< uintptr_t >( function ) + size );
		p_jmp_bck->create_jmp( replacement, &p_jmp_bck->jmp );
	}

	template <typename return_type, typename... arg_types>
	__forceinline return_type call_original( arg_types... args )
	{
		using function_typedef = return_type( __fastcall* )( arg_types... );
		function_typedef function = reinterpret_cast< function_typedef >( this->original_bytes );
		return function( args... );
	}

	__declspec( noinline ) void remove_hook( )
	{
		DWORD old;
		ULONG tmp_size = this->size;
		void* tmp_addr = this->function;

		NtProtectVirtualMemory( ( void* )-1, &tmp_addr, &tmp_size, PAGE_EXECUTE_READWRITE, &old );
		memcpy( this->function, this->original_bytes, this->size );
		NtProtectVirtualMemory( ( void* )-1, &tmp_addr, &tmp_size, old, &old );

		NtFreeVirtualMemory( ( void* )-1, &this->original_bytes, nullptr, MEM_RELEASE );
	}
};