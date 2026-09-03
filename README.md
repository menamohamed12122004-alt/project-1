# Practice-project-1
# Project 1 — My Piggy Bank

## The story 

You have a piggy bank. You drop coins in it. Sometimes you take coins out to
buy something. The piggy bank tells you how much money is inside, which coin
you have the most of, and whether you have enough for a toy.

## The data

```c
#define COIN_KINDS   5U
#define TOY_COUNT    4U
#define NAME_LEN    16U

/* the coins we know about, in piastres */
static const uint16_t COIN_VALUE[COIN_KINDS] = { 25U, 50U, 100U, 200U, 500U };

/* how many of each coin are in the bank right now */
static uint16_t coinCount[COIN_KINDS];

typedef struct {
    char     name[NAME_LEN];
    uint32_t price;        /* in piastres */
} Toy_t;

static Toy_t shop[TOY_COUNT];
```

## The functions — you write the bodies

```c
static void     seedBank(void);
static void     addCoins(void);
static void     takeCoins(void);
static uint32_t bankTotal(void);
static uint32_t sumCoins(const uint16_t *counts, uint8_t n);
static uint8_t  biggestPile(void);
static void     showBank(void);
static void     drawBar(uint16_t value, uint16_t full, uint8_t width);
static void     buyToy(void);
static void     bankReport(void);
```

| Function | What it must do, in easy words |
|---|---|
| `seedBank()` | Put some starting coins in the piggy bank and write the four toy names and prices into `shop`. This is the "new game" button. |
| `addCoins()` | Ask which coin (0–4) and how many. Drop them in. If the person types a coin that does not exist, say so and change nothing. |
| `takeCoins()` | Ask which coin and how many to take out. If the bank does not have that many, refuse and take **nothing**. Never let a count go below zero. |
| `bankTotal()` | Give back how much money is in the bank altogether, in piastres. Every coin counted, nothing left out. |
| `sumCoins()` | Add up the numbers in an array — but with **recursion**, no loop. Zero coins means zero. Otherwise: the last one plus all the ones before it. |
| `biggestPile()` | Tell which coin you have the most of, by giving back its position (0–4). If two are tied, the smaller position wins. |
| `showBank()` | Draw the bank: one line per coin kind showing the coin's value, how many you have, and a bar so you can *see* which pile is tallest. |
| `drawBar()` | Print exactly `width` characters: `#` for the full part, `-` for the empty part. A value bigger than `full` fills the whole bar and not one character more. |
| `buyToy()` | Show the four toys and their prices. Ask which one. If the bank has enough money, say "you can buy it" and how much is left over. If not, say how much more you need. Do not remove coins. |
| `bankReport()` | The summary page: total money, the number of coins altogether, the tallest pile's name, and how many of the four toys you can afford today. |

## When you are done, this must be true

- Taking out more coins than you own changes nothing at all.
- `sumCoins()` has no `for` and no `while` anywhere inside it.
- Typing `hello` at the menu prints one polite message, not an endless spin.
- An empty piggy bank shows a total of 0 and four toys you cannot afford.

---
