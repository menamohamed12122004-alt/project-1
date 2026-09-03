#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define COIN_KINDS   5U
#define TOY_COUNT    4U
#define NAME_LEN    16U

static const uint16_t COIN_VALUE[COIN_KINDS] = { 25U, 50U, 100U, 200U, 500U };
static uint16_t coinCount[COIN_KINDS];

typedef struct {
    char     name[NAME_LEN];
    uint32_t price;        
} Toy_t;

static Toy_t shop[TOY_COUNT] = {
    { "Rubber Duck", 300U  },
    { "Yo-Yo",        750U  },
    { "Lego Set",     1500U },
    { "RC Car",       3000U }
};
static void seedBank(void)
{
    coinCount[0] = 4U;  
    coinCount[1] = 6U;  
    coinCount[2] = 10U; 
    coinCount[3] = 3U; 
    coinCount[4] = 1U; 

    printf("\n[+] Piggy Bank reset and seeded successfully!\n");
}

/* 2. إضافة عملات للحصالة */
static void addCoins(void)
{
    int kindInput = 0;
    int countInput = 0;

    printf("\nAvailable coins:\n");
    for (uint8_t i = 0U; i < COIN_KINDS; ++i)
    {
        printf("  %u) %u pt\n", i, COIN_VALUE[i]);
    }

    if (!readInt("Select coin kind (0-4): ", &kindInput) || kindInput < 0 || kindInput >= (int)COIN_KINDS)
    {
        printf("[!] Invalid coin kind! Nothing added.\n");
        return;
    }

    if (!readInt("How many coins to add? ", &countInput) || countInput <= 0)
    {
        printf("[!] Invalid count! Nothing added.\n");
        return;
    }

    coinCount[kindInput] += (uint16_t)countInput;
    printf("[+] Added %d coin(s) of %u pt.\n", countInput, COIN_VALUE[kindInput]);
}

static void takeCoins(void)
{
    int kindInput = 0;
    int countInput = 0;

    printf("\nAvailable coins:\n");
    for (uint8_t i = 0U; i < COIN_KINDS; ++i)
    {
        printf("  %u) %u pt (You have: %u)\n", i, COIN_VALUE[i], coinCount[i]);
    }

    if (!readInt("Select coin kind (0-4): ", &kindInput) || kindInput < 0 || kindInput >= (int)COIN_KINDS)
    {
        printf("[!] Invalid coin kind! Refused.\n");
        return;
    }

    if (!readInt("How many coins to take? ", &countInput) || countInput <= 0)
    {
        printf("[!] Invalid amount! Refused.\n");
        return;
    }

    if ((uint16_t)countInput > coinCount[kindInput])
    {
        printf("[!] Refused: Not enough coins of this kind! Nothing taken.\n");
        return;
    }

    coinCount[kindInput] -= (uint16_t)countInput;
    printf("[-] Took out %d coin(s) of %u pt.\n", countInput, COIN_VALUE[kindInput]);
}

static uint32_t bankTotal(void)
{
    uint32_t total = 0U;
    for (uint8_t i = 0U; i < COIN_KINDS; ++i)
    {
        total += (uint32_t)coinCount[i] * COIN_VALUE[i];
    }
    return total;
}

static uint32_t sumCoins(const uint16_t *counts, uint8_t n)
{
    if (n == 0U)
    {
        return 0U;
    }
    return (uint32_t)counts[n - 1U] + sumCoins(counts, n - 1U);
}

static uint8_t biggestPile(void)
{
    uint8_t maxIdx = 0U;
    for (uint8_t i = 1U; i < COIN_KINDS; ++i)
    {
        if (coinCount[i] > coinCount[maxIdx])
        {
            maxIdx = i;
        }
    }
    return maxIdx;
}

static void drawBar(uint16_t value, uint16_t full, uint8_t width)
{
    if (full == 0U)
    {
        full = 1U;
    }

    uint32_t filledChars = ((uint32_t)value * width) / full;
    if (filledChars > width)
    {
        filledChars = width;
    }

    for (uint8_t i = 0U; i < width; ++i)
    {
        if (i < filledChars)
        {
            putchar('#');
        }
        else
        {
            putchar('-');
        }
    }
}

static void showBank(void)
{
    uint16_t maxCount = coinCount[biggestPile()];
    if (maxCount == 0U)
    {
        maxCount = 1U;
    }

    printf("\n================ PIGGY BANK ================\n");
    for (uint8_t i = 0U; i < COIN_KINDS; ++i)
    {
        printf("%3u pt | Count: %4u | ", COIN_VALUE[i], coinCount[i]);
        drawBar(coinCount[i], maxCount, 20U);
        printf("\n");
    }
    printf("============================================\n");
}

static void buyToy(void)
{
    uint32_t currentMoney = bankTotal();
    int choice = 0;

    printf("\n--- Toy Shop ---\n");
    printf("Current Money: %u pt\n\n", currentMoney);

    for (uint8_t i = 0U; i < TOY_COUNT; ++i)
    {
        printf("  %u) %-12s - %u pt\n", i, shop[i].name, shop[i].price);
    }

    if (!readInt("Which toy would you like to check (0-3)? ", &choice) || choice < 0 || choice >= (int)TOY_COUNT)
    {
        printf("[!] Invalid choice!\n");
        return;
    }

    Toy_t selected = shop[choice];
    printf("\nToy: %s | Price: %u pt\n", selected.name, selected.price);

    if (currentMoney >= selected.price)
    {
        uint32_t leftover = currentMoney - selected.price;
        printf("[✓] You CAN afford this toy! Remaining balance would be: %u pt.\n", leftover);
    }
    else
    {
        uint32_t needed = selected.price - currentMoney;
        printf("[✗] You CANNOT afford this toy yet. You need %u pt more.\n", needed);
    }
}

static void bankReport(void)
{
    uint32_t totalMoney = bankTotal();
    uint32_t totalCoins = sumCoins(coinCount, COIN_KINDS);
    uint8_t tallestIdx  = biggestPile();

    uint8_t affordableCount = 0U;
    for (uint8_t i = 0U; i < TOY_COUNT; ++i)
    {
        if (totalMoney >= shop[i].price)
        {
            affordableCount++;
        }
    }

    printf("\n============= BANK SUMMARY REPORT =============\n");
    printf(" Total Money      : %u piastres\n", totalMoney);
    printf(" Total Coins      : %u coins\n", totalCoins);
    printf(" Largest Pile     : %u pt coin (%u coins)\n", COIN_VALUE[tallestIdx], coinCount[tallestIdx]);
    printf(" Affordable Toys  : %u out of %u\n", affordableCount, TOY_COUNT);
    printf("===============================================\n");
}

int main(void)
{
    int choice = 0;

    seedBank();

    do
    {
        printf("\n========== MY PIGGY BANK ==========\n");
        printf(" 1. Show Bank Visuals\n");
        printf(" 2. Add Coins\n");
        printf(" 3. Take Coins\n");
        printf(" 4. Check Toy Shop\n");
        printf(" 5. Full Bank Report\n");
        printf(" 6. Reset / Seed Bank\n");
        printf(" 0. Exit\n");
        printf("===================================\n");

        if (!readInt("Select option: ", &choice))
        {
            printf("[!] Invalid input! Please enter a number.\n");
            continue;
        }

        switch (choice)
        {
            case 1:
                showBank();
                break;
            case 2:
                addCoins();
                break;
            case 3:
                takeCoins();
                break;
            case 4:
                buyToy();
                break;
            case 5:
                bankReport();
                break;
            case 6:
                seedBank();
                break;
            case 0:
                printf("\nGoodbye!\n");
                break;
            default:
                printf("[!] Unknown choice. Try again.\n");
                break;
        }

    } while (choice != 0);

    return 0;
}