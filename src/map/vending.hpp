// Copyright (c) rAthena Dev Teams - Licensed under GNU GPL
// For more information, see LICENCE in the main folder

#ifndef	_VENDING_HPP_
#define	_VENDING_HPP_

#include <common/cbasetypes.hpp>
#include <common/db.hpp>
#include <common/mmo.hpp>

class MapSessionData;
struct s_search_store_search;
struct s_autotrader;

struct s_vending {
	short index; /// cart index (return item data)
	short amount; ///amout of the item for vending
	unsigned int value; ///at wich price
};

DBMap * vending_getdb();
void do_final_vending(void);
void do_init_vending(void);
void do_init_vending_autotrade( void );
 
void vending_reopen( MapSessionData* sd );
void vending_closevending(MapSessionData* sd);
int8 vending_openvending(MapSessionData* sd, const char* message, const uint8* data, int count, struct s_autotrader *at);
void vending_vendinglistreq(MapSessionData* sd, int id);
void vending_purchasereq(MapSessionData* sd, int aid, int uid, const uint8* data, int count);
bool vending_search(MapSessionData* sd, t_itemid nameid);
bool vending_searchall(MapSessionData* sd, const struct s_search_store_search* s);
void vending_update(MapSessionData &sd);

#endif /* _VENDING_HPP_ */
