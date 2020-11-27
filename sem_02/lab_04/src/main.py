#!/usr/bin/env python3

from flask import Flask, render_template, request, abort
from queueing_system.modeller import Modeller

app = Flask(__name__)


@app.route("/", methods=["GET"])
def index():
    return render_template("index.html", form=[], result=[])


@app.route("/", methods=["POST"])
def solve():
    a = float(request.form["a"])
    b = float(request.form["b"])
    mu = float(request.form["mu"])
    sigma = float(request.form["sigma"])
    probality = float(request.form["reenter_probability"])
    model = Modeller(a, b, mu, sigma, probality)
    count = int(request.form["count_request"])
    result = []
    if request.form["method"] == "event":
        result = model.event_based_modelling(count)
    elif request.form["method"] == "time":
        dt = float(request.form["dt"])
        result = model.time_based_modelling(count, dt)
    else:
        abort(404)
    return render_template("index.html", form=request.form, result=result)


if __name__ == "__main__":
    app.run(debug=True)
