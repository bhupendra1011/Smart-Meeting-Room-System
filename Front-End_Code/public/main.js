
// bind click button

document.getElementById("botao").addEventListener("click", function(){
    document.querySelector("#loading").classList.remove("hidden");
    fetchData();
});

  function reqListener() {
    var data = this.responseText;
    // 1 : room free show green color
    // 0 : room busy show red color
    var room = document.querySelector("#colorBlock");
    var roomTxt = document.querySelector("#roomStatus");
    if (Number(data)) {
        // room available 
        room.classList.remove("red");
        room.classList.add("green");
        roomTxt.textContent = "Available !"
        
    }
    else {
        // room busy
        room.classList.remove("green");
        room.classList.add("red");
        roomTxt.textContent = "Busy !"
    }
    document.querySelector("#loading").classList.add("hidden");
  }
  
  function reqError(err) {
    console.log('Fetch Error :-S', err);
  }

  function fetchData() {
  var oReq = new XMLHttpRequest();
  oReq.onload = reqListener;
  oReq.onerror = reqError;
 // oReq.open('get', 'http://localhost:3000/getData?t='+ new Date().getTime() , true);
 oReq.open('get', window.location.href+'getData?t='+ new Date().getTime() , true);
  oReq.send();
  }

  //initialize data
  fetchData();
 
  

  