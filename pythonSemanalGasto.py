import pandas as pd
import matplotlib.pyplot as plt
import sys

nombrecsv = sys.argv[1]
csv = pd.read_csv(nombrecsv, sep = ",")
gastos = csv.loc[range(0,7),6]

fig, ax = plt.subplots()
ax.plot(gasto)

# Establecer el título y etiquetas de los ejes
ax.set_title("Gráfico De gastos en función del día")
ax.set_xlabel("Índice")
ax.set_ylabel("Valor de gasto")

# Mostrar el gráfico
plt.show()
