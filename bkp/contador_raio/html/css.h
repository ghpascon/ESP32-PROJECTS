const char css[] PROGMEM = R"rawliteral(

body {
    font-family: Arial, sans-serif;
    background-color: #000000;
    display: flex;
    margin: 3%;
    width: 94%;
    flex-direction: column;
    align-items: center;
}

h1 {
  color: #ffff00;
  font-size: 50px;
  font-family: Arial, sans-serif;
  padding-top: 0px;
  padding-right: 0px;
  padding-bottom: 0px;
  padding-left: 0px;
}

label {
  font-size: 30px;
  color: #ffffff;
  font-family: 'Times New Roman', Times, serif;
  padding-top: 0px;
  padding-right: 0px;
  padding-bottom: 0px;
  padding-left: 0px;
  cursor: pointer;
}

.bt_style {
  font-size: 20px;
  color: #000000;
  font-family: 'Times New Roman', Times, serif;
  padding-top: 10px;
  padding-right: 20px;
  padding-bottom: 10px;
  padding-left: 20px;
  border: 2px solid #ffffff;
  border-radius: 10px;
  background-color: #ffff00;
  cursor: pointer;
}

button {
  font-size: 20px;
  color: #000000;
  font-family: 'Times New Roman', Times, serif;
  padding-top: 10px;
  padding-right: 20px;
  padding-bottom: 10px;
  padding-left: 20px;
  border: 2px solid #ffffff;
  border-radius: 10px;
  background-color: #ffff00;
  cursor: pointer;
}

.placeholder_style {
  font-size: 20px;
  color: #ffffff;
  background-color: #000000;
  padding: 10px;
  border: 2px solid #cccccc;
  border-radius: 5px;
  margin-bottom: 15px;
  width: 300px;
}

.container1{
    float: top;
    clear: both;                                  
    padding-bottom: 30px;
  }  
  
.container2{
    float: left;
    padding-right: 30px;
    text-align: left;
  }

)rawliteral";