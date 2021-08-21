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

#include "walkbot.hpp"
#include <ctime>
#include "../../nav/nav_file.h"
#include "../renderer/renderer.hpp"
#include "../../engine/utilities/math.hpp"
namespace walkbot {
	struct {
		nav_mesh::nav_file* nav;

		std::vector<vec3_t> path;
		int current_point;
		int64_t next_path_refresh = 0;

		std::string map_name{};
	} ctx;
}

void correct_movement(c_usercmd* command, vec3 old_angles, float old_forward, float old_sidemove) { /* keep this last because its really messy */
	if (command->forward_move >= 450) command->forward_move = 450;
	if (command->side_move >= 450) command->side_move = 450;
	if (command->up_move >= 450) command->up_move = 450;
	if (command->forward_move <= -450) command->forward_move = -450;
	if (command->side_move <= -450) command->side_move = -450;
	if (command->up_move <= -450) command->up_move = -450;

	// side/forward move correction
	float delta;
	float f1;
	float f2;

	if (old_angles.y < 0.f)
		f1 = 360.0f + old_angles.y;
	else
		f1 = old_angles.y;

	if (command->view_angles.y < 0.0f)
		f2 = 360.0f + command->view_angles.y;
	else
		f2 = command->view_angles.y;

	if (f2 < f1)
		delta = abs(f2 - f1);
	else
		delta = 360.0f - abs(f1 - f2);

	delta = 360.0f - delta;

	command->forward_move = cos(utils::math::deg_to_rad(delta)) * old_forward + cos(utils::math::deg_to_rad(delta + 90.f)) * old_sidemove;
	command->side_move = sin(utils::math::deg_to_rad(delta)) * old_forward + sin(utils::math::deg_to_rad(delta + 90.f)) * old_sidemove;
}

void walkbot::on_painttraverse() {
	static bool initialized = false;
	if (!initialized) {
		if (strlen(interfaces::client_state->level_name) < 2)
			return;

		initialized = true;
		// fix path v
		if (ctx.nav)
			delete ctx.nav;

		std::string map_name = interfaces::client_state->level_name;
		map_name = map_name.substr(0, map_name.find_last_of("."));

		ctx.nav = new nav_mesh::nav_file(std::string("csgo\\").append(map_name).append(".nav"));
		ctx.map_name = interfaces::client_state->level_name;
		// fix path ^
	}

	if (ctx.map_name != std::string(interfaces::client_state->level_name)) {
		initialized = false;
		return;
	}

	auto local = interfaces::entity_list->get<player_t>(interfaces::engine->get_local_player());
	if (!local->sane(false, false, false))
		return;

	if (time(nullptr) > ctx.next_path_refresh) {
		printf("refreshing path\n");

		std::vector<player_t*> enemies;

		for (int i = 1; i <= 64; i++) {
			auto ent = interfaces::entity_list->get<player_t>(i);
			if (ent->sane(true, false) && ent->team() != local->team())
				enemies.emplace_back(ent);
		}

		const auto local_position = local->abs_origin();

		std::sort(enemies.begin(), enemies.end(),
			[&](player_t* a, player_t* b) -> bool
			{
				return a->abs_origin().dist_to(local_position) > b->abs_origin().dist_to(local_position);
			});

		if (enemies.empty()) {
			ctx.next_path_refresh = time(nullptr) + 1;
			return;
		}

		for (auto enemy : enemies) {
			const auto pos = enemy->abs_origin();
			ctx.path = ctx.nav->find_path(local->abs_origin(), pos);
			if (!ctx.path.empty())
				break;
		}

		ctx.next_path_refresh = time(nullptr) + 3;

		ctx.current_point = 0;
	}

	for (int i = 1; i < ctx.path.size(); i++) {
		const auto current_point = ctx.path[i];
		const auto previous_point = ctx.path[i - 1];

		// this is epic
		const auto c = color((int)current_point.x % 255, (int)current_point.y % 255, (int)current_point.z % 255);

		vec3_t screen_point;
		vec3_t screen_previous;
		if (interfaces::debug_overlay->world_to_screen(current_point, screen_point) &&
			interfaces::debug_overlay->world_to_screen(previous_point, screen_previous))
			render::line(point(screen_point.x, screen_point.y), point(screen_previous.x, screen_previous.y), c);
	}
}

bool can_hit(weapon_t* weapon) {
	weapon->update_accuracy_penalty();
	float hit_chance = 1.0f / max(0.0000001f, weapon->get_innacuracy());
	return (hit_chance >= (static_cast<float>(50.f) * 1.5f));
}

void walkbot::on_create_move(c_usercmd* cmd) {
	auto local = interfaces::entity_list->get<player_t>(interfaces::engine->get_local_player());
	static bool was_alive = false;
	static int death_tick = 0;
	if (!local->sane(false, false, false)) {
		if (!ctx.path.empty())
			ctx.path.clear();

		was_alive = false;
		death_tick = interfaces::globals->tick_count;
		return;
	}

	if (!local->alive()) {
		was_alive = false;
		death_tick = interfaces::globals->tick_count;
		return;
	}

	if (!was_alive) {
		// this is broken buy 25 ticks later
		if (interfaces::globals->tick_count - death_tick > 25) {
			interfaces::engine->execute_cmd("buy ak47");
			interfaces::engine->execute_cmd("buy m4a1");
			was_alive = true;
		}

		return;
	}

	// do the aimbot here so it doesnt walak and shoto :D:D :D
	player_t* enemy = nullptr;
	for (int i = 1; i <= 64; i++) {
		auto ent = interfaces::entity_list->get<player_t>(i);
		if (!ent->sane(true, true))
			continue;

		if (ent->team() == local->team())
			continue;

		if (!local->can_see(ent, ent->bone_pos(6)))
			continue;

		enemy = ent;
		break;
	}

	if (enemy) {
		if (!ctx.path.empty())
			ctx.path.clear();

		auto aim_angle = utils::math::calc_angle(local->eye_pos(), enemy->bone_pos(6));
		// add smoothing

		auto delta = aim_angle - interfaces::engine->get_view_angles(); delta.clamp();
		delta = delta / 4.5f;

		auto new_angles = interfaces::engine->get_view_angles() + delta;

		auto weapon = local->active_weapon();
		if (!weapon)
			return;

		interfaces::engine->set_view_angles(new_angles);
		if (utils::math::get_fov(cmd->view_angles, aim_angle) < 3.f && can_hit(weapon))
			cmd->buttons |= in_attack;

			cmd->view_angles -= local->aim_punch_angle() * 2;
		return;
	}

	if (ctx.current_point >= ctx.path.size() - 1) {
		ctx.path.clear();
		return;
	}

	if (ctx.path.empty())
		return;

	if (ctx.current_point + 2 < ctx.path.size()) {
		auto point_angle = utils::math::calc_angle(local->eye_pos(), ctx.path[ctx.current_point + 2]);
		point_angle.x = std::clamp(point_angle.x, -20.f, 0.f);
		auto yaw_delta = (point_angle - cmd->view_angles);
		yaw_delta.clamp();

		auto angles = cmd->view_angles;
		angles.y += yaw_delta.y / 10.f;
		angles.x += yaw_delta.x / 20.f;


		cmd->view_angles = angles;
		interfaces::engine->set_view_angles(angles);
	}

	auto weapon = local->active_weapon();

	static bool reloading = false;
	if (interfaces::globals->tick_count % 120 == 7 && weapon)
		if (weapon->clip1_count() < 16)
			cmd->buttons |= in_reload;
	

	cmd->forward_move = 450.f;

	vec3 old_angles = cmd->view_angles;
	float old_forward_move = cmd->forward_move;
	float old_side_move = cmd->side_move;

	const auto ang = utils::math::calc_angle(local->eye_pos(), ctx.path[ctx.current_point]);
	if (local->abs_origin().dist_to(ctx.path[ctx.current_point]) < 27.f) {
		ctx.current_point++;
	}

	correct_movement(cmd, ang, old_forward_move, old_side_move);
	if (local->velocity().length_2d() < 5.f && ctx.path[ctx.current_point].z - local->abs_origin().z > 25.f) {
		cmd->buttons |= in_jump;
	}
}