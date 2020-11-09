from flask import Flask, render_template, session, request

app = Flask(__name__)
app.secret_key = "A0Zr98j/3yX R~XHH!jmN]LWX/,?RT"


@app.route("/")
@app.route("/<int:count>")
def index(count=1):
    if "username" not in session:
        session["username"] = "user"
        session["data"] = []
        session["result"] = None
    session["count"] = count
    return render_template("index.html", session=session, solve=False)


@app.route("/plus")
def add_count():
    session["count"] += 1
    session["result"] = None
    return render_template("index.html", session=session, solve=False)


@app.route("/minus")
def remove_count():
    if session["count"] > 1:
        session["count"] -= 1
        session["result"] = None
    return render_template("index.html", session=session, solve=False)


@app.route("/", methods=["POST"])
@app.route("/<int:count>", methods=["POST"])
@app.route("/plus", methods=["POST"])
@app.route("/minus", methods=["POST"])
def solve():
    count = session["count"]
    data = []
    for i in range(count):
        data.append([])
        for j in range(count):
            s = request.form[str(i * count + j)]
            data[i].append(int(s) if s != "" else 0)
    session["data"] = data
    return render_template("index.html", session=session, solve=True)


if __name__ == "__main__":
    app.run(debug=True)
