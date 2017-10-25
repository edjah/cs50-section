import os
from flask import Flask, Response, url_for, render_template, request, session

# configuration of the Flask session
app = Flask(__name__)

@app.route('/', methods=['GET'])
def index():
    return render_template('index.html')

@app.route('/multiplier', methods=['GET'])
def mutliplier():
    return render_template('multiplier.html')

@app.route('/multiply', methods=['GET'])
def multily():
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


@app.route('/times_table', methods=['POST'])
def times_table():
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
