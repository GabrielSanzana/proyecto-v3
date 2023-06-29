import pandas as pd
import matplotlib.pyplot as plt

csv = pd.read_csv("csvDiario.csv", sep=",")
csvMin = csv.loc[5:10]

# Crear una figura y un conjunto de ejes para el gráfico de mínimo
fig, ax = plt.subplots()
ax.bar(csvMin["Producto"], csvMin["CantVendida"])
ax.set_title("Gráfico de productos menos vendidos.")
ax.set_ylim(0, max(csvMin["CantVendida"]))
plt.savefig('omerochino_min.png')
plt.show()