import os
from flask import Flask, Response, url_for, render_template, request, session

# configuration of the Flask session
app = Flask(__name__)

@app.route('/', methods=['GET'])
def index():
    return render_template('index.html')

@app.route('/multiplier', methods=['GET'])
def multiplier():
    return render_template('multiplier_index.html')

@app.route('/multiply', methods=['POST'])
def multiply():
    x = int(request.form.get('x', -1))
    y = int(request.form.get('y', -1))

    if x < 0 or y < 0:
        return render_template(
            'error.html',
            code=1337,
            title='Invalid arguments',
            desc='invalid arguments provided '
        )

    return str(x * y)

@app.route('/generate_table', methods=['GET'])
def generate_table():
    if request.method == 'GET':
        try:
            width = int(request.args.get('width'))
            height = int(request.args.get('height'))
            assert (height > 0 and width > 0)
            table = [[i * j for j in range(1, width + 1)] for i in range(1, height + 1)]
            return render_template('times_table.html', table=table, width=width, height=height)

        except Exception as e:
            return render_template(
                'error.html',
                code=1337,
                title='Invalid arguments',
                desc=str(e)
            )

if __name__ == '__main__':
    port = int(os.environ.get('PORT', 5000))
    app.run(host='0.0.0.0', port=port)
