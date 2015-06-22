
import sys, subprocess, os, time

# maybe Recipe should just know about tools and command
# with an abstract way of passing inputs to the command
# and defining the output file names 

# then you would instantiate a brewing step by giving recipe and inputs?

# separate output and actual output file location
# recipes have to return the actual location 

class Recipe :
    '''A recipe is a rule to create output files on disks
    by running a command (which uses tools)
    on the input files'''
        
    recipes = []

    def __init__(self, **kwargs):
        self.__dict__ = kwargs
        self.inputs = []
        if "inputs" in kwargs.keys() : 
            try:
                self.inputs.extend(kwargs["inputs"])
            except TypeError:
                self.inputs.append(kwargs["inputs"])
                
        # split command into app and args        
        self.com=self.command.split(' ',2)
        if len(self.com)==1 : self.com.append("")        
        # add to the list of recipes
        Recipe.recipes.append(self)

    def brew(self) :
        '''main function to execute the recipe
        checks if the output has already been computed
        checks if this recipe is currently brewing
        checks if the input files are available and older than the output
        if not it looks for a recipe to make the input
        '''
    
        # DO WE HAVE TO BREW?
        # do the inputs exist?
        print "Checking inputs ..."
        it={}
        for i in self.inputs :
            # no - is there a recipe to brew them?
            if not os.path.isfile(i) :
                for r in recipes :
                    if i in r.outputs :
                        #     yes - brew that recipe
                        r.brew()
                        break; # stop looping over recipes
            # check if the input is now there
            if not os.path.isfile(i) :
                print "Failed to brew target " + i
                exit;
            #      no - abort with error
            # yes - what is their timestamp?
            it[i] = os.path.getmtime(i)

        # do the tools exist?
        # no - abort with error message
        # yes - what is their timestamp?

        # do the outputs exist?
        # yes - what is their timestamp?
        ot = {}
        for o in self.outputs :
            try : 
                t=os.path.getmtime(o) 
                #       reset status in database to done 
                
            except os.error:
                t=0
                
            ot[o]=t;

        #print ot
        # no - are they already brewing?
        #      yes - abort with warning
        #      no - let's se if we are ready to brew

        # compare timestamps
        # are outputs younger than inputs and tools?
        try :
            itmax=max(it.values())
        except ValueError : 
            itmax=0

        otmin=min(ot.values())
        
        # yes - nothing to do
        # no - try to brew
        if itmax >= otmin :
            print "Executing " + self.command
            subprocess.call(self.com);

        # if recipe is deferred (remote job)
        # set status to running in database

        # if after finish
        
        
        
        
        
    
