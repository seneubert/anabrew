# anabrew
Basic pipelining of data analysis tasks. 

Goal: build a pipeline for LHCb data analyses supporting delayed jobs (grid)

## Quick start

This demo runs a small phasespace simulation, divided into 5 jobs; It 
h-adds the output into an ntuple and finally produces a plot from the ntuple. 

Make sure you have [ROOT]{root.cern.ch} installed.

Clone this git repo to somewhere:
````bash
mkdir testlmw
cd testlmw
git clone https://github.com/seneubert/anabrew.git .
````

Run the example script (or one that you have already)
````bash
python root_example.py 
````
