
var scatterChartData = {
      datasets: [{
        label: 'My First dataset',
        borderColor: '#86C0A5',
        backgroundColor: '#86C0A5',
        data: [{
          x: 20,
          y: 34,
        }, {
          x: -20,
          y: 46,
        }],
        bezierCurve: true,
        fill: false,
        showLine: true
      }, {
        label: 'My Second dataset',
        borderColor: '#86C0A5',
        backgroundColor: '#86C0A5',
        data: [{
          x: 46,
          y: 34,
        }, {
          x: 10,
          y: 10,
        }, {
          x: -30,
          y: -25,
        }],
        bezierCurve: true,
        fill: false,
        showLine: true
      }]
    };

let posChart = new Chart('positionChart', {
  type: 'scatter',
  data: scatterChartData,
  options: {
    responsive: true,
    scales: {
      xAxes: [{
        ticks: {
          min: -50
        }
      }],
      yAxes: [{
        ticks: {
          min: -50
        }
      }]
    },
    title: {
      display: true,
      text: 'Chart.js Draw Line On Chart'
    },
    tooltips: {
      mode: 'index',
      intersect: true
    },
    annotation: {
      annotations: [{
        type: 'line',
        mode: 'horizontal',
        scaleID: 'y-axis-0',
        value: 5,
        borderColor: 'rgb(75, 192, 192)',
        borderWidth: 4,
        label: {
          enabled: false,
          content: 'Test label'
        }
      }]
    }
  }
});
console.log(posChart.options);