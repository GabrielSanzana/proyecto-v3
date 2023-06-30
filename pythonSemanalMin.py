import pandas as pd
import matplotlib.pyplot as plt
import sys

nombrecsv = sys.argv[1]
csv = pd.read_csv(nombrecsv, sep = ",")
csvMin = csv.loc[range(5,10), ['Producto', 'CantVendida']]

fig, ax = plt.subplots()
ax.bar(csvMin["Producto"], csvMin["CantVendida"])
ax.set_title("Gráfico de productos menos vendidos")
ax.set_xlabel("Producto")
ax.set_ylabel("Cantidad Vendida")

plt.show()
plt.savefig('graficoSemMin.png')