from flask import Flask, request
from markupsafe import escape
import sqlite3, subprocess, os
app = Flask(__name__)
def db():
    c=sqlite3.connect(":memory:")
    c.execute("CREATE TABLE users(user TEXT, pass TEXT)")
    c.execute("INSERT INTO users VALUES('admin','S3cret!')")
    return c
@app.route("/login")
def login():
    u=request.args.get("user",""); p=request.args.get("pass","")
    rows=db().execute("SELECT * FROM users WHERE user=? AND pass=?",(u,p)).fetchall()  # requete parametree
    return ("OK\n" if rows else "echec\n")
@app.route("/ping")
def ping():
    host=request.args.get("host","127.0.0.1")
    if not all(ch.isalnum() or ch in ".-" for ch in host): return "hote invalide\n",400  # validation
    out=subprocess.check_output(["getent","hosts",host])  # liste d'arguments, pas de shell
    return out
@app.route("/file")
def rf():
    name=request.args.get("name","notes.txt")
    base="/workspace/src/web/docs"
    full=os.path.realpath(os.path.join(base,name))
    if not full.startswith(base+os.sep): return "acces refuse\n",403  # confinement
    with open(full) as f: return f.read()
@app.route("/search")
def s():
    return "<h1>Resultats pour %s</h1>" % escape(request.args.get("q",""))  # encodage de sortie
