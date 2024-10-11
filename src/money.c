#include <stdio.h>
#include "./headers/money.h"

#define CONVERT_TO_COPPER(entity) \
    ((entity).copper_coin \
    + (entity).silver_coin * COPPER_TO_SILVER_VALUE \
    + (entity).gold_coin * SILVER_TO_GOLD_VALUE * COPPER_TO_SILVER_VALUE \
    + (entity).platinum_coin * GOLD_TO_PLATINUM_VALUE * SILVER_TO_GOLD_VALUE * COPPER_TO_SILVER_VALUE)

const unsigned short COPPER_TO_SILVER_VALUE = 1000;
const unsigned short SILVER_TO_GOLD_VALUE = 5000;
const unsigned short GOLD_TO_PLATINUM_VALUE = 10000;

void ConvertFace(struct Wallet *wallet)
{
  wallet->silver_coin += wallet->copper_coin / COPPER_TO_SILVER_VALUE;
  wallet->copper_coin %= COPPER_TO_SILVER_VALUE; 
  wallet->gold_coin += wallet->silver_coin / SILVER_TO_GOLD_VALUE;
  wallet->silver_coin %= SILVER_TO_GOLD_VALUE;
  wallet->platinum_coin += wallet->gold_coin / GOLD_TO_PLATINUM_VALUE;
  wallet->gold_coin %= GOLD_TO_PLATINUM_VALUE;
}

void AddMoney(struct Wallet *userWallet, struct Wallet gainWallet)
{
  // No overflow check, just speedrun how fast you can positive arithmetic overflow this shit
  userWallet->copper_coin += gainWallet->copper_coin;
  userWallet->silver_coin += gainWallet->silver_coin;
  userWallet->gold_coin += gainWallet->gold_coin;
  userWallet->platinum_coin += gainWallet->platinum_coin;

  ConvertFace(userWallet);
}

struct Wallet ConvertFromCopper(size_t totalCopper)
{
  struct Wallet wallet = {0};

  wallet.platinum_coin = totalCopper / (GOLD_TO_PLATINUM_VALUE * SILVER_TO_GOLD_VALUE * COPPER_TO_SILVER_VALUE);
  totalCopper %= (GOLD_TO_PLATINUM_VALUE * SILVER_TO_GOLD_VALUE * COPPER_TO_SILVER_VALUE);

  wallet.gold_coin = totalCopper / (SILVER_TO_GOLD_VALUE * COPPER_TO_SILVER_VALUE);
  totalCopper %= (SILVER_TO_GOLD_VALUE * COPPER_TO_SILVER_VALUE);

  wallet.silver_coin = totalCopper / COPPER_TO_SILVER_VALUE;
  wallet.copper_coin = totalCopper % COPPER_TO_SILVER_VALUE;

  return wallet;
}

struct MoneyOperation RemoveMoney(struct Wallet userWallet, struct Wallet loseWallet) 
{
  ConvertFace(&userWallet);
  struct MoneyOperation operationResult;

  // Hoping you're not trying to buy something out of budget
  operationResult.OperationAborted = SUCCESS;

  // Evetything is copper
  size_t userTotalCopper = CONVERT_TO_COPPER(userWallet);
  size_t loseTotalCopper = CONVERT_TO_COPPER(loseWallet);

  // Check if you're broke in copper
  if (userTotalCopper < loseTotalCopper) operationResult.OperationAborted = FAILED;

  if ( operationResult.OperationAborted != FAILED ) userTotalCopper -= loseTotalCopper;

  // Give your money back
  operationResult.userWallet = ConvertFromCopper(userTotalCopper);

  return operationResult;
}

struct MoneyOperation DepositIntoBank(struct Wallet *userWallet, struct Wallet moneyToDeposit, struct Bank *bank)
{
  ConvertFace(userWallet);

  struct MoneyOperation operationResult;
  operationResult.OperationAborted = SUCCESS;

  // Convertir en cuivre pour comparer les sommes globales
  size_t totalUserCopper = CONVERT_TO_COPPER(*userWallet);
  size_t totalDepositCopper = CONVERT_TO_COPPER(moneyToDeposit);

  if (totalUserCopper < totalDepositCopper) operationResult.OperationAborted = FAILED;


  if ( operationResult.OperationAborted == SUCCESS )
  {
    // Mettre à jour la banque
    bank->copper_coin += moneyToDeposit.copper_coin;
    bank->silver_coin += moneyToDeposit.silver_coin;
    bank->gold_coin += moneyToDeposit.gold_coin;
    bank->platinum_coin += moneyToDeposit.platinum_coin;

    // Retirer l'argent du portefeuille
    *userWallet = ConvertFromCopper(totalUserCopper - totalDepositCopper);
  }

  operationResult.userWallet = *userWallet;

  return operationResult;
}

struct MoneyOperation WithDrawFromBank(struct Wallet *userWallet, struct Wallet moneyToWithdraw, struct Bank *bank)
{
  ConvertFace(userWallet);

  struct MoneyOperation operationResult;
  operationResult.OperationAborted = SUCCESS;

  size_t totalBankCopper = CONVERT_TO_COPPER(*bank);
  size_t totalWithdrawCopper = CONVERT_TO_COPPER(moneyToWithdraw);

  if (totalBankCopper < totalWithdrawCopper) operationResult.OperationAborted = FAILED;

  if ( operationResult.OperationAborted == SUCCESS )
  {
    // Mettre à jour la banque
    bank->copper_coin -= moneyToWithdraw.copper_coin;
    bank->silver_coin -= moneyToWithdraw.silver_coin;
    bank->gold_coin -= moneyToWithdraw.gold_coin;
    bank->platinum_coin -= moneyToWithdraw.platinum_coin;

    // Ajouter l'argent au portefeuille de l'utilisateur
    *userWallet = ConvertFromCopper(CONVERT_TO_COPPER(*userWallet) + totalWithdrawCopper);
  }

  operationResult.userWallet = *userWallet;

  return operationResult;
}