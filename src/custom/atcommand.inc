// Copyright (c) rAthena Dev Teams - Licensed under GNU GPL
// For more information, see LICENCE in the main folder

/**
 * Custom Atcommands
 * Place the body of custom atcommands in this file.
 * Format:
 *	ACMD_FUNC(command_name)
 *	{
 *		<code>;
 *	}
 **/

//ACMD_FUNC(newcommand)
//{
//	clif_displaymessage(fd, "It works!");
//	clif_specialeffect(&sd->bl, EF_HEARTCASTING, AREA);
//	return 0;
//}



/*==========================================
 *
 *------------------------------------------*/
ACMD_FUNC(master)
{
	const int maxsummons = 6;
	char name[maxsummons][NAME_LENGTH];
	int mob_id = 0;
	struct mob_data* master = nullptr;
	struct mob_data* md = nullptr;
	t_tick tick=gettick();
	int count = 0;
	nullpo_retr(-1, sd);
	int n = 0;
	if (!message || !*message || (n=sscanf(message, "%23s %23s %23s %23s %23s %23s", name[0], name[1], name[2], name[3], name[4], name[5])) < 1)
	{
		clif_displaymessage(fd, msg_txt(sd,1225)); // Please enter a monster name (usage: @summon <monster name> {duration}).
		return -1;
	}
	//parent_cmd = atcommand_alias_db.checkAlias(command+1);
	mob_ai ai = AI_NONE;
	int size = SZ_SMALL;
	if (strcmp(command+1, "masterbig") == 0)
		size = SZ_BIG;
	else if (strcmp(command+1, "mastersmall") == 0)
		size = SZ_MEDIUM;
	else if (strcmp(command+1, "friendmaster") == 0)
		ai = AI_GUILD;
	else if (strcmp(command+1, "friendmasterbig") == 0){
		ai = AI_GUILD;
		size = SZ_BIG;
	}else if (strcmp(command+1, "friendmastersmall") == 0){
		ai = AI_GUILD;
		size = SZ_MEDIUM;
	}
	for (int i = 0; i < n; ++i) {
		if (i > 0) {
			if (name[i] == "")
				continue;
			if ((mob_id = atoi(name[i])) == 0)
				mob_id = mobdb_searchname(name[i]);
			if (mob_id == 0 || mobdb_checkid(mob_id) == 0)
			{
				//clif_displaymessage(fd, msg_txt(sd, 40));	// Invalid monster ID or name.
				continue;
			}
			md = mob_once_spawn_sub(&master->bl, master->bl.m, -1, -1, "--ja--", mob_id, "", size, ai);
			if (!md)
				continue;
			md->master_id = master->bl.id;
			//md->special_state.ai = AI_ATTACK;
			clif_specialeffect(&md->bl, EF_ENTRY2, AREA);
			mob_spawn(md);
			sc_start4(nullptr, &md->bl, SC_MODECHANGE, 100, 1, 0, MD_AGGRESSIVE, 0, 0);
			clif_skill_poseffect(&master->bl, AM_CALLHOMUN, 1, md->bl.x, md->bl.y, tick);
		} else {
			if (name[i] == "")
				;
			else if ((mob_id = atoi(name[i])) == 0)
				mob_id = mobdb_searchname(name[i]);
			else if (mob_id == 0 || mobdb_checkid(mob_id) == 0)
			{
				clif_displaymessage(fd, msg_txt(sd, 40));	// Invalid master ID or name.
				return -1;
			}

			master=mob_once_spawn_sub(&sd->bl, sd->bl.m, -1, -1, "--ja--", mob_id, "", size, ai);
			if (!master)
				return -1;
			clif_specialeffect(&master->bl, EF_ENTRY2, AREA);
			master->can_summon = true;
			mob_spawn(master);
		}
		count++;
	}
	if (count == 0)
		return -1;
	clif_displaymessage(fd, msg_txt(sd,39));	// All monster summoned!

	return 0;
}
