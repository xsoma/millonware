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

#include "skins.hpp"
#include "../../source engine/sdk.hpp"
#include "../../engine/utilities/config.hpp"

namespace skins::general
{
	struct hud_weapons_t
	{
		std::int32_t* wpn_count( )
		{
			return reinterpret_cast< std::int32_t* >( std::uintptr_t( this ) + 0x80 );
		}
	};

	void full_update( )
	{
		if ( !interfaces::engine->is_in_game( ) )
			return;

		static auto clear_hud_weapon_icon_fn = reinterpret_cast< std::int32_t( __thiscall* )( void*, std::int32_t ) >(
			utils::memory::pattern_scan( "client.dll", "55 8B EC 51 53 56 8B 75 08 8B D9 57 6B FE 2C" ) );

		auto element = utils::engine::find_hud_element<std::uintptr_t*>( ( "CCSGO_HudWeaponSelection" ) );

		auto hud_weapons = reinterpret_cast< hud_weapons_t* >( std::uintptr_t( element ) - 0xa0 );
		if ( hud_weapons == nullptr )
			return;

		if ( !*hud_weapons->wpn_count( ) )
			return;

		for ( std::int32_t i = 0; i < *hud_weapons->wpn_count( ); i++ )
			i = clear_hud_weapon_icon_fn( hud_weapons, i );

		interfaces::client_state->full_update( );
	}
}

namespace skins::knifes
{
	uintptr_t world_model_handle;
	viewmodel_t* world_model;
	std::unordered_map<int, const char*> viewmodel_cfg;

	struct knife_t
	{
		int item_definition_index;
		const char* model_name;
		const char* killfeed_name;
	};

	std::vector<knife_t> knives = {
		{ 500, "models/weapons/v_knife_bayonet.mdl", "bayonet" },
		{ 503, "models/weapons/v_knife_css.mdl", "knife_css" },
		{ 505, "models/weapons/v_knife_flip.mdl", "knife_flip" },
		{ 506, "models/weapons/v_knife_gut.mdl", "knife_gut" },
		{ 507, "models/weapons/v_knife_karam.mdl", "knife_karambit" },
		{ 508, "models/weapons/v_knife_m9_bay.mdl", "knife_m9_bayonet" },
		{ 509, "models/weapons/v_knife_tactical.mdl", "knife_tactical"},
		{ 512, "models/weapons/v_knife_falchion_advanced.mdl", "knife_falchion" },
		{ 514, "models/weapons/v_knife_survival_bowie.mdl", "knife_survival_bowie" },
		{ 515, "models/weapons/v_knife_butterfly.mdl", "knife_butterfly" },
		{ 516, "models/weapons/v_knife_push.mdl", "knife_push"},
		{ 517, "models/weapons/v_knife_cord.mdl", "knife_cord"},
		{ 518, "models/weapons/v_knife_canis.mdl", "knife_canis"},
		{ 519, "models/weapons/v_knife_ursus.mdl", "knife_ursus"},
		{ 520, "models/weapons/v_knife_gypsy_jackknife.mdl", "knife_gypsy_jackknife"},
		{ 521, "models/weapons/v_knife_outdoor.mdl", "knife_outdoor" },
		{ 522, "models/weapons/v_knife_stiletto.mdl", "knife_stiletto" },
		{ 523, "models/weapons/v_knife_widowmaker.mdl", "knife_widowmaker" },
		{ 525, "models/weapons/v_knife_skeleton.mdl", "knife_skeleton" }
	};

	void update_knife( weapon_t* weapon )
	{
		player_t* local = interfaces::entity_list->get<player_t>( interfaces::engine->get_local_player( ) );
		if ( !local )
		{
			skins::general::full_update( );
			return;
		}

		attributable_item_t* weapon_attributable = ( attributable_item_t* )weapon;

		world_model_handle = weapon_attributable->world_model_handle( );
		if ( world_model_handle ) world_model = ( viewmodel_t* )interfaces::entity_list->get_client_entity( world_model_handle );

		if ( weapon->is_knife( ) )
		{
			int chosen_knife = *config::get<int>( crc( "misc:knife" ) ) - 1;
			if ( chosen_knife < 0 )
				return;

			int model = interfaces::model_info->get_model_index( knives[ chosen_knife ].model_name );

			weapon_attributable->item( ).item_definition_index( ) = knives[ chosen_knife ].item_definition_index;

			if ( local->view_model( ) )
			{
				if ( local->active_weapon( ) && local->active_weapon( )->is_knife( ) )
				{
					local->view_model( )->model_index( ) = model;
					local->view_model( )->viewmodel_index( ) = model;
				}
			}

			( ( viewmodel_t* )weapon )->model_index( ) = model;
			( ( viewmodel_t* )weapon )->viewmodel_index( ) = model;

			if ( world_model )
			{
				world_model->model_index( ) = model + 1;
			}

			weapon_attributable->fallback_paint_kit( ) = *config::get<int>( crc( "misc:knife_paintkit" ) );
			weapon_attributable->fallback_wear( ) = 0.000000001f;
			weapon_attributable->fallback_seed( ) = 0;
			weapon_attributable->fallback_stattrak( ) = -1;
			weapon_attributable->item( ).item_id_high( ) = -1;
			weapon_attributable->item( ).entity_quality( ) = 3;
		}

		static int last_knife = *config::get<int>( crc( "misc:knife" ) );
		if ( last_knife != *config::get<int>( crc( "misc:knife" ) ) )
		{
			skins::general::full_update( );
			last_knife = *config::get<int>( crc( "misc:knife" ) );
		}

		static int last_paintkit = *config::get<int>( crc( "misc:knife_paintkit" ) );
		if ( last_paintkit != *config::get<int>( crc( "misc:knife_paintkit" ) ) )
		{
			skins::general::full_update( );
			last_paintkit = *config::get<int>( crc( "misc:knife_paintkit" ) );
		}
	}

	const char* update_kill_icons( )
	{
		int chosen_knife = *config::get<int>( crc( "misc:knife" ) ) - 1;
		if ( chosen_knife < 0 )
		{
			return xor ( "" );
		}

		return knives[ chosen_knife ].killfeed_name;
	}
}

namespace skins::gloves
{
	struct glove_item_t
	{
		int index = -1;
		const char* model = nullptr;
	};

	struct glove_skin_t
	{
		int paint_kit = -1;
	};

	const std::vector<glove_item_t> glove_list =
	{
		{ 5027, "models/weapons/v_models/arms/glove_bloodhound/v_glove_bloodhound.mdl" }, //Bloodhound
		{ 5030, "models/weapons/v_models/arms/glove_sporty/v_glove_sporty.mdl" }, //Sport
		{ 5031, "models/weapons/v_models/arms/glove_slick/v_glove_slick.mdl" }, //Slick
		{ 5032, "models/weapons/v_models/arms/glove_handwrap_leathery/v_glove_handwrap_leathery.mdl" }, //Handwrap
		{ 5033, "models/weapons/v_models/arms/glove_motorcycle/v_glove_motorcycle.mdl" }, //Moto
		{ 5034, "models/weapons/v_models/arms/glove_specialist/v_glove_specialist.mdl" }, //Specialist
		{ 5035, "models/weapons/v_models/arms/glove_bloodhound/v_glove_bloodhound_hydra.mdl" } //Hydra
	};

	// xddddddddd
	const std::vector<glove_skin_t> glove_skin_list =
	{
		//whoever did this retarded ass method ill rip ur fucking head off cunt
		{ 10006 }, //Charred
		{ 10007 }, //Snakebite
		{ 10008 }, //Bronzed
		{ 10039 }, //Guerrilla
		{ 10009 }, //Leather
		{ 10010 }, //Spruce DDPAT	
		{ 10036 }, //Badlands
		{ 10021 }, //Slaughter
		{ 10013 }, //Lunar Weave
		{ 10015 }, //Convoy
		{ 10016 }, //Crimson Weave
		{ 10040 }, //Diamondback
		{ 10018 }, //Superconductor
		{ 10019 }, //Arid
		{ 10037 }, //Pandora's Box
		{ 10038 }, //Hedge Maze	
		{ 10024 }, //Eclipse
		{ 10026 }, //Spearmint
		{ 10027 }, //Boom!
		{ 10028 }, //Cool Mint
		{ 10030 }, //Forest DDPAT
		{ 10033 }, //Crimson Kimono	
		{ 10034 }, //Emerald Web	
		{ 10035 }  //Foundation	
	};

	create_client_class_fn get_wearable_create_fn( )
	{
		auto _class = interfaces::client->get_client_classes( );

		while ( strcmp( _class->network_name, xor ( "CEconWearable" ) ) )
		{
			_class = _class->next_ptr;
		}

		return _class->create_fn;
	}

	void set_glove_model( )
	{
		player_t* local = interfaces::entity_list->get<player_t>( interfaces::engine->get_local_player( ) );
		if ( !local || !local->alive( ) || !interfaces::engine->is_connected( ) || !interfaces::engine->is_in_game( ) )
		{
			return;
		}

		static unsigned long glove_handle = 0;

		auto my_wearables_handle = local->wearables( );
		auto my_wearables = ( attributable_item_t* )interfaces::entity_list->get_client_entity_handle( my_wearables_handle[ 0 ] );

		if ( !my_wearables )
		{
			auto glove = ( attributable_item_t* )interfaces::entity_list->get_client_entity_handle( glove_handle );

			if ( glove )
			{
				my_wearables_handle[ 0 ] = glove_handle;
				my_wearables = glove;
			}
		}

		if ( !local->alive( ) )
		{
			if ( my_wearables )
			{
				my_wearables->networkable( )->set_destroyed_on_recreate_entities( );
				my_wearables->networkable( )->release( );
			}
			return;
		}

		if ( !my_wearables )
		{
			static auto create_wearable_fn = get_wearable_create_fn( );
			auto entry = interfaces::entity_list->get_highest_entity_index( ) + 1;

			auto serial = rand( ) % 0x1000;
			create_wearable_fn( entry, serial );

			my_wearables = ( interfaces::entity_list->get<attributable_item_t>( entry ) );

			auto index = entry | ( serial << 16 );

			glove_handle = index;

			*local->wearables( ) = index;
		}

		if ( my_wearables && *config::get<int>( crc( "misc:glove_model" ) ) > 0 )
		{
			set_glove_attributes( my_wearables );
		}

		static int last_glove = *config::get<int>( crc( "misc:glove_model" ) );
		if ( last_glove != *config::get<int>( crc( "misc:glove_model" ) ) )
		{
			skins::general::full_update( );
			last_glove = *config::get<int>( crc( "misc:glove_model" ) );
		}

		static int last_skin = *config::get<int>( crc( "misc:glove_skin" ) );
		if ( last_skin != *config::get<int>( crc( "misc:glove_skin" ) ) )
		{
			skins::general::full_update( );
			last_skin = *config::get<int>( crc( "misc:glove_skin" ) );
		}
	}

	void set_glove_attributes( attributable_item_t* item )
	{
		*( int* )( ( std::uint32_t )item + 0x64 ) = -1;

		auto glove_definition_index = glove_list[ *config::get<int>( crc( "misc:glove_model" ) ) - 1 ].index;
		auto glove_model_index = interfaces::model_info->get_model_index( glove_list[ *config::get<int>( crc( "misc:glove_model" ) ) - 1 ].model );

		item->item( ).item_id_high( ) = -1;
		item->item( ).item_definition_index( ) = glove_definition_index;
		item->fallback_paint_kit( ) = glove_skin_list[ *config::get<int>( crc( "misc:glove_skin" ) ) ].paint_kit;
		item->fallback_wear( ) = 0.1f;
		( ( viewmodel_t* )item )->model_index( ) = glove_model_index;
		item->networkable( )->pre_data_update( 0 );
	}
}