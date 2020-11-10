from flask import Flask, render_template, session, request
import numpy as np

app = Flask(__name__)
app.secret_key = "A0Zr98j/3yX R~XHH!jmN]LWX/,?RT"


@app.route("/")
@app.route("/<int:count>")
def index(count=1):
    if "username" not in session:
        session["username"] = "user"
        session["data"] = []
        session["result"] = []
    session["count"] = count
    return render_template("index.html", session=session)


@app.route("/plus")
def add_count():
    session["count"] += 1
    session["result"] = []
    return render_template("index.html", session=session)


@app.route("/minus")
def remove_count():
    if session["count"] > 1:
        session["count"] -= 1
        session["result"] = []
    return render_template("index.html", session=session)


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

    coef = np.zeros((count, count))
    summ = np.zeros(count)

    for i in range(count):
        summ[i] = sum(data[i])
        for j in range(count):
            coef[i][j] = data[j][i]
        coef[i][i] = -summ[i]

    m = np.zeros(count)
    m[-1] = 1
    coef[-1] = 1
    out = np.linalg.solve(coef, m)
    time = (1 - out) / out / summ
    session["result"] = [round(t, 4) for t in time.tolist()]

    return render_template("index.html", session=session)


if __name__ == "__main__":
    app.run(debug=True)
