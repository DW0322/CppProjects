import matplotlib.pyplot as plt
import pandas as pd

data = pd.read_csv("orbitData.csv")

plt.plot(data["time"], data["position"])
plt.grid()
plt.show()
