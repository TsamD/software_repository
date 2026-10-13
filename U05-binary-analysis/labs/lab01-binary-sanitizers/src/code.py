# code.py - programme Python a auditer (TP U9.3)
# Faiblesses a identifier avec bandit : shell=True, SQL concatene, eval
import sqlite3, subprocess, sys

def recherche(terme):
    con = sqlite3.connect(":memory:")
    q = "SELECT * FROM t WHERE nom = '" + terme + "'"   # SQLi (B608)
    try: return con.execute(q).fetchall()
    except Exception: return []

def ping(hote):
    return subprocess.check_output("ping -c1 " + hote, shell=True)   # injection (B602)

def calcul(expr):
    return eval(expr)   # eval sur entree (B307)

if __name__ == "__main__":
    print(recherche(sys.argv[1] if len(sys.argv) > 1 else "x"))
