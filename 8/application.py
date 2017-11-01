import os
import datetime
from flask import Flask, Response, url_for, redirect, render_template, request, session
from cs50 import SQL

# configuration of the Flask session
app = Flask(__name__)


# a list of people
db = SQL("sqlite:///finance.db")

@app.route('/', methods=['GET'])
def index():
    return render_template('index.html')

@app.route('/multiplier', methods=['GET'])
def mutliplier():
    return render_template('multiplier.html')

@app.route('/database', methods=['GET'])
def get_database():
    rows = db.execute("SELECT * FROM people")
    return render_template('database.html', people=rows)


@app.route('/register', methods=['POST'])
def register():
    user = request.form.get('username')
    pass1 = request.form.get('password')
    pass2 = request.form.get('password2')
    net_worth = int(request.form.get('net_worth') or 69)

    if not user or not pass1 or not pass2:
        return render_template(
            'error.html',
            code='420',
            title='Must provide (almost) all arguments',
            desc=''
        )

    if pass1 != pass2:
        return render_template(
            'error.html',
            code='420',
            title='Passwords must match',
            desc=''
        )

    rows = db.execute("SELECT * FROM people where username = :user", user=user)
    if len(rows) > 0:
        return render_template(
            'error.html',
            code='420',
            title='Username already exists!',
            desc=''
        )

    db.execute("INSERT INTO people (username,password,net_worth) VALUES (:user,:pass1,:net_worth)",
               user=user, pass1=pass1, net_worth=net_worth)

    return redirect(url_for('get_database'))

@app.route('/multiply', methods=['GET'])
def multiply():
    try:
        x = int(request.args.get('x'))
        y = int(request.args.get('y'))
        return str(x * y)

    except Exception as e:
        return render_template(
            'error.html',
            code='420',
            title='Invalid arguments',
            desc='Please provide a valid x and y'
        )


@app.route('/times_table', methods=['POST', 'GET'])
def times_table():
    if request.method == 'POST':
        try:
            width = int(request.form.get('width'))
            height = int(request.form.get('height'))
            assert width >= 0 and height >= 0

            table = [[i * j for i in range(width + 1)] for j in range(height + 1)]
            return render_template('times_table.html', table=table, height=height, width=width)

        except Exception:
            return render_template(
                'error.html',
                code='420',
                title='Invalid arguments',
                desc='The provided height and width are invalid :('
            )
    else:
        return render_template('times_table_form.html')


@app.errorhandler(404)
def handle_404(error):
    return render_template(
        'error.html',
        code='404',
        title='Not Found',
        desc='Requested page does not exist :('
    )


if __name__ == '__main__':
    port = int(os.environ.get('PORT', 5000))
    app.run(host='0.0.0.0', port=port)
