import pandas as pd
import matplotlib.pyplot as plt
import sys

nombrecsv = sys.argv[1]
csv = pd.read_csv(nombrecsv, sep=",")

gastos = csv.loc[range(0, 7), 'GastoDia']

fig, ax = plt.subplots()
ax.bar(range(len(gastos)), gastos)

# Establecer los días de la semana como etiquetas del eje x
dias_semana = ['Lunes', 'Martes', 'Miércoles', 'Jueves', 'Viernes', 'Sábado', 'Domingo']
ax.set_xticks(range(len(gastos)))
ax.set_xticklabels(dias_semana)

# Establecer el título y etiquetas de los ejes
ax.set_title("Gráfico de Gastos en función del día")
ax.set_xlabel("Día de la semana")
ax.set_ylabel("Valor de gastos")

# Mostrar el gráfico
plt.show()
plt.savefig('graficoSemGasto.png')

