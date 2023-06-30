import pandas as pd
import matplotlib.pyplot as plt

csv = pd.read_csv("csvDiarioDinero.csv", sep=",")

# Crear una figura y un conjunto de ejes para el gráfico de máximo
fig, ax = plt.subplots()

# Determinar el ancho de las barras
bar_width = 0.4

# Graficar la columna "Gastos"
ax.bar(csv.index, csv["Gastos"], width=bar_width, label="Gastos")

# Graficar la columna "Ganancia" al lado de "Gastos"
ax.bar(csv.index + bar_width, csv["Ganancia"], width=bar_width, label="Ganancia")

ax.set_title("Gráfico de ganancias y pérdidas del día")
ax.set_xlabel("Tipo")
ax.set_ylabel("Monto")
ax.legend()  # Agregar leyenda

plt.savefig('dineroDiario.png')
plt.show()
