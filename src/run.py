# This script written by Mgwoo.
# 2018.02.22.
# 
# mgwoo@unist.ac.kr

import os
import sys
import subprocess as sp
from datetime import datetime

dirpos = "../bench"
binaryName = "./iccad19gr"
outpos = "../output"
logpos = "../log"
#latestDir = "../output/latest"

def ExecuteCommand( curCmd ):
    print( curCmd )
    sp.call( curCmd , shell=True)

benchNum = -1
benchName = ""

if len(sys.argv) <=2:
    print("usage:   ./run.py <benchname or number> <# Threads>")
    print("Example: ")
    print("         ./run.py 2 1")
    print("         ./run.py example_2.input 1")
    sys.exit(1)

if sys.argv[1].isdigit():
    benchNum = int(sys.argv[1])
    benchName = sorted(os.listdir(dirpos))[benchNum]
elif sys.argv[1] == "all":
    benchName = sorted(os.listdir(dirpos))
else:
    benchName = sys.argv[1]

benchDir = benchName
benchPath = "%s/%s" % (dirpos, benchDir)
outputPath = "%s/%s" % (outpos, benchDir)
dumpPath = "%s/%s" % (logpos, benchDir)

numThreads = int(sys.argv[2])
curTime = datetime.now().strftime('%m_%d_%H_%M')

#print curTime

if type(benchName) is list:
    for curBench in benchName:
        lefPath = "%s/%s.input.lef" % (benchPath, curBench)
        defPath = "%s/%s.input.def" % (benchPath, curBench)
        outPath = "%s/%s.out" % (outputPath, curBench)
        logPath = "%s/%s.log" % (dumpPath, curTime)
        
        exeStr = "%s -lef %s -def %s -output %s -threads %s | tee %s" % (binaryName, lefPath, defPath, outPath, numThreads, logPath)
        ExecuteCommand(exeStr)
else:
    lefPath = "%s/%s.input.lef" % (benchPath, benchName)
    defPath = "%s/%s.input.def" % (benchPath, benchName)
    gudPath = "%s/%s.input.guide" % (benchPath, benchName)
    outPath = "%s/%s.out" % (outputPath, benchName)
    logPath = "%s/%s.log" % (dumpPath, curTime)
    exeStr = "%s -lef %s -def %s -output %s -threads %s | tee %s" % (binaryName, lefPath, defPath, outPath, numThreads, logPath)
    ExecuteCommand(exeStr)
