import pandas as pd
import matplotlib.pyplot as plt
import subprocess

subprocess.check_call(["pip", "install", "-r", "requirements.txt"])
                      
csv = pd.read_csv("csvDiario.csv", sep = ",")
csvMax = csv.loc[(0,1,2,3,4)]
csvMin = csv.loc[(5,6,7,8,9,10)]
# Crear una figura y un conjunto de ejes
fig, ax = plt.subplots()

# Generar el gráfico de barras
ax.bar(csvMin["Producto"], csvMin["CantVendida"])

# Establecer el título y los límites del eje y
ax.set_title("Gráfico de productos menos vendidos.")
ax.set_ylim(0, max(csvMin["CantVendida"]))

# Mostrar el gráfico
plt.savefig('omerochino.png')
