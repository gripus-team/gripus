gripus
======

gripus is a common name for a set of tools capable of doing classical mechanics simualtions in 3D world.

It consists of three main utilities

*  `gripus-core` - a library that loads the simulations into memory, performs them, serializes output into XML and saves them back to output files

* `gripus-simulator` - a program for executing functions of `gripus-core` library

* `gripus-viewer` - a program for 3D visualisation, able to perform just-in-time simulation (simulation while rendering) or to view already simulated outputs

**Supported features**

* tracking of object movement in space, accessing their properties (position, orientation, speed, angular speed, acceleration, angular acceleration)

* applying external forces on objects, modifying their state

* simulating effects of arbitrary configurable gravitational fields of 4+ different types

* simulating mass-induced gravitation of objects (or gravitation of object on another object)

* performing perfectly-elastic collisions [not yet]

## Compiling
After you've cloned gripus into a folder, enter it and execute

    mkdir build
    cd build
    cmake ..
    make
Compilation can take some time because of all the dependencies gripus uses. 
You may miss `cmake` or some additional libraries on your computer. If so, install them and if you've found it out during compilation,

    make clean
    cmake ..
    make

## Writing a simulation XML file
Writing a simulation XML file isn't anything complicated. There are no mandatory elements or attributes, simply leaving some element or attribute out is interpreted by the program as a command to use default value. 

First of all there must be a root XML element called `<simulation>`

    <simulation>
        <!-- here goes the simulation -->
    <simulation>
There can be only a single simulation per XML file.

The rest of the simulation format is explained in this example XML file

	<simulation>
		<!-- Settings are common for both simulator and viewer -->
		<settings>
			<time start="0.0" end="2592000" step="900" />
			<!-- 
				Is the time of simulation. Simulation will be performed from the `start` to the `end` in `step`-second steps. Everything is measured in seconds.
			-->
	
			<precision delta="1.0" />
			<!-- 
				Floating point numbers as well as physical simulations are known for their imprecisions. The `delta` value represents the desired precision for results in simulation outputs. The more precise simulation you request, the more time it takes to perform it. 
			-->
	
			<projection type="perspective" size="-0.08284 0.08284 -0.08284 0.08284 0.1 1e3" scale="1e-6 1e-6 1e-6" />
			<!-- 
				This is 3D visualisation-only option configuring visualisation projection.
				There are two `type`s of projections, parallel and perspective (more on this on wikipedia).
	
				`size` specifies the projection frustrum parameters in the following order: left right bottom top near far. 
				As an example, to get ALPHA field-of-view perspective projection wit aspect ratio R showing everything at least N meters from observer and clipping everything farther than F meters, you can use following formulas:
				left = -tan(ALPHA)*N
				right = tan(ALPHA)*N
				bottom = -R*left
				top = R*right
				near = N
				far = F
	
				`scale` specifies the scale of world. Be aware of using learge floating-point numbers for coordinates can cause problems due to floating-point imprecision. Use real-to-scene scaling whenever necessary
			-->
	
			<view eye="0.0 0.0 0.0" center="0.0 0.0 -1.0" up="0.0 1.0 0.0" step="1e1" />
			<!--
				This is 3D visualisation-only option configuring initial orientation of visualisation camera.
	
				`eye` vector (x, y, z) configures the camera postion
				`center` vector specifies the point at which the camera points. Therefore, (`center` - `eye`) vector is pointing in camera`s direction
				`up` vector tells the camera which way it is "up"
				`step` specifies the speed of camera movement in scene (scaled world)
			 -->
	
			<speed boost="86400" />
			<!-- 
				A parameter used for visualisation specifying how many times faster should the visualisation go than the simulation works
			 -->
		</settings>
		<environment>
			<gravitation type="uniform" acceleration="10.0" />
			<!-- Sets up an acceleration with constant direction of -`acceleration` and constant magnitude of `acceleration` -->
	
			<gravitation type="planar" position="0.0 0.0 0.0" acceleration="1.0 0.0 0.0" />
			<!-- Sets up an acceleration with constant magnitude and the direction of `acceleration`, always pointing on the plane at position `position`. In the shown example, an object at position (1.0 0.0 0.0) would be accelerated by (-1.0 0.0 0.0), while an object at position (-1.0 0.0 0.0) would be accelerated by (1.0 0.0 0.0). Object exactly at position (0.0 0.0 0.0) would not be accelerated. -->
	
			<gravitation type="point" position="100.0 0.0 0.0" acceleration="10.0" />
			<!-- Sets up an acceleration in direction of `position`-(object`s position) and constant magnitude of `acceleration` -->
	
			<gravitation type="mass" position="0. 0.0 0.0" mass="1000" />
			<!-- Sets up an acceleration in direction of `position`-(object`s position) and magnitude of G*`mass`*(object`s mass)/(magnitude of `position`-(object`s position)) squared -->
		</environment>
		<system>
				<object id="earth"	mesh="earth"	mass="5.97219e24"	position="0.0 0.0 0.0"			velocity="0.0 0.0 0.0" 			rotation="0.0 -0.00007272205 0.0" />
				<!--
					Places object `id` with mesh `mesh` and assigns specified properties.
				-->
	
				<object id="moon"	mesh="moon"		mass="7.35e22"		position="0.0 0.0 -3.844e8"		velocity="1.01827015e3 0.0 0.0"		rotation="0.0 -0.00000264898 0.0"/>
		</system>
		<forces>
			<force object="moon" force="0.0 100.0 0.0" startTime="1" endTime="1000.0" />
			<!-- Applies a force `force` (vector) on object with id `object` in during simulation between time <`startTime`, `endTime`) -->
		</forces>
		<scene>
			<!-- Scenes don't use lights, and use only colors or diffuse textures. -->
			<mesh name="earth" path="objects/earth/earth.obj" transform="	6.378e6		 	0.0 			0.0 			0.0
																			0.0 			6.378e6		 	0.0 			0.0
																			0.0 			0.0 			6.378e6			0.0
																			0.0 			0.0 			0.0 			1.0"/>
			<!--
				Loads mesh width name `name` from path `path` into visualisation and transforms it by matrix `transform`.
				A mesh must have its textures specified by a path to its own.
			-->
	
			<mesh name="moon" path="objects/moon/moon.obj" transform="	5.88949e4		0.0 			0.0 			0.0
																		0.0 			5.88949e4		0.0 			0.0
																		0.0 			0.0 			5.88949e4		0.0
																		0.0 			0.0 			0.0 			1.0" />
		</scene>
	</simulation>

## Simulating into a file
Simulation using `gripus-simulator` is extremely simple, just execute

    gripus-simulator <path_to_simulation> <output_path>

## Viewing the simulation output
...is also very simple. Just run 

    gripus-viewer <path_to_simulation> <path_to_output>
for visualisation of a pre-simulated output, and

    gripus-viewer --jit <path_to_simulation>
for visualising and simulating at once. 

You can explore the simulation in more details using `W`, `A`, `S`, `D` keys for moving origin, mouse for rotating around origin, mouse button to enter and leave the viewer, mouse scroll for zooming in and out and `P` for pause, `I` for decreasing speed of viewing and `O`for increasing it.