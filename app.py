from flask import Flask, render_template

app = Flask(__name__)

@app.route("/")
def index():
    # my_list = [1, 2, 3, 4, 5]
    # return render_template("index.html", my_list=my_list)
    return render_template("child.html")