import pandas as pd
import numpy as np
from plotnine import *
import subprocess

subprocess.run('./main.exe', shell=True)

diario = pd.read_csv("csvDiario.csv",sep=",")
diario

