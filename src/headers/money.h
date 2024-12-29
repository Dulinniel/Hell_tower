#ifndef MONEY_H
#define MONEY_H

struct Wallet
{
  size_t platinum_coin;
  size_t gold_coin;
  size_t silver_coin;
  size_t copper_coin;
};

struct Bank
{
  unsigned long platinum_coin;
  unsigned long gold_coin;
  unsigned long silver_coin;
  unsigned long copper_coin;
};

enum OperationStatus
{
  FAILED,
  SUCCESS,
};

struct MoneyOperation
{
  struct Wallet userWallet;
  enum OperationStatus OperationAborted;
};

void ConvertFace(struct Wallet *wallet);
void AddMoney(struct Wallet *userWallet, struct Wallet gainWallet);
struct MoneyOperation RemoveMoney(struct Wallet *userWallet, struct Wallet loseWallet);

struct Wallet ConvertFromCopper(size_t totalCopper);

struct MoneyOperation DepositIntoBank(struct Wallet *userWallet, struct Wallet moneyToDeposit, struct Bank *bank);
struct MoneyOperation WithDrawFromBank(struct Wallet *userWallet, struct Wallet moneyToWithdraw, struct Bank *bank);

#endif