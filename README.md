# anabrew
Basic pipelining of data analysis tasks. 

Goal: build a pipeline for LHCb data analyses supporting delayed jobs (grid)

## Quick start

This demo runs a small phasespace simulation, divided into 5 jobs; It 
h-adds the output into an ntuple and finally produces a plot from the ntuple. 

Make sure you have [ROOT](http://root.cern.ch) installed.

Clone this git repo to somewhere:
````bash
git clone https://github.com/seneubert/anabrew.git .
````

Run the example script
````bash
python root_example.py 
````
