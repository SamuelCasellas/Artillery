<!DOCTYPE html>
<html>
<head>
	<title>M777 Howitzer Prototype Simulation</title>
</head>
<body>

	<h1>M777 Howitzer Prototype Simulation</h1>

	<h2>Contributors</h2>

	<ul>
		<li><strong>Samuel Casellas</strong></li>
		<li><strong>Andrew Swayze</strong></li>
		<li><strong>Isaac Radford</strong></li>
	</ul>

	<h2>Description</h2>

	<p>This program simulates firing the M777 howitzer 15mm artillery piece.</p>

	<h2>Usage</h2>

	<p>To run the simulation, compile and run the program. Once running, the simulation can be interacted with using the following controls:</p>

	<ul>
		<li><strong>up arrow</strong> and <strong>down arrow</strong> to adjust the angle of the howitzer.</li>
		<li><strong>left arrow</strong> and <strong>right arrow</strong> to adjust the power of the shot.</li>
		<li><strong>space</strong> to fire the howitzer.</li>
	</ul>

	<h2>Implementation Details</h2>

	<p>The simulation is implemented using C++ and OpenGL. The <code>uiInteract</code> and <code>uiDraw</code> libraries are used for graphics rendering, and the <code>ground</code>, <code>bullet</code>, <code>howitzer</code>, <code>position</code>, and <code>physics</code> modules are used to simulate the movement of the howitzer, bullets, and ground. The simulation is organized into a <code>Demo</code> class, which contains all of the state and logic needed to simulate the firing of the howitzer. The <code>callBack</code> function is called repeatedly by the graphics engine to draw each frame of the simulation and update its state based on user input.</p>

</body>
</html>
