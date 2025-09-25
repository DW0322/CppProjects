import matplotlib.pyplot as plt
import pandas as pd

data = pd.read_csv("orbitData.csv")

plt.plot(data["x"], data["y"])
plt.axis('equal')
plt.grid()
plt.show()
