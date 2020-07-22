import os
import datetime

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    users = db.execute("SELECT cash FROM users WHERE id = :user_id", user_id=session["user_id"])
    stocks = db.execute("SELECT symbol, name, SUM(shares) as totalshares FROM transactions WHERE user_id = :user_id GROUP BY symbol HAVING totalshares > 0", user_id=session["user_id"])

    cash = users[0]["cash"]
    total = cash
    for stock in stocks:
        stock["current"]  = lookup(stock["symbol"])["price"]
        stock["total"] = stock["current"] * stock["totalshares"]
        total += stock["total"]

    return render_template("index.html", stocks=stocks, cash=cash, total=total)

@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    if request.method == "GET":
        return render_template("buy.html")

    else:
        stock = lookup(request.form.get("symbol"))

        if stock == None:
            return apology("This stock symbol does not exist", 400)

        try:
            shares = int(request.form.get("shares"))
        except:
            return apology("Shares must be a positive integer", 400)

        if shares <= 0:
            return apology("You must buy one or more shares", 400)

        rows = db.execute("SELECT cash FROM users WHERE id=:user_id", user_id=session["user_id"])

        cash = rows[0]["cash"]
        price = stock["price"]

        total_price = price * shares

        if total_price > cash:
            return apology("Not enough funds", 400)

        time = datetime.datetime.now()


        db.execute("UPDATE users SET cash = cash - :total_price WHERE id = :user_id", total_price=total_price, user_id=session["user_id"])
        db.execute("INSERT INTO transactions (user_id, symbol, name, shares, price_per_share, datetime) VALUES (:user_id, :symbol, :name, :shares, :price, :time)"
        , user_id=session["user_id"], symbol=request.form.get("symbol").upper(), name=stock["name"], shares=shares, price=price, time=time.strftime("%c"))

        flash("Bought!")

        return redirect("/")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    stocks = db.execute("SELECT symbol, name, shares, price_per_share, datetime FROM transactions WHERE user_id = :user_id ORDER BY datetime DESC", user_id=session["user_id"])
    return render_template("history.html", stocks=stocks)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    if request.method == "GET":
        return render_template("quote.html")

    else:
        stock = lookup(request.form.get("quote"))
        if stock == None:
            return apology("This stock symbol does not exist", 400)

        return render_template("quoteresult.html", name=stock["name"], price=usd(stock["price"]), symbol=stock["symbol"])


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    if request.method == "GET":
        return render_template("register.html")

    else:
        if not request.form.get("username"):
            return apology("You must provide a username", 400)

        elif not request.form.get("password"):
            return apology("You must provide a password", 400)


        elif request.form.get("password") != request.form.get("confirmation"):
            return apology("Passwords do not match", 400)

        users = db.execute("SELECT * from users WHERE username = :username", username=request.form.get("username"))

        if len(users) > 0:
            return apology("Username taken", 400)

        passwordhash = generate_password_hash(request.form.get("password"))

        new_user = db.execute("INSERT INTO users (username, hash) VALUES(:username, :hash)", username=request.form.get("username"), hash=passwordhash)

        session["user_id"] = new_user

        flash("Registered!")

        return redirect("/")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    if request.method == "GET":
        stocks = db.execute("SELECT DISTINCT symbol FROM transactions WHERE user_id = :user_id", user_id=session["user_id"])

        return render_template("sell.html", stocks=stocks)

    else:

        try:
            shares = int(request.form.get("shares"))
        except:
            return apology("shares must be a positive integer", 400)

        if shares <= 0:
            return apology("can't sell less than or 0 shares", 400)

        quote = lookup(request.form.get("symbol"))

        stocks = db.execute("SELECT SUM(shares) as totalshares FROM transactions WHERE user_id = :user_id and symbol = :symbol", user_id=session["user_id"], symbol=request.form.get("symbol"))
        totalshares = int(stocks[0]["totalshares"])

        if shares > totalshares:
            return apology("You cannot sell more stocks than you have", 400)

        totalprice = quote["price"] * shares

        time = datetime.datetime.now()

        db.execute("UPDATE users SET cash = cash + :price WHERE id = :user_id", price=totalprice, user_id=session["user_id"])
        db.execute("INSERT INTO transactions (user_id, symbol, name, shares, price_per_share, datetime) VALUES (:user_id, :symbol, :name, :shares, :price, :time)"
        , user_id=session["user_id"], symbol=quote["symbol"], name=quote["name"], shares=-shares, price=quote["price"], time=time.strftime("%c"))

        flash("Sold!")

        return redirect("/")

def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
