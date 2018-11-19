
#include "card.h"

char *SUIT_STRING[] = {
    "DIAMOND",
    "CLUBS",
    "HARTH",
    "SPADES"};

Card *card__init(int value, Suit suit)
{
    if (value < 0 || value > 13)
    {
        fprintf(stderr, "INVALID CARD VALUE %d\n", value);
        exit(EXIT_FAILURE);
    };
    Card *c = (Card *)malloc(sizeof(Card));
    c->value = value;
    c->suit = suit;
    return c;
}

char *card__value(int value)
{
    if (value < 11 && value > 1)
    {
        char *str = malloc(sizeof(char) * 4);
        sprintf(str, "%d", value);
        return str;
    }
    switch (value)
    {
    case 1:
        return "A";
    case 11:
        return "J";
    case 12:
        return "Q";
    case 13:
        return "K";
    default:
        fprintf(stderr, "INVALID CARD VALUE %d\n", value);
        exit(EXIT_FAILURE);
    }
}

char *card__suit(Suit suit)
{
    return SUIT_STRING[suit];
}

void card__print(Card *card, FILE *fp)
{
    fprintf(fp, "%s of %s", card__value(card->value), card__suit(card->suit));
}

void card__print_for_list(void *card)
{
    card__print((Card *)card, stdout);
    puts("");
}
