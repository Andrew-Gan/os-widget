import numpy as np
import subprocess as sp
import re

def appendToFile(path, val):
    with open(path, "a") as fp:
        fp.write(str(val) + '\n')

def findLargestProg(path, listCount):
    # use dpkg-query to print size and name of installed packages in descending order of size
    appList = sp.run(["dpkg-query -Wf '${Installed-Size}\t${Package}\n' | sort -n -r"], stdout=sp.PIPE, shell=True)

    # eliminate entries with phrase 'linux' and obtain fixed number of entries
    r = re.compile(r'^((?!linux).)*$')
    appList = list(filter(r.match, str(appList.stdout).split('\\n')))[:listCount]

    # convert appList to format [int, str] for each package info entry
    appList = np.asarray([[i.split('\\t')[0], i.split('\\t')[1]] for i in appList])
    np.savetxt(path, appList, fmt='%s')
    print('called')