import glob, os, sys
os.chdir(sys.argv[1])
for file in glob.glob(sys.argv[2]):
    print(sys.argv[1]+file)