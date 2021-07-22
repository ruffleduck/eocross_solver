from flask import Flask, render_template, request
import subprocess

app = Flask(__name__)

@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":
        return render_template("index.html",
            solutions=(str(subprocess.run(["./eocross", request.form["text"]],
                capture_output=True).stdout).split("\\n")[1:-1]),
            scramble=request.form["text"])
    else:
        return render_template("index.html", solutions=[], scamble="")

if __name__ == "__main__":
    app.run()
