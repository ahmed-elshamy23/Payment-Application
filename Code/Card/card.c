#include <stdio.h>
#include <string.h>
#include "card.h"

EN_cardError_t getCardHolderName(ST_cardData_t *cardData)
{
    printf("Enter card holder\'s name: ");
    scanf("%[^\n]*c", &cardData->cardHolderName);
    if (strlen(cardData->cardHolderName) >= 20 && strlen(cardData->cardHolderName) <= 24)
    {
        return OK_CARD;
    }
    else
    {
        return WRONG_NAME;
    }
}

EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData)
{
    printf("Enter card expiry date: ");
    scanf("%[^\n]*c", &cardData->cardExpirationDate);
    for (uint8_t i = 0; i < strlen(cardData->cardExpirationDate); i++)
    {
        if (i == 2)
            if (cardData->cardExpirationDate[2] != '/')
                return WRONG_EXP_DATE;
        if (cardData->cardExpirationDate[i] < '0' && cardData->cardExpirationDate[i] > '9')
            return WRONG_EXP_DATE;
    }
    if (strlen(cardData->cardExpirationDate) == 5)
    {
        return OK_CARD;
    }
    else
    {
        return WRONG_EXP_DATE;
    }
}

EN_cardError_t getCardPAN(ST_cardData_t *cardData)
{
    printf("Enter card Primary Account Number: ");
    scanf("%[^\n]*c", &cardData->primaryAccountNumber);
    if (strlen(cardData->primaryAccountNumber) >= 16 && strlen(cardData->primaryAccountNumber) <= 19)
    {
        return OK_CARD;
    }
    else
    {
        return WRONG_PAN;
    }
}