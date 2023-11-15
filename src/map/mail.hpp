// Copyright (c) rAthena Dev Teams - Licensed under GNU GPL
// For more information, see LICENCE in the main folder

#ifndef MAIL_HPP
#define MAIL_HPP

#include <common/mmo.hpp>

enum mail_attach_result {
	MAIL_ATTACH_SUCCESS = 0,
#if PACKETVER >= 20150513
	MAIL_ATTACH_WEIGHT = 1,
	MAIL_ATTACH_ERROR = 2,
	MAIL_ATTACH_SPACE = 3,
	MAIL_ATTACH_UNTRADEABLE = 4,
#else
	MAIL_ATTACH_WEIGHT = 1,
	MAIL_ATTACH_ERROR = 1,
	MAIL_ATTACH_SPACE = 1,
	MAIL_ATTACH_UNTRADEABLE = 1,
#endif

	// Unofficial
	MAIL_ATTACH_EQUIPSWITCH = 99,
};

void mail_clear(MapSessionData *sd);
int mail_removeitem(MapSessionData *sd, short flag, int idx, int amount);
bool mail_removezeny(MapSessionData *sd, bool flag);
enum mail_attach_result mail_setitem(MapSessionData *sd, short idx, uint32 amount);
bool mail_setattachment(MapSessionData *sd, struct mail_message *msg);
void mail_getattachment(MapSessionData* sd, struct mail_message* msg, int zeny, Item* item);
int mail_openmail(MapSessionData *sd);
void mail_deliveryfail(MapSessionData *sd, struct mail_message *msg);
bool mail_invalid_operation(MapSessionData *sd);
void mail_send(MapSessionData *sd, const char *dest_name, const char *title, const char *body_msg, int body_len);
void mail_refresh_remaining_amount( MapSessionData* sd );

#endif /* MAIL_HPP */
