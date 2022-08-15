#include <stdio.h>
#include <string.h>
#include "terminal.h"

EN_terminalError_t getTransactionDate(ST_terminalData_t *termData)
{
    printf("Enter transaction date: "); // DD/MM/YYYY
    scanf("%[^\n]*c", &termData->transactionDate);
    for (uint8_t i = 0; i < strlen(termData->transactionDate); i++)
    {
        if (i == 2 || i == 5)
            continue;
        if (termData->transactionDate[i] < '0' && termData->transactionDate[i] > '9')
            return WRONG_DATE;
    }
    if (strlen(termData->transactionDate) == 10 && termData->transactionDate[2] == '/' && termData->transactionDate[5] == '/')
    {
        return OK_TERMINAL;
    }
    else
    {
        return WRONG_DATE;
    }
}

EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData)
{
    // card: MM/YY
    // terminal: DD/MM/YYYY
    for (uint8_t i = 3; i < 5; i++)
    {
        if (cardData.cardExpirationDate[i] < termData.transactionDate[i + 5])
        {
            return EXPIRED_CARD;
        }
    }
    for (uint8_t i = 0; i < 2; i++)
    {
        if (cardData.cardExpirationDate[i] < termData.transactionDate[i + 3])
        {
            return EXPIRED_CARD;
        }
    }
    return OK_TERMINAL;
}

EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData)
{
    printf("Enter transaction amount: ");
    scanf("%f", &termData->transAmount);
    if (termData->transAmount > 0.0f)
    {
        return OK_TERMINAL;
    }
    else
    {
        return INVALID_AMOUNT;
    }
}

EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData)
{
    if (termData->transAmount <= termData->maxTransAmount)
    {
        return OK_TERMINAL;
    }
    else
    {
        return EXCEED_MAX_AMOUNT;
    }
}

EN_terminalError_t setMaxAmount(ST_terminalData_t *termData)
{
    termData->maxTransAmount = 10000;
    if (termData->maxTransAmount > 0.0f)
    {
        return OK_TERMINAL;
    }
    else
    {
        return INVALID_MAX_AMOUNT;
    }
}