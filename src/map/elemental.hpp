// Copyright (c) rAthena Dev Teams - Licensed under GNU GPL
// For more information, see LICENCE in the main folder

#ifndef ELEMENTAL_HPP
#define ELEMENTAL_HPP

#include <common/database.hpp>
#include <common/mmo.hpp>
#include <common/timer.hpp>

#include "status.hpp" // struct StatusData, struct StatusChange
#include "unit.hpp" // units::UnitData

const t_tick MIN_ELETHINKTIME = 100;
#define MIN_ELEDISTANCE 2
#define MAX_ELEDISTANCE 5

#define EL_MODE_AGGRESSIVE (MD_CANMOVE|MD_AGGRESSIVE|MD_CANATTACK)
#define EL_MODE_ASSIST (MD_CANMOVE|MD_ASSIST)
#define EL_MODE_PASSIVE MD_CANMOVE

///Enum of Elemental Skill Mode
enum e_elemental_skillmode : uint8 {
	EL_SKILLMODE_PASSIVE    = 0x1,
	EL_SKILLMODE_ASSIST     = 0x2,
	EL_SKILLMODE_AGGRESSIVE = 0x4,
};

#if __cplusplus < 201402L
namespace std {
	template <> struct hash<e_elemental_skillmode> {
		size_t operator() (const e_elemental_skillmode& t) const { return size_t(t); }
	};
}
#endif

///Enum of Elemental ID
enum elemental_elementalid  : uint16 {
	// Sorcerer's Elementals
	ELEMENTALID_AGNI_S = 2114,
	ELEMENTALID_AGNI_M,
	ELEMENTALID_AGNI_L,
	ELEMENTALID_AQUA_S,
	ELEMENTALID_AQUA_M,
	ELEMENTALID_AQUA_L,
	ELEMENTALID_VENTUS_S,
	ELEMENTALID_VENTUS_M,
	ELEMENTALID_VENTUS_L,
	ELEMENTALID_TERA_S,
	ELEMENTALID_TERA_M,
	ELEMENTALID_TERA_L,

	// Elemental Master's Elementals
	ELEMENTALID_DILUVIO = 20816,
	ELEMENTALID_ARDOR,
	ELEMENTALID_PROCELLA,
	ELEMENTALID_TERREMOTUS,
	ELEMENTALID_SERPENS,
};

struct s_elemental_skill {
	uint16 id, lv;
};

struct s_elemental_db {
	int32 class_;
	std::string sprite, name;
	uint16 lv;
	uint16 range2, range3;
	StatusData status;
	ViewData vd;
	std::unordered_map<e_elemental_skillmode, std::shared_ptr<s_elemental_skill>> skill;	/// mode, skill
};

struct s_elemental_data {
	BlockList bl;
	units::UnitData ud;
	ViewData *vd;
	StatusData base_status, battle_status;
	StatusChange sc;
	RegenData regen;

	std::shared_ptr<s_elemental_db> db;
	s_elemental elemental;

	int masterteleport_timer;
	MapSessionData *master;
	int summon_timer;
	int skill_timer;

	t_tick last_thinktime, last_linktime, last_spdrain_time;
	short min_chase;
	int target_id, attacked_id;
};

class ElementalDatabase : public TypesafeYamlDatabase<int32, s_elemental_db> {
public:
	ElementalDatabase() : TypesafeYamlDatabase("ELEMENTAL_DB", 1) {

	}

	const std::string getDefaultLocation() override;
	uint64 parseBodyNode(const ryml::NodeRef& node) override;
};

extern ElementalDatabase elemental_db;

ViewData * elemental_GetViewData(int class_);

int elemental_create(MapSessionData *sd, int class_, unsigned int lifetime);
int elemental_data_received(s_elemental *ele, bool flag);
int elemental_save(s_elemental_data *ed);

int elemental_change_mode_ack(s_elemental_data *ed, e_elemental_skillmode skill_mode);
int elemental_change_mode(s_elemental_data *ed, int mode);

void elemental_heal(s_elemental_data *ed, int hp, int sp);
int elemental_dead(s_elemental_data *ed);

int elemental_delete(s_elemental_data *ed);
void elemental_summon_stop(s_elemental_data *ed);

t_tick elemental_get_lifetime(s_elemental_data *ed);

int elemental_unlocktarget(s_elemental_data *ed);
bool elemental_skillnotok(uint16 skill_id, s_elemental_data *ed);
int elemental_set_target( MapSessionData *sd, BlockList *bl );
int elemental_clean_effect(s_elemental_data *ed);
int elemental_action(s_elemental_data *ed, BlockList *bl, t_tick tick);
struct s_skill_condition elemental_skill_get_requirements(uint16 skill_id, uint16 skill_lv);

#define elemental_stop_walking(ed, type) units::StopWalking(&(ed)->bl, type)
#define elemental_stop_attack(ed) units::StopAttack(&(ed)->bl)

void do_init_elemental(void);
void do_final_elemental(void);

#endif /* ELEMENTAL_HPP */
