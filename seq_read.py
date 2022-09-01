#!/usr/bin/env python3

import subprocess
import pandas as pd
import matplotlib.pyplot as plt

cpi_arr = []
wss_arr = []
for exponent in range(10, 36):
    output = subprocess.check_output(["./seq_read", str(exponent), "8"], encoding="utf-8").strip()
    _ , wss, cpi = output.split(",")
    cpi_arr.append(float(cpi))
    wss_arr.append(int(wss))
df = pd.DataFrame(cpi_arr, index=wss_arr, columns=["cpi"])
plt.style.use("seaborn")
plt.figure()
df.plot(ylim=(0,6), marker="D")
plt.xscale('log', base=2)
