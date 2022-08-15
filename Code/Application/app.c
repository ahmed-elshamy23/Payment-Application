#include <stdio.h>
#include <string.h>
#include "app.h"
#include "../Card/card.h"
#include "../Terminal/terminal.h"
#include "../Server/server.h"

extern ST_accountsDB_t accounts[];
extern ST_transaction_t transactions[];

void appStart(void)
{
    ST_cardData_t card;
    ST_terminalData_t terminal;
    ST_transaction_t transaction;
    uint8_t choice;
    printf("*********Welcome to the new banking system*********\n");
    printf("Enter 1 to make a new transaction.\nEnter 2 to search for a previous transaction.\n");
    scanf("%d", &choice);
    if (choice == 1)
    {
        fflush(stdin);
        uint8_t name = getCardHolderName(&card);
        while (name == WRONG_NAME)
        {
            printf("You entered a wrong name. Please try again: ");
            fflush(stdin);
            name = getCardHolderName(&card);
        }
        fflush(stdin);
        uint8_t expiryDate = getCardExpiryDate(&card);
        while (expiryDate == WRONG_EXP_DATE)
        {
            printf("You entered a wrong expiry date. Please try again: ");
            fflush(stdin);
            expiryDate = getCardExpiryDate(&card);
        }
        fflush(stdin);
        uint8_t pan = getCardPAN(&card);
        while (pan == WRONG_PAN)
        {
            printf("You entered a wrong PAN. Please try again: ");
            fflush(stdin);
            pan = getCardPAN(&card);
        }
        fflush(stdin);
        uint8_t transactionDate = getTransactionDate(&terminal);
        while (transactionDate == WRONG_DATE)
        {
            printf("You entered a wrong transaction date. Please try again: ");
            fflush(stdin);
            transactionDate = getTransactionDate(&terminal);
        }
        uint8_t isExpired = isCardExpired(card, terminal);
        if (isExpired == EXPIRED_CARD)
        {
            printf("\n\n************Declined Operation (Expired Card)************\n");
            printf("************************Thank You************************\n");
        }
        else
        {
            fflush(stdin);
            uint8_t transcationAmount = getTransactionAmount(&terminal);
            while (transcationAmount == INVALID_AMOUNT)
            {
                printf("You entered a wrong transaction amount. Please try again: ");
                fflush(stdin);
                transcationAmount = getTransactionAmount(&terminal);
            }
            setMaxAmount(&terminal);
            if (isBelowMaxAmount(&terminal) == EXCEED_MAX_AMOUNT)
            {
                printf("\n\n************Declined Operation (Exceeded Max Amount)************\n");
                printf("***************************Thank You****************************\n");
            }
            else
            {
                uint8_t valid = isValidAccount(&card);
                if (valid == DECLINED_STOLEN_CARD)
                {
                    printf("\n\n************Declined Operation (Invalid Account)************\n");
                    printf("*************************Thank You**************************\n");
                }
                else
                {
                    uint8_t amount = isAmountAvailable(&terminal);
                    if (amount == LOW_BALANCE)
                    {
                        printf("\n\n************Declined Operation (Insufficient Funds)************\n");
                        printf("**************************Thank You****************************\n");
                    }
                    else
                    {
                        if (recieveTransactionData(&transaction) == SAVING_FAILED)
                        {
                            printf("\n\n************Declined Operation (Saving Failed)************\n");
                            printf("************************Thank You*************************\n");
                        }
                        else
                        {
                            printf("\n\n************Successful Operation!************\n");
                            printf("An amount of %.2f has been deducted from your account\n", terminal.transAmount);
                            printf("Date of operation: %s\n", terminal.transactionDate);
                            printf("*****************Thank You*******************\n");
                        }
                    }
                }
            }
        }
    }
    else
    {
        uint32_t sequenceNumber = 0;
        printf("Enter transaction sequence number: ");
        scanf("%d", sequenceNumber);
        if (getTransaction(sequenceNumber, &transaction) == OK_SERVER)
        {
            printf("\n\nTransaction found successfuly!\n");
        }
        else
        {
            printf("Transaction not found.\n");
        }
        printf("*****************Thank You*******************\n");
    }
}