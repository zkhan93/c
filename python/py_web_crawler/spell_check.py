from bitmap import BitMap
import hashlib
wordListFilename='word-list'
bm=BitMap(100000)
wordListFile=''
try:
    wordListFile=open(wordListFilename,'r')
except:
    print 'wordlist file does not exist'
else:
    print hashlib.md5(wordListFile.readline()).hexdigest()[:16]
