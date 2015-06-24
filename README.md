# anabrew
Basic pipelining of data analysis tasks. 

Goal: build a pipeline for LHCb data analyses supporting delayed jobs (grid)

Steps in the analysis are described by `recipes` that take `inputs`, operate on them with `tools` and return `outputs`. `inputs` and `outputs` are files on disk. anabrew aims at reducing boilerplate code in the pipline definition to a minimum, while providing the full flexibility of python to define the workflow as shown in this example:
```
from anabrew import Recipe

step1 = []
for i in range(0,4) :
    step1.append(Recipe(inputs=[],
                        tools=["scripts/ps.C"],
                        outputs=["ps%i.root" % i],
                        command='root -l -b -q scripts/ps.C\\(\\"ps%i.root\\",12345\\)' % i))
    
step2=Recipe(inputs=["ps%i.root"%i for i in range(0,4)], 
             tools=[],
             outputs=["ntuple.root"],
             command='hadd -f ntuple.root ps*.root')

step3=Recipe(inputs=["ntuple.root"],
             tools=[],
             outputs=["plots.root"],
             command='root -l -b -q scripts/plot.C\\(\\"ntuple.root\\",\\"plots.root\\"\\)')

step3.brew()

``` 


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
