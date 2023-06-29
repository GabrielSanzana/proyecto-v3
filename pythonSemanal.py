import pandas as pd
import matplotlib.pyplot as plt

nombrecsv = input("Escriba el nommbre del informe semanal con el formato .csv al final")
csv = pd.read_csv(nombrecsv, sep = ",")
csvMin = csv.loc[range(0,5),range(0,5)]
csvMax = csv.loc[range(5,10),range(0,5)]
ganancias = csv.loc[range(0,7),5]
gastos = csv.loc[range(0,7),6]

