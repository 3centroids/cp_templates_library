import pandas as pd
import matplotlib.pyplot as plt
import subprocess

# Generate data
with open("results.csv", "w") as f:
    subprocess.run(["./test"], stdout=f)

# Read CSV output
df = pd.read_csv("bench.csv")  # output from previous C++ run

plt.figure(figsize=(8,5))
plt.plot(df['N'], df['Treap(ms)'], marker='o', label='Treap')
plt.plot(df['N'], df['multiset(ms)'], marker='s', label='std::multiset')

# plt.xscale('log')
# plt.yscale('log')
plt.xlabel('Number of elements N')
plt.ylabel('Average time (ms)')
plt.title('Treap vs std::multiset performance')
plt.legend()
plt.grid(True, which='both', ls='--', lw=0.5)
plt.tight_layout()
plt.savefig("plot.png", dpi=300)
