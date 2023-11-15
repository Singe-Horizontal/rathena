// Copyright (c) rAthena Dev Teams - Licensed under GNU GPL
// For more information, see LICENCE in the main folder

#ifndef TRADE_HPP
#define TRADE_HPP

class MapSessionData;

void trade_traderequest(MapSessionData *sd, MapSessionData *target_sd);
void trade_tradeack(MapSessionData *sd,int type);
void trade_tradeadditem(MapSessionData *sd,short index,short amount);
void trade_tradeaddzeny(MapSessionData *sd,int amount);
void trade_tradeok(MapSessionData *sd);
void trade_tradecancel(MapSessionData *sd);
void trade_tradecommit(MapSessionData *sd);

#endif /* TRADE_HPP */
