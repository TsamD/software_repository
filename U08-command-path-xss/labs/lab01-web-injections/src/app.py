# app.py - application VOLONTAIREMENT vulnerable (labo isole uniquement)
from flask import Flask, request
import sqlite3, os, subprocess
app = Flask(__name__)

def db():
    c = sqlite3.connect(":memory:")
    c.execute("CREATE TABLE users(user TEXT, pass TEXT)")
    c.execute("INSERT INTO users VALUES('admin','S3cret!')")
    c.execute("INSERT INTO users VALUES('alice','pw123')")
    return c

@app.route("/login")
def login():
    u = request.args.get("user","")
    p = request.args.get("pass","")
    q = "SELECT * FROM users WHERE user='%s' AND pass='%s'" % (u, p)  # VULN SQLi
    rows = db().execute(q).fetchall()
    return ("OK - connecte: %s\n" % rows) if rows else "echec\n", 200, {"X-Query": q}

@app.route("/ping")
def ping():
    host = request.args.get("host","127.0.0.1")
    out = subprocess.check_output("echo pong: " + host, shell=True, stderr=subprocess.STDOUT)  # VULN cmd injection
    return out

@app.route("/file")
def readfile():
    name = request.args.get("name","notes.txt")
    with open(os.path.join("/workspace/src/docs", name)) as f:  # VULN path traversal
        return f.read()

@app.route("/search")
def search():
    q = request.args.get("q","")
    return "<h1>Resultats pour %s</h1>" % q  # VULN XSS reflechi
