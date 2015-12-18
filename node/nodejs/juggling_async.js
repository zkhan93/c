var http=require('http');
var bl=require('bl');
var asyncTask=2;
var final_data=[];
function done(data,i){
    console.log(i);
    final_data[i-2]=data.toString();
    if(asyncTask>=0){
       if(asyncTask>-1)
            return;
    }
    final_data.forEach(function(dd){
       console.log(dd);
    });
}
function print_data(){
    final_data.forEach(function(d){
        console.log(d);
    });
}
var get_data=function(index){
    http.get(process.argv[index+2],function(response){    
       response.pipe(bl(function(err,data){
           if(err)
                return console.error(err);
            final_data[index]=data.toString();
            if(index==3)
                print_data();
            else
                get_data(index+1);
       })); 
    });
}
get_data(0);


