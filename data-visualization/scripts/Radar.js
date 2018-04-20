

let directions = [
  'Front',
  'Front Right',
  'Right',
  'Back Right',
  'Back',
  'Back Left',
  'Left',
  'Front Left'
];

let radarData = {
  labels: directions,
  datasets: [{
    backgroundColor: '#c11319',
    borderColor: '#a83236',
    data: [20, 20, 0, 0, 0, 0, 0, 20],
    label: 'Front',
    lineTension: 0.2
  }, {
    backgroundColor: '#cfcd42',
    borderColor: '#b6b55e',
    data: [0, 0, 0, 35, 35, 35, 0, 0],
    label: 'Back',
    lineTension: 0.2
  }, {
    backgroundColor: '#cfcd42',
    borderColor: '#b6b55e',
    data: [0, 0, 0, 0, 0, 40, 40, 40],
    label: 'Left',
    lineTension: 0.2
  }, {
    backgroundColor: '#95D1A0',
    borderColor: '#5fb86f',
    data: [0, 60, 60, 60, 0, 0, 0, 0],
    label: 'Right',
    lineTension: 0.2
  }]
};

let options = {
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
  },
  scale: {
    gridLines: {
      circular: true
    },
    ticks: {
      beginAtZero: true,
      max: 100
    }
  },
  legend: {
    display: false
  }
};

let chart = new Chart('radar', {
  type: 'radar',
  data: radarData,
  options: options
});

//console.log(chart.options);
chart.options.scale.gridLines.circular = true;
chart.options.scale.ticks.beginAtZero = true;
chart.options.scale.ticks.max = 100;
chart.options.legend.display = false;

// eslint-disable-next-line no-unused-vars
function togglePropagate(btn) {
  let value = btn.classList.toggle('btn-on');
  chart.options.plugins.filler.propagate = value;
  chart.update();
}
// eslint-disable-next-line no-unused-vars
function toggleSmooth(btn) {
  let value = btn.classList.toggle('btn-on');
  chart.options.elements.line.tension = value ? 0.4 : 0.000001;
  chart.update();
}

function updateRadar(data) {
  let sensorID = data.senderStamp;
  let distanceRead = data.payload.fields[0].value * 100;
  if(distanceRead <= 25) {
    radarData.datasets[0].backgroundColor = '#c0262e';
  }else if(distanceRead <= 50) {
    radarData.datasets[0].backgroundColor = '#faea36';
  }else {
    radarData.datasets[0].backgroundColor = '#95D1A0';
  }
  if(sensorID == 0) {
    
    radarData.datasets[0].data = [distanceRead, distanceRead, 0, 0, 0, 0, 0, distanceRead];
    chart.update();
  }else if(sensorID == 1) {
    
    radarData.datasets[1].data = [0, 0, 0, distanceRead, distanceRead, distanceRead, 0, 0];
    chart.update();
  }else if(sensorID == 2) {
    
    radarData.datasets[2].backgroundColor = 'rgb(30, 201, 200)';
    radarData.datasets[2].data = [0, 0, 0, 0, 0, distanceRead, distanceRead, distanceRead];
    chart.update();
  }else if(sensorID == 3) {
    
    radarData.datasets[3].data = [0, distanceRead, distanceRead, distanceRead, 0, 0, 0, 0];
    chart.update();
  }
}
