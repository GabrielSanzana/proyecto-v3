import pandas as pd
import matplotlib.pyplot as plt
import sys
nombrecsv = sys.argv[1]
csv = pd.read_csv(nombrecsv, sep = ",")
ganancias = csv.loc[range(0,7),5]

fig, ax = plt.subplots()
ax.plot(gasto)

# Establecer el título y etiquetas de los ejes
ax.set_title("Gráfico De Ganancias en función del día")
ax.set_xlabel("Índice")
ax.set_ylabel("Valor de ganancias")

# Mostrar el gráfico
plt.show()
