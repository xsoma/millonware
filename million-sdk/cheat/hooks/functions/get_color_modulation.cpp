#include "../hooks.hpp"
#include "../../../engine/utilities/config.hpp"

void __fastcall hooks::get_color_modulation(void* ecx, void* edx, float* r, float* g, float* b) {
	gcm_holy_hook.call_original<void>(ecx, edx, r, g, b);

	if (false) {
		auto material = reinterpret_cast<i_material*>(ecx);

		auto name = material->get_name();
		auto group = material->get_group_name();

		if (strstr(group, "Other") || strstr(name, "player") || strstr(name, "chams") ||
			strstr(name, "weapon") || strstr(name, "glow"))
			return;

		bool is_prop = strstr(group, "StaticProp");

		*r *= is_prop ? 0.5f : 0.2f;
		*g *= is_prop ? 0.5f : 0.2f;
		*b *= is_prop ? 0.5f : 0.2f;
	}
}