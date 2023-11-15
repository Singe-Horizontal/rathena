// Copyright (c) rAthena Dev Teams - Licensed under GNU GPL
// For more information, see LICENCE in the main folder

#ifndef PARTY_HPP
#define PARTY_HPP

#include <stdarg.h>

#include <common/mmo.hpp> // struct party

struct BlockList;
class MapSessionData;
struct party;
struct Item;

#define MAX_PARTY_BOOKING_JOBS 6
#define MAX_PARTY_BOOKING_RESULTS 10

struct party_member_data {
	MapSessionData *sd;
	unsigned int hp; //For HP,x,y refreshing.
	unsigned short x, y;
};

struct party_data {
	struct party party;
	struct party_member_data data[MAX_PARTY];
	uint8 itemc; //For item distribution, position of last picker in party
	int instance_id;
	struct {
		unsigned monk : 1; //There's at least one monk in party?
		unsigned sg : 1;	//There's at least one Star Gladiator in party?
		unsigned snovice :1; //There's a Super Novice
		unsigned tk : 1; //There's a taekwon
	} state;
};

struct party_booking_detail {
	short level;
    short mapid;
    short job[MAX_PARTY_BOOKING_JOBS];
};

struct party_booking_ad_info {
	unsigned long index;
	char charname[NAME_LENGTH];
	long starttime;
	struct party_booking_detail p_detail;
};

struct s_party_booking_requirement{
	uint16 minimum_level;
	uint16 maximum_level;
};

extern int party_create_byscript;

void do_init_party(void);
void do_final_party(void);
struct party_data* party_search(int party_id);
struct party_data* party_searchname(const char* str);
int party_getmemberid(struct party_data* p, MapSessionData* sd);
MapSessionData* party_getavailablesd(struct party_data *p);

int party_create(MapSessionData *sd,char *name, int item, int item2);
void party_created(uint32 account_id,uint32 char_id,int fail,int party_id,char *name);
int party_request_info(int party_id, uint32 char_id);
int party_invite(MapSessionData *sd,MapSessionData *tsd);
void party_member_joined(MapSessionData *sd);
int party_member_added(int party_id,uint32 account_id,uint32 char_id,int flag);
int party_leave(MapSessionData *sd);
int party_removemember(MapSessionData *sd,uint32 account_id,char *name);
int party_removemember2(MapSessionData *sd,uint32 char_id,int party_id);
int party_member_withdraw(int party_id, uint32 account_id, uint32 char_id, char *name, enum e_party_member_withdraw type);
bool party_isleader( MapSessionData* sd );
void party_join( MapSessionData* sd, int party_id );
bool party_booking_load( uint32 account_id, uint32 char_id, struct s_party_booking_requirement* booking );
int party_reply_invite(MapSessionData *sd,int party_id,int flag);
#define party_add_member(party_id,sd) party_reply_invite(sd,party_id,1)
int party_recv_noinfo(int party_id, uint32 char_id);
int party_recv_info(struct party* sp, uint32 char_id);
int party_recv_movemap( int party_id, uint32 account_id, uint32 char_id, int online, int lv, const char* map );
int party_broken(int party_id);
int party_optionchanged(int party_id,uint32 account_id,int exp,int item,int flag);
int party_changeoption(MapSessionData *sd,int exp,int item);
int party_setoption(struct party_data *party, int option, int flag);
int party_changeleader(MapSessionData *sd, MapSessionData *t_sd, struct party_data *p);
void party_send_movemap(MapSessionData *sd);
void party_send_levelup(MapSessionData *sd);
int party_send_logout(MapSessionData *sd);
int party_send_message(MapSessionData *sd,const char *mes,int len);
int party_recv_message(int party_id,uint32 account_id,const char *mes,int len);
int party_skill_check(MapSessionData *sd, int party_id, uint16 skill_id, uint16 skill_lv);
int party_send_xy_clear(struct party_data *p);
void party_exp_share(struct party_data *p,BlockList *src,t_exp base_exp,t_exp job_exp,int zeny);
int party_share_loot(struct party_data* p, MapSessionData* sd, Item* item, int first_charid);
int party_send_dot_remove(MapSessionData *sd);
int party_sub_count(BlockList *bl, va_list ap);
int party_sub_count_class(BlockList *bl, va_list ap);
int party_foreachsamemap(int (*func)(BlockList *,va_list),MapSessionData *sd,int range,...);

/*==========================================
 * Party Booking in KRO [Spiria]
 *------------------------------------------*/
void party_booking_register(MapSessionData *sd, short level, short mapid, short* job);
void party_booking_update(MapSessionData *sd, short* job);
void party_booking_search(MapSessionData *sd, short level, short mapid, short job, unsigned long lastindex, short resultcount);
bool party_booking_delete(MapSessionData *sd);

#endif /* PARTY_HPP */
