class tokenizer()
  private:
    var command="Bob|Ross|The|king|of|Gondor|"
    var StrIn=[];
    var tokens=[];
    var b=0;
    bool x=false;
    var f=0;
public:
tokenize(){
 for(i=0 i<=StrIn.length,i++){
   
   If(StrIn[i]=="|"){
     f++;
     i++;
   }
   Token[f]=Token[f]+StrIn[i];
   Serial.Println(Token[F]);
 }
  f=0;
collect(){
  if(Serial.Available){
    while(x){
      StrIn[b]=Serial.read;
      b++;
      if(Serial.available){
        x=true;
      }
    }
    tokenize();
  }
  
 
