var http=require('http');
var server=http.createServer(function(req,res){
    if(req.method!='POST')
        res.end("invalid request");
    req.on('data',function(chunk){
        res.write(chunk.toString().toUpperCase());
    });
    req.on('end',function(end){
        res.end();
    });
});
server.listen(process.argv[2]);