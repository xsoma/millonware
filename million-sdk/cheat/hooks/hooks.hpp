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
#include "../../engine/interfaces/interfaces.hpp"
#include <cstdint>

#include "../../source engine/classes/c_usercmd.hpp"#
#include "../../source engine/structs/models.hpp"
#include "../../engine/utilities/xorstring.hpp"
#include "holy_hook.hpp"

namespace hooks
{
	class c_hook
	{
	private:
		uint8_t m_original_bytes[ 5 ];
		uint32_t m_original_address;
		uint32_t m_hook_address;
		bool m_is_rwx = false;
	public:
		void hook_function( uint32_t _original_address, uint32_t _hook_address );

		void unhook( );

		void rehook( );
		uint32_t get_ofunc( );
	};

	inline c_holy_hook pt_holy_hook;
	inline c_holy_hook fsn_holy_hook;
	inline c_holy_hook cm_holy_hook;
	inline c_holy_hook lc_holy_hook;
	inline c_holy_hook dme_holy_hook;
	inline c_holy_hook dpu_holy_hook;
	inline c_holy_hook gcm_holy_hook;
	inline c_holy_hook iuspdm_holy_hook;

	inline c_hook pt_hook;
	inline c_hook fsn_hook;
	inline c_hook cm_hook;
	inline c_hook lc_hook;
	inline c_hook es_hook;
	inline c_hook snm_hook;
	inline c_hook dme_hook;
	inline c_hook dpu_hook;
	inline c_hook cc_hook;
	inline c_hook ossc_hook;

	inline bool b_predicting;

	void __fastcall paint_traverse( void* ecx, void* edx, unsigned int panel, bool force, bool allow_force );
	void __fastcall frame_stage_notify( void* ecx, void* edx, int stage );
	bool __fastcall create_move( void* ecx, void* edx, float frame_time, c_usercmd* cmd );
	void __fastcall lock_cursor( void* ecx, void* edx );
	void __fastcall emit_sound( void* ecx, void* edx, void* filter, int iEntIndex, int iChannel, const char* pSoundEntry, unsigned int nSoundEntryHash, const char* pSample, float flVolume, float flAttenuation, int nSeed, int iFlags, int iPitch, const vec3* pOrigin, const vec3* pDirection, vec3* pUtlVecOrigins, bool bUpdatePositions, float soundtime, int speakerentity, void* fwer );
	bool __fastcall send_net_msg( void* channel, uint32_t, void* msg, bool reliable, bool voice );
	void __fastcall draw_model_execute( void* ecx, void* edx, void* ctx, void* state, model_render_info_t* info, matrix_t* matrix );
	bool __fastcall dispatch_user_message( void*, void*, int type, uint32_t a3, uint32_t len, void* msg_data );
	void __fastcall client_cmd( void* ecx, void* edx, const char* cmd );
	void __fastcall on_screen_size_change( void* ecx, void* edx, int old_w, int old_h );
	void __fastcall get_color_modulation(void* ecx, void* edx, float* r, float* g, float* b);
	bool __stdcall  is_using_static_prop_debug_modes();
	
	void init( );

	void revert( );
}