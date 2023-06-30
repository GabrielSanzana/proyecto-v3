import pandas as pd
import matplotlib.pyplot as plt
import sys

nombrecsv = sys.argv[1]
csv = pd.read_csv(nombrecsv, sep=",")

csvMax = csv.loc[range(0, 5), ['Producto', 'CantVendida']]

fig, ax = plt.subplots()
ax.bar(csvMax["Producto"], csvMax["CantVendida"])
ax.set_title("Gráfico de productos más vendidos")
ax.set_xlabel("Producto")
ax.set_ylabel("Cantidad Vendida")

plt.show()
plt.savefig('graficoSemMax.png')
