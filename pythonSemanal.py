import pandas as pd
import matplotlib.pyplot as plt
import subprocess


nombrecsv = input("Escriba el nommbre del informe semanal con el formato .csv al final\n")

subprocess.run(["python", "pythonSemanalMax.py", nombrecsv])
subprocess.run(["python", "pythonSemanalMin.py", nombrecsv])
subprocess.run(["python", "pythonSemanalGasto.py", nombrecsv])
subprocess.run(["python", "pythonSemanalGanancia.py", nombrecsv])


