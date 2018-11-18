import plotly.plotly as py
import plotly.graph_objs as go

import numpy as np

def read_data(filename):
    trivial = []
    CO = []
    N = []
    with open(filename, 'r', encoding = 'utf-8') as file:
        temp = file.read().splitlines()
        for line in temp:
            parts = line.split(" ")
            N.append(int(parts[0]))
            trivial.append(float(parts[1]))
            CO.append(float(parts[2]))
    return [N, trivial, CO]


trivial_Y = []
CO_Y = []
X = []
for i in range(54, 139):
    filename1 = "matrix" + str(i) + ".txt"
    [N, trivial, CO] = read_data(filename1)
    trivial_Y.append(trivial)
    X.append(N)
    CO_Y.append(CO)

trace1 = go.Scatter(x = X, y = trivial_Y, name = "Trivial transposition", line=dict(width = 2))
trace2 = go.Scatter(x = X, y = CO_Y, name = "Cache oblivious transposition", line=dict(width = 2))
data = [trace1, trace2]
layout = dict(title = 'Comparison of trivial and cache-oblivous matrix transposition', autosize=True, titlefont = dict(size=32),
              xaxis = dict(title = 'Size of matrix\'s side', tickfont = dict(size=16), zerolinewidth=1,
                           showgrid=True, type='log', ticklen = 6, showline=True, zeroline=True,
                           linewidth=1.5, ticks="inside", gridwidth=1, autorange=True, titlefont = dict(size=24)),
              yaxis = dict(title = 'Time needed for 2 elements transpose', tickfont = dict(size=16), zerolinewidth=1,
                           showgrid=True, type='linear', ticklen = 6, showline=True, zeroline=True,
                           linewidth=1.5, ticks="inside", gridwidth=1, autorange=True,titlefont = dict(size=24)))
fig = dict(data=data, layout=layout)
py.iplot(fig, filename='Matrix transposition - real PC')

