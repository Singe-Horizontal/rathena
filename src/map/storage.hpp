// Copyright (c) rAthena Dev Teams - Licensed under GNU GPL
// For more information, see LICENCE in the main folder

#ifndef STORAGE_HPP
#define STORAGE_HPP

#include <memory>
#include <unordered_map>
#include <vector>

#include <common/cbasetypes.hpp>
#include <common/mmo.hpp>

struct s_storage;
struct Item;
class MapSessionData;

extern std::unordered_map<uint16, std::shared_ptr<struct s_storage_table>> storage_db;

enum e_storage_add {
	STORAGE_ADD_OK,
	STORAGE_ADD_NOROOM,
	STORAGE_ADD_NOACCESS,
	STORAGE_ADD_INVALID,
};

/// Guild storage flags
enum e_guild_storage_flags : uint8 {
	GSTORAGE_OPEN = 0,
	GSTORAGE_STORAGE_ALREADY_OPEN,
	GSTORAGE_ALREADY_OPEN,
	GSTORAGE_NO_GUILD,
	GSTORAGE_NO_STORAGE,
	GSTORAGE_NO_PERMISSION
};

enum e_guild_storage_log : uint16 {
	GUILDSTORAGE_LOG_SUCCESS,
	GUILDSTORAGE_LOG_FINAL_SUCCESS,
	GUILDSTORAGE_LOG_EMPTY,
	GUILDSTORAGE_LOG_FAILED,
};

struct guild_log_entry{
	uint32 id;
	char name[NAME_LENGTH];
	char time[NAME_LENGTH];
	Item item;
	int16 amount;
};

const char *storage_getName(uint8 id);
bool storage_exists(uint8 id);

int storage_delitem(MapSessionData* sd, struct s_storage *stor, int index, int amount);
int storage_storageopen(MapSessionData *sd);
void storage_storageadd(MapSessionData *sd, struct s_storage *stor, int index, int amount);
void storage_storageget(MapSessionData *sd, struct s_storage *stor, int index, int amount);
void storage_storageaddfromcart(MapSessionData *sd, struct s_storage *stor, int index, int amount);
void storage_storagegettocart(MapSessionData *sd, struct s_storage *stor, int index, int amount);
void storage_storagesave(MapSessionData *sd);
void storage_storageclose(MapSessionData *sd);
void storage_sortitem(Item* items, unsigned int size);
void do_init_storage(void);
void do_final_storage(void);
void do_reconnect_storage(void);
void storage_storage_quit(MapSessionData *sd, int flag);

struct s_storage* guild2storage(int guild_id);
struct s_storage* guild2storage2(int guild_id);
void storage_guild_delete(int guild_id);
char storage_guild_storageopen(MapSessionData *sd);
enum e_guild_storage_log storage_guild_log_read( MapSessionData* sd );
bool storage_guild_additem(MapSessionData *sd,struct s_storage *stor,Item *ItemData,int amount);
bool storage_guild_additem2(struct s_storage* stor, Item* item, int amount);
bool storage_guild_delitem(MapSessionData *sd,struct s_storage *stor,int n,int amount);
void storage_guild_storageadd(MapSessionData *sd,int index,int amount);
void storage_guild_storageget(MapSessionData *sd,int index,int amount);
void storage_guild_storageaddfromcart(MapSessionData *sd,int index,int amount);
void storage_guild_storagegettocart(MapSessionData *sd,int index,int amount);
void storage_guild_storageclose(MapSessionData *sd);
void storage_guild_storage_quit(MapSessionData *sd,int flag);
bool storage_guild_storagesave(uint32 account_id, int guild_id, int flag);
void storage_guild_storagesaved(int guild_id); //Ack from char server that guild store was saved.

// Premium Storage [Cydh]
void storage_premiumStorage_open(MapSessionData *sd);
bool storage_premiumStorage_load(MapSessionData *sd, uint8 num, uint8 mode);
void storage_premiumStorage_save(MapSessionData *sd);
void storage_premiumStorage_close(MapSessionData *sd);
void storage_premiumStorage_quit(MapSessionData *sd);

int compare_item(Item *a, Item *b);

#endif /* STORAGE_HPP */
