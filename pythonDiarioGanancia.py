import pandas as pd
import matplotlib.pyplot as plt

csv = pd.read_csv("csvDiarioDinero.csv", sep=",")

# Crear una figura y un conjunto de ejes para el gráfico de máximo
fig, ax = plt.subplots()

# Graficar la columna "Gastos"
ax.bar(csv.index, csv["Gastos"], label="Gastos")

# Graficar la columna "Ganancia" con un desplazamiento horizontal
ax.bar(csv.index + 0.2, csv["Ganancia"], label="Ganancia")

ax.set_title("Gráfico de ganancias y pérdidas del día")
ax.set_xlabel("Tipo")
ax.set_ylabel("Monto")
ax.legend()  # Agregar leyenda

plt.savefig('dineroDiario.png')
plt.show()
