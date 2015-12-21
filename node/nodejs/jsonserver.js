var http=require('http');
var url=require('url');
var strftime=require('strftime');
var static_id=1;
var res=[];
var server=http.createServer(function(req,res){
    res.writeHead(200, { 'Content-Type': 'application/json' })
    if(req.method!='GET')
        res.end('invalid request')
    var path=url.parse(req.url,true);
    var data={}
    if(path.pathname=='/api/parsetime'){
        var date=new Date(path.query['iso']);
        data['hour']=date.getHours();
        data['minute']=date.getMinutes();
        data['second']=date.getSeconds();
        res.end(JSON.stringify(data));
    }else if(path.pathname=='/api/unixtime'){
        var date=new Date(path.query['iso'])
        res.end(JSON.stringify({'unixtime':date.getTime()}));
    }else{
        res.end('path not matched');
    }
});
server.listen(process.argv[2]);