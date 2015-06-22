# basic test if we can run a process to generate a file
# and if we try to brew it again it should not run
from anabrew import Recipe

step1=Recipe(inputs=[],
             tools=["scripts/delayed.sh"],
             outputs=["test.text"],
             command="scripts/delayed.sh test.text")

step1.brew()

#brewing again should do nothing
step1.brew()
