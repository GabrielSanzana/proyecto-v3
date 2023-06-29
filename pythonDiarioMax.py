import pandas as pd
import matplotlib.pyplot as plt

csv = pd.read_csv("csvDiario.csv", sep=",")
csvMax = csv.loc[0:4]

# Crear una figura y un conjunto de ejes para el gráfico de máximo
fig, ax = plt.subplots()
ax.bar(csvMax["Producto"], csvMax["CantVendida"])
ax.set_title("Gráfico de productos más vendidos")
ax.set_ylim(0, max(csvMax["CantVendida"]))
plt.savefig('omerochino_max.png')
plt.show()