# example of delayed target

from anabrew import Recipe
from datetime import timedelta

step1delayed = Recipe(inputs=[],
                        tools=['scripts/delayed.sh'],
                        outputs=['del.txt'],
                        command='scripts/delayed.sh del.txt &')

step2 = Recipe(inputs=['del.txt'],
                tools=[],
                outputs=['delcopy.txt'],
                command='cp del.txt delcopy.txt',
                timeout=timedelta(seconds=40),
                dtpoll=timedelta(seconds=5))

step2.brew()
