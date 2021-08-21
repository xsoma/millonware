#include "../hooks.hpp"
#include <cstdio>

#include "../../../source engine/sdk.hpp"
#include "../../features/bt.hpp"
#include "../../../engine/utilities/config.hpp"
#include "../../../source engine/classes/key_values.hpp"

void __fastcall hooks::draw_model_execute( void* ecx, void* edx, void* ctx, void* state, model_render_info_t* info, matrix_t* matrix )
{
	auto original = [ & ]( matrix_t* _matrix )
	{
		dme_holy_hook.call_original<void>( ecx, edx, ctx, state, info, _matrix );
	};

	if ( interfaces::model_render->is_forced_material_override( ) )
	{
		original( matrix );
		return;
	}

	static auto flat = interfaces::material_system->find_material( xor ( "debug/debugdrawflat" ) );
	static auto textured = interfaces::material_system->find_material( xor ( "debug/debugambientcube" ) );

	static i_material* mat = nullptr;

	switch ( *config::get<int>( crc( "esp:chams:material" ) ) )
	{
	case 0: mat = textured; break;
	case 1: mat = flat; break;
	}

	if ( mat == textured )
	{
		static key_values* kv = nullptr;
		if ( !kv )
		{
			kv = static_cast< key_values* >( malloc( 36 ) );
			kv->init( xor ( "VertexLitGeneric" ) );
		}
		else
		{
			static bool something_changed = true;

			color clr( *config::get<color>( crc( "esp:chams:reflectivity_clr" ) ) );
			static color old_clr = clr;

			float reflectivity = *config::get<float>( crc( "esp:chams:reflectivity" ) );
			static float old_reflectivity = reflectivity;

			float pearlescent = *config::get<float>( crc( "esp:chams:pearlescent" ) );
			static float old_pearlescent = pearlescent;

			float shine = *config::get<float>( crc( "esp:chams:shine" ) );
			static float old_shine = shine;

			float rim = *config::get<float>( crc( "esp:chams:rim" ) );
			static float old_rim = rim;

			if ( old_clr != clr ||
				 old_reflectivity != reflectivity ||
				 old_pearlescent != pearlescent ||
				 old_shine != shine )
			{
				something_changed = true;
			}

			if ( something_changed )
			{
				kv->set_string( "$basetexture", "" );

				// reflectivity
				{
					char $envmaptint[ 64 ];
					sprintf( $envmaptint, "[%f %f %f]", float( clr.r / 255.f ) * reflectivity / 100.f, float( clr.g / 255.f ) * reflectivity / 100.f, float( clr.b / 255.f ) * reflectivity / 100.f );

					kv->set_string( "$envmaptint", $envmaptint );
					kv->set_string( "$envmap", "env_cubemap" );
				}

				// pearlescence
				{
					char $pearlescent[ 64 ];
					sprintf( $pearlescent, "%f", pearlescent );

					kv->set_string( "$pearlescent", $pearlescent );
				}

				// shine
				{
					kv->set_int( "$phong", 1 );
					kv->set_int( "$phongexponent", 15 );
					kv->set_int( "$normalmapalphaenvmask", 1 );

					char $phongboost[ 64 ];
					sprintf( $phongboost, "[%f %f %f]", shine / 100.f, shine / 100.f, shine / 100.f );

					kv->set_string( "$phongboost", $phongboost );
					kv->set_string( "$phongfresnelranges", "[.5 .5 1]" );
					kv->set_int( "$BasemapAlphaPhongMask", 1 );
				}

				// rim
				{
					kv->set_int( "$rimlight", 1 );
					kv->set_int( "$rimlightexponent", 2 );
					char $rimlightboost[ 64 ];
					sprintf( $rimlightboost, "%f", rim / 100.f );
					kv->set_string( "$rimlightboost", $rimlightboost );
				}

				mat->set_shader_and_params( kv );

				old_clr = clr;
				old_reflectivity = reflectivity;
				old_pearlescent = pearlescent;
				old_shine = shine; // alpha ty kurwa idioto
				something_changed = false;
			}
		}
	}

	if ( strstr( info->model->name, xor ( "shadow" ) ) != nullptr )
	{ // fucking shadows are ugly anyways smfh
		return;
	}

	auto local = interfaces::entity_list->get<player_t>( interfaces::engine->get_local_player( ) );
	if ( local && info && info->entity_index && info->entity_index < 65 )
	{
		if ( strstr( info->model->name, xor ( "models/player" ) ) != nullptr )
		{
			[ & ]( )
			{
				auto ent = interfaces::entity_list->get<player_t>( info->entity_index );
				if ( !ent )
					return;

				if ( !ent->health( ) )
					return;

				if ( ent->team( ) == local->team( ) )
					return;

				auto record = backtrack::find_last_record( info->entity_index );
				if ( record.has_value( ) && *config::get<bool>( crc( "ass:backtrack" ) ) && *config::get<bool>( crc( "esp:chams:backtrack" ) ) )
				{
					if ( std::fabs( ( ent->abs_origin( ) - record.value( ).m_abs_origin ).length( ) ) > 2.5f )
					{
						color clr( *config::get<color>( crc( "ass:backtrack:color" ) ) );

						flat->set_color( clr.r, clr.g, clr.b );
						flat->set_alpha( clr.a );
						flat->set_flag( ( 1 << 15 ), false );

						interfaces::model_render->force_override_material( flat );
						original( record.value( ).m_matrix );
						interfaces::model_render->force_override_material( nullptr );
					}
				}

				if ( *config::get<bool>( crc( "esp:chams:invisible" ) ) )
				{
					color clr( *config::get<color>( crc( "esp:chams:invisible_color" ) ) );

					mat->set_color( clr.r, clr.g, clr.b );
					mat->set_alpha( clr.a );
					mat->set_flag( ( 1 << 15 ), true );

					interfaces::model_render->force_override_material( mat );
					original( matrix );

					if ( !*config::get<bool>( crc( "esp:chams:visible" ) ) )
					{
						interfaces::model_render->force_override_material( nullptr );
						original( matrix );
					}
				}

				if ( *config::get<bool>( crc( "esp:chams:visible" ) ) )
				{
					color clr( *config::get<color>( crc( "esp:chams:color" ) ) );

					mat->set_color( clr.r, clr.g, clr.b );
					mat->set_alpha( clr.a );
					mat->set_flag( ( 1 << 15 ), false );

					interfaces::model_render->force_override_material( mat );
					original( matrix );
				}
			}( );
		}
	}

	original( matrix );
	interfaces::model_render->force_override_material( nullptr );
}