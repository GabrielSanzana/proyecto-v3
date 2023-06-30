import pandas as pd
import matplotlib.pyplot as plt
import sys

nombrecsv = sys.argv[1]
csv = pd.read_csv(nombrecsv, sep = ",")
csvMin = csv.loc[range(5,10),range(0,5)]
fig, ax = plt.subplots()
ax.bar(csvMax["Producto"], csvMax["CantVendida"])
ax.set_title("Gráfico de productos más vendidos")
ax.set_ylim(0, max(csvMax["CantVendida"]))
ax.set_ylim(bottom=0) 
plt.savefig('omerochino_semanal_max.png')
plt.show()