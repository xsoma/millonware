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
#include <vector>

class convar;
using fn_change_callback_t = void( * )( convar * var, const char* pOldValue, float flOldValue );

inline int UtlMemory_CalcNewAllocationCount( int nAllocationCount, int nGrowSize, int nNewSize, int nBytesItem )
{
	if ( nGrowSize )
		nAllocationCount = ( ( 1 + ( ( nNewSize - 1 ) / nGrowSize ) ) * nGrowSize );
	else
	{
		if ( !nAllocationCount )
			nAllocationCount = ( 31 + nBytesItem ) / nBytesItem;

		while ( nAllocationCount < nNewSize )
			nAllocationCount *= 2;
	}

	return nAllocationCount;
}

template< class T, class I = int >
class CUtlMemory
{
public:
	T& operator[]( I i )
	{
		return m_pMemory[ i ];
	}

	T* Base( )
	{
		return m_pMemory;
	}

	int NumAllocated( ) const
	{
		return m_nAllocationCount;
	}

	bool IsExternallyAllocated( ) const
	{
		return m_nGrowSize < 0;
	}

protected:
	T* m_pMemory;
	int m_nAllocationCount;
	int m_nGrowSize;
};

template <class T>
inline T* Construct( T* pMemory )
{
	return ::new( pMemory ) T;
}

template <class T>
inline void Destruct( T* pMemory )
{
	pMemory->~T( );
}

template< class T, class A = CUtlMemory<T> >
class CUtlVector
{
	typedef A CAllocator;
public:
	T& operator[]( int i )
	{
		return m_Memory[ i ];
	}

	T& Element( int i )
	{
		return m_Memory[ i ];
	}

	T* Base( )
	{
		return m_Memory.Base( );
	}

	int Count( ) const
	{
		return m_Size;
	}

	void RemoveAll( )
	{
		for ( int i = m_Size; --i >= 0; )
			Destruct( &Element( i ) );

		m_Size = 0;
	}

	int AddToTail( )
	{
		return InsertBefore( m_Size );
	}

	void SetSize( int size )
	{
		m_Size = size;
	}

	int InsertBefore( int elem )
	{
		GrowVector( );
		ShiftElementsRight( elem );
		Construct( &Element( elem ) );

		return elem;
	}

protected:
	void GrowVector( int num = 1 )
	{
		if ( m_Size + num > m_Memory.NumAllocated( ) )
			m_Memory.Grow( m_Size + num - m_Memory.NumAllocated( ) );

		m_Size += num;
		ResetDbgInfo( );
	}

	void ShiftElementsRight( int elem, int num = 1 )
	{
		int numToMove = m_Size - elem - num;
		if ( ( numToMove > 0 ) && ( num > 0 ) )
			memmove( &Element( elem + num ), &Element( elem ), numToMove * sizeof( T ) );
	}

	CAllocator m_Memory;
	int m_Size;

	T* m_pElements;

	inline void ResetDbgInfo( )
	{
		m_pElements = Base( );
	}
};

enum cvar_flags
{
	fcvar_none = 0,
	fcvar_unregistered = ( 1 << 0 ),
	fcvar_developmentonly = ( 1 << 1 ),
	fcvar_gamedll = ( 1 << 2 ),
	fcvar_clientdll = ( 1 << 3 ),
	fcvar_hidden = ( 1 << 4 ),
	fcvar_protected = ( 1 << 5 ),
	fcvar_sponly = ( 1 << 6 ),
	fcvar_archive = ( 1 << 7 ),
	fcvar_notify = ( 1 << 8 ),
	fcvar_userinfo = ( 1 << 9 ),
	fcvar_printableonly = ( 1 << 10 ),
	fcvar_unlogged = ( 1 << 11 ),
	fcvar_never_as_string = ( 1 << 12 ),
	fcvar_replicated = ( 1 << 13 ),
	fcvar_cheat = ( 1 << 14 ),
	fcvar_ss = ( 1 << 15 ),
	fcvar_demo = ( 1 << 16 ),
	fcvar_dontrecord = ( 1 << 17 ),
	fcvar_ss_added = ( 1 << 18 ),
	fcvar_release = ( 1 << 19 ),
	fcvar_reload_materials = ( 1 << 20 ),
	fcvar_reload_textures = ( 1 << 21 ),
	fcvar_not_connected = ( 1 << 22 ),
	fcvar_material_system_thread = ( 1 << 23 ),
	fcvar_archive_xbox = ( 1 << 24 ),
	fcvar_accessible_from_threads = ( 1 << 25 ),
	fcvar_server_can_execute = ( 1 << 28 ),
	fcvar_server_cannot_query = ( 1 << 29 ),
	fcvar_clientcmd_can_execute = ( 1 << 30 ),
	fcvar_meme_dll = ( 1 << 31 ),
	fcvar_material_thread_mask = ( fcvar_reload_materials | fcvar_reload_textures | fcvar_material_system_thread )
};

class convar
{
public:
	float get_float( )
	{
		using original_fn = float( __thiscall* )( convar* );
		return ( *( original_fn** )this )[ 12 ]( this );
	}
	void set_value( const char* value )
	{
		using original_fn = void( __thiscall* )( convar*, const char* );
		return ( *( original_fn** )this )[ 14 ]( this, value );
	}
	void set_value( float value )
	{
		using original_fn = void( __thiscall* )( convar*, float );
		return ( *( original_fn** )this )[ 15 ]( this, value );
	}
	void set_value( int value )
	{
		using original_fn = void( __thiscall* )( convar*, int );
		return ( *( original_fn** )this )[ 16 ]( this, value );
	}
	void set_value( bool value )
	{
		using original_fn = void( __thiscall* )( convar*, int );
		return ( *( original_fn** )this )[ 16 ]( this, static_cast< int >( value ) );
	}

private:
	char pad_0x0000[ 0x4 ];

public:
	convar* next;
	__int32 is_registered;
	char* name;
	char* help_string;
	__int32 flags;

private:
	char pad_0x0018[ 0x4 ];

public:
	convar* parent;
	char* default_value;
	char* string;
	__int32 string_length;
	float float_value;
	__int32 numerical_value;
	__int32 has_min;
	float min;
	__int32 has_max;
	float max;
	CUtlVector<fn_change_callback_t> callbacks;
};