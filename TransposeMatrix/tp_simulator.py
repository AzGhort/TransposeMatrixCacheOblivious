import plotly.plotly as py
import plotly.graph_objs as go
import math
import numpy as np

def read_data(filename):
    trivial = []
    CO = []
    N = []
    with open(filename, 'r', encoding = 'utf-8') as file:
        while True:
            lines = []
            # 10 lines = 4 lines trivial - empty line - 4 lines CO - empty line
            for i in range(10):
                try:
                    lines.append(next(file)) 
                except StopIteration: 
                    return [N, trivial, CO]
            # number of elements
            elements = int(lines[0].split(" ")[1])
            numswapped = int(lines[1].split(" ")[1])/2
            N.append(math.sqrt(elements))
            missesTrivial = int(lines[2].split(" ")[1])
            missesCO = int(lines[7].split(" ")[1])
            trivial.append(missesTrivial / numswapped)
            CO.append(missesCO / numswapped)
    return [N, trivial, CO]

[N1, trivial1, CO1] = read_data("c64-64.txt")
[N2, trivial2, CO2] = read_data("c64-1024.txt")
[N3, trivial3, CO3] = read_data("c64-4096.txt")
[N4, trivial4, CO4] = read_data("c512-512.txt")
[N5, trivial5, CO5] = read_data("c4096-64.txt")

trace1 = go.Scatter(x = N1, y = trivial1, name = "Cache 64x64B", line=dict(width = 2))
trace2 = go.Scatter(x = N2, y = trivial2, name = "Cache 1024x64B", line=dict(width = 2))
trace3 = go.Scatter(x = N3, y = trivial3, name = "Cache 4096x64B", line=dict(width = 2))
trace4 = go.Scatter(x = N4, y = trivial4, name = "Cache 512x512B", line=dict(width = 2))
trace5 = go.Scatter(x = N5, y = trivial5, name = "Cache 64x4096B", line=dict(width = 2))

data = [trace1, trace2, trace3, trace4, trace5]
layout = dict(title = 'Trivial matrix transposition on ideal full associative caches', autosize=True, titlefont = dict(size=32),
              xaxis = dict(title = 'Size of matrix\'s side', tickfont = dict(size=16), zerolinewidth=1,
                           showgrid=True, type='log', ticklen = 6, showline=True, zeroline=True,
                           linewidth=1.5, ticks="inside", gridwidth=1, autorange=True, titlefont = dict(size=24)),
              yaxis = dict(title = 'Average cache miss for 2 elements transpose', tickfont = dict(size=16), zerolinewidth=1,
                           showgrid=True, type='linear', ticklen = 6, showline=True, zeroline=True,
                           linewidth=1.5, ticks="inside", gridwidth=1, autorange=True,titlefont = dict(size=24)))
fig = dict(data=data, layout=layout)
py.iplot(fig, filename='Matrix trivial transposition - ideal cache')

trace1 = go.Scatter(x = N1, y = CO1, name = "Cache 64x64B", line=dict(width = 2))
trace2 = go.Scatter(x = N2, y = CO2, name = "Cache 1024x64B", line=dict(width = 2))
trace3 = go.Scatter(x = N3, y = CO3, name = "Cache 4096x64B", line=dict(width = 2))
trace4 = go.Scatter(x = N4, y = CO4, name = "Cache 512x512B", line=dict(width = 2))
trace5 = go.Scatter(x = N5, y = CO5, name = "Cache 64x4096B", line=dict(width = 2))

data = [trace1, trace2, trace3, trace4, trace5]
layout = dict(title = 'Cache oblivious matrix transposition on ideal full associative caches', autosize=True, titlefont = dict(size=32),
              xaxis = dict(title = 'Size of matrix\'s side', tickfont = dict(size=16), zerolinewidth=1,
                           showgrid=True, type='log', ticklen = 6, showline=True, zeroline=True,
                           linewidth=1.5, ticks="inside", gridwidth=1, autorange=True, titlefont = dict(size=24)),
              yaxis = dict(title = 'Average cache miss for 2 elements transpose', tickfont = dict(size=16), zerolinewidth=1,
                           showgrid=True, type='linear', ticklen = 6, showline=True, zeroline=True,
                           linewidth=1.5, ticks="inside", gridwidth=1, autorange=True,titlefont = dict(size=24)))
fig = dict(data=data, layout=layout)
py.iplot(fig, filename='Matrix Cache oblivious transposition - ideal cache')
