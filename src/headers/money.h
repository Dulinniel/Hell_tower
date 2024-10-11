struct Wallet
{
  size_t platinum_coin;
  size_t gold_coin;
  size_t silver_coin;
  size_t copper_coin
}

struct Bank
{
  unsigned long platinum_coin;
  unsigned long gold_coin;
  unsigned long silver_coin;
  unsigned long copper_coin
}

enum OperationStatus
{
  FAILED,
  SUCCESS
};

struct MoneyOperation
{
  struct Wallet userWallet;
  enum OperationStatus OperationAborted;
}

void ConvertFace(struct Wallet *wallet);
void AddMoney(struct Wallet *userWallet, struct Wallet gainWallet);
MoneyOperation RemoveMoney(struct Wallet *userWallet, struct Wallet loseWallet);

struct Wallet ConvertFromCopper(size_t totalCopper);

MoneyOperation SendToBank(struct Wallet *userWallet, struct Wallet moneyToDeposit, struct Bank *bank);
MoneyOperation WithDrawFromBank(struct Wallet *userWallet, struct Wallet moneyToWithdraw, struct Bank *bank);