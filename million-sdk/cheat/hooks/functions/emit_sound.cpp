#include "../hooks.hpp"
#include <cstdio>

#include "../../features/misc.hpp"

bool landed = false;
typedef void( __fastcall* EmitSoundFn )( void*, void*, void*, int, int, const char*, unsigned int, const char*, float, float, int, int, int, const vec3*, const vec3*, vec3*, bool, float, int, void* );
void __fastcall hooks::emit_sound( void* ecx, void* edx, void* filter, int iEntIndex, int iChannel, const char* pSoundEntry,
								   unsigned int nSoundEntryHash, const char* pSample, float flVolume, float flAttenuation, int nSeed, int iFlags, int iPitch,
								   const vec3* pOrigin, const vec3* pDirection, vec3* pUtlVecOrigins, bool bUpdatePositions, float soundtime, int speakerentity, void* fds )
{

	if ( !strcmp( pSoundEntry, "UIPanorama.popup_accept_match_beep" ) )
	{
		misc::auto_accept( );
	}

	if ( iEntIndex == interfaces::engine->get_local_player( ) )
	{
		if ( strstr( pSample, xor ( "land" ) ) && b_predicting )
		{
			b_predicting = false;
			landed = true;
			return;
		}

		if ( strstr( pSample, xor ( "suit" ) ) && landed )
		{
			landed = false;
			return;
		}
	}

	es_hook.unhook( );
	const static auto ofunc = ( EmitSoundFn )es_hook.get_ofunc( );
	ofunc( ecx, edx, filter, iEntIndex, iChannel, pSoundEntry, nSoundEntryHash, pSample, flVolume, flAttenuation, nSeed, iFlags, iPitch, pOrigin, pDirection, pUtlVecOrigins, bUpdatePositions, soundtime, speakerentity, fds );
	es_hook.rehook( );

	//printf("%s %s\n", pSoundEntry, pSample);
}