var fs=require('fs');
function gotFile(err,data){
	if(err==null)
		console.log(data.toString().split('\n').length-1);
}
fs.readFile(process.argv[2],gotFile)
