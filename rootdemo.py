# basic test if we can run a process to generate a file
# and if we try to brew it again it should not run
from anabrew import Recipe

step1 = []
for i in range(0,4) :
    step1.append(Recipe(inputs=[],
                        tools=["scripts/ps.C"],
                        outputs=["ps%i.root" % i],
                        command='root -l -b -q scripts/ps.C\\(\\"ps%i.root\\",12345\\)' % i))
    
step2=Recipe(inputs=["ps%i.root"%i for i in range(0,4)], # get this from step1
             tools=[],
             outputs=["ntuple.root"],
             command='hadd -f ntuple.root ps*.root')

step3=Recipe(inputs=["ntuple.root"],
             tools=[],
             outputs=["plots.root"],
             command='root -l -b -q scripts/plot.C\\(\\"ntuple.root\\",\\"plots.root\\"\\)')

step3.brew()

#brewing again should do nothing
#step1.brew()
