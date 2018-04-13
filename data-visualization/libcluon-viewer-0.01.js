/*
Copyright 2018 Ola Benderius

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

const g_renderFreq = 4.0;
const g_maxDataAge = 10.0;
const g_maxFieldChartValues = 10;

var g_charts = new Map();
var g_chartConfigs = new Map();
var g_data = new Map();
var g_pause = false;

let lc;
let ws;
let date = new Date();
let lastControllerMessage;

$(document).ready(function(){
  
  $('body').on('click', 'tr.dataHeader', function() {
    const idFieldsRow = $(this).attr('id') + '_fields';
    $('#' + idFieldsRow).toggleClass('hidden');
  });
  
  $('body').on('click', 'button#pause', function() {
    g_pause = !g_pause;
    if (g_pause) {
      $('button#pause').html('Continue');
    } else {
      $('button#pause').html('Pause');
    }
  });
  
  setupViewer();
});


function speedClick(){

  let testSpeed = Math.floor(Math.random() * Math.floor(100));
  document.getElementById("pedalPosition").innerHTML = testSpeed;
  document.getElementById("currentSpeed").innerHTML = testSpeed;
  $("#speedbox-score").css("transform","rotate("+testSpeed+"deg)");
  $("#notification").fadeIn("slow").append('New follower request! Click to accept or dismiss thata way -->');
  $(".dismiss").click(function(){
       $("#notification").fadeOut("slow");
});
  sendMessage(lc, ws, testSpeed);
}


function setupViewer() {
  lc = libcluon();

  if ("WebSocket" in window) {
    ws = new WebSocket("ws://" + window.location.host + "/");
    ws.binaryType = 'arraybuffer';

    ws.onopen = function() {
      onStreamOpen(lc);
      $("#speedbox-score").css("transform","rotate("+50+"deg)");
    }

    ws.onmessage = function(evt) {
      onMessageReceived(lc, evt.data);
    };

    ws.onclose = function() {
      onStreamClosed();
    };

  } else {
    console.log("Error: websockets not supported by your browser.");
  }
}



function onStreamOpen(lc) {
  function getResourceFrom(url) {
    var xmlHttp = new XMLHttpRequest();
    xmlHttp.open("GET", url, false);
    xmlHttp.send(null);
    return xmlHttp.responseText;
  }

  var odvd = getResourceFrom("messages.odvd");

  console.log("Connected to stream.");
  console.log("Loaded " + lc.setMessageSpecification(odvd) + " messages from specification.");
  
  setInterval(onInterval, Math.round(1000 / g_renderFreq));
}

function onStreamClosed() {
  console.log("Disconnected from stream.");
}

function onMessageReceived(lc, msg) {

  console.log('Recieved a message');

  if (g_pause) {
    return;
  }

  var data_str = lc.decodeEnvelopeToJSON(msg);

  if (data_str.length == 2) {
    return;
  }

  d = JSON.parse(data_str);


  // Translate to nice JSON ..
  var payloadFields = new Array();

  const payloadName = Object.keys(d)[5];
  
  for (const fieldName in d[payloadName]) {
    const fieldValue = d[payloadName][fieldName];
    const field = {
      name : fieldName,
      value : fieldValue,
      type : (typeof fieldValue)
    };
    payloadFields.push(field);
  }

  const data = {
    dataType : d.dataType,
    payload : {
      name : payloadName,
      fields : payloadFields
    },
    received : d.received,
    sampleTimeStamp : d.sampleTimeStamp,
    senderStamp : d.senderStamp,
    sent : d.sent
  };
  // .. done.
  console.log(data);
  console.log(data.payload.fields[0].value);
  console.log(data.payload.fields[0].name);
  const sourceKey = data.dataType + '_' + data.senderStamp;
  const dataSourceIsKnown = g_data.has(sourceKey);
  if(data.payload.fields[0].name == 'pedal') {
    document.getElementById("pedalPosition").innerHTML = data.payload.fields[0].value * 100;
    document.getElementById("currentSpeed").innerHTML = data.payload.fields[0].value;

    $("#speedbox-score").css("transform","rotate("+data.payload.fields[0].value  * 100 +"deg)");
  }else if(data.payload.fields[0].name == 'distance') {
    updateRadar(data);
  }else if(data.payload.fields[0].name == 'voltage') {
    data.senderStamp = data.senderStamp + 2;
    updateRadar(data);
  }
  if (!dataSourceIsKnown) {
    addTableData(sourceKey, data);
    addFieldCharts(sourceKey, data);
    
    g_data.set(sourceKey, new Array());
  }
  
  storeData(sourceKey, data);
}

function toTime(t) {
  const milliseconds = t.seconds * 1000 + t.microseconds / 1000;
  return moment(milliseconds).format('YYYY-MM-DD hh:mm:ss');
}

function cutLongField(type, value) {
  if (type == 'string' && value.length > 20) {
    value = value.substr(0, 20) + ' <span class="dots">[...]</span>';
  }
  return value;
}

function addTableData(sourceKey, data) {
  
  if($('tr#' + sourceKey).length == 0) {

    const name = data.payload.name;
    const type = data.dataType;
    const sender = data.senderStamp;
    const timestamp = toTime(data.sampleTimeStamp);

    const headerHtml = '<tr id="' + sourceKey + '" class="dataHeader"><td>' 
      + type + '</td><td>' + sender + '</td><td>' + name + '</td><td id="' 
      + sourceKey + '_frequency">N/A</td><td id="' 
      + sourceKey + '_timestamp">' + timestamp + '</td></tr>';

    const fieldCount = data.payload.fields.length;

    var fieldsHtml = '<tr id="' + sourceKey + '_fields" class="hidden">'
      + '<td colspan="6"><table class="dataFields">';
    for (var i = 0; i < fieldCount; i++) {
    
      const field = data.payload.fields[i];
      const fieldName = field.name;   
      const fieldValue = cutLongField(field.type, field.value);
      
      fieldsHtml += '<tr><td class="field-name">' + fieldName + '</td>' 
        + '<td class="field-plot"><canvas id="' + sourceKey + '_field' 
        + i + '_canvas"></canvas></td><td id="' + sourceKey + '_field' 
        + i + '_value" class="field-value">' + fieldValue + '</td></tr>';
    }
    
    fieldsHtml += '</td></tr></table>';

    $('#dataView > tbody:last-child').append(headerHtml);
    $('#dataView > tbody:last-child').append(fieldsHtml); 
  }
}

function addFieldCharts(sourceKey, data) {

  const fieldCount = data.payload.fields.length;

  for (var i = 0; i < fieldCount; i++) {

    const field = data.payload.fields[i];
    const fieldType = field.type;
    
    if (fieldType == 'number') {

      const fieldKey = sourceKey + '_' + i;

      const fieldName = field.name;
      const fieldValue = field.value;
      
      const config = {
        type: 'line',
        data: {
          labels: [0.0],
          datasets: [{
            label: fieldName,
            data: [fieldValue],
            backgroundColor: 'rgb(255, 99, 132)',
            borderColor: 'rgb(255, 99, 132)',
            fill: false
          }]
        },
        options: {
          responsive: true,
          title: {
            display: false,
          },
          tooltips: {
            mode: 'index',
            intersect: false,
          },
          hover: {
            mode: 'nearest',
            intersect: true
          },
          legend: {
            display: false
          },
          animation: {
            duration: 0
          },
          scales: {
            xAxes: [{
              display: true,
              scaleLabel: {
                display: true,
                labelString: 'time'
              }
            }],
            yAxes: [{
              display: true,
              scaleLabel: {
                display: true,
                labelString: fieldName
              }
            }]
          }
        }
      };
      
      var ctx = document.getElementById(sourceKey + '_field' + i + '_canvas').getContext('2d');
      var chart = new Chart(ctx, config);
      
      g_charts[fieldKey] = chart;
      g_chartConfigs[fieldKey] = config;
    }
  }
}

function storeData(sourceKey, data) {
  
  const newDataTime = data.sent.seconds;
  const dataList = g_data.get(sourceKey);

  var dataPointsToShift = 0;
  for (var i = 0; i < dataList.length; i++) {
    const prevData = dataList[i];
    const dataTime = prevData.sent.seconds;
    const age = newDataTime - dataTime;
    
    if (age > g_maxDataAge) {
      dataPointsToShift++;
    } else {
      break;
    }
  }

  for (var i = 0; i < dataPointsToShift; i++) {
    g_data.get(sourceKey).shift();
  }
  g_data.get(sourceKey).push(data);
}

function onInterval() {
  if (g_pause) {
    return;
  }

  g_data.forEach(function(dataList, sourceKey, map) {
    const newestData = dataList[dataList.length - 1];
    updateTableData(sourceKey, newestData);
    updateFieldCharts(sourceKey, dataList);
  });
}

function updateTableData(sourceKey, data) {

  const dataList = g_data.get(sourceKey);
  if (dataList.length > 10) {
    const firstTimestamp = dataList[0].sent;
    const firstTime = firstTimestamp.seconds * 1000 + firstTimestamp.microseconds / 1000;
    const lastTimestamp = dataList[dataList.length - 1].sent;
    const lastTime = lastTimestamp.seconds * 1000 + lastTimestamp.microseconds / 1000;
    const frequency = Math.round(1000 * dataList.length / (lastTime - firstTime));
    $('td#' + sourceKey + '_frequency').html(frequency);
  } else {
    $('td#' + sourceKey + '_frequency').html('N/A');
  }

  const timestamp = toTime(data.sampleTimeStamp);
  $('td#' + sourceKey + '_timestamp').html(timestamp);

  const fieldCount = data.payload.fields.length;
  for (var i = 0; i < fieldCount; i++) {
    const field = data.payload.fields[i];
    const fieldValue = cutLongField(field.type, field.value);
    $('td#' + sourceKey + '_field' + i + '_value').html(fieldValue);
  }
}

function updateFieldCharts(sourceKey, dataList) {

  const latestData = dataList[dataList.length - 1];
  const latestTimestamp = latestData.sent;
  const latestTime = latestTimestamp.seconds * 1000 + latestTimestamp.microseconds / 1000;
  
  const fieldCount = latestData.payload.fields.length;
  
  // Clear charts.
  for (var i = 0; i < fieldCount; i++) {
    const field = latestData.payload.fields[i];
    const fieldType = field.type;
    if (fieldType == 'number') {
      const fieldKey = sourceKey + '_' + i;
      const config = g_chartConfigs[fieldKey];
      config.data.labels = new Array();
      config.data.datasets[0].data = new Array();
    }
  }
  
  // Add new data.
  const dataCount = dataList.length;
  const decimation = Math.floor(dataCount / (g_maxFieldChartValues - 1));
  for (var j = 0, k = 0; j < dataCount; j++, k++) {
    if (j != dataCount - 1) {
      if (k == decimation) {
        k = 0;
      }
      if (k != 0) {
        continue;
      }
    }
    
    const data = dataList[j];
    const timestamp = data.sent;
    const time = timestamp.seconds * 1000 + timestamp.microseconds / 1000; 
    
    const deltaTime = (time - latestTime) / 1000.0;
    
    for (var i = 0; i < fieldCount; i++) {
      const field = data.payload.fields[i];
      const fieldType = field.type;
    
      if (fieldType == 'number') {
    
        const fieldKey = sourceKey + '_' + i;
        const fieldValue = field.value;
      
        const config = g_chartConfigs[fieldKey];
   
        config.data.labels.push(deltaTime.toFixed(1));
        config.data.datasets[0].data.push(fieldValue);
      }
    }
  }
  
  // Update.
  for (var i = 0; i < fieldCount; i++) {
    const field = latestData.payload.fields[i];
    const fieldType = field.type;
    if (fieldType == 'number') {
      const fieldKey = sourceKey + '_' + i;
      const chart = g_charts[fieldKey];
      chart.update();
    }
  }
}

    
    var Months = [
      'Front',
      'Front Right',
      'Right',
      'Back Right',
      'Back',
      'Back Left',
      'Left',
      'Front Left'
    ];
    var radarData = {
      labels: Months,
      datasets: [{
        backgroundColor: 'rgb(255, 99, 132)',
        borderColor: 'rgb(255, 99, 132)',
        data: [0, 0, 0, 0, 0, 0, 0, 0],
        label: 'Front',
        lineTension: 0.2
      }, {
        backgroundColor: 'rgb(255, 99, 132)',
        borderColor: 'rgb(255, 99, 132)',
        data: [20, 10],
        hidden: true,
        label: 'Back',
        lineTension: 0.2
      }, {
        backgroundColor: 'rgb(255, 99, 132)',
        borderColor: 'rgb(255, 99, 132)',
        data: [20, 10],
        label: 'Left',
        lineTension: 0.2
      }, {
        backgroundColor: 'rgb(255, 99, 132)',
        borderColor: 'rgb(255, 99, 132)',
        data: [20, 10],
        label: 'Right',
        lineTension: 0.2
      }]
    };
    var options = {
      maintainAspectRatio: true,
      spanGaps: false,
      elements: {
        line: {
          tension: 0.000001
        }
      },
      plugins: {
        filler: {
          propagate: false
        },
        'samples-filler-analyser': {
          target: 'chart-analyser'
        }
      }
      
    };
    var chart = new Chart('radar', {
      type: 'radar',
      data: radarData,
      options: options
    });
    console.log(chart.options);
    chart.options.scale.gridLines.circular = true;
    chart.options.scale.ticks.beginAtZero = true;
    chart.options.scale.ticks.max = 100;

    // eslint-disable-next-line no-unused-vars
    function togglePropagate(btn) {
      var value = btn.classList.toggle('btn-on');
      chart.options.plugins.filler.propagate = value;
      chart.update();
    }
    // eslint-disable-next-line no-unused-vars
    function toggleSmooth(btn) {
      var value = btn.classList.toggle('btn-on');
      chart.options.elements.line.tension = value ? 0.4 : 0.000001;
      chart.update();
    }



function sendMessage(lc, ws, jsonMessageToBeSent, messageID) {
  // __libcluon is your handle to libcluon.
   // ws is your websocket
   //var jsonMessageToBeSent = "{\"pedal\":" + val + "}";

   
   var protoEncodedPayload = lc.encodeEnvelopeFromJSONWithoutTimeStamps(jsonMessageToBeSent, messageID, 0);  // 19 is the message identifier from your .odvd file, 0 is the senderStamp (can be 0 in your case)

   strToAB = str =>
     new Uint8Array(str.split('')
       .map(c => c.charCodeAt(0))).buffer;

   ws.send(strToAB(protoEncodedPayload), { binary: true });
}

var s = function (sel) { return document.querySelector(sel); };
var sId = function (sel) { return document.getElementById(sel); };
var removeClass = function (el, clss) {
    el.className = el.className.replace(new RegExp('\\b' + clss + ' ?\\b', 'g'), '');
}
var joysticks = {
    dynamic: {
        zone: s('.zone.dynamic'),
        color: 'blue',
        multitouch: true
    },
    semi: {
        zone: s('.zone.semi'),
        mode: 'semi',
        catchDistance: 150,
        color: 'white'
    },
    static: {
        zone: s('.zone.static'),
        mode: 'static',
        position: {left: '50%', top: '50%'},
        color: 'red'
    }
};
var joystick;



// Get debug elements and map them
var elDebug = sId('debug');
var elDump = elDebug.querySelector('.dump');
var els = {
    position: {
        x: elDebug.querySelector('.position .x .data'),
        y: elDebug.querySelector('.position .y .data')
    },
    force: elDebug.querySelector('.force .data'),
    pressure: elDebug.querySelector('.pressure .data'),
    distance: elDebug.querySelector('.distance .data'),
    angle: {
        radian: elDebug.querySelector('.angle .radian .data'),
        degree: elDebug.querySelector('.angle .degree .data')
    },
    direction: {
        x: elDebug.querySelector('.direction .x .data'),
        y: elDebug.querySelector('.direction .y .data'),
        angle: elDebug.querySelector('.direction .angle .data')
    }
};

sId('buttons').onclick = createNipple;
createNipple('dynamic');

function bindNipple () {
    joystick.on('start end', function (evt, data) {
        let jsonPedal = "{\"pedal\":" + 0 + "}";
        sendMessage(lc, ws, jsonPedal, 1002);

        let jsonSteering = "{\"steering\":" + 0 + "}";
        sendMessage(lc, ws, jsonSteering, 1003);
        dump(evt.type);
        debug(data);
    }).on('move', function (evt, data) {
        calculateControl(data);
        debug(data);
    }).on('dir:up plain:up dir:left plain:left dir:down ' +
        'plain:down dir:right plain:right',
        function (evt, data) {
            dump(evt.type);
        }
    ).on('pressure', function (evt, data) {
        debug({pressure: data});
    });
}

function createNipple (evt) {
    var type = typeof evt === 'string' ?
        evt : evt.target.getAttribute('data-type');
    if (joystick) {
        joystick.destroy();
    }
    removeClass(s('.zone.active'), 'active');
    removeClass(s('.button.active'), 'active');
    removeClass(s('.highlight.active'), 'active');
    s('.highlight.' + type).className += ' active';
    s('.button.' + type).className += ' active';
    s('.zone.' + type).className += ' active';
    joystick = nipplejs.create(joysticks[type]);
    bindNipple();
}

// Print data into elements
function debug (obj) {
    function parseObj(sub, el) {
        for (var i in sub) {
            if (typeof sub[i] === 'object' && el) {
                parseObj(sub[i], el[i]);
            } else if (el && el[i]) {
                el[i].innerHTML = sub[i];
            }
        }
    }
    setTimeout(function () {
        parseObj(obj, els);
    }, 0);
}

var nbEvents = 0;

// Dump data
function dump (evt) {
    setTimeout(function () {
        if (elDump.children.length > 4) {
            elDump.removeChild(elDump.firstChild);
        }
        var newEvent = document.createElement('div');
        newEvent.innerHTML = '#' + nbEvents + ' : <span class="data">' +
            evt + '</span>';
        elDump.appendChild(newEvent);
        nbEvents += 1;
    }, 0);
}

function calculateControl(data) {
  let pedalPercent;
  let steeringAngle;

  let newDate = new Date();
  let thisControllerMessage = newDate.getTime();

  if(thisControllerMessage - lastControllerMessage < 500){
    return;
  }
  pedalPercent = data.distance / 100;
  steeringAngle = data.angle.degree - 90;

  if(data.angle.degree > 180) {
    pedalPercent = pedalPercent * -1;
    steeringAngle = steeringAngle - 180;
  }
  steeringAngle = steeringAngle / 2;
  console.log(steeringAngle);

  let jsonPedal = "{\"pedal\":" + pedalPercent + "}";
  sendMessage(lc, ws, jsonPedal, 1002);

  let jsonSteering = "{\"steering\":" + steeringAngle + "}";
  sendMessage(lc, ws, jsonSteering, 1003);

  date = new Date;
  lastControllerMessage = date.getTime();
}

//function sendLeaderStatus() {
  //let jsonLeaderStatus = "{\"timestamp\":" + Math.floor(Date.now() / 1000) + ",\"speed\":" + pedalPercent + ",\"steeringAngle\":" + steeringAngle + ",\"distanceTraveled\":" + Math.floor(Date.now() / 1000) + "}";
//}

function updateRadar(data) {
  let sensorID = data.senderStamp;
  if(sensorID == 0) {
    let distanceRead = data.payload.fields[0].value * 100;
    //backgroundColor: 'rgb(255, 99, 132)',
      //  borderColor:
    radarData.datasets[0].backgroundColor = 'rgb(30, 201, 33)';
    radarData.datasets[0].data = [distanceRead, distanceRead, 0, 0, 0, 0, 0, distanceRead];
    chart.update();
  }else if(sensorID == 1) {
    let distanceRead = data.payload.fields[0].value * 100;
    console.log(radarData);
    //backgroundColor: 'rgb(255, 99, 132)',
      //  borderColor:
    radarData.datasets[1].backgroundColor = 'rgb(30, 201, 33)';
    radarData.datasets[1].data = [0, 0, 0, distanceRead, distanceRead, distanceRead, 0, 0];
    chart.update();
  }else if(sensorID == 2) {
    let distanceRead = data.payload.fields[0].value * 50;
    console.log(radarData);
    //backgroundColor: 'rgb(255, 99, 132)',
      //  borderColor:
    radarData.datasets[2].backgroundColor = 'rgb(30, 201, 200)';
    radarData.datasets[2].data = [0, 0, 0, 0, 0, distanceRead, distanceRead, distanceRead];
    chart.update();
  }else if(sensorID == 3) {
    let distanceRead = data.payload.fields[0].value * 50;
    console.log(radarData);
    //backgroundColor: 'rgb(255, 99, 132)',
      //  borderColor:
    radarData.datasets[3].backgroundColor = 'rgb(200, 201, 33)';
    radarData.datasets[3].data = [0, distanceRead, distanceRead, distanceRead, 0, 0, 0, 0];
    chart.update();
  }
}
