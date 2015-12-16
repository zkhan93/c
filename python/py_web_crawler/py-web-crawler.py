import urllib2
import urlparse

def saveUrlToFile(url,filename):
    pieces = urlparse.urlparse(url)
    if not all([pieces.scheme, pieces.netloc]):
        print 'invalid url'
    elif filename.strip().length()==0:
        print 'filename cannot be empty'
    else:
        url=pieces.geturl()
        uo=urllib2.urlopen(url)
        file=open(filename,"w")
        file.write(uo.read())
        file.close()

def countLinesInFile(filename):
    count=0
    try:
        file=open(filename,'r')
        while file.readline()!='':
            count+=1
    except:
        pass
    finally:
        file.close()
    return count
    
def copyContent(fromFilename,toFilename,noOfLines,offset):
    try:
        fromFile=open(fromFilename,'r')
        toFile=open(toFilename,'w')
        linenos=1
        count=0
        while linenos<=offset:
            fromFile.readline()
            linenos+=1
        lines=[]
        while count<noOfLines:
            lines.append(fromFile.readline())
            count+=1
        toFile.writelines(lines)
    except Exception as ex:
        print 'error occured '+str(ex)

#print 'Enter URL:',
#url=raw_input()
#print 'Enter filename:',
#filename=raw_input()
#saveUrlToFile(url,filename)
#print countLinesInFile('word-list')

copyContent('word-list','word-list-short',10,10)