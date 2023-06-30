import pandas as pd
import matplotlib.pyplot as plt
import subprocess

csvAux = pd.read_csv("nombre.csv")
nombrecsv = csvAux.columns[0]

subprocess.run(["python", "pythonSemanalMax.py", nombrecsv])
subprocess.run(["python", "pythonSemanalMin.py", nombrecsv])
subprocess.run(["python", "pythonSemanalGasto.py", nombrecsv])
subprocess.run(["python", "pythonSemanalGanancia.py", nombrecsv])


