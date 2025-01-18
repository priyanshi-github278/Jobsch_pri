import pandas as pd
import matplotlib.pyplot as plt

# Read the CSV file
data = pd.read_csv('jobs.csv')

# Plot bar graphs
plt.figure(figsize=(10, 6))

# Bar graph for memory requirements per job
plt.subplot(2, 1, 1)
plt.bar(data['JobId'], data['MemReq'], color='blue')
plt.xlabel('Job ID')
plt.ylabel('Memory Required (GB)')
plt.title('Memory Requirements per Job')

# Bar graph for CPU requirements per job
plt.subplot(2, 1, 2)
plt.bar(data['JobId'], data['CPUReg'], color='green')
plt.xlabel('Job ID')
plt.ylabel('CPU Required')
plt.title('CPU Requirements per Job')

# Show the plot
plt.tight_layout()
plt.show()
