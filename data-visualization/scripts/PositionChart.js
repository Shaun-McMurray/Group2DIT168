
var scatterChartData = {
      datasets: [{
        label: 'My Car',
        borderColor: '#86C0A5',
        backgroundColor: '#86C0A5',
        data: [{
          x: 0,
          y: 0,
        }, {
          x: 2,
          y: 9,
        }, {
          x: 4,
          y: 14,
        }, {
          x: 7,
          y: 15,
        }, {
          x: 10,
          y: 12,
        }],
        bezierCurve: true,
        fill: false,
        showLine: true
      }, {
        label: 'Leading Car',
        borderColor: '#5A7DA4',
        backgroundColor: '#5A7DA4',
        data: [{
          x: 3,
          y: 3,
        }, {
          x: 5,
          y: 12,
        }, {
          x: 7,
          y: 16,
        }, {
          x: 12,
          y: 19,
        }, {
          x: 13,
          y: 15,
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
          min: -20
        }
      }],
      yAxes: [{
        ticks: {
          min: -20
        }
      }]
    },
    title: {
      display: true,
      text: 'Car Positions'
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