#include "player.h"

Player player__init()
{
    return list__init();
}

void player__draw(Deck *deck, Player *player, int num_cards)
{
    for (int i = 0; i < num_cards; i++)
    {
        if (!deck__is_empty(deck))
            list__insert(deck__draw(deck), player);
    }
}
int player__empty_hand(Player player)
{
    return list__is_empty(player);
}

Card *player__play(Player *player)
{
    return list__remove(player);
}

void player__print(Player player)
{
    list__foreach(player, card__print_for_list);
}