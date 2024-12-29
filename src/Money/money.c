#include <stdio.h>
#include "../headers/money.h"

// Convert faces to copper equivalent
// Use define because it can be either a Wallet or a Bank
#define CONVERT_TO_COPPER(entity) \
    ((entity).copper_coin \
    + (entity).silver_coin * COPPER_TO_SILVER_VALUE \
    + (entity).gold_coin * SILVER_TO_GOLD_VALUE * COPPER_TO_SILVER_VALUE \
    + (entity).platinum_coin * GOLD_TO_PLATINUM_VALUE * SILVER_TO_GOLD_VALUE * COPPER_TO_SILVER_VALUE)

// Face values
const unsigned short COPPER_TO_SILVER_VALUE = 1000;
const unsigned short SILVER_TO_GOLD_VALUE = 5000;
const unsigned short GOLD_TO_PLATINUM_VALUE = 10000;

/*
* @name: ConvertFace
* @description: Convert face value to another of higher value when applicable  
* @return:
* * * type: void
* @params:
* * * wallet -> Pointer to a wallet ( struct Inventory )
*/
void ConvertFace(struct Wallet *wallet)
{
  // Makes your money worth with modulo and division
  wallet->silver_coin += wallet->copper_coin / COPPER_TO_SILVER_VALUE;
  wallet->copper_coin %= COPPER_TO_SILVER_VALUE; 
  wallet->gold_coin += wallet->silver_coin / SILVER_TO_GOLD_VALUE;
  wallet->silver_coin %= SILVER_TO_GOLD_VALUE;
  wallet->platinum_coin += wallet->gold_coin / GOLD_TO_PLATINUM_VALUE;
  wallet->gold_coin %= GOLD_TO_PLATINUM_VALUE;
}

/*
* @name: AddMoney
* @description: Give money to the user  
* @return:
* * * type: void
* @params:
* * * wallet -> Pointer to a wallet ( struct Inventory )
*/
void AddMoney(struct Wallet *userWallet, struct Wallet gainWallet)
{
  // No overflow check, just speedrun how fast you can positive arithmetic overflow this shit
  userWallet->copper_coin += gainWallet.copper_coin;
  userWallet->silver_coin += gainWallet.silver_coin;
  userWallet->gold_coin += gainWallet.gold_coin;
  userWallet->platinum_coin += gainWallet.platinum_coin;

  ConvertFace(userWallet);
}

/*
* @name: ConverFromCopper
* @description: Convert a full copper wallet to an organised Wallet 
* @return:
* * * type: struct Wallet 
* * * Success: Return the organised Walltet with every faces
* * * Fail: None
* @params:
* * * totalCopper -> The amount of copper to convert to faces ( size_t )
*/
struct Wallet ConvertFromCopper(size_t totalCopper)
{
  struct Wallet wallet = {0};

  // Just some basic artihmetic to convert from copper to higher faces
  wallet.platinum_coin = totalCopper / (GOLD_TO_PLATINUM_VALUE * SILVER_TO_GOLD_VALUE * COPPER_TO_SILVER_VALUE);
  totalCopper %= (GOLD_TO_PLATINUM_VALUE * SILVER_TO_GOLD_VALUE * COPPER_TO_SILVER_VALUE);

  wallet.gold_coin = totalCopper / (SILVER_TO_GOLD_VALUE * COPPER_TO_SILVER_VALUE);
  totalCopper %= (SILVER_TO_GOLD_VALUE * COPPER_TO_SILVER_VALUE);

  wallet.silver_coin = totalCopper / COPPER_TO_SILVER_VALUE;
  wallet.copper_coin = totalCopper % COPPER_TO_SILVER_VALUE;

  return wallet;
}

/*
* @name: RemoveMoney
* @description: Take money from a wallet 
* @return:
* * * type: struct MoneyOperation 
* * * Success: Return status SUCCESS + the final wallet
* * * Fail: Return status FAILED + the initial wallet
* @params:
* * * userWallet -> The wallet of the user to remove from ( struct Wallet )
* * * lostWallet -> The amount of money to remove ( struct Wallet )
*/
struct MoneyOperation RemoveMoney(struct Wallet *userWallet, struct Wallet loseWallet) 
{
  ConvertFace(userWallet);
  struct MoneyOperation operationResult;

  // Hoping you're not trying to buy something out of budget
  operationResult.OperationAborted = SUCCESS;

  // Everything is copper
  size_t userTotalCopper = CONVERT_TO_COPPER(*userWallet);
  size_t loseTotalCopper = CONVERT_TO_COPPER(loseWallet);

  // Check if you're broke in copper
  if (userTotalCopper < loseTotalCopper) operationResult.OperationAborted = FAILED;
  else userTotalCopper -= loseTotalCopper;

  // Give your money back
  operationResult.userWallet = ConvertFromCopper(userTotalCopper);

  return operationResult;
}

/*
* @name: DepositIntoBank
* @description: Place user money into bank 
* @return:
* * * type: struct MoneyOperation 
* * * Success: Return status SUCCESS + the final wallet
* * * Fail: Return status FAILED + the initial wallet
* @params:
* * * userWallet -> The wallet of the user to remove from ( struct Wallet )
* * * moneyToDeposit -> The amount of money to deposit into the bank ( struct Wallet )
* * * bank -> Pointer to a bank ( struct Bank* )
*/
struct MoneyOperation DepositIntoBank(struct Wallet *userWallet, struct Wallet moneyToDeposit, struct Bank *bank)
{
  // Techncially, when you come to the bank your money is already converted but I don't trust you
  ConvertFace(userWallet);

  struct MoneyOperation operationResult;
  operationResult.OperationAborted = SUCCESS;

  // You'll be rich in copper
  size_t totalUserCopper = CONVERT_TO_COPPER(*userWallet);
  size_t totalDepositCopper = CONVERT_TO_COPPER(moneyToDeposit);

  // Check if you didn't try to scam the bank 
  if (totalUserCopper >= totalDepositCopper) 
  {
    // Bank got your money
    bank->copper_coin += moneyToDeposit.copper_coin;
    bank->silver_coin += moneyToDeposit.silver_coin;
    bank->gold_coin += moneyToDeposit.gold_coin;
    bank->platinum_coin += moneyToDeposit.platinum_coin;

    // No, you don't keep it
    *userWallet = ConvertFromCopper(totalUserCopper - totalDepositCopper);
  } else operationResult.OperationAborted = FAILED;

  operationResult.userWallet = *userWallet;

  return operationResult;
}

/*
* @name: WithDrawFromBank
* @description: Get user money back from banl 
* @return:
* * * type: struct MoneyOperation 
* * * Success: Return status SUCCESS + the final wallet
* * * Fail: Return status FAILED + the initial wallet
* @params:
* * * userWallet -> The wallet of the user to give to ( struct Wallet )
* * * moneyToWithdraw -> The amount of money to get from the bank ( struct Wallet )
* * * bank -> Pointer to a bank ( struct Bank* )
*/
struct MoneyOperation WithDrawFromBank(struct Wallet *userWallet, struct Wallet moneyToWithdraw, struct Bank *bank)
{
  // Same thing as earlier, and I still don't trust you
  ConvertFace(userWallet);

  struct MoneyOperation operationResult;
  operationResult.OperationAborted = SUCCESS;

  // Again, I use Alchemy ( pre-processor instruction ) to transmute ( Compute an equivalent of ) your money into copper
  size_t totalBankCopper = CONVERT_TO_COPPER(*bank);
  size_t totalWithdrawCopper = CONVERT_TO_COPPER(moneyToWithdraw);

  if (totalBankCopper < totalWithdrawCopper) operationResult.OperationAborted = FAILED;

  // If you asked for something you actually deposed
  if ( operationResult.OperationAborted == SUCCESS )
  {
    // Highjack the bank
    bank->copper_coin -= moneyToWithdraw.copper_coin;
    bank->silver_coin -= moneyToWithdraw.silver_coin;
    bank->gold_coin -= moneyToWithdraw.gold_coin;
    bank->platinum_coin -= moneyToWithdraw.platinum_coin;

    // Give your money back
    *userWallet = ConvertFromCopper(CONVERT_TO_COPPER(*userWallet) + totalWithdrawCopper);
  }

  operationResult.userWallet = *userWallet;

  return operationResult;
}