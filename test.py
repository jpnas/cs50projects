from cs50 import SQL
from helpers import apology, login_required, lookup, usd
db = SQL("sqlite:///finance.db")

stocks = db.execute("SELECT symbol, name, shares, price_per_share, datetime FROM transactions")

print(stocks)