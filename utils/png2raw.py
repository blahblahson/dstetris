#!/usr/bin/env python
 
import os
import glob
 
OUTFOLDER = 'data/'
 
def convert(filename):
    outfile = filename.split('/')[-1].split('.')[0] + '.raw'
    print '%s -> %s%s' % (filename, OUTFOLDER, outfile)
 
    os.system('./png2raw %s %s%s' % (filename, OUTFOLDER, outfile))
 
def dostuff(g):
    for i in g:
        if i.split('/')[-1][0] == '-':
            continue
        if os.path.isdir(i):
            dostuff(glob.glob(i+'/*'))
        else:
            convert(i)
 
def main():
    g = glob.glob('data/*')
    dostuff(g)
 
if __name__ == '__main__':
    main()
