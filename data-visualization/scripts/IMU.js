
const backgroundColor = '#95D1A0';

/*////////////////////////////////////////*/

var renderCalls = [];
function render () {
  requestAnimationFrame( render );
  renderCalls.forEach((callback)=>{ callback(); });
}
render();

/*////////////////////////////////////////*/

var scene = new THREE.Scene();

var camera = new THREE.PerspectiveCamera( 80, 1, 0.1, 800 );
camera.position.set(0, 20, 20);

var renderer = new THREE.WebGLRenderer( { antialias: true } );
renderer.setPixelRatio( window.devicePixelRatio );
renderer.setSize(500, 500 );
renderer.setClearColor( backgroundColor );

// renderer.toneMapping = THREE.LinearToneMapping;
// renderer.toneMappingExposure = Math.pow( 0.94, 5.0 );
// renderer.shadowMap.enabled = true;
// renderer.shadowMap.type = THREE.PCFShadowMap;

window.addEventListener( 'resize', function () {
  camera.aspect = window.innerWidth / window.innerHeight;
  camera.updateProjectionMatrix();
  renderer.setSize( window.innerWidth, window.innerHeight );
}, false );

//document.getElementById("imu").append(renderer.domElement);
container = document.getElementById( 'imu' );
document.body.appendChild( container );
container.appendChild( renderer.domElement );

function renderScene(){ renderer.render( scene, camera ); }
renderCalls.push(renderScene);

/* ////////////////////////////////////////////////////////////////////////// */

var controls = new THREE.OrbitControls( camera );

controls.rotateSpeed = 0.4;
controls.enableZoom = false;
controls.panSpeed = 0;

controls.enableDamping = true;
controls.dampingFactor = 0.1;

renderCalls.push(function(){
  controls.update()
});

var geometry = new THREE.BoxGeometry( 10, 20, 8 );
var material = new THREE.MeshBasicMaterial({ color: 0x000000, wireframe: true});
var cube = new THREE.Mesh( geometry, material );
console.log(material);
scene.add( cube );

/*renderCalls.push(function(){
  scene.rotation.x += 0.01;
  scene.rotation.y += 0.01;
  scene.rotation.z += 0.01;
});
*/
