#include <stdio.h>
#include <string.h>
#include "server.h"

uint8_t currentAccountIndex = 0;

uint8_t currentSequenceIndex = 0;

ST_accountsDB_t accounts[255] = {{5000, "1234567812345678"}, {6000, "1122334455667788"}};

ST_transaction_t transactions[255] = {{0, 0, 0, 0}};

EN_transState_t recieveTransactionData(ST_transaction_t *transData)
{
    if (isValidAccount(&transData->cardHolderData) == DECLINED_STOLEN_CARD)
    {
        transData->transState = DECLINED_STOLEN_CARD;
        return DECLINED_STOLEN_CARD;
    }
    else if (isAmountAvailable(&transData->terminalData) == LOW_BALANCE)
    {
        transData->transState = DECLINED_INSUFFECIENT_FUND;
        return DECLINED_INSUFFECIENT_FUND;
    }
    else if (saveTransaction(transData) == SAVING_FAILED)
    {
        transData->transState = SAVING_FAILED;
        return SAVING_FAILED;
    }
    else
    {
        accounts[currentAccountIndex].balance -= transData->terminalData.transAmount;
        return APPROVED;
    }
}

EN_serverError_t isValidAccount(ST_cardData_t *cardData)
{
    for (uint8_t i = 0; i < 255; i++)
    {
        if (!strcmp(cardData->primaryAccountNumber, accounts[i].primaryAccountNumber))
        {
            currentAccountIndex = i;
            return OK_SERVER;
        }
        else
        {
            return DECLINED_STOLEN_CARD;
        }
    }
}

EN_serverError_t isAmountAvailable(ST_terminalData_t *termData)
{
    if (accounts[currentAccountIndex].balance >= termData->transAmount)
        return OK_SERVER;
    else
        return LOW_BALANCE;
}

EN_serverError_t saveTransaction(ST_transaction_t *transData)
{
    if (currentSequenceIndex >= 255)
    {
        return SAVING_FAILED;
    }
    transactions[currentSequenceIndex].transactionSequenceNumber = transData->transactionSequenceNumber;
    transactions[currentSequenceIndex].cardHolderData = transData->cardHolderData;
    transactions[currentSequenceIndex].terminalData = transData->terminalData;
    transactions[currentSequenceIndex].transState = transData->transState;
    currentSequenceIndex++;
    return OK_SERVER;
}

EN_serverError_t getTransaction(uint32_t transactionSequenceNumber, ST_transaction_t *transData)
{
    for (uint8_t i = 0; i < 255; i++)
    {
        if (transactionSequenceNumber == transactions[i].transactionSequenceNumber)
        {
            return OK_SERVER;
        }
    }
    return TRANSACTION_NOT_FOUND;
}